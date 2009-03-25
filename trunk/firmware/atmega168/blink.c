#include <avr/io.h>
//#include <avr/inttypes.h>
#include <util/delay.h>

//Uint16_t i;
uint16_t i;

/* Try to blink the LED on the arduino board. */
int main (void)
{
	// The arduino LED pin is Port B, Pin 5
	DDRB |= 1<<DDB5; // Set the pin to output.

	while(1)
	{
		PORTB |= 1<<PB5;  // Set the output to high.

		_delay_ms(500);

		PORTB &= ~(1<<PB5); // Set the output to low.	

		_delay_ms(500);

	}
        return 0;
}
