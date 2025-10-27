#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = DDRB | (1 << DDB0); // on met le bit 0 de DDRB a 1 pour que PB0 = broche de sortie
	DDRB = DDRB | (1 << DDB1);
	DDRB = DDRB | (1 << DDB2);
	DDRB = DDRB | (1 << DDB4);

	DDRD = DDRD & ~(1 << PD2); // on met en entree les deux boutons
	DDRD = DDRD & ~(1 << PD4);

	int value = 0;

	while (1)
	{
		if (!(PIND & (1 << PD2))) // verification si jappuie
		{
			_delay_ms(200);
			value++;
			if (value > 15)
				value = 0;
			while (!(PIND & (1 << PD2)))
				_delay_ms(10);
		}
		else if (!(PIND & (1 << PD4)))
		{
			_delay_ms(200);
			value--;
			if (value < 0)
				value = 15;
			while (!(PIND & (1 << PD4)))
				_delay_ms(10);
		}
		PORTB &= ~((1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB4)); // jenleve laffichage de toutes les leds
		if (value & (1 << 0)) // je verifie une par une la valeur en bit avec un masque si vrai jaffiche
			PORTB |= (1 << PB0);
		if (value & (1 << 1))
			PORTB |= (1 << PB1);
		if (value & (1 << 2))
			PORTB |= (1 << PB2);
		if (value & (1 << 3))
			PORTB |= (1 << PB4);
	}
}
