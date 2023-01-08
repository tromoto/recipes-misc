#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <setjmp.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include "ion.h"
#include "meson_ion.h"
#include "ge2d.h"

#define FBTFT_UPDATE _IO('m', 313)
#define CLEAR(x) memset(&(x), 0, sizeof(x))
#define IMG_WIDTH 752
#define IMG_HEIGHT 480

typedef struct {
  void *start;
  size_t length;
  unsigned long phys_addr;
  ion_user_handle_t handle;
} ion_buffer;

int xioctl(int fd, int request, void *arg);

void alloc_ion_buffer(int ion_fd, ion_buffer *ion_buffer, int size);

void free_ion_buffer(int ion_fd, ion_user_handle_t handle);

// Naive test to see if framebuffer is an LCD using the fbtft driver
int is_fbtft(char *fb_dev);

// Needed for jump back error handling
jmp_buf env;

void handle_error(char * msg);

int main(int argc, char** argv) {
  int opt = 0, err = 0;
  char *fb_dev = NULL;
  char *image_path = "capture.bmp";
  FILE *img_file = NULL;
  int fb_fd = -1, ge2d_fd = -1, ion_fd = -1;
  ion_buffer ion_buffer;
  struct fb_var_screeninfo fb_vinfo;
  struct fb_fix_screeninfo fb_finfo;
  ge2d_para_t blit_rect;
  config_para_t ge2d_config; 

  while ((opt = getopt(argc, argv, "d:")) != -1) {
    switch (opt) {
      case 'd':
        fb_dev = optarg;
        break;
      //case 'i':
      //  image_path = optarg;
      //  break;
      case '?':
        if (optopt == 'd')
          puts("Missing framebuffer device argument (-d)");
        //else if (optopt == 'i')
        //  puts("Missing image file path argument (-i)");
        else 
          printf("Unknown argument: %c\n", optopt);
        break;
    }
  }

  if (!fb_dev || !image_path) {
    puts("Usage: test.out -d [framebuffer device path]");
    return EXIT_FAILURE;
  }

  // Jump back to here on error and cleanup (saves writing lots of '{}' and 'gotos')
  err = setjmp(env);
  if (err) {
    if (img_file)
      fclose(img_file);

    if (ion_fd >= 0) {
      free_ion_buffer(ion_fd, ion_buffer.handle);
      close(ion_fd);
    }

    if (fb_fd >= 0)
      close(fb_fd);

    if (ge2d_fd >= 0)
      close(ge2d_fd);

    return EXIT_FAILURE;
  }

  puts("Error jump back set.");

  img_file = fopen(image_path, "r");

  if (!img_file) {
    handle_error("Error opening image file");
  }

  // Get an ION buffer to read the image file into.
  ion_fd = open("/dev/ion", O_RDWR);

  if (ion_fd < 0)
    handle_error("Error opening ION device");
  
  alloc_ion_buffer(ion_fd, &ion_buffer, IMG_WIDTH * IMG_HEIGHT);

  // Read in the image file
  fread(ion_buffer.start, 1, ion_buffer.length, img_file);

  if (ferror(img_file))
    handle_error("Error reading image file");

  // Open the framebuffer device and get info
  fb_fd = open(fb_dev, O_RDWR);

  if (fb_fd < 0)
    handle_error("Error opening framebuffer device");
 
  CLEAR(fb_vinfo);
  if (xioctl(fb_fd, FBIOGET_VSCREENINFO, &fb_vinfo) < 0) 
    handle_error("FBIOGET_VSCREENINFO Failed");

  CLEAR(fb_finfo);
  if (xioctl(fb_fd, FBIOGET_FSCREENINFO, &fb_finfo) < 0)
    handle_error("FBIOGET_FSCREENINFO Failed");

  // Configure GE2D device
  ge2d_fd = open("/dev/ge2d", O_RDWR);

  if (ge2d_fd < 0)
    handle_error("Error opening GE2D device");

  CLEAR(ge2d_config);
  ge2d_config.src_dst_type = ALLOC_ALLOC;
  ge2d_config.alu_const_color = 0xffffffff;
  ge2d_config.src_planes[0].addr = ion_buffer.phys_addr; 
  ge2d_config.src_planes[0].w = IMG_WIDTH;
  ge2d_config.src_planes[0].h = IMG_HEIGHT;
  ge2d_config.src_format = GE2D_LITTLE_ENDIAN | GE2D_FORMAT_S8_Y;

  ge2d_config.dst_planes[0].addr = (unsigned long int) fb_finfo.smem_start;
  ge2d_config.dst_planes[0].w = fb_vinfo.xres;
  ge2d_config.dst_planes[0].h = fb_vinfo.yres;

  printf("Frambuffer Phys Addr: %#010x\n", (unsigned long int) fb_finfo.smem_start);

  switch (fb_vinfo.bits_per_pixel) {
    case 16:
      ge2d_config.dst_format = GE2D_LITTLE_ENDIAN | GE2D_FORMAT_S16_RGB_565;
      break;
    case 24:
      ge2d_config.dst_format = GE2D_LITTLE_ENDIAN | GE2D_FORMAT_S24_RGB;
      break;
    case 32:
      ge2d_config.dst_format = GE2D_LITTLE_ENDIAN | GE2D_FORMAT_S32_ARGB;
      break;
    default:
      handle_error("Framebuffer has unsupported bits per pixel");
  }

  if (xioctl(ge2d_fd, GE2D_CONFIG, &ge2d_config) < 0)
    handle_error("GE2D_CONFIG Failed");

  CLEAR(blit_rect);
  blit_rect.src1_rect.x = 0;
  blit_rect.src1_rect.y = 0;
  blit_rect.src1_rect.w = IMG_WIDTH;
  blit_rect.src1_rect.h = IMG_HEIGHT;

  blit_rect.dst_rect.x = 0;
  blit_rect.dst_rect.y = 0;
  blit_rect.dst_rect.w = fb_vinfo.xres;
  blit_rect.dst_rect.h = fb_vinfo.yres;

  if (xioctl(ge2d_fd, GE2D_STRETCHBLIT_NOALPHA, &blit_rect) < 0) 
    handle_error("GE2D blit Failed");

  if (is_fbtft(fb_dev))
    if (ioctl(fb_fd, FBTFT_UPDATE) < 0)
      handle_error("FBTFT_UPDATE Failed");

  fclose(img_file);
  free_ion_buffer(ion_fd, ion_buffer.handle);
  close(ion_fd);
  close(fb_fd);
  close(ge2d_fd);

  return EXIT_SUCCESS;
}

void handle_error(char *msg) {
  perror(msg);
  longjmp(env, 1);
}

int is_fbtft(char *fb_dev) {
  int dev_num = fb_dev[strlen(fb_dev) - 1] - '0';
  return dev_num > 1;
}

int xioctl(int fd, int request, void *arg) {
  int r;

  do {
    r = ioctl(fd, request, arg);
  } while (r == -1 && errno == EINTR);

  return r;
}

void print_ion_buffer(ion_buffer *ion_buffer) {
  printf(
      "ION Buffer:\n"
      "\tAddr: %#010x\n"
      "\tPhys Addr: %#010x\n"
      "\tLength: %d\n"
      "\tHandle: %d\n",
      ion_buffer->start, 
      ion_buffer->phys_addr, 
      ion_buffer->length,
      ion_buffer->handle);
}

void alloc_ion_buffer(int ion_fd, ion_buffer *ion_buffer, int size) {
  // ION data structures
  struct ion_allocation_data ion_alloc_data;
  struct ion_fd_data ion_data;
  struct meson_phys_data meson_phys_data;
  struct ion_custom_data ion_custom_data;

  CLEAR(ion_alloc_data);

  ion_alloc_data.len = size;

  ion_alloc_data.heap_id_mask = ION_HEAP_CARVEOUT_MASK;
  ion_alloc_data.flags = 0;
  if (xioctl(ion_fd, ION_IOC_ALLOC, &ion_alloc_data) < 0) 
    handle_error("ION_IOC_ALLOC Failed");

  CLEAR(ion_data);
  ion_data.handle = ion_alloc_data.handle;
  if (xioctl(ion_fd, ION_IOC_SHARE, &ion_data) < 0)
    handle_error("ION_IOC_SHARE Failed");

  CLEAR(meson_phys_data);
  meson_phys_data.handle = ion_data.fd;

  CLEAR(ion_custom_data);
  ion_custom_data.cmd = ION_IOC_MESON_PHYS_ADDR;
  ion_custom_data.arg = (long unsigned int)&meson_phys_data;
  if (xioctl(ion_fd, ION_IOC_CUSTOM, &ion_custom_data) < 0)
    handle_error("IOC_IOC_MESON_PHYS_ADDR Failed");

  ion_buffer->start = mmap(
      NULL,
      ion_alloc_data.len,
      PROT_READ | PROT_WRITE,
      MAP_FILE | MAP_SHARED,
      ion_data.fd,
      0);

  if (ion_buffer->start == MAP_FAILED)
    handle_error("Mapping ION memory failed");

  ion_buffer->handle = ion_alloc_data.handle;
  ion_buffer->length = ion_alloc_data.len;
  ion_buffer->phys_addr = meson_phys_data.phys_addr;

  print_ion_buffer(ion_buffer);
}

void free_ion_buffer(int ion_fd, ion_user_handle_t handle) {
  struct ion_handle_data ion_handle_data;

  printf("Freeing ION buffer with handle: %d\n", handle);

  CLEAR(ion_handle_data);
  ion_handle_data.handle = handle;

  if (xioctl(ion_fd, ION_IOC_FREE, &ion_handle_data) < 0)
    puts("ION_IOC_FREE failed");
}
