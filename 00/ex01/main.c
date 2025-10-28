#include <avr/io.h>

int main(void)
{
	DDRB = DDRB | (1 << DDB0); // on met le bit 0 de DDRB a 1 pour que PB0 = broche de sortie
	PORTB = PORTB | (1 << PB0); // on met le bit 0 de PORTB a 1 pour envoyer du courant a PB0
	while (1)
	{
	}
}
