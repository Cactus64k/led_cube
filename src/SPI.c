#include "chunks.h"

void SPI_send_word(uint16_t word)
{
	SPI_PORT = SPI_PORT & ~_BV(SS_PIN);

	SPDR = word >> 8;
	loop_until_bit_is_set(SPSR, SPIF);

	SPDR = word & 0xFF;
	loop_until_bit_is_set(SPSR, SPIF);

	SPI_PORT = SPI_PORT | _BV(SS_PIN);
}
