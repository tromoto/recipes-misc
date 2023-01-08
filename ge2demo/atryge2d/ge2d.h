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

