#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR (TIMER1_COMPA_vect) 
{ 
}

void UARTInit( void ) {
	UBRRL = 103;
	UBRRH = 0;
	UCSRA = 0;
	UCSRB = 0b00011000;
	UCSRC = 0b10000110;
}

void sendUART ( unsigned char c ) {
	while( !(UCSRA & (1 << UDRE))) {
	}
	UDR = c;
}

unsigned char readUART( void ) {
	while(!(UCSRA & (1 << RXC ))) {
	}
	return UDR; 
}	

void greenHighlight( void ) {
	PORTD &= 0b01111111;//зажигаем зеленый
}

void yellowHighlight( void ) {
	PORTD &= 0b10111111;//зажигаем желтый
}

void greenUnhighlight( void ) {
	PORTD |= 0b10000000;//зажигаем зеленый
}

void yellowUnhighlight( void ) {
	PORTD |= 0b01000000;//зажигаем желтый
}
 

void init(void) {
	DDRA = 0b000011111;
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0b11000000;

	PORTA |= 0b10000;

	greenHighlight();
	yellowUnhighlight();
}

void clkHigh() {
	PORTA |= 0b100000;
}

void clkLow() {
	PORTA &= 0b011111;
}

void clkPulse(void) {
	
	clkHigh();
	_delay_ms(50);
	clkLow();
	_delay_ms(50);
}

int main( void ) {
	unsigned char i=0;
	init();
	while(1) {
		clkPulse();
		clkPulse();
		clkPulse();
		clkPulse();
		clkPulse();

		i = PINB;
		i &=0b1111111;

		if(i == 0x00) 
			greenHighlight();
		else {
			yellowHighlight();
			greenUnhighlight();
		}		
	}
	return 0;
}
