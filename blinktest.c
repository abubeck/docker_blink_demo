#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <linux/types.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include "blinkt.h"


void simple_routine()
{
	printf("Running simple routine\n");
    set_pixel_uint32(0, rgb(0,120,0));
    show();
	usleep(1000000);
	set_pixel_uint32(0, rgb(120,0,0));
	show();
	usleep(1000000);
	clear();
	show();
	usleep(1000000);
	stop();
}

#define NUM_PIXELS 8
void complex_routine()
{
	unsigned int i,j;
	time_t start_time, now;
	int REDS[16] = {0, 0, 0, 0, 0, 16, 64, 255, 64, 16, 0, 0, 0, 0, 0, 0};
	time(&start_time);

	for(i = 0; i < 40; i++)
	{
		time(&now);
		double delta = difftime(now, start_time) * 16;
		//int delta = ((int)time(NULL) - start_time) * 16;
		//printf("delta=%f\n", delta);
		int offset = i; //abs((delta % 16) - NUM_PIXELS);
		//printf("offset=%d\n", offset);
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
	complex_routine();
	//simple_routine();
	

	return 0;
}