#include "chunks.h"

void cube_self_test(LED_FRAME* frame)
{
	frame->qword = 0xFFFFFFFFFFFFFFFF;

	for(uint8_t c=0; c<8;)
	{
		if(need_update == true)
		{
			c++;
			need_update = false;
		}
		update_cube(frame);
	}

}
