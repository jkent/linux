/*
 * Samsung SoC USB 1.1/2.0 PHY driver - S5PV210 support
 *
 * Copyright (C) 2013 Jeff Kent
 *
 * Based on source from:
 *   Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *   Authors: Kamil Debski <k.debski@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/usb/phy.h>
#include <plat/cpu.h>
#include <plat/usb-phy.h>
#include <mach/map.h>

/* Exynos USB PHY registers */

/* System power */
#define S5PV210_SYSPWR_PHY		0xE80C
#define S5PV210_SYSPWR_PHY0		BIT(0)
#define S5PV210_SYSPWR_PHY1		BIT(1)

/* PHY power control */
#define S5PV210_UPHYPWR			0x0

#define S5PV210_UPHYPWR_PHY0_SUSPEND	BIT(0)
#define S5PV210_UPHYPWR_PHY0_PWR	BIT(3)
#define S5PV210_UPHYPWR_PHY0_OTG_PWR	BIT(4)
#define S5PV210_UPHYPWR_PHY0	( \
	S5PV210_UPHYPWR_PHY0_SUSPEND | \
	S5PV210_UPHYPWR_PHY0_PWR | \
	S5PV210_UPHYPWR_PHY0_OTG_PWR)

#define S5PV210_UPHYPWR_PHY1_SUSPEND	BIT(6)
#define S5PV210_UPHYPWR_PHY1_PWR	BIT(7)
#define S5PV210_UPHYPWR_PHY1 ( \
	S5PV210_UPHYPWR_PHY1_SUSPEND | \
	S5PV210_UPHYPWR_PHY1_PWR)

/* PHY clock control */
#define S5PV210_UPHYCLK			0x4

#define S5PV210_UPHYCLK_PHYFSEL_MASK	(0x3 << 0)
#define S5PV210_UPHYCLK_PHYFSEL_48MHZ	(0x0 << 0)
#define S5PV210_UPHYCLK_PHYFSEL_24MHZ	(0x3 << 0)
#define S5PV210_UPHYCLK_PHYFSEL_12MHZ	(0x2 << 0)

#define S5PV210_UPHYCLK_PHY0_ID_PULLUP	BIT(2)
#define S5PV210_UPHYCLK_PHY0_COMMON_ON	BIT(4)
#define S5PV210_UPHYCLK_PHY1_COMMON_ON	BIT(7)

/* PHY reset control */
#define S5PV210_UPHYRST			0x8

#define S5PV210_URSTCON_PHY0		BIT(0)
#define S5PV210_URSTCON_OTG_HLINK	BIT(1)
#define S5PV210_URSTCON_OTG_PHYLINK	BIT(2)
#define S5PV210_URSTCON_PHY1_ALL	BIT(3)
#define S5PV210_URSTCON_HOST_LINK_ALL	BIT(4)

/* Isolation, configured in the power management unit */
#define S5PV210_USB_ISOL_DEVICE_OFFSET	0x704
#define S5PV210_USB_ISOL_DEVICE		BIT(0)
#define S5PV210_USB_ISOL_HOST_OFFSET	0x708
#define S5PV210_USB_ISOL_HOST		BIT(1)


static int s5pv210_get_type(struct platform_device *pdev, int *type)
{
	if (strstr(pdev->name, "otg"))
		*type = USB_PHY_TYPE_DEVICE;
	else if (strstr(pdev->name, "hci"))
		*type = USB_PHY_TYPE_HOST;
	else
		return -EINVAL;

	return 0;
}

static int s5pv210_phy_pwr(struct platform_device *pdev, bool on)
{
	int err;
	int type;
	struct clk *otg_clk;
	struct clk *clk_xusbxti;
	u32 pwrctl, pwrctlbits = 0;
	u32 phyclk, phyclkbits = 0;
	u32 phypwr, phypwrbits = 0;
	u32 phyrst, phyrstbits = 0;
	void __iomem *sysbase = (void __iomem *)S3C_VA_SYS;
	void __iomem *phybase = (void __iomem *)S3C_VA_USB_HSPHY;

	err = s5pv210_get_type(pdev, &type);
	if (err) {
		dev_err(&pdev->dev, "Failed to get phy type\n");
		return err;
	}

	/* PHY registers are gated by the OTG clock */
	otg_clk = clk_get(&pdev->dev, "otg");
	if (IS_ERR(otg_clk)) {
		dev_err(&pdev->dev, "Failed to get otg clock\n");
		return PTR_ERR(otg_clk);
	}

	err = clk_enable(otg_clk);
	if (err) {
		dev_err(&pdev->dev, "Could not enable otg clock\n");
		clk_put(otg_clk);
		return err;
	}

	switch (type) {
	case USB_PHY_TYPE_DEVICE:
		pwrctlbits =	S5PV210_SYSPWR_PHY0;
		phyclkbits =	S5PV210_UPHYCLK_PHY0_COMMON_ON;
		phypwrbits =	S5PV210_UPHYPWR_PHY0;
		phyrstbits =	S5PV210_URSTCON_PHY0 |
				S5PV210_URSTCON_OTG_HLINK |
				S5PV210_URSTCON_OTG_PHYLINK;
		break;
	case USB_PHY_TYPE_HOST:
		pwrctlbits =	S5PV210_SYSPWR_PHY1;
		phyclkbits =	0;
		phypwrbits =	S5PV210_UPHYPWR_PHY1;
		phyrstbits =	S5PV210_URSTCON_PHY1_ALL |
				S5PV210_URSTCON_HOST_LINK_ALL;
		break;
	};

	if (on) {
		clk_xusbxti = clk_get(&pdev->dev, "xusbxti");
		if (IS_ERR(clk_xusbxti)) {
			dev_err(&pdev->dev, "Failed to get xusbxti clock\n");
			clk_disable(otg_clk);
			clk_put(otg_clk);
			return err;
		}
		switch (clk_get_rate(clk_xusbxti)) {
		case 12 * MHZ:
			phyclkbits |= S5PV210_UPHYCLK_PHYFSEL_12MHZ;
			break;
		case 24 * MHZ:
			phyclkbits |= S5PV210_UPHYCLK_PHYFSEL_24MHZ;
			break;
		case 48 * MHZ:
			phyclkbits |= S5PV210_UPHYCLK_PHYFSEL_48MHZ;
			break;
		default:
			dev_err(&pdev->dev, "Invalid xusbxti clock\n");
			clk_put(clk_xusbxti);
			clk_disable(otg_clk);
			clk_put(otg_clk);
			return -EINVAL;
		}
		clk_put(clk_xusbxti);

		pwrctl = readl(sysbase + S5PV210_SYSPWR_PHY);
		pwrctl |= pwrctlbits;
		writel(pwrctl, sysbase +  S5PV210_SYSPWR_PHY);

		phyclk = readl(phybase + S5PV210_UPHYCLK);
		phyclk &= ~S5PV210_UPHYCLK_PHYFSEL_MASK;
		phyclk |= phyclkbits;
		writel(phyclk, phybase + S5PV210_UPHYCLK);

		phypwr = readl(phybase + S5PV210_UPHYPWR);
		phypwr &= ~phypwrbits;
		writel(phypwr, phybase + S5PV210_UPHYPWR);

		phyrst = readl(phybase + S5PV210_UPHYRST);
		phyrst |= phyrstbits;
		writel(phyrst, phybase + S5PV210_UPHYRST);

		udelay(10);

		phyrst &= ~phyrstbits;
		writel(phyrst, phybase + S5PV210_UPHYRST);
	}
	else {
		phypwr = readl(phybase + S5PV210_UPHYPWR);
		phypwr |= phypwrbits;
		writel(phypwr, phybase + S5PV210_UPHYPWR);

		pwrctl = readl(sysbase + S5PV210_SYSPWR_PHY);
		pwrctl &= ~pwrctlbits;
		writel(pwrctl, sysbase +  S5PV210_SYSPWR_PHY);
	}

	clk_disable(otg_clk);
	clk_put(otg_clk);

	return 0;
}

int s5p_usb_phy_init(struct platform_device *pdev, int type)
{
	return s5pv210_phy_pwr(pdev, true);
}

int s5p_usb_phy_exit(struct platform_device *pdev, int type)
{
	return s5pv210_phy_pwr(pdev, false);
}
