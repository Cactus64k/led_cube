#include "chunks.h"

void cube_filing(LED_FRAME* frame)
{
	uint8_t cube[64];
	frame->qword = 0;

	for(uint8_t i=0; i<64; i++)
		cube[i] = i+1;


	for(uint8_t i=0; i<64; i++)
	{
		int r = rand()%64;

		uint8_t tmp = cube[i];
		cube[i] = cube[r];
		cube[r] = tmp;
	}

	frame->qword = 0;

	for(uint8_t i=0; i<64;)
	{
		if(need_update == true)
		{
			frame->qword = frame->qword | (UINT64_C(1) << cube[i]);

			need_update = false;
			i++;
		}

		update_cube(frame);
	}

	for(uint8_t i=0; i<64;)
	{
		if(need_update == true)
		{
			frame->qword = frame->qword & ~(UINT64_C(1) << cube[i]);

			need_update = false;
			i++;
		}

		update_cube(frame);
	}
}
