#include "chunks.h"

ISR(TIMER1_COMPA_vect)
{
	need_update = true;
}

ISR(PCINT1_vect)
{
	if((PINC & _BV(PC5)))
		cube_mode++;

	cube_mode = (cube_mode > 3)? 0: cube_mode;
	eeprom_write_byte(EEPROM_MODE_ADDRES, cube_mode);
}
