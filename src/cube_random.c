#include "chunks.h"

void cube_random(LED_FRAME* frame)
{
	while(1)
	{
		if(need_update == true)
		{
			random_64(&frame->qword);
			need_update = false;
		}

		if(need_break == true)
		{
			need_break = false;
			goto function_end;
		}
		update_cube(frame);
	}

	function_end:;
}


void random_64(uint64_t* num)
{
	for(uint8_t i=0; i<8; i++)			// можно за пять проходов
	{
		int r1 = rand();
		*num = (*num << 8) | (r1 & 0xFF);
	}
}
