#ifndef CHUNKS_H_
	#define CHUNKS_H_

	#ifndef FCPU
		#define F_CPU 16000000UL
	#endif

	#ifndef DEVICE
		#define DEVICE atmega325p
	#endif

	#ifndef __AVR_ATmega328P__
		#define __AVR_ATmega328P__
	#endif

	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdint.h>
	#include <stdbool.h>
	#include <stdlib.h>
	#include <avr/interrupt.h>
	#include <avr/eeprom.h>

	#define SPI_PORT	PORTB
	#define SPI_DDR		DDRB
	#define SS_PIN		PB2
	#define MOSI_PIN	PB3
	#define MISO_PIN	PB4
	#define SCK_PIN		PB5

	#define TRANS_PORT	PORTD
	#define TRANS_DDR	DDRD
	#define TRANS1_PIN	PD2
	#define TRANS2_PIN	PD3
	#define TRANS3_PIN	PD4
	#define TRANS4_PIN	PD5

	#define MULTIPLEXING_DELAY 4.0

	#define EEPROM_MODE_ADDRES ((uint8_t*)0)

	typedef union LED_FRAME
	{
		uint16_t floor[4];
		uint64_t qword;
	} LED_FRAME;

	extern bool need_update;
	extern bool need_break;
	extern uint8_t cube_mode;

	void SPI_send_word(uint16_t word);
	void update_cube(LED_FRAME* frame);
	void random_64(uint64_t* num);
	void cube_self_test(LED_FRAME* frame);
	void cube_random(LED_FRAME* frame);
	void cube_filing(LED_FRAME* frame);
	void cube_slow_random(LED_FRAME* frame);

#endif /* CHUNKS_H_ */
