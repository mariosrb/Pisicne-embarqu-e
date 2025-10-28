#include <avr/io.h>

int main(void)
{
	DDRB = DDRB | (1 << DDB1); // on configure PB1 comme une sortie (bit DDB1 = 1)
	unsigned long timer = 0;
	while (1)
	{
		timer = 0;
		PORTB ^= (1 << PB1);
		while (timer <= 2000000)
			timer++;
	}
}

