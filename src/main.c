#include "chunks.h"

#define MULTIPLEXING_DELAY 4.0
bool need_update = true;

int main(void)
{
	TRANS_DDR	= (_BV(TRANS1_PIN) | _BV(TRANS2_PIN) | _BV(TRANS3_PIN) | _BV(TRANS4_PIN));

	SPI_DDR		= _BV(MOSI_PIN) | _BV(SCK_PIN) | _BV(SS_PIN);
	SPCR		= _BV(SPE) | _BV(MSTR);		// SPI включен в режиме мастера
	SPSR		= _BV(SPI2X);				// скорость F_CPU/2

	SPI_PORT	= SPI_PORT | _BV(SS_PIN);	// линия SS должна быть по дефолту в 1
	SPI_send_word(0x0);

	//##########################
	ADMUX	= _BV(REFS0) | _BV(REFS1) | _BV(MUX3);					// внутренний источник на 1.1 вольт и температурный сенсор
	ADCSRA	= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);		// предделитель на 128

	//##########################
	cli();
	TCCR1A	= 0x0;
	TCCR1B	= _BV(WGM12) | _BV(CS12) | _BV(CS10);	// предделитель 1024, очистка таймера по прерыванию
	TIMSK1	= _BV(OCIE1A);							// прерывание по совпадению
	OCR1A	= (F_CPU/1024)/2-1;						// раз в пол секунды
	sei();

	self_test();
	cube_random();
}

ISR(TIMER1_COMPA_vect)
{
	need_update = true;
}

void self_test()
{
	uint8_t transystors[] = {TRANS1_PIN, TRANS2_PIN, TRANS3_PIN, TRANS4_PIN};


	for(uint8_t t=0; t<4; t++)
	{
		SPI_send_word(0xFFFF);

		TRANS_PORT = TRANS_PORT | _BV(transystors[t]);
		_delay_ms(500);
		TRANS_PORT = TRANS_PORT & ~_BV(transystors[t]);
	}

	for(uint8_t c=0; c<60; c++)
	{
		for(uint8_t t=0; t<4; t++)
		{
			SPI_send_word(0xFFFF);

			TRANS_PORT = TRANS_PORT | _BV(transystors[t]);
			_delay_ms(MULTIPLEXING_DELAY);
			TRANS_PORT = TRANS_PORT & ~_BV(transystors[t]);
		}
	}
}


void cube_random()
{
	uint8_t transystors[] = {TRANS1_PIN, TRANS2_PIN, TRANS3_PIN, TRANS4_PIN};

	typedef union LED_FRAME
	{
		uint16_t floor[4];
		uint64_t qword;
	} LED_FRAME;

	LED_FRAME frame;

	while(1)
	{
		if(need_update == true)
		{
			random_64(&frame.qword);
			need_update = false;
		}

		for(uint8_t t=0; t<4; t++)
		{
			SPI_send_word(frame.floor[t]);

			TRANS_PORT = TRANS_PORT | _BV(transystors[t]);
			_delay_ms(MULTIPLEXING_DELAY);
			TRANS_PORT = TRANS_PORT & ~_BV(transystors[t]);
		}
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

void SPI_send_word(uint16_t word)
{
	SPI_PORT = SPI_PORT & ~_BV(SS_PIN);

	SPDR = word >> 8;
	loop_until_bit_is_set(SPSR, SPIF);

	SPDR = word & 0xFF;
	loop_until_bit_is_set(SPSR, SPIF);

	SPI_PORT = SPI_PORT | _BV(SS_PIN);
}
