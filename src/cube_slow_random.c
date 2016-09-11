#include "chunks.h"

void cube_slow_random(LED_FRAME* frame)
{
	while(1)
	{
		if(need_update == true)
		{
			frame->qword = frame->qword ^ (UINT64_C(1) << rand()%64);
			frame->qword = frame->qword ^ (UINT64_C(1) << rand()%64);
			//frame->qword = frame->qword ^ (UINT64_C(1) << rand()%64);
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


