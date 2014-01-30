/* linux/arch/arm/mach-s5pv210/mini210-lcd.c
 *
 * Copyright (c) 2013 Jeff Kent
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/fb.h>
#include <linux/init.h>
#include <video/samsung_fimd.h>
#include <linux/platform_data/video_s3c.h>
#include <video/platform_lcd.h>
#include <plat/fb.h>

/* W50 */
static struct fb_videomode w50_lcd_timing __initdata = {
	.left_margin	= 40,
	.right_margin	= 40,
	.upper_margin	= 20,
	.lower_margin	= 20,
	.hsync_len	= 48,
	.vsync_len	= 12,
	.xres		= 800,
	.yres		= 480,
	.refresh	= 61,
};

static struct s3c_fb_pd_win w50_fb_win __initdata = {
	.max_bpp	= 32,
	.default_bpp	= 24,
	.xres		= 800,
	.yres		= 480,
	.virtual_x	= 800,
	.virtual_y	= 480,
};

static struct s3c_fb_platdata w50_lcd_platform_data __initdata = {
	.win[0]		= &w50_fb_win,
	.vtiming	= &w50_lcd_timing,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
	.setup_gpio	= s5pv210_fb_gpio_setup_24bpp,
};

/* A70 */
static struct fb_videomode a70_lcd_timing __initdata = {
	.left_margin	= 40,
	.right_margin	= 40,
	.upper_margin	= 29,
	.lower_margin	= 17,
	.hsync_len	= 48,
	.vsync_len	= 24,
	.xres		= 800,
	.yres		= 480,
	.refresh	= 65,
};

static struct s3c_fb_pd_win a70_fb_win __initdata = {
	.max_bpp	= 32,
	.default_bpp	= 24,
	.xres		= 800,
	.yres		= 480,
	.virtual_x	= 800,
	.virtual_y	= 480,
};

static struct s3c_fb_platdata a70_lcd_platform_data __initdata = {
	.win[0]		= &a70_fb_win,
	.vtiming	= &a70_lcd_timing,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
	.setup_gpio	= s5pv210_fb_gpio_setup_24bpp,
};

/* S70 */
static struct fb_videomode s70_lcd_timing __initdata = {
	.left_margin	= 36,
	.right_margin	= 80,
	.upper_margin	= 15,
	.lower_margin	= 22,
	.hsync_len	= 10,
	.vsync_len	= 8,
	.xres		= 800,
	.yres		= 480,
	.refresh	= 65,
};

static struct s3c_fb_pd_win s70_fb_win __initdata = {
	.max_bpp	= 32,
	.default_bpp	= 24,
	.xres		= 800,
	.yres		= 480,
	.virtual_x	= 800,
	.virtual_y	= 480,
};

static struct s3c_fb_platdata s70_lcd_platform_data __initdata = {
	.win[0]		= &s70_fb_win,
	.vtiming	= &s70_lcd_timing,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
	.setup_gpio	= s5pv210_fb_gpio_setup_24bpp,
};

/* H43 */
static struct fb_videomode h43_lcd_timing __initdata = {
	.left_margin	= 40,
	.right_margin	= 5,
	.upper_margin	= 8,
	.lower_margin	= 8,
	.hsync_len	= 2,
	.vsync_len	= 2,
	.xres		= 480,
	.yres		= 272,
	.refresh	= 65,
};

static struct s3c_fb_pd_win h43_fb_win __initdata = {
	.max_bpp	= 32,
	.default_bpp	= 24,
	.xres		= 480,
	.yres		= 272,
	.virtual_x	= 480,
	.virtual_y	= 272,
};

static struct s3c_fb_platdata h43_lcd_platform_data __initdata = {
	.win[0]		= &h43_fb_win,
	.vtiming	= &h43_lcd_timing,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
	.setup_gpio	= s5pv210_fb_gpio_setup_24bpp,
};

/* A97 */
static struct fb_videomode a97_lcd_timing __initdata = {
	.left_margin	= 12,
	.right_margin	= 12,
	.upper_margin	= 8,
	.lower_margin	= 8,
	.hsync_len	= 4,
	.vsync_len	= 4,
	.xres		= 1024,
	.yres		= 768,
	.refresh	= 62,
};

static struct s3c_fb_pd_win a97_fb_win __initdata = {
	.max_bpp	= 32,
	.default_bpp	= 24,
	.xres		= 1024,
	.yres		= 768,
	.virtual_x	= 1024,
	.virtual_y	= 768,
};

static struct s3c_fb_platdata a97_lcd_platform_data __initdata = {
	.win[0]		= &a97_fb_win,
	.vtiming	= &a97_lcd_timing,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
	.setup_gpio	= s5pv210_fb_gpio_setup_24bpp,
};

/* L80 */
static struct fb_videomode l80_lcd_timing __initdata = {
	.left_margin	= 53,
	.right_margin	= 35,
	.upper_margin	= 29,
	.lower_margin	= 3,
	.hsync_len	= 48,
	.vsync_len	= 12,
	.xres		= 640,
	.yres		= 480,
	.refresh	= 65,
};

static struct s3c_fb_pd_win l80_fb_win __initdata = {
	.max_bpp	= 32,
	.default_bpp	= 24,
	.xres		= 640,
	.yres		= 480,
	.virtual_x	= 640,
	.virtual_y	= 480,
};

static struct s3c_fb_platdata l80_lcd_platform_data __initdata = {
	.win[0]		= &l80_fb_win,
	.vtiming	= &l80_lcd_timing,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
	.setup_gpio	= s5pv210_fb_gpio_setup_24bpp,
};

/* G10 */
static struct fb_videomode g10_lcd_timing __initdata = {
	.left_margin	= 99,
	.right_margin	= 60,
	.upper_margin	= 34,
	.lower_margin	= 10,
	.hsync_len	= 1,
	.vsync_len	= 1,
	.xres		= 640,
	.yres		= 480,
	.refresh	= 65,
};

static struct s3c_fb_pd_win g10_fb_win __initdata = {
	.max_bpp	= 32,
	.default_bpp	= 24,
	.xres		= 640,
	.yres		= 480,
	.virtual_x	= 640,
	.virtual_y	= 480,
};

static struct s3c_fb_platdata g10_lcd_platform_data __initdata = {
	.win[0]		= &g10_fb_win,
	.vtiming	= &g10_lcd_timing,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= 0,
	.setup_gpio	= s5pv210_fb_gpio_setup_24bpp,
};

/* A56 */
static struct fb_videomode a56_lcd_timing __initdata = {
	.left_margin	= 134,
	.right_margin	= 16,
	.upper_margin	= 11,
	.lower_margin	= 32,
	.hsync_len	= 10,
	.vsync_len	= 2,
	.xres		= 640,
	.yres		= 480,
	.refresh	= 65,
};

static struct s3c_fb_pd_win a56_fb_win __initdata = {
	.max_bpp	= 32,
	.default_bpp	= 24,
	.xres		= 640,
	.yres		= 480,
	.virtual_x	= 640,
	.virtual_y	= 480,
};

static struct s3c_fb_platdata a56_lcd_platform_data __initdata = {
	.win[0]		= &a56_fb_win,
	.vtiming	= &a56_lcd_timing,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC
				| VIDCON1_INV_VCLK,
	.setup_gpio	= s5pv210_fb_gpio_setup_24bpp,
};

/* W101 */
static struct fb_videomode w101_lcd_timing __initdata = {
	.left_margin	= 40,
	.right_margin	= 40,
	.upper_margin	= 10,
	.lower_margin	= 10,
	.hsync_len	= 120,
	.vsync_len	= 12,
	.xres		= 1024,
	.yres		= 600,
	.refresh	= 60,
};

static struct s3c_fb_pd_win w101_fb_win __initdata = {
	.max_bpp	= 32,
	.default_bpp	= 24,
	.xres		= 1024,
	.yres		= 600,
	.virtual_x	= 1024,
	.virtual_y	= 600,
};

static struct s3c_fb_platdata w101_lcd_platform_data __initdata = {
	.win[0]		= &w101_fb_win,
	.vtiming	= &w101_lcd_timing,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
	.setup_gpio	= s5pv210_fb_gpio_setup_24bpp,
};

/* W35 */
static struct fb_videomode w35_lcd_timing __initdata = {
	.left_margin	= 70,
	.right_margin	= 4,
	.upper_margin	= 12,
	.lower_margin	= 4,
	.hsync_len	= 4,
	.vsync_len	= 4,
	.xres		= 320,
	.yres		= 240,
	.refresh	= 65,
};

static struct s3c_fb_pd_win w35_fb_win __initdata = {
	.max_bpp	= 32,
	.default_bpp	= 24,
	.xres		= 320,
	.yres		= 240,
	.virtual_x	= 320,
	.virtual_y	= 240,
};

static struct s3c_fb_platdata w35_lcd_platform_data __initdata = {
	.win[0]		= &w35_fb_win,
	.vtiming	= &w35_lcd_timing,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_VCLK,
	.setup_gpio	= s5pv210_fb_gpio_setup_24bpp,
};

struct lcd_types {
	char *name;
	struct s3c_fb_platdata *platdata;
};

static struct lcd_types mini210_lcd_types[] = {
	{ .name = "w50", .platdata = &w50_lcd_platform_data },
	{ .name = "a70", .platdata = &a70_lcd_platform_data },
	{ .name = "s70", .platdata = &s70_lcd_platform_data },
	{ .name = "h43", .platdata = &h43_lcd_platform_data },
	{ .name = "a97", .platdata = &a97_lcd_platform_data },
	{ .name = "l80", .platdata = &l80_lcd_platform_data },
	{ .name = "g10", .platdata = &g10_lcd_platform_data },
	{ .name = "a56", .platdata = &a56_lcd_platform_data },
	{ .name = "w101", .platdata = &w101_lcd_platform_data },
	{ .name = "w35", .platdata = &w35_lcd_platform_data },
	{ /* sentinel */ },
};

static struct s3c_fb_platdata *mini210_lcd_pdata;

static int __init mini210_lcd_param(char *name)
{
        struct lcd_types *type = mini210_lcd_types;

        while (type->name) {
                if (strcasecmp(type->name, name) == 0)
                        break;
                type++;
        }
        mini210_lcd_pdata = type->platdata;

        if (!mini210_lcd_pdata)
                pr_err("invalid lcd parameter");

        return 0;
}
early_param("lcd", mini210_lcd_param);

struct s3c_fb_platdata *mini210_get_lcd(void)
{
        if (!mini210_lcd_pdata) {
                /* possibly do autodetection here? */
                return NULL;
        }

        return mini210_lcd_pdata;
};
