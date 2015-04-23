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
#include "gameover.h"
//#include "efm32gg.h"

struct fb_var_screeninfo screen_info;


// int screensize_bytes;
bool restart(void);
bool direction(void);
char input_value;
time_t t;
bool play=true;
int did;

int main(int argc, char *argv[])
{	
	
	uint16_t *screen;
	struct fb_copyarea rect;
	rect.dx=0;
	rect.dy=0;
	rect.width=320;
	rect.height=240;
	///////////////////////////// writing to framebuffer /////////////////////////////
	int descr = open("/dev/fb0", O_RDWR);
	int test = sizeof(array)/sizeof(array[0]);	
	printf("lengden på array %d \n",test);	
	printf("Storleika til input value: %d \n",sizeof(input_value));
	printf("descr: %d\n", descr); 
	if(descr == -1)
	{	
		printf("open fail1\n");
		exit(1);
	}	
	
	
	did = open("/dev/gamepad", O_RDONLY);
	if(did == -1){	
		printf("open fail2\n");
		exit(1);
	} else {
		printf("Open success\n");
	}
		
	
	

	
	
	

	
	
	screen = (uint16_t*)mmap(NULL, 320*240*2, PROT_READ|PROT_WRITE, MAP_SHARED, descr, 0);
	if((void*)screen == MAP_FAILED)
	{
		printf("Screen mapping failed\n");
		exit(1);
	}	


	
	while(1){
	fake_game(descr,screen,array,hoyde,bredde);
	}
	
	
	close(descr);
	

	printf("chiken\n");

	exit(EXIT_SUCCESS);
}

void refresh_screen(int descr, uint16_t *screen){
	int i;

	struct fb_copyarea rect;
	rect.dx=0;
	rect.dy=0;
	rect.width=320;
	rect.height=240;

	for(i = 0; i < 320*240; i++){
		screen[i] = 0;
		
	}
	//ioctl(descr, 0x4680, &rect);
}

void refresh_area(uint16_t *screen, int x_pos, int y_pos, int w, int h){
	int x = 0;
	int y = 0;

	for(x = x_pos; x < x_pos+w; x++){
		for(y = y_pos; x < y_pos+h; y++){ 
			screen[320*y + x] = 0;
		}
	}
	//ioctl(descr, 0x4680, &rect);
}


void make_line(int descr, uint16_t *screen, int pos, uint16_t color, int y_start)
{	

	int gap=50;
	int y;
	
	
	for (y = 0; y < 240; y++)
	{
	if( y<y_start+gap && y>y_start)
	{
		screen[320*y + pos] = 0;
	}
	else
	{
		screen[320*y + pos] = color;
	}
	}
		
}


void make_obstacle(int descr, uint16_t *screen, int y_start, int pos)
{
	
	
	
	uint16_t colors[]={0xff00, 0x0ff0, 0x00ff};
	int i=0;
	for(i=0;i<3;i++)
	{
		
		make_line(descr, screen, pos+i*4, colors[i], y_start);
		
	
	}
		

}


int y_start_maker(time_t *t)
{
srand((unsigned) time(t));
return rand() %160;
}


void test_screen(int descr, uint16_t *screen)
{

	time_t temp;
	int ystart = y_start_maker(temp); 
	int x=315;
	for(x =305; x > 0; x--)
	{
		refresh_screen(descr, screen);
		make_obstacle(descr, screen, ystart, x);
		
	
	} 
}


void fake_game(int descr, uint16_t *screen,int array, int hoyde, int bredde)
{
	time_t temp;
	int x1, x2,x3,x4, offset1=80, offset2=160, offset3=240;
	
	x1=315;
	x2=315+offset1;
	x3=315+offset2;
	x4=315+offset3;
	struct fb_copyarea rect;
	rect.dx=0;
	rect.dy=0;
	rect.width=320;
	rect.height=240;
	
	int y=100;
	bool up=true;
	
	int ystart1 = y_start_maker(temp);
		
	usleep(300);
		
	int ystart2 = y_start_maker(temp); 
	usleep(300);
		
	int ystart3 = y_start_maker(temp);
	usleep(300);
		
	int ystart4 = y_start_maker(temp);
		
	int test;
	
	while(1)
	{
		
		
		
	
		
	
		
		
		refresh_screen(descr, screen);
		if(x1<315)
		{
		make_obstacle(descr, screen, ystart1, x1);
		if(x1==1)
		{
			x1=315;
			ystart1 = y_start_maker(temp);
			
		}
		}
		
		
		
		if(x2 < 315)
		{
		make_obstacle(descr, screen, ystart2, x2);
		if(x2==1)
		{
			x2=315;
			ystart2 = y_start_maker(temp);
			
		}
		}
		
		if(x3 < 315)
		{
		make_obstacle(descr, screen, ystart3, x3);
		if(x3==1)
		{
			x3=315;
			ystart3 = y_start_maker(temp);
		}
		}
		
		if(x4 < 315)
		{
		make_obstacle(descr, screen, ystart4, x4);
		if(x4==1)
		{
			x4=315;
			ystart4 = y_start_maker(temp);
			
		}
		
		}
		
		
		if(y> 230)
		{
			y=y-3;
		}
		
		if(y<5)
		{
			y=y+3;
		}
		
		if(direction())
		{	
			y += 2;
			test = make_square(y,descr,screen,array,hoyde,bredde);
			if(test==0)
			{
				game_over(descr,screen,array,hoyde,bredde);
				refresh_screen(descr, screen);
				ioctl(descr, 0x4680, &rect);
				break;
			}
			
			
			
		}
		if(!direction())
		{	
			y -= 2;
			test = make_square(y,descr,screen,array,hoyde,bredde);
			if(test==0)
			{
				game_over(descr,screen,array,hoyde,bredde);
				refresh_screen(descr, screen);
				ioctl(descr, 0x4680, &rect);
				break;
			}
			
			
			}
			
			
		
		
		
		ioctl(descr, 0x4680, &rect);
	
	 	x1 = x1-1;
	 	x2 = x2-1;
	 	x3 = x3-1;
	 	x4 = x4-1;
		
		
	
	}

}



int make_square(int y_pos, int descr, uint16_t *screen, int array, int hoyde, int bredde)
{


	const int x_pos = 45;
	int x, y;
	//refresh_screen(descr, screen);
	struct fb_copyarea rect;
	rect.dx=0;
	rect.dy=0;
	rect.width=320;
	rect.height=240;
	
	
	for(x=0;x<11;x++)
	{
		for(y=0; y<11;y++)
		{	
			
			if(screen[320*(y+y_pos) + (x+x_pos)] == 0x0000)
			{	
				screen[320*(y+y_pos) + (x+x_pos)] = 0xffff;
				
			}
			else if(screen[320*(y+y_pos) + (x+x_pos)] == 0xff00 || screen[320*(y+y_pos) + (x+x_pos)] == 0x0ff0 || screen[320*(y+y_pos) + (x+x_pos)] == 0x00ff)
			{
			printf("Traff hinder\n");
			return 0;
			}
		
		}
	
	}
	
	
	return 1;

}


void test_control_square(int descr, uint16_t *screen)
{
	
	
	int y=20;
	bool up=true;
	while(1)  
	{
	
		if(y> 280)
		{
			up=false;
		}
		
		if(y<20)
		{
			up=true;
		}
		
		if(up) 
		{
			make_square(y,descr,screen,array,hoyde,bredde);
			
			y++;
		}
		else  
		{
			make_square(y,descr,screen,array,hoyde,bredde);
			
			y--;
		
		}
	
	}

}

void game_over(int descr, uint16_t *screen, uint32_t *array, int hoyde, int bredde) {
	refresh_screen(descr, screen);
	play=false;
	struct fb_copyarea rect;
	rect.dx=0;
	rect.dy=0;
	rect.width=320;
	rect.height=240;
	ioctl(descr, 0x4680, &rect);
int i;
int j;
int x;
for(x=0;x<hoyde*bredde;x++) {
		
	if(array[x] < 0x7f) {
		array[x] = 0xffff;
		
	} else {
		array[x] = 0x0000;
	
	}
} 

		
for(i=0;i<bredde;i++) {
	for(j=0;j<hoyde;j++) { 
			
		screen[320*j+i] = array[i+bredde*j];
	}
}
	

ioctl(descr, 0x4680, &rect);
bool wait=true;

while(wait)
{
	if(restart())
	{
		wait = false;
		
	
	}

}
	
}


bool direction(void)
{


	ssize_t vasar = read(did, &input_value, 1);
	
	
	if((int)(input_value) == 2)
	{
		return true;
	}
	if((int)(input_value == 4))
	{
		return false;
	}

	return false;

}

bool restart(void)
{
	ssize_t vasar = read(did, &input_value, 1);
	
	if((int)(input_value) == 3)
	{
		return true;
	}
	return false;

}
