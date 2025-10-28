#include <avr/io.h>

int main(void)
{
	DDRB = DDRB | (1 << DDB0); // on met le bit 0 de DDRB a 1 pour que PB0 = broche de sortie
	DDRD = DDRD & ~(1 << PD2); // on met le bit a 0 pour configurer en entree
	while (1)
	{
		if (PIND & (1 << PD2)) // est ce que le bouton est relache (est ce que le bit est a 1)
			PORTB &= ~(1 << PB0); // laisse le a 0
		else //sinon si jai appuye sur le bouton
			PORTB = PORTB | (1 << PB0); // allume la led
	}
}
