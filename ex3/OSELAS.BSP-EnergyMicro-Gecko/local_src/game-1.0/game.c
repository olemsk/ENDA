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
	if(descr == -1)		// Check if open is a success
	{	
		printf("open fail1\n");
		exit(1);
	}	
	
	
	did = open("/dev/gamepad", O_RDONLY);	//Open driver for input from gamepad
	if(did == -1){				//Check for open success
		printf("open fail2\n");
		exit(1);
	} else {
		printf("Open success\n");
	}
		
	
	

	
	
	

	
	
	screen = (uint16_t*)mmap(NULL, 320*240*2, PROT_READ|PROT_WRITE, MAP_SHARED, descr, 0); //Get memory location for display
	if((void*)screen == MAP_FAILED) 
	{
		printf("Screen mapping failed\n");
		exit(1);
	}	


	
	while(1){
	fake_game(descr,screen,array,hoyde,bredde);  // Starts game 
	}
	
	
	close(descr);
	

	printf("chiken\n");

	exit(EXIT_SUCCESS);
}

void refresh_screen(int descr, uint16_t *screen){	//Writes entire screen to black
	int i;

	struct fb_copyarea rect;
	rect.dx=0;
	rect.dy=0;
	rect.width=320;
	rect.height=240;

	for(i = 0; i < 320*240; i++){ //For all pixels in display 
		screen[i] = 0;	//Fill with black
		
	}
	//ioctl(descr, 0x4680, &rect);
}

void refresh_area(uint16_t *screen, int x_pos, int y_pos, int w, int h){  //Supposed to fill a smaller portion of screen with black-not functioning properly
	int x = 0;
	int y = 0;

	for(x = x_pos; x < x_pos+w; x++){
		for(y = y_pos; x < y_pos+h; y++){ 
			screen[320*y + x] = 0;
		}
	}
	//ioctl(descr, 0x4680, &rect);
}


void make_line(int descr, uint16_t *screen, int pos, uint16_t color, int y_start) //Makes a vertical line with gap, used in game
{	

	int gap=50;
	int y;
	
	
	for (y = 0; y < 240; y++)
	{
	if( y<y_start+gap && y>y_start) // Fills in gap
	{
		screen[320*y + pos] = 0;
	}
	else
	{
		screen[320*y + pos] = color;//Make line in specified color
	}
	}
		
}


void make_obstacle(int descr, uint16_t *screen, int y_start, int pos) //Makes obstacle in game-consists of three lines in different color
{
	
	
	
	uint16_t colors[]={0xff00, 0x0ff0, 0x00ff};
	int i=0;
	for(i=0;i<3;i++)
	{
		
		make_line(descr, screen, pos+i*4, colors[i], y_start); //Uses make line to make the three lines
		
	
	}
		

}


int y_start_maker(time_t *t) //Makes random variable t
{
srand((unsigned) time(t));
return rand() %160;
}


void test_screen(int descr, uint16_t *screen) //Used for testing screen, not in game
{

	time_t temp;
	int ystart = y_start_maker(temp); 
	int x=315;
	for(x =305; x > 0; x--) //Moves line over screen
	{
		refresh_screen(descr, screen);
		make_obstacle(descr, screen, ystart, x);
		
	
	} 
}


void fake_game(int descr, uint16_t *screen,int array, int hoyde, int bredde) // Final, not fake, game
{
	time_t temp;
	int x1, x2,x3,x4, offset1=80, offset2=160, offset3=240; // Four variables for four lines at a time, x1,x2,x3 and x4
	
	x1=315;			
	x2=315+offset1;		// Each line has an offset from the first line to enable game
	x3=315+offset2;
	x4=315+offset3;
	struct fb_copyarea rect;
	rect.dx=0;
	rect.dy=0;
	rect.width=320;
	rect.height=240;
	
	int y=100;
	bool up=true;
	
	int ystart1 = y_start_maker(temp);  // Gives random posistion of gap
		
	usleep(300);
		
	int ystart2 = y_start_maker(temp); 
	usleep(300);
		
	int ystart3 = y_start_maker(temp);
	usleep(300);
		
	int ystart4 = y_start_maker(temp);
		
	int test;
	
	while(1)
	{
		
		
		
	
		
	
		/////////////////////// Moves the four lines over the screen ///////////
		
		refresh_screen(descr, screen);  // Write display to black
		if(x1<315)
		{
		make_obstacle(descr, screen, ystart1, x1); //Move line
		if(x1==1) //If at end of display
		{
			x1=315; //Reset line
			ystart1 = y_start_maker(temp); //Give ned position of gap
			
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
		
		/////////////////Control figure /////////////
		
		if(y> 230) // Figure reach end of screen, top
		{
			y=y-3; // Move down three places
		}
		
		if(y<5)		// If figure reach end of display, buttom
		{
			y=y+3;
		}
		
		if(direction()) // Move up or down
		{	
			y += 2; // Move figure two plases vertically
			test = make_square(y,descr,screen,array,hoyde,bredde); // Test for game over and move figure
			if(test==0) // If game over
			{
				game_over(descr,screen,array,hoyde,bredde); // Make game over screen
				refresh_screen(descr, screen); // Write display black
				ioctl(descr, 0x4680, &rect); // Update screen buffer
				break; //Break and start over agin with game
			}
			
			
			
		} 
		if(!direction()) // Move down
		{	
			y -= 2; 
			test = make_square(y,descr,screen,array,hoyde,bredde);// Test for game over and move figure
			if(test==0)// If game over
			{
				game_over(descr,screen,array,hoyde,bredde);// Make game over screen
				refresh_screen(descr, screen); // Write display black
				ioctl(descr, 0x4680, &rect);//Break and start over agin with game
				break; //Break and start over agin with game
			}
			
			
			}
			
			
		
		
		
		ioctl(descr, 0x4680, &rect); // Update screenbuffer
		// Move lines over screen
	 	x1 = x1-1; 
	 	x2 = x2-1;
	 	x3 = x3-1;
	 	x4 = x4-1;
		
		
	
	}

}



int make_square(int y_pos, int descr, uint16_t *screen, int array, int hoyde, int bredde)  // Make figure at y_position, fixed x_position
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
			
			if(screen[320*(y+y_pos) + (x+x_pos)] == 0x0000) // If black display(not anything to interfare with)
			{	
				screen[320*(y+y_pos) + (x+x_pos)] = 0xffff; //write figure at position
				
			}
			else if(screen[320*(y+y_pos) + (x+x_pos)] == 0xff00 || screen[320*(y+y_pos) + (x+x_pos)] == 0x0ff0 || screen[320*(y+y_pos) + (x+x_pos)] == 0x00ff) // If screen already written to by obstacles:
			{
			printf("Traff hinder\n"); 
			return 0; // Enables game-over screen
			}
		
		}
	
	}
	
	
	return 1;

}


void test_control_square(int descr, uint16_t *screen) // Not used in final game
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


bool direction(void) // Check for moving figure up or down
{


	ssize_t vasar = read(did, &input_value, 1); //Read value from gamepad-driver into input_value
	
	
	if((int)(input_value) == 2) // If button 2 is pushed
	{
		return true; // Return true to move figure up
	}
	if((int)(input_value == 4))
	{
		return false; // Move figure down
	}

	return false; // Move figure down

}

bool restart(void)
{
	ssize_t vasar = read(did, &input_value, 1); // Read value from gamepad-driver into input_value
	
	if((int)(input_value) == 3) // If button SW3 is pushed:
	{
		return true; // Enable restart
	}
	return false; // Else wait for button SW3 to be pushed 

}
