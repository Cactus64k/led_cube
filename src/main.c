#include "chunks.h"

bool need_update		= true;
uint8_t cube_mode		= 0;

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

int main(void)
{
	TRANS_DDR	= (_BV(TRANS1_PIN) | _BV(TRANS2_PIN) | _BV(TRANS3_PIN) | _BV(TRANS4_PIN));

	SPI_DDR		= _BV(MOSI_PIN) | _BV(SCK_PIN) | _BV(SS_PIN);
	SPCR		= _BV(SPE) | _BV(MSTR);		// SPI включен в режиме мастера
	SPSR		= _BV(SPI2X);				// скорость F_CPU/2

	SPI_PORT	= SPI_PORT | _BV(SS_PIN);	// линия SS должна быть по дефолту в 1
	SPI_send_word(0x0);

	//##########################

	cube_mode	= eeprom_read_byte(EEPROM_MODE_ADDRES);

	//##########################

	cli();
	TCCR1A	= 0x0;
	TCCR1B	= _BV(WGM12) | _BV(CS12) | _BV(CS10);	// предделитель 1024, очистка таймера по прерыванию
	TIMSK1	= _BV(OCIE1A);							// прерывание по совпадению
	OCR1A	= (F_CPU/1024)/8-1;						// раз в 0.125 секунды

	//##########################

	DDRC	= DDRC & ~_BV(PC5);
	PCICR	= _BV(PCIE1);
	PCMSK1	= _BV(PCINT13);

	sei();


	LED_FRAME frame = {.qword = 0};

	while(1)
	{
		if(cube_mode == 0)
		{
			cube_self_test(&frame);
			cube_mode++;
		}
		else if(cube_mode == 1)
			cube_slow_random(&frame);
		else if(cube_mode == 2)
			cube_filing(&frame);
		else if(cube_mode == 3)
			cube_random(&frame);
		else
			cube_mode = 0;

		update_cube(&frame);
	}
}
