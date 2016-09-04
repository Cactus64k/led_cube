#include "chunks.h"

void update_cube(LED_FRAME* frame)
{
	uint8_t transystors[] = {TRANS1_PIN, TRANS2_PIN, TRANS3_PIN, TRANS4_PIN};

	for(uint8_t t=0; t<4; t++)
	{
		SPI_send_word(frame->floor[t]);

		TRANS_PORT = TRANS_PORT | _BV(transystors[t]);
		_delay_ms(MULTIPLEXING_DELAY);
		TRANS_PORT = TRANS_PORT & ~_BV(transystors[t]);
	}
}
