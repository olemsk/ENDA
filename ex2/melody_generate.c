#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"



//length = sizeof(array)/sizeof(array[0]);

int length_tone(int  inn[])
{
  int ret = 0;
  length= sizeof(inn)/sizeof(inn[0]);
  for (int i = 0; i < length; i++)
    {
      ret+= inn[i];
    }

  return ret;
}



int length_sound(int inn[]}
{
  int ret = 0;
  length= sizeof(inn)/sizeof(inn[0]);
  for (int i = 0; i < length; i++)
    {
      ret+= inn[i];
    }

  return ret;
}


int** createArray(int m, int n)
{
  int* values = calloc(m*n, sizeof(int));
  int** rows = malloc(n*sizeof(int*));
  for(int i=0; i<n; ++i)
    {
      rows[i]= values + i*m;

    }
  return rows;

}
