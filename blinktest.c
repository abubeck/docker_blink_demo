#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <linux/types.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include "blinkt.h"
#include <math.h>


#define NUM_PIXELS 8
void larson()
{
	unsigned int i,j;
	struct timespec start_time, now;
	int REDS[16] = {0, 0, 0, 0, 0, 16, 64, 255, 64, 16, 0, 0, 0, 0, 0, 0};
	clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);

	for(i = 0; i < 80; i++)
	{
		clock_gettime(CLOCK_MONOTONIC_RAW, &now);
		double delta = (now.tv_sec - start_time.tv_sec) * 1000000 + (now.tv_nsec - start_time.tv_nsec) / 1000; 
		int idelta = delta/1000000 * 16;;
		int offset = abs( (idelta % 16) - NUM_PIXELS);
		for(j = 0; j < NUM_PIXELS; j++)
		{
			set_pixel_uint32(j, rgb(REDS[offset + j],0,0));
		}
		
		show();

		usleep(100000);
	}
}

int main()
{
	if (start()){
		printf("Unable to start apa102\n"); 
		return 1;
	}
	larson();

	return 0;
}