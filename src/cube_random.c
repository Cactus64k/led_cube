#include "chunks.h"

void cube_random(LED_FRAME* frame)
{
	if(need_update == true)
	{
		random_64(&frame->qword);
		need_update = false;
	}
}


void random_64(uint64_t* num)
{
	for(uint8_t i=0; i<8; i++)			// можно за пять проходов
	{
		int r1 = rand();
		*num = (*num << 8) | (r1 & 0xFF);
	}
}
