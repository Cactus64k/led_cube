#include "chunks.h"

void cube_slow_random(LED_FRAME* frame)
{
	if(need_update == true)
	{
		frame->qword = frame->qword ^ (UINT64_C(1) << rand()%64);
		frame->qword = frame->qword ^ (UINT64_C(1) << rand()%64);
		//frame->qword = frame->qword ^ (UINT64_C(1) << rand()%64);
		need_update = false;
	}

	update_cube(frame);
}
