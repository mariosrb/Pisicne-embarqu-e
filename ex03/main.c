#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = DDRB | (1 << DDB0); // on met le bit 0 de DDRB a 1 pour que PB0 = broche de sortie
	DDRD = DDRD & ~(1 << PD2); // on met le bit a 0 pour configurer en entree

	int	led = 0; // variable utile pour savoir si jai appuye ou non

	while (1)
	{
		if (!(PIND & (1 << PD2))) // si jappuie
		{
			led = !led; // je change la valeur de led
			if (led)
				PORTB = PORTB | (1 << PB0);
			else
				PORTB &= ~(1 << PB0);
			while (!(PIND & (1 << PD2)))
				_delay_ms(10);
		}
	}
}
