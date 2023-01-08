#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#include "ge2d.h"

// RGBA colors
const int BLUE = 0x0000ffff;
const int RED = 0xff0000ff;
const int BLACK = 0x000000ff;

// Test pattern sizes
const int testWidth = 256;
const int testHeight = 256;
const int testLength = testWidth * testHeight * 4; // 4 bytes per pixel

// /dev/fb1 memory location from dmesg output
// mesonfb1(low)           : 0x07900000 - 0x07a00000 (1M)
//const unsigned long physicalAddress = 0x07900000;
//##fb: reserved memory base:0x000000007f800000, size:800000
//#fb1 starts at 80000000
//#const unsigned long physicalAddress = 0x55400000
const unsigned long physicalAddress = 0x0000000080000000;

void CreateTestPattern()
{
    // The GE2D hardware only works with physically contiguous bus addresses.
    // Only the kernel or a driver can provide this type of memory.  Instead of
    // including a kernel driver, this code borrows memory from /dev/fb1.  This
    // makes the code fragile and prone to breakage should the kernel change.
    // Production code should use the kernel CMA allocator instead.


    // Borrow physical memory from /dev/fb1
    // Must be root
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0)
    {
        printf("Can't open /dev/mem (%x)\n", fd);
        exit(1);
    }

    int* data = (int*) mmap(0, testLength, PROT_READ|PROT_WRITE, MAP_SHARED, fd, physicalAddress);
    if (data == NULL)
    {
        printf("Can't mmap\n");
        exit(1);
    }

    printf("virtual address = %x\n", *data);


    // Create a checkerboard in memory
    int x;
    int y;

    for (y = 0; y < testHeight; ++y)
    {
        for (x = 0; x < testWidth; ++x)
        {
            int color;
            bool renderFlag;

            if ((x & 0x20) == 0)
            {
                renderFlag = true;
            }
            else
            {
                renderFlag = false;
            }

            if ((y & 0x20) == 0)
            {
                renderFlag = !renderFlag;
            }

            if (renderFlag)
            {
                color = RED; //RGBA
            }
            else
            {
                color = BLACK;
            }

            data[y * testWidth + x] = color;
        }
    }
    printf("Pattern created OK\n");

    // Clean up
    munmap(data, testLength);
    close(fd);
    printf("munmap and close OK\n");
}

int OpenGe2d() {
	int fd = open("/dev/ge2d", O_RDWR);
	if (fd < 0) {
		printf("open /dev/ge2d failed.");
		exit(1);
	}
	printf("/dev/ge2d file handle: %x\n", fd);
//	close(fd);  // TODO: If closed no GE2D operation works!
	return fd;
}


int  GE2DConfig(void) {
// Tell the hardware the destination is /dev/fb0
	config_para_t config;
	memset((char*)&config, 0, sizeof(config));

	config.src_dst_type = OSD0_OSD0;
	int fd_ge2d = OpenGe2d();
	int ret = ioctl(fd_ge2d, GE2D_CONFIG, &config);
	printf("GE2DConfig: GE2D_CONFIG ret: %x\n", ret);
	return fd_ge2d;
}


int GE2DConfigEx(void) {
    // get OSD dimesnions x,y
    int fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        printf("Can't open framebuffer device\n");
        exit(1);
    }
    struct fb_var_screeninfo vinfo;
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information\n");
        exit(1);
    }
    close(fbfd);
    int screenWidth = vinfo.xres;
    int screenHeight = vinfo.yres;


    // Tell the hardware we will source memory (that we borrowed)
    // and write to /dev/fb0

    // This shows the expanded form of config.  Using this expanded
    // form allows the blit source x and y read directions to be specified
    // as well as the destination x and y write directions.  Together
    // they allow overlapping blit operations to be performed.
    config_para_ex_t configex;
    memset(&configex, 0x00, sizeof(configex));

//    configex.src_para.mem_type = CANVAS_ALLOC;     // src is some other memory
    configex.src_para.mem_type = CANVAS_OSD0;
//    configex.src_para.format = GE2D_FORMAT_S32_RGBA; // not our source format we use OSD
    configex.src_para.format = GE2D_FORMAT_S32_BGRA;
//    configex.src_planes[0].addr = (unsigned long)physicalAddress;
    configex.src_planes[0].w = screenWidth;   //testWidth;
    configex.src_planes[0].h = screenHeight;  //testHeight;
    configex.src_para.left = 0;
    configex.src_para.top = 0;
    configex.src_para.width =  screenWidth;   //testWidth;
    configex.src_para.height = screenHeight;  //testHeight;
    configex.src_para.x_rev = 0;
    configex.src_para.y_rev = 0;

//    configex.src2_para.mem_type = CANVAS_TYPE_INVALID;

    configex.dst_para.mem_type = CANVAS_OSD0;
    configex.dst_para.left = 0;
    configex.dst_para.top = 0;
    configex.dst_para.width = screenWidth;
    configex.dst_para.height = screenHeight;
    configex.dst_para.x_rev = 0;
    configex.dst_para.y_rev = 0;

	int fd_ge2d = OpenGe2d();
	int ret = ioctl(fd_ge2d, GE2D_CONFIG_EX, &configex);
	printf("GE2DConfigEc: GE2D_CONFIG_EX ret: %x\n", ret);
	return fd_ge2d;
}


void FillRectangle(int fd_ge2d, int x, int y, int width, int height, int color)
{
int ret;

    // Tell the hardware the destination is /dev/fb0
    config_para_t config;
//    struct config_para_s config = {0};
    //memset(&config, 0x00, sizeof(config));
	memset((char*)&config, 0, sizeof(config));

    config.src_dst_type = OSD0_OSD0;

    ret = ioctl(fd_ge2d, GE2D_CONFIG, &config);
    printf("GE2D_CONFIG ret: %x\n", ret);


	// GE2D
//	int ge2d_fd = OpenGe2d();

    // Perform a fill operation;
    ge2d_para_t fillRectParam;
    fillRectParam.src1_rect.x = x;
    fillRectParam.src1_rect.y = y;
    fillRectParam.src1_rect.w = width;
    fillRectParam.src1_rect.h = height;
    fillRectParam.color = color; // R G B A

    ret = ioctl(fd_ge2d, GE2D_FILLRECTANGLE, &fillRectParam);
    printf("GE2D_FILLRECTANGLE ret: %x\n", ret);
}

void FillRect(int fd_ge2d, int x, int y, int width, int height, int color) {
    // Perform a fill operation;
    ge2d_para_t fillRectParam;
    fillRectParam.src1_rect.x = x;
    fillRectParam.src1_rect.y = y;
    fillRectParam.src1_rect.w = width;
    fillRectParam.src1_rect.h = height;
    fillRectParam.color = color; // R G B A

    int ret = ioctl(fd_ge2d, GE2D_FILLRECTANGLE, &fillRectParam);
}



void BlitTestPattern(int fd_ge2d, int dstX, int dstY, int screenWidth, int screenHeight)
{
    // Tell the hardware we will source memory (that we borrowed)
    // and write to /dev/fb0

    // This shows the expanded form of config.  Using this expanded
    // form allows the blit source x and y read directions to be specified
    // as well as the destination x and y write directions.  Together
    // they allow overlapping blit operations to be performed.
    config_para_ex_t configex;
    memset(&configex, 0x00, sizeof(configex));

    configex.src_para.mem_type = CANVAS_ALLOC;
    //configex.src_para.format = GE2D_FORMAT_S32_RGBA;
    configex.src_para.format = GE2D_FORMAT_S32_BGRA;
    configex.src_planes[0].addr = (unsigned long)physicalAddress;
    configex.src_planes[0].w = testWidth;
    configex.src_planes[0].h = testHeight;
    configex.src_para.left = 0;
    configex.src_para.top = 0;
    configex.src_para.width = testWidth;
    configex.src_para.height = testHeight;
    configex.src_para.x_rev = 0;
    configex.src_para.y_rev = 0;

    configex.src2_para.mem_type = CANVAS_TYPE_INVALID;

    configex.dst_para.mem_type = CANVAS_OSD0;
    //configex.dst_para.mem_type = OSD0_OSD0;
    configex.dst_para.left = 0;
    configex.dst_para.top = 0;
    configex.dst_para.width = screenWidth;
    configex.dst_para.height = screenHeight;
    configex.dst_para.x_rev = 0;
    configex.dst_para.y_rev = 0;


    int ret = ioctl(fd_ge2d, GE2D_CONFIG_EX, &configex);
    printf("GE2D_CONFIG_EX ret: %x\n", ret);


    // Perform the blit operation
    ge2d_para_t blitRectParam2;
    memset(&blitRectParam2, 0, sizeof(blitRectParam2));

    blitRectParam2.src1_rect.x = 0;
    blitRectParam2.src1_rect.y = 0;
    blitRectParam2.src1_rect.w = testWidth;
    blitRectParam2.src1_rect.h = testHeight;
    blitRectParam2.dst_rect.x = dstX;
    blitRectParam2.dst_rect.y = dstY;

    ret = ioctl(fd_ge2d, GE2D_BLIT, &blitRectParam2);
    printf("GE2D_BLIT ret: %x\n", ret);
}


void BlitNoInit(int fd_ge2d, int src_x, int src_y, int w, int h, int dst_x, int dst_y) {
    // Perform the blit operation
    ge2d_para_t blitRectParam2;
    memset(&blitRectParam2, 0, sizeof(blitRectParam2));

    blitRectParam2.src1_rect.x = src_x;
    blitRectParam2.src1_rect.y = src_y;
    blitRectParam2.src1_rect.w = w;
    blitRectParam2.src1_rect.h = h;
    blitRectParam2.dst_rect.x = dst_x;
    blitRectParam2.dst_rect.y = dst_y;

    int ret = ioctl(fd_ge2d, GE2D_BLIT, &blitRectParam2);
//    int ret = ioctl(fd_ge2d, GE2D_BLIT_NOALPHA, &blitRectParam2);  // does not copy color
    printf("GE2D_BLIT NoInit ret: %x\n", ret);
}




/////////////////////////////////////////////////////////////
int main()
{
    int y;
    int fd_ge2d = open("/dev/ge2d", O_RDWR);
    if (fd_ge2d < 0)
    {
        printf("Can't open /dev/ge2d\n");
        exit(1);
    }
    printf("Opened /dev/ge2d\n");

    // Get the screen height and width
    int fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        printf("Can't open framebuffer device\n");
        exit(1);
    }

    struct fb_var_screeninfo vinfo;
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information\n");
        exit(1);
    }

	struct fb_fix_screeninfo fb_finfo;
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fb_finfo) == -1) {
        perror("Error reading variable information\n");
        exit(1);
    }

    printf("Fixed: Frambuffer memory Phys Addr: %#010lx\n", (unsigned long int) fb_finfo.smem_start);
    printf("Fixed: Phys memory length-size = %d / %#010x Line Length =  %d\n", fb_finfo.smem_len, fb_finfo.smem_len, fb_finfo.line_length);
    close(fbfd);

    int screenWidth = vinfo.xres;
    int screenHeight = vinfo.yres;

    printf("Variable: Screen size = %d x %d\n", vinfo.xres, vinfo.yres);
    printf("Variable: Virtual Screen size = %d x %d\n", vinfo.xres_virtual, vinfo.yres_virtual);
    printf("Variable: Offset x and y = %d x %d\n", vinfo.xoffset, vinfo.yoffset);
    printf("Variable: BPP = %d\n", vinfo.bits_per_pixel);
    printf("GE2D_CONFIG = %lu\n GE2D_CONFIG_EX %lu\n",_IOC_TYPE(GE2D_CONFIG), _IOC_TYPE(GE2D_CONFIG_EX));


// a) no GE2_CONFIG no FillRect, seems no BlitNoInit
// b) FillRectangle GE2_CONFIG  FillRect ok , seems ok BlitNoInit, need reboot check
// c) or init GE2DConfig works, NOALPHA does not copy color FillRect ok , seems ok BlitNoInit, ok reboot check
// d) need test for GE2DConfigEx --> BAD
// e) both GE2DConfigEx and GE2DConfig seem to work the same

//    //CreateTestPattern();
//    FillRectangle(fd_ge2d, 500, 50, 51, 51, BLUE); // RGBA
//	getchar();

	fd_ge2d = GE2DConfig();
//	fd_ge2d = GE2DConfigEx();
	BlitNoInit(fd_ge2d, 800, 50, 400, 400, 750,10);
	getchar();


	BlitNoInit(fd_ge2d, 10, 10, 200, 200, 300,300);
	getchar();


////void BlitNoInit(int fd_ge2d, int src_x, int src_y, int w, int h, int dst_x, int dst_y)
    BlitNoInit(fd_ge2d, 310, 310, 200, 200, 320,320);
	getchar();

    for (y = 0; y < 100 ; ++y)
    {
//	    FillRect(fd_ge2d, 0+y, 0+y, 512, 512, BLUE); // RGBA
    }
	getchar();


    for (y = 0; y < 1000 ; ++y)
    {
	BlitNoInit(fd_ge2d, 0+y, 0+y, 200, 200, 550+y,20);
    }
	getchar();



    close(fd_ge2d);

    return 0;
}
