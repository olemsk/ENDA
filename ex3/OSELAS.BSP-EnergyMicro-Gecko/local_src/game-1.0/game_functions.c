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
 

Define screen_size 40





void make_line(uint16_t *screen, int pos)
{
	int i = 240;

	while(i > 0)
	{
	screen[240*pos + i] = 0xffff;
	i++;	
		
	}
}

void make_block(uint16_t *screen, int pos_x, int pos_y )
{


	for( int i = pos_x; i < pos_x+4 ; i++)
	{
	for( int k = pos_y; k < pos_y+4 ; k++)
	{
		screen[240*i + k] =0xffff;

	
	}
	}


}


void pos_control()
{


}



void refresh_screen(void)
{
	ioctl(descr, 0x4680, &rect);
}

void clear_screen(void)
{

	
	for( int i = 0; i < 240 ; i++)
	{
	for( int k = 0; k < 320 ; k++)
	{
		screen[240*i + k] =0x0;

	
	}
	}

}





