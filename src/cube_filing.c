#include "chunks.h"

void cube_filing(LED_FRAME* frame)
{
	static uint8_t cube[64];
	static uint8_t ittr = 0;

	if(ittr == 0)
	{
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
		ittr++;
	}
	else if(ittr > 128)
		ittr = 0;
	else
	{
		if(need_update == true)
		{
			if(ittr < 64)
				frame->qword = frame->qword ^ (UINT64_C(1) << cube[ittr]);
			else
				frame->qword = frame->qword ^ (UINT64_C(1) << cube[ittr-64]);

			need_update = false;
			ittr++;
		}

		update_cube(frame);
	}
}
