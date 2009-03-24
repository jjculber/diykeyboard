#include <avr/io.h>
//#include <avr/inttypes.h>

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

		long reps = 1000;
		// Kill some time.
		for(i=0; i<reps; i++)
		{
			
		}

		PORTB &= ~(1<<PB5); // Set the output to low.	

		// Kill some time.
		for(i=0; i<reps; i++)
		{
			
		}

	}
        return 0;
}
