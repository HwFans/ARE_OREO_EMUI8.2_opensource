#ifndef _LCD_KIT_EFFECT_H_
#define _LCD_KIT_EFFECT_H_

#include <sys.h>
#include <boot.h>
#include <oeminfo_ops.h>
#include <global_ddr_map.h>
#include "hisi_fb.h"

#define LCD_KIT_COLOR_INFO_SIZE 8
#define LCD_KIT_SERIAL_INFO_SIZE 16

struct panelid {
	uint32_t modulesn;
	uint32_t equipid;
	uint32_t modulemanufactdate;
	uint32_t vendorid;
};

struct coloruniformparams {
	uint32_t c_lmt[3];
	uint32_t mxcc_matrix[3][3];
	uint32_t white_decay_luminace;
};

struct colormeasuredata {
	uint32_t chroma_coordinates[4][2];
	uint32_t white_luminance;
};

struct lcdbrightnesscoloroeminfo {
	uint32_t id_flag;
	uint32_t tc_flag;
	struct panelid  panel_id;
	struct coloruniformparams color_params;
	struct colormeasuredata color_mdata;
};
#if defined(FASTBOOT_DISPLAY_LOGO_KIRIN970)
void lcd_bright_rgbw_id_from_oeminfo_process(struct hisi_fb_data_type* phisifd);
#endif

#if defined (FASTBOOT_DISPLAY_LOGO_HI3660) || defined (FASTBOOT_DISPLAY_LOGO_KIRIN970) || defined (FASTBOOT_DISPLAY_LOGO_KIRIN980)
int lcd_kit_write_gm_to_reserved_mem();
#endif

#endif
