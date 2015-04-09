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
 



int main(int argc, char *argv[])
{	

	///////////////////////////// writing to framebuffer /////////////////////////////
	int descr = open("/dev/fb0", O_RDWR);
	//int descr1 = open("/dev/driver-gamepad", O_RDONLY);
	
	//ssize_t temp_ c=read(descr1, &buffer, 1);
	//ssize_t temp_d=write(descr1, &awda, 1);
		
	int y;
	int x;
	uint16_t *screen = mmap(0, 340*240*2, PROT_READ|PROT_WRITE, MAP_SHARED, descr, 0);
	
	for( y = 0; y < 200; y++)
	{	
	for( x = 1; x < 201; x++)
	{
		screen[240*y + x] = 0xff00; 
	


	}
	}
	struct fb_copyarea rect;
	rect.dx=0;
	rect.dy=0;
	rect.width=320;
	rect.height=240;
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
	
	//int temp_a=close(descr);
	//int temp_b=close(descr1);

	printf("CHICKENCHICKENCHICKENCHICKENCHICKENCHICKENCHICKEN\n");

	exit(EXIT_SUCCESS);
}
