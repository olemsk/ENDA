#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>   
#include <stdbool.h>  
 

struct fb_var_screeninfo screen_info;
int screensize_bytes;


int main(int argc, char *argv[])
{	
	uint16_t *screen;
	struct fb_copyarea rect;
	rect.dx=0;
	rect.dy=0;
	rect.width=320;
	rect.height=240;
	printf("TEST4\n");
	///////////////////////////// writing to framebuffer /////////////////////////////
	int descr = open("/dev/fb0", O_RDWR);
	
	lif(!descr)
	{	
		printf("open fail");
		exit(1);
	}	


	//int descr1 = open("/dev/driver-gamepad", O_RDONLY);
	
	//ssize_t temp_ c=read(descr1, &buffer, 1);
	//ssize_t temp_d=write(descr1, &awda, 1);
	

	screensize_bytes = (320*240)*screen_info.bits_per_pixel/8;
	int y;
	int x;
	 screen = (uint16_t*) mmap(NULL, screensize_bytes, PROT_READ | PROT_WRITE, MAP_SHARED, descr, 0);
	if((int)screen == MAP_FAILED)
	{
		printf("screen fail");
		exit(1);
	}	


	for( y = 0; y < 300; y++)
	{	
	for( x = 1; x < 221; x++)
	{
		screen[240*y + x] = 0xffff; 
	


	}
	}
	
	ioctl(descr, 0x4680, &rect);
/*
	screen[240*100 + 100] = 0xffff; 
	struct fb_copyarea rect;
	rect.dx=0;
	rect.dy=0;
	rect.width=320;
	rect.height=240;
	ioctl(descr, 0x4680, &rect);
*/	
	
	int temp_a=close(descr);
	//int temp_b=close(descr1);

	printf("CHICKENCHICKENCHICKENCHICKENCHICKENCHICKENCHICKEN\n");

	exit(EXIT_SUCCESS);
}
