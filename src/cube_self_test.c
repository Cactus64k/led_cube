#include "chunks.h"

void cube_self_test(LED_FRAME* frame)
{
	frame->qword = 0xFFFFFFFFFFFFFFFF;

	for(uint8_t i=0; i<64;)
	{
		if(need_update == true)
		{
			 i++;
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
