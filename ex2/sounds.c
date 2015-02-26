#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#define C    1911
#define C1    1804
#define D    1703
#define Eb    1607
#define E    1517
#define F    1432
#define F1    1352
#define G    1276
#define Ab    1204
#define A    1136
#define Bb    1073
#define B    1012
#define c       955
#define c1      902
#define d       851
#define eb      803
#define e       758
#define f       716
#define f1      676
#define g       638
#define ab      602
#define a       568
#define bb      536
#define b       506

uint32_t TEMP = 0xFFF; // 0xFFF?

int find_sound(uint32_t inn);
void play_melody(uint32_t melody);
void play_mario(void);
void play_peer_gynt(void);
void play_smoke(void);
void play_natal(void);


int play_sound(uint32_t sound)
{

 



 if ( sound != 1000)
{

  

  for(int i = 0; i < sound; i++)
    {


    
  *DAC0_CH0DATA ^= TEMP;
  *DAC0_CH1DATA ^= TEMP;
  // for (int j=0; j < 1; j++)
  // {}
  //*DAC0_CH0DATA ^=TEMP;
  //*DAC0_CH1DATA ^=TEMP;
    
  

    }


 }  
    
  return 0;
}


int find_sound(uint32_t inn)
{
  int sound = 1000;

 

  switch(inn)
{
  /*
 case 0xFE:
   sound = 29;  //A#
 break;
  */
 case 0xFD:
   sound = 34 ; //C#
   break;
 case 0xFB:
   sound = 38 ; //D#
   break;
 case 0xF7:
   sound = 46; //F#
   break;

 case 0xEF:
   sound = 51; // G#
   break;
case 0xDF:
  sound = 58; // A#
   break;
 case 0xBF:
   sound = 69; // C#
   break;

 case 0x7F:
   sound = 77; // D#
   break;

 default:
     sound = 1000;

     return sound; 
 }
  return sound;
}








void play_melody(uint32_t inn)
{
  /*
   int mario[] = {e, e, e, c, e, g, G, c, G, E, A, B, Bb, A, G, e, g, a, f, g, e, c, d, B, c};
int ritmo_mario[] = {6, 12, 12, 6, 12, 24, 24, 18, 18, 18, 12, 12, 6, 12, 8, 8, 8, 12, 6, 12, 12, 6, 6, 6, 12};


int peergynt_m[] = {G, E, D, C, D, E, G, E, D, C, D, E, D, E,G, E, G, A, E, A, G, E, D, C};
int peergynt_r[] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 16};
 
int smoke_m[] = {E, G, A, E, G, Bb, A, E, G, A, G, E};
int smoke_r[] = {12, 12, 18, 12, 12, 6, 18, 12, 12, 18, 12, 24};
 
int natal_m[] = {G, A, G, E, G, A, G, E, c, c, A, B, B, G, A, G, A, c, B, A, G, A, G, E};
int natal_r[] = {12, 4, 8, 16, 12, 4, 8, 16, 12, 4, 16, 12, 4, 16, 12, 4, 8, 8, 8, 8, 12, 4, 8, 16};
 
 int LTS_m[] = {Bb, G, G, Bb, G, G, Bb, ,G, G, Bb, G, G, Bb, G, C, G, Bb, G, G, Bb, G, G, Bb, G, G, Bb, G, G, Bb, G, F, D, F, D, G, F, D, C, Bb, G, Bb, C, C1, C, Bb, F, D, Bb, G, F, D, C, Bb, D, C, Bb, G} ;

int LTS_r[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

*/

  switch(inn)
{
 

 case 0xFD:
   play_mario() ; 
   break;
 case 0xFB:
   play_peer_gynt() ; 
   break;
 case 0xF7:
   play_smoke();
   break;

 case 0xEF:
   play_natal();
   break;

   /*case 0xDF:
  play_LTS();
   break;
   */
 default:
   return;
 }



}




void play_mario(void)
{

int mario[] = {e, e, e, c, e, g, G, c, G, E, A, B, Bb, A, G, e, g, a, f, g, e, c, d, B, c};
int ritmo_mario[] = {6, 12, 12, 6, 12, 24, 24, 18, 18, 18, 12, 12, 6, 12, 8, 8, 8, 12, 6, 12, 12, 6, 6, 6, 12};


  
 for(int k = 0; k <  25; k++)
   {  
   int  temp= mario[k];

 for(int j =0; j < ritmo_mario[k]; j++)
   {

   if(  temp != 1000)
{
 
   for (int i=0; i < temp; i++)
  {
  //*DAC0_CH0DATA = TEMP;
  //*DAC0_CH1DATA = TEMP;
  
  *DAC0_CH0DATA ^=TEMP;
  *DAC0_CH1DATA ^=TEMP;
    }
 }
   }


 for(int x = 0; x < 155500; x++ )
{*DAC0_CH0DATA =0x00;
  *DAC0_CH1DATA =0x000;}

}
for(int i = 0; i < 600000; i++){
*DAC0_CH0DATA =0;
  *DAC0_CH1DATA =0;}

}



void play_peer_gynt(void)
{

int peergynt_m[] = {G, E, D, C, D, E, G, E, D, C, D, E, D, E,G, E, G, A, E, A, G, E, D, C};
int peergynt_r[] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 16};
 
  
 for(int k = 0; k <  25; k++)
   {  
   int  temp= peergynt_m[k];

 for(int j =0; j < peergynt_r[k]; j++)
   {

   if(  temp != 1000)
{
 
   for (int i=0; i < temp; i++)
  {
  //*DAC0_CH0DATA = TEMP;
  //*DAC0_CH1DATA = TEMP;
  
  *DAC0_CH0DATA ^=TEMP;
  *DAC0_CH1DATA ^=TEMP;
    }
 }
   }


 for(int x = 0; x < 155500; x++ )
{*DAC0_CH0DATA = 0x00;
 *DAC0_CH1DATA = 0x00;}

}
for(int i = 0; i < 600000; i++){
  *DAC0_CH0DATA = 0x00;
 *DAC0_CH1DATA = 0x00;

}
}



void play_smoke(void)
{

int smoke_m[] = {E, G, A, E, G, Bb, A, E, G, A, G, E};
int smoke_r[] = {12, 12, 18, 12, 12, 6, 18, 12, 12, 18, 12, 24};
 
  
 for(int k = 0; k <  12; k++)
   {  
   int  temp= smoke_m[k]/6;

 for(int j =0; j < smoke_r[k]*40; j++)
   {

   if(  temp != 1000)
{
 
   for (int i=0; i < temp; i++)
  {
  //*DAC0_CH0DATA = TEMP;
  //*DAC0_CH1DATA = TEMP;
  
  *DAC0_CH0DATA ^=TEMP;
  *DAC0_CH1DATA ^=TEMP;
    }
 }
   }


 for(int x = 0; x < 155500; x++ )
{}

}
for(int i = 0; i < 600000; i++){
  *DAC0_CH0DATA = 0x00;
 *DAC0_CH1DATA = 0x00;

}
}



void play_natal(void)
{

int natal_m[] = {G, A, G, E, G, A, G, E, c, c, A, B, B, G, A, G, A, c, B, A, G, A, G, E};
int natal_r[] = {12, 4, 8, 16, 12, 4, 8, 16, 12, 4, 16, 12, 4, 16, 12, 4, 8, 8, 8, 8, 12, 4, 8, 16};
 
  
 for(int k = 0; k <  24; k++)
   {  
   int  temp= natal_m[k]/6;

 for(int j =0; j < natal_r[k]*40; j++)
   {

   if(  temp != 1000)
{
 
   for (int i=0; i < temp; i++)
  {
  //*DAC0_CH0DATA = TEMP;
  //*DAC0_CH1DATA = TEMP;
  
  *DAC0_CH0DATA ^=TEMP;
  *DAC0_CH1DATA ^=TEMP;
    }
 }
   }


 for(int x = 0; x < 155500; x++ )
{}

}
for(int i = 0; i < 600000; i++){
  *DAC0_CH0DATA = 0x00;
 *DAC0_CH1DATA = 0x00;

}
}


/*
void play_LTS(void)
{

  int LTS_m[] = {Bb, G, G, Bb, G, G, Bb, ,G, G, Bb, G, G, Bb, G, C, G, Bb, G, G, Bb, G, G, Bb, G, G, Bb, G, G, Bb, G, F, D, F, D, G, F, D, C, Bb, G, Bb, C, C1, C, Bb, F, D, Bb, G, F, D, C, Bb, D, C, Bb, G};

int LTS_r[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};


  
 for(int k = 0; k <  56; k++)
   {  
   int  temp= LTS_m[k]/6;

 for(int j =0; j < LTS_r[k]*40; j++)
   {

   if(  temp != 1000)
{
 
   for (int i=0; i < temp; i++)
  {
  *DAC0_CH0DATA = TEMP;
  *DAC0_CH1DATA = TEMP;
  
  *DAC0_CH0DATA ^=TEMP;
  *DAC0_CH1DATA ^=TEMP;
    }
 }
   }


 for(int x = 0; x < 155500; x++ )
{}

}
for(int i = 0; i < 600000; i++){
  *DAC0_CH0DATA = 0x00;
 *DAC0_CH1DATA = 0x00;

}
}
*/
