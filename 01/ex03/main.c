#include <avr/io.h>
#include <util/delay.h>

/*
	Je veux allumer 0.5s et eteidnre 0.5s
	Mon microprocesseur = 16MHz = 16 000000hz
	16 / 256 = 62 500 --> maitenant il fait 62500 ticks par seconde
	1 / 62500 = 0.000016s
	Etant donne que moi jai besoin de 0.5 s --> 0.5 / 0.000016 = 31250
	Lorsque time 1 a compter 31250 = 0.5s 1tcik se fait en 0.000016 seconde
	65535 - 31250 = 34286 --> si je debute a cette valeur, une fois que jaurai atteint 65535
	ca veut dire que 31250 sera atteint et en plus overflow donc le drapeau overflow sera leve
	et je peux utiliser son signal pour changer le bit de la LED.

	======================================================

	Ou alors je set le drapeau a 31250 et des que jatteint cette valeur, je leve le drapeau, change le bit
	de la led et je remet le timer a 0.
	Pour cela je dois utiliser le mode CTC --> registre TCCR1A et TCCR1B bit3 WGM12 (page 140 141)
	CTC --> Clear time on compare match reset sur une comparaison

	======================================================

	On va utiliser le mode PWM (Pulse width Modulation) pour creer un signal de pulse et faire clignoter, varier la led.
	En mode CTC OCRn = TOP (p 129) --- En mode PWM ICR1 = TOP (p 133) et OCRn = genere un signal PWM sur la sortie OCRn
	On utilise ICR1 car le TOP est fixe (31250) donc on libere OCRn pour envoyer le signal PWM p133 end
	cf tableau 16-4 p141-142 --> le fast PWM 14 est le meilleur car on utilise un top ICR1 top fixe (WGM13 - WGM12 - WGM11)
*/

int main(void)
{
	DDRB = DDRB | (1 << DDB1); // on configure PB1 comme une sortie (bit DDB1 = 1)
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1A |= (1 << COM1A1) | (1 << WGM11); // Mode PWM non inverse : OCR1A = HIGH tant que TCNT1 < OCR1A et LOW quand TCNT1 >= OCR1A p.140 + bit de WGM11 a 1
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS12); // On active le bit 4 WGM13 et WGM12 cf tableau p622 + prescaler 256
	ICR1 = 62500;
	OCR1A = 6250; // On veut 10% donc 31250 * 0.1 = 3125

	uint64_t status_sw1 = 0;
	uint64_t old_status_sw1 = 0;
	uint64_t old_status_sw2 = 0;
	uint64_t status_sw2 = 0;

	while (1)
	{
		status_sw1 = !(PIND & (1 << PD2)); // il rencoie 0 quand le bouton est appuye du coup linverse = 1 sil est appuye
		status_sw2 = !(PIND & (1 << PD4));
		if (status_sw1 && !old_status_sw1) // Verification si jappuie et que jetais pas deja en train dappuyer
		{
			OCR1A += ICR1 / 10; // jajoute 10% de ICR1 a OCR1A
			if (OCR1A > ICR1) // si je depasse 100% je reviens a 100%
				OCR1A = ICR1;
		}
		if (status_sw2 && !old_status_sw2) // Verification si jappuie
		{
			OCR1A -= ICR1 / 10; // j'enleve 10 % de ICR1 a OCR1A
			if (OCR1A > ICR1 / 10) // si OCR1A devient < 10% je le remet a 10%
				OCR1A = ICR1 / 10;
		}
		old_status_sw1 = status_sw1; // je met a jour les anciens status pour la prochaine boucle
		old_status_sw2 = status_sw2;
		_delay_ms(50);
	}
}
