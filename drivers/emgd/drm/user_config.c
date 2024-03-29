/*
 *-----------------------------------------------------------------------------
 * Filename: user_config.c
 * $Revision: 1.24.60.2 $
 *-----------------------------------------------------------------------------
 * Copyright (c) 2002-2010, Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *-----------------------------------------------------------------------------
 * Description:
 *  A file that contains the initial display configuration information of the
 *  EMGD kernel module.  A user can edit this file in order to affect the way
 *  that the kernel initially configures the displays.  This file is compiled
 *  into the EMGD kernel module.
 *-----------------------------------------------------------------------------
 */
#include "user_config.h"

#warning ****
#warning **** This driver has NOT been configured for your system.  You are
#warning **** building with a sample user_config.c configuration that may or
#warning **** may not meet your needs.  It is recommended that you run CED to
#warning **** generate an appropriate configuration or see the User Guide
#warning **** for more information about driver configuration.
#warning ****


/*
 * One array of igd_display_info_t structures should exist for each port that
 * needs to provide a DTD list.  Each igd_display_info_t contains the DTD
 * information for a given resolution/refresh-rate.  This is especially needed
 * for analog/VGA ports.
 */

/* Crossville 7' */
static igd_display_info_t dtd_config1_port4_dtdlist[] = {
	{
		800,	/* Width */
		480,	/* Height */
		0,	/* Refresh Rate */
		31746,	/* Dot Clock */
		999,	/* Horizontal Total (horizontal synch end) */
		799,	/* Horizontal Blank Start (h_active-1) */
		999,	/* Horizontal Blank End (start + h_blank) */
		859,	/* Horizontal Sync Start (h_active+h_synch-1) */
		999,	/* Horizontal Sync End (start + h_syncp) */
		524,	/* Vertical Total (Vertical synch end) */
		479,	/* Vertical Blank Start (v_active-1) */
		524,	/* Vertical Blank End (start + v_blank) */
		507,	/* Vertical Sync Start (v_active+v_synch-1) */
		538,	/* Vertical Sync End (start + v_synchp) */
		0,	/* Mode Number */
		0x8020000,	/* Flags */
		0,	/* X Offset */
		0,	/* Y Offset */
		NULL,	/* pd extension pointer */
		0, 0   /* mode extension pointer */
	},
};
static igd_param_attr_t attrs_config1_port4[] = {
	{0x46, 100},
	{0x1a, 24},
	{0x47, 20300},
};

/* CrownBay 13' */
static igd_display_info_t dtd_config2_port4_dtdlist[] = {
	{
		1366,   /* Width */
		768,    /* Height */
		60,     /* Refresh Rate */
		72300,  /* Dot Clock */
		1525,   /* Horizontal Total (horizontal synch end) */
		1365,   /* Horizontal Blank Start (h_active-1) */
		1525,   /* Horizontal Blank End (start + h_blank) */
		1413,   /* Horizontal Sync Start (h_active+h_synch-1) */
		1445,   /* Horizontal Sync End (start + h_syncp) */
		789,    /* Vertical Total (Vertical synch end) */
		767,    /* Vertical Blank Start (v_active-1) */
		789,    /* Vertical Blank End (start + v_blank) */
		770,    /* Vertical Sync Start (v_active+v_synch-1) */
		775,    /* Vertical Sync End (start + v_synchp) */
		0,  /* Mode Number */
		0x20000,    /* Flags */
		0,  /* X Offset */
		0,  /* Y Offset */
		NULL,   /* pd extension pointer */
		0, 0   /* mode extension pointer */
	},
};
/* shares attributes with config1 */

/* NexCom VCT1000 7' */
static igd_display_info_t dtd_config3_port4_dtdlist[] = {
	{
		800,	/* Width */
		480,	/* Height */
		0,	/* Refresh Rate */
		31746,	/* Dot Clock */
		999,	/* Horizontal Total (horizontal synch end) */
		799,	/* Horizontal Blank Start (h_active-1) */
		999,	/* Horizontal Blank End (start + h_blank) */
		859,	/* Horizontal Sync Start (h_active+h_synch-1) */
		999,	/* Horizontal Sync End (start + h_syncp) */
		524,	/* Vertical Total (Vertical synch end) */
		479,	/* Vertical Blank Start (v_active-1) */
		524,	/* Vertical Blank End (start + v_blank) */
		507,	/* Vertical Sync Start (v_active+v_synch-1) */
		538,	/* Vertical Sync End (start + v_synchp) */
		0,	/* Mode Number */
		0x8020000,	/* Flags */
		0,	/* X Offset */
		0,	/* Y Offset */
		NULL,	/* pd extension pointer */
		0, 0   /* mode extension pointer */
	},
};
static igd_param_attr_t attrs_config3_port4[] = {
	{0x46, 100},
	{0x1a, 24},
	{0x47, 20300},
	{0x31, 1},
};

static emgd_drm_splash_screen_t splash_screen_data = {
	0x000000,		/* bg_color */
	0,			/* x */
	0,			/* y */
	0,			/* width */
	0,			/* height */
};

static emgd_drm_splash_video_t splash_video_data = {
	0,			/* offset */
	0,			/* pixel_format */
	0,			/* src_width */
	0,			/* src_height */
	0,			/* src_pitch */
	0,			/* dst_x */
	0,			/* dst_y */
	0,			/* dst_width */
	0,			/* dst_height */
};

/* Config #1: Crossville 7' */
static igd_param_t config_params_config1 = {
	1*256*1024,		/* Page request */
	0,		/* Max frame buffer size */
	1,		/* Preserve registers */
	0x6,		/* Display flags */
	{ 4, 0, 0, 0, 0 },		/* Display port order */
	{		/* Display Params */
		{		/* Port */
			4,		/* Display port number */
			0x180,		/* Parameters present */
			0x0,		/* EDID flag */
			0x0,		/* Flags when EDID is available */
			0x4,		/* Flags when EDID is not available */
			0,		/* DDC GPIO pins */
			0,		/* DDC speed */
			0,		/* DDC DAB */
			0,		/* I2C GPIO pins */
			0,		/* I2C speed */
			0,		/* I2C DAB */
			{		/* Flat Panel Info */
				0,		/* Flat Panel width */
				0,		/* Flat Panel height */
				0,		/* Flat Panel power method */
				0,		/* VDD active & DVO clock/data active */
				0,		/* DVO clock/data active & backlight enable */
				0,		/* backlight disable & DVO clock/data inactive */
				0,		/* DVO clock/data inactive & VDD inactive */
				0			/* VDD inactive & VDD active */
			},
			{		/* DTD Info */
				sizeof(dtd_config1_port4_dtdlist)/sizeof(igd_display_info_t),		/* Number of DTDs */
				dtd_config1_port4_dtdlist		/* DTD name */
			},
			{		/* Attribute Info */
				sizeof(attrs_config1_port4)/sizeof(igd_param_attr_t),		/* Number of attributes */
				attrs_config1_port4		/* Attr name */
			}
		},
		{		/* Port */
			2,		/* Display port number */
			0x0,		/* Parameters present */
			0x0,		/* EDID flag */
			0x5,		/* Flags when EDID is available */
			0x5,		/* Flags when EDID is not available */
			0,		/* DDC GPIO pins */
			0,		/* DDC speed */
			0,		/* DDC DAB */
			0,		/* I2C GPIO pins */
			0,		/* I2C speed */
			0,		/* I2C DAB */
			{		/* Flat Panel Info */
				0,		/* Flat Panel width */
				0,		/* Flat Panel height */
				0,		/* Flat Panel power method */
				0,		/* VDD active & DVO clock/data active */
				0,		/* DVO clock/data active & backlight enable */
				0,		/* backlight disable & DVO clock/data inactive */
				0,		/* DVO clock/data inactive & VDD inactive */
				0			/* VDD inactive & VDD active */
			},
			{		/* DTD Info */
			0, NULL
			},
			{		/* Attribute Info */
			0, NULL
			}
		},
	},
	0,			/* 24-bit RGB color that framebuffer is cleared to */
	1,			/* Quickboot (1 = enabled) */
	0,			/* Quickboot seamless (1 = enabled) */
	0,			/* Quickboot video input (1 = enabled) */
	0			/* Polling (1 = override interrupt support and use polling) */
};

/* Config #2: CrownBay 13' */
static igd_param_t config_params_config2 = {
	1*256*1024,		/* Page request */
	0,		/* Max frame buffer size */
	1,		/* Preserve registers */
	0x6,		/* Display flags */
	{ 4, 0, 0, 0, 0 },		/* Display port order */
	{		/* Display Params */
		{		/* Port */
			4,		/* Display port number */
			0x80,		/* Parameters present */
			0x0,		/* EDID flag */
			0x5,		/* Flags when EDID is available */
			0x5,		/* Flags when EDID is not available */
			0,		/* DDC GPIO pins */
			0,		/* DDC speed */
			0,		/* DDC DAB */
			0,		/* I2C GPIO pins */
			0,		/* I2C speed */
			0,		/* I2C DAB */
			{		/* Flat Panel Info */
				0,		/* Flat Panel width */
				0,		/* Flat Panel height */
				0,		/* Flat Panel power method */
				0,		/* VDD active & DVO clock/data active */
				0,		/* DVO clock/data active & backlight enable */
				0,		/* backlight disable & DVO clock/data inactive */
				0,		/* DVO clock/data inactive & VDD inactive */
				0			/* VDD inactive & VDD active */
			},
			{		/* DTD Info */
				sizeof(dtd_config2_port4_dtdlist)/sizeof(igd_display_info_t),		/* Number of DTDs */
				dtd_config2_port4_dtdlist		/* DTD name */
			},
			{		/* Attribute Info */
				sizeof(attrs_config1_port4)/sizeof(igd_param_attr_t),		/* Number of attributes */
				attrs_config1_port4		/* Attr name */
			}
		},
		{		/* Port */
			2,		/* Display port number */
			0x0,		/* Parameters present */
			0x0,		/* EDID flag */
			0x5,		/* Flags when EDID is available */
			0x5,		/* Flags when EDID is not available */
			0,		/* DDC GPIO pins */
			0,		/* DDC speed */
			0,		/* DDC DAB */
			0,		/* I2C GPIO pins */
			0,		/* I2C speed */
			0,		/* I2C DAB */
			{		/* Flat Panel Info */
				0,		/* Flat Panel width */
				0,		/* Flat Panel height */
				0,		/* Flat Panel power method */
				0,		/* VDD active & DVO clock/data active */
				0,		/* DVO clock/data active & backlight enable */
				0,		/* backlight disable & DVO clock/data inactive */
				0,		/* DVO clock/data inactive & VDD inactive */
				0			/* VDD inactive & VDD active */
			},
			{		/* DTD Info */
			0, NULL
			},
			{		/* Attribute Info */
			0, NULL
			}
		},
	},
	0,			/* 24-bit RGB color that framebuffer is cleared to */
	1,			/* Quickboot (1 = enabled) */
	0,			/* Quickboot seamless (1 = enabled) */
	0,			/* Quickboot video input (1 = enabled) */
	0			/* Polling (1 = override interrupt support and use polling) */
};

/* Config #3: NexCom VCT1000 7' */
static igd_param_t config_params_config3 = {
	1*256*1024,		/* Page request */
	0,		/* Max frame buffer size */
	1,		/* Preserve registers */
	0x6,		/* Display flags */
	{ 4, 0, 0, 0, 0 },		/* Display port order */
	{		/* Display Params */
		{		/* Port */
			4,		/* Display port number */
			0x180,		/* Parameters present */
			0x0,		/* EDID flag */
			0x0,		/* Flags when EDID is available */
			0x4,		/* Flags when EDID is not available */
			0,		/* DDC GPIO pins */
			0,		/* DDC speed */
			0,		/* DDC DAB */
			0,		/* I2C GPIO pins */
			0,		/* I2C speed */
			0,		/* I2C DAB */
			{		/* Flat Panel Info */
				0,		/* Flat Panel width */
				0,		/* Flat Panel height */
				0,		/* Flat Panel power method */
				0,		/* VDD active & DVO clock/data active */
				0,		/* DVO clock/data active & backlight enable */
				0,		/* backlight disable & DVO clock/data inactive */
				0,		/* DVO clock/data inactive & VDD inactive */
				0			/* VDD inactive & VDD active */
			},
			{		/* DTD Info */
				sizeof(dtd_config3_port4_dtdlist)/sizeof(igd_display_info_t),		/* Number of DTDs */
				dtd_config3_port4_dtdlist		/* DTD name */
			},
			{		/* Attribute Info */
				sizeof(attrs_config3_port4)/sizeof(igd_param_attr_t),		/* Number of attributes */
				attrs_config3_port4		/* Attr name */
			}
		},
		{		/* Port */
			2,		/* Display port number */
			0x0,		/* Parameters present */
			0x0,		/* EDID flag */
			0x5,		/* Flags when EDID is available */
			0x5,		/* Flags when EDID is not available */
			0,		/* DDC GPIO pins */
			0,		/* DDC speed */
			0,		/* DDC DAB */
			0,		/* I2C GPIO pins */
			0,		/* I2C speed */
			0,		/* I2C DAB */
			{		/* Flat Panel Info */
				0,		/* Flat Panel width */
				0,		/* Flat Panel height */
				0,		/* Flat Panel power method */
				0,		/* VDD active & DVO clock/data active */
				0,		/* DVO clock/data active & backlight enable */
				0,		/* backlight disable & DVO clock/data inactive */
				0,		/* DVO clock/data inactive & VDD inactive */
				0			/* VDD inactive & VDD active */
			},
			{		/* DTD Info */
			0, NULL
			},
			{		/* Attribute Info */
			0, NULL
			}
		},
	},
	0,			/* 24-bit RGB color that framebuffer is cleared to */
	1,			/* Quickboot (1 = enabled) */
	0,			/* Quickboot seamless (1 = enabled) */
	0,			/* Quickboot video input (1 = enabled) */
	0			/* Polling (1 = override interrupt support and use polling) */
};

/* Config #4: Crossville sDVO (VGA) - LVDS 7' */
static igd_param_t config_params_config4 = {
       1*256*1024,             /* Page request */
       0,              /* Max frame buffer size */
       1,              /* Preserve registers */
       0x6,            /* Display flags */
       { 2, 4, 0, 0, 0 },              /* Display port order */
       {               /* Display Params */
               {               /* Port */
                       4,              /* Display port number */
                       0x180,          /* Parameters present */
                       0x0,            /* EDID flag */
                       0x0,            /* Flags when EDID is available */
                       0x4,            /* Flags when EDID is not available */
                       0,              /* DDC GPIO pins */
                       0,              /* DDC speed */
                       0,              /* DDC DAB */
                       0,              /* I2C GPIO pins */
                       0,              /* I2C speed */
                       0,              /* I2C DAB */
                       {               /* Flat Panel Info */
                               0,              /* Flat Panel width */
                               0,              /* Flat Panel height */
                               0,              /* Flat Panel power method */
                               0,              /* VDD active & DVO clock/data active */
                               0,              /* DVO clock/data active & backlight enable */
                               0,              /* backlight disable & DVO clock/data inactive */
                               0,              /* DVO clock/data inactive & VDD inactive */
                               0                       /* VDD inactive & VDD active */
                       },
                       {               /* DTD Info */
                               sizeof(dtd_config1_port4_dtdlist)/sizeof(igd_display_info_t),           /* Number of DTDs */
                               dtd_config1_port4_dtdlist               /* DTD name */
                       },
                       {               /* Attribute Info */
                               sizeof(attrs_config1_port4)/sizeof(igd_param_attr_t),           /* Number of attributes */
                               attrs_config1_port4             /* Attr name */
                       }
               },
               {               /* Port */
                       2,              /* Display port number */
                       0x0,            /* Parameters present */
                       0x1,            /* EDID flag */
                       0x2,            /* Flags when EDID is available */
                       0x1,            /* Flags when EDID is not available */
                       0,              /* DDC GPIO pins */
                       0,              /* DDC speed */
                       0,              /* DDC DAB */
                       0,              /* I2C GPIO pins */
                       0,              /* I2C speed */
                       0,              /* I2C DAB */
                       {               /* Flat Panel Info */
                               0,              /* Flat Panel width */
                               0,              /* Flat Panel height */
                               0,              /* Flat Panel power method */
                               0,              /* VDD active & DVO clock/data active */
                               0,              /* DVO clock/data active & backlight enable */
                               0,              /* backlight disable & DVO clock/data inactive */
                               0,              /* DVO clock/data inactive & VDD inactive */
                               0                       /* VDD inactive & VDD active */
                       },
                       {               /* DTD Info */
                       0, NULL
                       },
                       {               /* Attribute Info */
                       0, NULL
                       }
               },
       },
       0,                      /* 24-bit RGB color that framebuffer is cleared to */
       1,                      /* Quickboot (1 = enabled) */
       0,                      /* Quickboot seamless (1 = enabled) */
       0,                      /* Quickboot video input (1 = enabled) */
       0                       /* Polling (1 = override interrupt support and use polling) */
};

/* Config #5: Nexcom VCT1000 sDVO (VGA) - LVDS 7' */
static igd_param_t config_params_config5 = {
       1*256*1024,             /* Page request */
       0,              /* Max frame buffer size */
       1,              /* Preserve registers */
       0x6,            /* Display flags */
       { 2, 4, 0, 0, 0 },              /* Display port order */
       {               /* Display Params */
               {               /* Port */
                       4,              /* Display port number */
                       0x180,          /* Parameters present */
                       0x0,            /* EDID flag */
                       0x0,            /* Flags when EDID is available */
                       0x4,            /* Flags when EDID is not available */
                       0,              /* DDC GPIO pins */
                       0,              /* DDC speed */
                       0,              /* DDC DAB */
                       0,              /* I2C GPIO pins */
                       0,              /* I2C speed */
                       0,              /* I2C DAB */
                       {               /* Flat Panel Info */
                               0,              /* Flat Panel width */
                               0,              /* Flat Panel height */
                               0,              /* Flat Panel power method */
                               0,              /* VDD active & DVO clock/data active */
                               0,              /* DVO clock/data active & backlight enable */
                               0,              /* backlight disable & DVO clock/data inactive */
                               0,              /* DVO clock/data inactive & VDD inactive */
                               0                       /* VDD inactive & VDD active */
                       },
                       {               /* DTD Info */
                               sizeof(dtd_config3_port4_dtdlist)/sizeof(igd_display_info_t),           /* Number of DTDs */
                               dtd_config3_port4_dtdlist               /* DTD name */
                       },
                       {               /* Attribute Info */
                               sizeof(attrs_config3_port4)/sizeof(igd_param_attr_t),           /* Number of attributes */
                               attrs_config3_port4             /* Attr name */
                       }
               },
               {               /* Port */
                       2,              /* Display port number */
                       0x0,            /* Parameters present */
                       0x1,            /* EDID flag */
                       0x2,            /* Flags when EDID is available */
                       0x1,            /* Flags when EDID is not available */
                       0,              /* DDC GPIO pins */
                       0,              /* DDC speed */
                       0,              /* DDC DAB */
                       0,              /* I2C GPIO pins */
                       0,              /* I2C speed */
                       0,              /* I2C DAB */
                       {               /* Flat Panel Info */
                               0,              /* Flat Panel width */
                               0,              /* Flat Panel height */
                               0,              /* Flat Panel power method */
                               0,              /* VDD active & DVO clock/data active */
                               0,              /* DVO clock/data active & backlight enable */
                               0,              /* backlight disable & DVO clock/data inactive */
                               0,              /* DVO clock/data inactive & VDD inactive */
                               0                       /* VDD inactive & VDD active */
                       },
                       {               /* DTD Info */
                       0, NULL
                       },
                       {               /* Attribute Info */
                       0, NULL
                       }
               },
       },
       0,                      /* 24-bit RGB color that framebuffer is cleared to */
       1,                      /* Quickboot (1 = enabled) */
       0,                      /* Quickboot seamless (1 = enabled) */
       0,                      /* Quickboot video input (1 = enabled) */
       0                       /* Polling (1 = override interrupt support and use polling) */
};


/*
 * The emgd_drm_config_t structure is the main configuration structure
 * for the EMGD kernel module.
 */
emgd_drm_config_t config_drm = {
	1,	/* Whether to initialize the display at EMGD module startup time
		 * (corresponds to the "init" module parameter)
		 */
	1,	/* The display configuration to use if initializing the display
		 * (corresponds to the "init" module parameter), where:
		 * - 1 = Single port/display
		 * - 2 = Cloned port/display (e.g. LVDS + CRT with different timings)
		 * - 4 = Twin ports/displays (e.g. LVDS + CRT with same timings)
		 *       Note: Twin is NOT CURRENTLY SUPPORTED
		 * - 8 = Extended displays (e.g. LVDS + CRT displaying different images)
		 */
	800,/* Display width to use if initializing the display
		 * (corresponds to the "width" module parameter)
		 */
	480,/* Display height to use if initializing the display
		 * (corresponds to the "height" module parameter)
		 */
	60,	/* Display refresh rate to use if initializing the display
		 * (corresponds to the "refresh" module parameter)
		 */
	1,  /* KMS */
	0,	/* ovl_brightness */
	0,	/* ovl_contrast */
	0,	/* ovl_saturation */
	0,	/* ovl_gamma_red */
	0,	/* ovl_gamma_green */
	0,	/* ovl_gamma_blue */
	&splash_screen_data,
	&splash_video_data,
	{   /* driver parameters from above */
		&config_params_config1,
		&config_params_config2,
		&config_params_config3,
		&config_params_config4,
		&config_params_config5
	}
#ifdef SUPPORT_V2G_CAMERA
	,
	0	/* disable v2g camera*/
#endif
};


/* type:  2:crownbay else:crossvile  */
void emgd_drm_override_user_config(int configid)
{
   if ( configid == 1 )
   {
       /* Crossville 7inch */
       config_drm.width = 800;
       config_drm.height = 480;
   }
   else if ( configid == 2 )
   {
       /* CrownBay 13inch LVDS */
       config_drm.width = 1366;
       config_drm.height = 768;
   }
   else if ( configid == 4 || configid == 5)
   {
       /* Config #4: sDVO (VGA) for both Crossville - Nexcom */
       config_drm.width = 1024;
       config_drm.height = 768;
   }
   else /* default */
   {
       /* NexCom VCT1000 7inch LVDS*/
       config_drm.width = 800;
       config_drm.height = 480;
   }
   return;
}
