#include <avr/io.h>
#include <util/delay.h>

/*
	Je veux allumer 0.5s et eteidnre 0.5s
	Mon microprocesseur = 16MHz = 16 000000hz
	16 / 4 = 62 500
	1 / 62500 = 0.000016s
	Etant donne que moi jai besoin de 0.5 s --> 0.5 / 0.000016 = 31250
	Lorsque time 1 a compter 31250 = 0.5s 1tcik se fait en 0.000016 seconde
	65535 - 31250 = 34286 --> si je debute a cette valeur, une fois que jaurai atteint 65535
	ca veut dire que 31250 sera atteint et en plus overflow donc le drapeau overflow sera leve
	et je peux utiliser son signal pour changer le bit de la LED.
*/

int main(void)
{
	DDRB = DDRB | (1 << DDB1); // on configure PB1 comme une sortie (bit DDB1 = 1)
	while (1)
	{}
}
