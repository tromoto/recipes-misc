#pragma once


// This file eliminates the need to have the kernel headers present
// on the system.  It is provided for convience only.  Production code
// should reference the appropriate kernel headers.


typedef struct
{
    int x; /* X coordinate of its top-left point */
    int y; /* Y coordinate of its top-left point */
    int w; /* width of it */
    int h; /* height of it */
}rectangle_t;

typedef struct
{
    unsigned int color ;
    rectangle_t src1_rect;
    rectangle_t src2_rect;
    rectangle_t	dst_rect;
    int	op;
}ge2d_para_t ;

#define GE2D_GET_CAP                        0x470b
#define GE2D_BLEND_NOALPHA_NOBLOCK          0x470a
#define GE2D_BLEND_NOALPHA                  0x4709
#define	GE2D_STRETCHBLIT_NOALPHA_NOBLOCK    0x4708
#define	GE2D_BLIT_NOALPHA_NOBLOCK           0x4707
#define	GE2D_BLEND_NOBLOCK                  0x4706
#define	GE2D_BLIT_NOBLOCK                   0x4705
#define	GE2D_STRETCHBLIT_NOBLOCK            0x4704
#define	GE2D_FILLRECTANGLE_NOBLOCK          0x4703
#define	GE2D_STRETCHBLIT_NOALPHA            0x4702
#define	GE2D_BLIT_NOALPHA                   0x4701
#define	GE2D_BLEND                          0x4700
#define	GE2D_BLIT                           0x46ff
#define	GE2D_STRETCHBLIT                    0x46fe
#define	GE2D_FILLRECTANGLE                  0x46fd
#define	GE2D_SRCCOLORKEY_OLD                0x46fc
#define	GE2D_SET_COEF                       0x46fb
#define	GE2D_CONFIG_EX_OLD                  0x46fa
#define	GE2D_CONFIG_OLD                     0x46f9
#define	GE2D_ANTIFLICKER_ENABLE             0x46f8


// IOCTLs have changed!!
#if 0
#define GE2D_STRETCHBLIT_NOALPHA_NOBLOCK 0x4708
#define GE2D_BLIT_NOALPHA_NOBLOCK 0x4707
#define GE2D_BLEND_NOBLOCK 0x4706
#define GE2D_BLIT_NOBLOCK 0x4705
#define GE2D_STRETCHBLIT_NOBLOCK 0x4704
#define GE2D_FILLRECTANGLE_NOBLOCK 0x4703
#define GE2D_STRETCHBLIT_NOALPHA 0x4702
#define GE2D_BLIT_NOALPHA	0x4701
#define GE2D_BLEND	0x4700
#define GE2D_BLIT 0x46ff
#define GE2D_STRETCHBLIT 0x46fe
#define GE2D_FILLRECTANGLE 0x46fd
#define GE2D_SRCCOLORKEY 0x46fc
#define	GE2D_SET_COEF	0x46fb
#define GE2D_CONFIG_EX 0x46fa
#define GE2D_CONFIG	0x46f9
#define	GE2D_ANTIFLICKER_ENABLE	0x46f8
#endif

typedef struct
{
    unsigned long addr;
    unsigned int	w;
    unsigned int	h;
}config_planes_t;

typedef struct
{
    int	key_enable;
    int	key_color;
    int key_mask;
    int key_mode;
}src_key_ctrl_t;

typedef struct
{
    int src_dst_type;
    int alu_const_color;
    unsigned int src_format;
    unsigned int dst_format ; //add for src&dst all in user space.
    config_planes_t src_planes[4];
    config_planes_t dst_planes[4];
    src_key_ctrl_t src_key;
}config_para_t;


typedef enum
{
    OSD0_OSD0 =0,
    OSD0_OSD1,
    OSD1_OSD1,
    OSD1_OSD0,
    ALLOC_OSD0,
    ALLOC_OSD1,
    ALLOC_ALLOC,
    TYPE_INVALID,
}ge2d_src_dst_t;



/* 16 bit */
#define GE2D_COLOR_MAP_YUV422		(0 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_RGB655		(1 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_YUV655		(1 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_RGB844		(2 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_YUV844		(2 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_RGBA6442     (3 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_YUVA6442     (3 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_RGBA4444     (4 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_YUVA4444     (4 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_RGB565       (5 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_YUV565       (5 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_ARGB4444		(6 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_AYUV4444		(6 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_ARGB1555     (7 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_AYUV1555     (7 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_RGBA4642     (8 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_YUVA4642     (8 << GE2D_COLOR_MAP_SHIFT)
/* 24 bit */
#define GE2D_COLOR_MAP_RGB888       (0 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_YUV444       (0 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_RGBA5658     (1 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_YUVA5658     (1 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_ARGB8565     (2 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_AYUV8565     (2 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_RGBA6666     (3 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_YUVA6666     (3 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_ARGB6666     (4 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_AYUV6666     (4 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_BGR888		(5 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_VUY888		(5 << GE2D_COLOR_MAP_SHIFT)
/* 32 bit */
#define GE2D_COLOR_MAP_RGBA8888		(0 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_YUVA8888		(0 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_ARGB8888     (1 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_AYUV8888     (1 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_ABGR8888     (2 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_AVUY8888     (2 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_BGRA8888     (3 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_VUYA8888     (3 << GE2D_COLOR_MAP_SHIFT)



#define GE2D_ENDIAN_SHIFT 24
#define GE2D_LITTLE_ENDIAN (1 << GE2D_ENDIAN_SHIFT)
#define GE2D_COLOR_MAP_SHIFT 20

#define GE2D_COLOR_MAP_RGB565 (5 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_ARGB8888 (1 << GE2D_COLOR_MAP_SHIFT)

/* 32 bit */
#define GE2D_COLOR_MAP_RGBA8888		(0 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_YUVA8888		(0 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_ARGB8888     (1 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_AYUV8888     (1 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_ABGR8888     (2 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_AVUY8888     (2 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_BGRA8888     (3 << GE2D_COLOR_MAP_SHIFT)
#define GE2D_COLOR_MAP_VUYA8888     (3 << GE2D_COLOR_MAP_SHIFT)


/*
 * format code is defined as:
 * [18] : 1-deep color mode(10/12 bit), 0-8bit mode
 * [17] : 1-YUV color space, 0-RGB color space
 * [16] : compress_range, 1-full ramge, 0-limited range
 * [9:8]: format
 * [7:6]: 8bit_mode_sel
 * [5]  : LUT_EN
 * [4:3]: PIC_STRUCT
 * [2]  : SEP_EN
 * [1:0]: X_YC_RATIO, SRC1_Y_YC_RATIO
 */
#define GE2D_FORMAT_MASK                0x0ffff
#define GE2D_BPP_MASK                   0x00300
#define GE2D_BPP_8BIT                   0x00000
#define GE2D_BPP_16BIT                  0x00100
#define GE2D_BPP_24BIT                  0x00200
#define GE2D_BPP_32BIT                  0x00300
#define GE2D_FORMAT_DEEP_COLOR   0x40000
#define GE2D_FORMAT_YUV                 0x20000
#define GE2D_FORMAT_FULL_RANGE          0x10000
/*bit8(2)  format   bi6(2) mode_8b_sel  bit5(1)lut_en   bit2 sep_en*/
/*M  separate block S one block.*/

#define GE2D_FMT_S8_Y		0x00000 /* 00_00_0_00_0_00 */
#define GE2D_FMT_S8_CB		0x00040 /* 00_01_0_00_0_00 */
#define GE2D_FMT_S8_CR		0x00080 /* 00_10_0_00_0_00 */
#define GE2D_FMT_S8_R		0x00000 /* 00_00_0_00_0_00 */
#define GE2D_FMT_S8_G		0x00040 /* 00_01_0_00_0_00 */
#define GE2D_FMT_S8_B		0x00080 /* 00_10_0_00_0_00 */
#define GE2D_FMT_S8_A		0x000c0 /* 00_11_0_00_0_00 */
#define GE2D_FMT_S8_LUT		0x00020 /* 00_00_1_00_0_00 */
#define GE2D_FMT_S16_YUV422	0x20102 /* 01_00_0_00_0_00 */
#define GE2D_FMT_S16_RGB (GE2D_LITTLE_ENDIAN|0x00100) /* 01_00_0_00_0_00 */
#define GE2D_FMT_S24_YUV444	0x20200 /* 10_00_0_00_0_00 */
#define GE2D_FMT_S24_RGB (GE2D_LITTLE_ENDIAN|0x00200) /* 10_00_0_00_0_00 */
#define GE2D_FMT_S32_YUVA444	0x20300 /* 11_00_0_00_0_00 */
#define GE2D_FMT_S32_RGBA (GE2D_LITTLE_ENDIAN|0x00300) /* 11_00_0_00_0_00 */
#define GE2D_FMT_M24_YUV420	0x20007 /* 00_00_0_00_1_11 */
#define GE2D_FMT_M24_YUV422	0x20006 /* 00_00_0_00_1_10 */
#define GE2D_FMT_M24_YUV444	0x20004 /* 00_00_0_00_1_00 */
#define GE2D_FMT_M24_RGB		0x00004 /* 00_00_0_00_1_00 */
#define GE2D_FMT_M24_YUV420T	0x20017 /* 00_00_0_10_1_11 */
#define GE2D_FMT_M24_YUV420B	0x2001f /* 00_00_0_11_1_11 */

#define GE2D_FMT_M24_YUV420SP		0x20207
#define GE2D_FMT_M24_YUV422SP           0x20206
/* 01_00_0_00_1_11 nv12 &nv21, only works on m6. */
#define GE2D_FMT_M24_YUV420SPT		0x20217
/* 01_00_0_00_1_11 nv12 &nv21, only works on m6. */
#define GE2D_FMT_M24_YUV420SPB		0x2021f

#define GE2D_FMT_S16_YUV422T	0x20110 /* 01_00_0_10_0_00 */
#define GE2D_FMT_S16_YUV422B	0x20138 /* 01_00_0_11_0_00 */
#define GE2D_FMT_S24_YUV444T	0x20210 /* 10_00_0_10_0_00 */
#define GE2D_FMT_S24_YUV444B	0x20218 /* 10_00_0_11_0_00 */

/* only works after TXL and for src1. */
#define GE2D_FMT_S24_10BIT_YUV444		0x60200
#define GE2D_FMT_S24_10BIT_YUV444T		0x60210
#define GE2D_FMT_S24_10BIT_YUV444B		0x60218

#define GE2D_FMT_S16_10BIT_YUV422		0x60102
#define GE2D_FMT_S16_10BIT_YUV422T		0x60112
#define GE2D_FMT_S16_10BIT_YUV422B		0x6011a

#define GE2D_FMT_S16_12BIT_YUV422		0x60102
#define GE2D_FMT_S16_12BIT_YUV422T		0x60112
#define GE2D_FMT_S16_12BIT_YUV422B		0x6011a
/* back compatible defines */
#define GE2D_FORMAT_S8_Y            (GE2D_FORMAT_YUV|GE2D_FMT_S8_Y)
#define GE2D_FORMAT_S8_CB          (GE2D_FORMAT_YUV|GE2D_FMT_S8_CB)
#define GE2D_FORMAT_S8_CR          (GE2D_FORMAT_YUV|GE2D_FMT_S8_CR)
#define GE2D_FORMAT_S8_R            GE2D_FMT_S8_R
#define GE2D_FORMAT_S8_G            GE2D_FMT_S8_G
#define GE2D_FORMAT_S8_B            GE2D_FMT_S8_B
#define GE2D_FORMAT_S8_A            GE2D_FMT_S8_A
#define GE2D_FORMAT_S8_LUT          GE2D_FMT_S8_LUT
#define GE2D_FORMAT_S12_RGB_655 (GE2D_FMT_S16_RGB | GE2D_COLOR_MAP_RGB655)
#define GE2D_FORMAT_S16_YUV422 (GE2D_FMT_S16_YUV422 | GE2D_COLOR_MAP_YUV422)
#define GE2D_FORMAT_S16_RGB_655 (GE2D_FMT_S16_RGB | GE2D_COLOR_MAP_RGB655)
#define GE2D_FORMAT_S24_YUV444 (GE2D_FMT_S24_YUV444 | GE2D_COLOR_MAP_YUV444)
#define GE2D_FORMAT_S24_RGB (GE2D_FMT_S24_RGB | GE2D_COLOR_MAP_RGB888)
#define GE2D_FORMAT_S32_YUVA444 (GE2D_FMT_S32_YUVA444 | GE2D_COLOR_MAP_YUVA4444)
#define GE2D_FORMAT_S32_RGBA (GE2D_FMT_S32_RGBA | GE2D_COLOR_MAP_RGBA8888)
#define GE2D_FORMAT_M24_YUV420      GE2D_FMT_M24_YUV420
#define GE2D_FORMAT_M24_YUV422      GE2D_FMT_M24_YUV422
#define GE2D_FORMAT_M24_YUV444      GE2D_FMT_M24_YUV444
#define GE2D_FORMAT_M24_RGB         GE2D_FMT_M24_RGB
#define GE2D_FORMAT_M24_YUV420T     GE2D_FMT_M24_YUV420T
#define GE2D_FORMAT_M24_YUV420B     GE2D_FMT_M24_YUV420B
#define GE2D_FORMAT_M24_YUV422SP (GE2D_FMT_M24_YUV422SP | GE2D_COLOR_MAP_NV12)
#define GE2D_FORMAT_S16_YUV422T (GE2D_FMT_S16_YUV422T | GE2D_COLOR_MAP_YUV422)
#define GE2D_FORMAT_S16_YUV422B (GE2D_FMT_S16_YUV422B | GE2D_COLOR_MAP_YUV422)
#define GE2D_FORMAT_S24_YUV444T (GE2D_FMT_S24_YUV444T | GE2D_COLOR_MAP_YUV444)
#define GE2D_FORMAT_S24_YUV444B (GE2D_FMT_S24_YUV444B | GE2D_COLOR_MAP_YUV444)



#define GE2D_FMT_S16_RGB (GE2D_LITTLE_ENDIAN|0x00100) /* 01_00_0_00_0_00 */
#define GE2D_FMT_S32_RGBA (GE2D_LITTLE_ENDIAN|0x00300) /* 11_00_0_00_0_00 */

#define GE2D_FORMAT_S16_RGB_565 (GE2D_FMT_S16_RGB | GE2D_COLOR_MAP_RGB565)
/*32 bit*/
#define GE2D_FORMAT_S32_ARGB (GE2D_FMT_S32_RGBA | GE2D_COLOR_MAP_ARGB8888)
#define GE2D_FORMAT_S32_ABGR (GE2D_FMT_S32_RGBA | GE2D_COLOR_MAP_ABGR8888)
#define GE2D_FORMAT_S32_BGRA (GE2D_FMT_S32_RGBA | GE2D_COLOR_MAP_BGRA8888)
// 32bpp e2 uses SURF_BGRA8888; 


typedef enum
{
    CANVAS_OSD0 =0,
    CANVAS_OSD1,
    CANVAS_ALLOC,
    CANVAS_TYPE_INVALID,
} ge2d_src_canvas_type;

typedef struct
{
    int canvas_index;
    int top;
    int left;
    int width;
    int height;
    int format;
    int mem_type;
    int color;
    unsigned char x_rev;
    unsigned char y_rev;
    unsigned char fill_color_en;
    unsigned char fill_mode;
} src_dst_para_ex_t ;

typedef struct
{
    src_dst_para_ex_t src_para;
    src_dst_para_ex_t src2_para;
    src_dst_para_ex_t dst_para;
    //key mask
    src_key_ctrl_t src_key;
    src_key_ctrl_t src2_key;
    //new
    unsigned char src1_cmult_asel;
    unsigned char src2_cmult_asel;
    int alu_const_color;
    //new
    unsigned char src1_gb_alpha_en;
    unsigned src1_gb_alpha;
    unsigned op_mode;
    unsigned char bitmask_en;
    unsigned char bytemask_only;
    unsigned int bitmask;
    unsigned char dst_xy_swap;
    // scaler and phase releated
    unsigned hf_init_phase;
    int hf_rpt_num;
    unsigned hsc_start_phase_step;
    int hsc_phase_slope;
    unsigned vf_init_phase;
    int vf_rpt_num;
    unsigned vsc_start_phase_step;
    int vsc_phase_slope;
    unsigned char src1_vsc_phase0_always_en;
    unsigned char src1_hsc_phase0_always_en;
    unsigned char src1_hsc_rpt_ctrl; //1bit, 0: using minus, 1: using repeat data
    unsigned char src1_vsc_rpt_ctrl; //1bit, 0: using minus 1: using repeat data
    //canvas info
    config_planes_t src_planes[4];
    config_planes_t src2_planes[4];
    config_planes_t dst_planes[4];
} config_para_ex_t;

typedef struct
{
	unsigned long addr;
	unsigned int w;
	unsigned int h;
	int shared_fd;
} config_planes_ion_t;

//////////////////

struct config_planes_s {
	unsigned long addr;
	unsigned int w;
	unsigned int h;
};


struct src_key_ctrl_s {
	int key_enable;
	int key_color;
	int key_mask;
	int key_mode;
};

struct config_para_s {
	int  src_dst_type;
	int  alu_const_color;
	unsigned int src_format;
	unsigned int dst_format; /* add for src&dst all in user space. */

	struct config_planes_s src_planes[4];
	struct config_planes_s dst_planes[4];
	struct src_key_ctrl_s  src_key;
};



struct  config_para_ex_s {
    src_dst_para_ex_t src_para;
    src_dst_para_ex_t src2_para;
    src_dst_para_ex_t dst_para;
    //key mask
    src_key_ctrl_t src_key;
    src_key_ctrl_t src2_key;
    //new
    unsigned char src1_cmult_asel;
    unsigned char src2_cmult_asel;
    int alu_const_color;
    //new
    unsigned char src1_gb_alpha_en;
    unsigned src1_gb_alpha;
    unsigned op_mode;
    unsigned char bitmask_en;
    unsigned char bytemask_only;
    unsigned int bitmask;
    unsigned char dst_xy_swap;
    // scaler and phase releated
    unsigned hf_init_phase;
    int hf_rpt_num;
    unsigned hsc_start_phase_step;
    int hsc_phase_slope;
    unsigned vf_init_phase;
    int vf_rpt_num;
    unsigned vsc_start_phase_step;
    int vsc_phase_slope;
    unsigned char src1_vsc_phase0_always_en;
    unsigned char src1_hsc_phase0_always_en;
    unsigned char src1_hsc_rpt_ctrl; //1bit, 0: using minus, 1: using repeat data
    unsigned char src1_vsc_rpt_ctrl; //1bit, 0: using minus 1: using repeat data
    //canvas info
    config_planes_t src_planes[4];
    config_planes_t src2_planes[4];
    config_planes_t dst_planes[4];
};




//#if 0
#define GE2D_IOC_MAGIC  'G'

#define GE2D_CONFIG		_IOW(GE2D_IOC_MAGIC, 0x00, struct config_para_s)
#define GE2D_CONFIG_EX	 _IOW(GE2D_IOC_MAGIC, 0x01,  struct config_para_ex_s)
#define	GE2D_SRCCOLORKEY     _IOW(GE2D_IOC_MAGIC, 0x02, struct config_para_s)

#define GE2D_CONFIG_EX_ION	_IOW(GE2D_IOC_MAGIC, 0x03,  struct config_para_ex_ion_s)

#define GE2D_REQUEST_BUFF _IOW(GE2D_IOC_MAGIC, 0x04, struct ge2d_dmabuf_req_s)
#define GE2D_EXP_BUFF _IOW(GE2D_IOC_MAGIC, 0x05, struct ge2d_dmabuf_exp_s)
#define GE2D_FREE_BUFF _IOW(GE2D_IOC_MAGIC, 0x06, int)

#define GE2D_CONFIG_EX_MEM	_IOW(GE2D_IOC_MAGIC, 0x07,  struct config_ge2d_para_ex_s)

#define GE2D_SYNC_DEVICE _IOW(GE2D_IOC_MAGIC, 0x08, int)
#define GE2D_SYNC_CPU _IOW(GE2D_IOC_MAGIC, 0x09, int)
//#endif

