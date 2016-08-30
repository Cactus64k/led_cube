#ifndef CHUNKS_H_
	#define CHUNKS_H_

	#define F_CPU 16000000UL
	#define DEVICE atmega328p

	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdint.h>
	#include <stdbool.h>
	#include <stdlib.h>
	#include <avr/interrupt.h>

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

	typedef union LED_FRAME
	{
		uint16_t floor[4];
		uint64_t qword;
	} LED_FRAME;

	void SPI_send_word(uint16_t word);
	void update_cube(LED_FRAME* frame);
	void random_64(uint64_t* num);
	void self_test();
	void cube_random();
	void cube_filing();
	void cube_slow_random();

#endif /* CHUNKS_H_ */
