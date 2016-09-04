#include "chunks.h"

bool need_update = true;
void test_pwm();

int main(void)
{
	TRANS_DDR	= (_BV(TRANS1_PIN) | _BV(TRANS2_PIN) | _BV(TRANS3_PIN) | _BV(TRANS4_PIN));

	SPI_DDR		= _BV(MOSI_PIN) | _BV(SCK_PIN) | _BV(SS_PIN);
	SPCR		= _BV(SPE) | _BV(MSTR);		// SPI включен в режиме мастера
	SPSR		= _BV(SPI2X);				// скорость F_CPU/2

	SPI_PORT	= SPI_PORT | _BV(SS_PIN);	// линия SS должна быть по дефолту в 1
	SPI_send_word(0x0);

	//##########################
	cli();
	TCCR1A	= 0x0;
	TCCR1B	= _BV(WGM12) | _BV(CS12) | _BV(CS10);	// предделитель 1024, очистка таймера по прерыванию
	TIMSK1	= _BV(OCIE1A);							// прерывание по совпадению
	OCR1A	= (F_CPU/1024)/8-1;						// раз в 0.25 секунды
	sei();



	uint8_t mode = 0;
	LED_FRAME frame = {.qword = 0};

	while(1)
	{
		switch (mode)
		{
			case 0:
			{
				cube_self_test(&frame);
				mode++;
				break;
			}
			case 1:
			{
				cube_slow_random(&frame);
				break;
			}
			case 2:
			{
				cube_filing(&frame);
				break;
			}
			case 3:
			{
				cube_random(&frame);
				break;
			}
		}
	}
}

void test_pwm()
{
	uint8_t transystors[] = {TRANS1_PIN, TRANS2_PIN, TRANS3_PIN, TRANS4_PIN};

	uint8_t led_state[16];

	for(uint8_t i=0; i<16; i++)
		led_state[i] = 0;

	uint8_t pos = 0;
	for(uint8_t i=0; i<16; i++)
	{
		led_state[i] = pos;
		pos +=16;
	}

	led_state[0] = 0;

	TRANS_PORT = TRANS_PORT | _BV(transystors[2]);

	uint16_t frame = 0;

	while(1)
	{
		for(uint8_t i=0; i<255; i++)
		{
			for(uint8_t f=0; f<16; f++)
			{
				if(led_state[f] > i)
					frame = frame | (UINT16_C(1) << f);
				else
					frame = frame & ~(UINT16_C(1) << f);
			}

			SPI_send_word(frame);

//			for(uint8_t t=0; t<4; t++)
//			{
//				TRANS_PORT = TRANS_PORT | _BV(transystors[t]);
//				//_delay_ms(MULTIPLEXING_DELAY);
//				TRANS_PORT = TRANS_PORT & ~_BV(transystors[t]);
//			}
		}
	}
}

ISR(TIMER1_COMPA_vect)
{
	need_update = true;
}

