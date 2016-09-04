#include "chunks.h"

void cube_self_test(LED_FRAME* frame)
{
	frame->qword = 0xFFFFFFFFFFFFFFFF;

	for(uint8_t c=0; c<60; c++)
		update_cube(frame);
}
