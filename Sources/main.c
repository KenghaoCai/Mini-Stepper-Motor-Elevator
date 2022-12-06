#include "fsl_device_registers.h"

uint32_t ROT_CW = 0, ROT_CCW = 0;
static int i = 0;

int main(void)
{

	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; /*Enable Port B Clock Gate Control*/
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; /*Enable Port D Clock Gate Control*/

	PORTB_GPCLR = 0x000C0100;		//GPIO for Port B
	PORTD_GPCLR = 0x003F0100;		//GPIO for Port D

	//Configure Port D Pins 0-5 for Output;
	GPIOD_PDDR |= (1 << 0);
	GPIOD_PDDR |= (1 << 1);
	GPIOD_PDDR |= (1 << 2);
	GPIOD_PDDR |= (1 << 3);
	GPIOD_PDDR |= (1 << 4);
	GPIOD_PDDR |= (1 << 5);

	//Set PB[3:2] for input;
	GPIOB_PDDR |= (0 << 2);
	GPIOB_PDDR |= (0 << 3);

	unsigned int delay = 9000;

	while(1) {
		ROT_CW = GPIOB_PDIR & 0x04;
		ROT_CCW = GPIOB_PDIR & 0x08;

		if (ROT_CW && !ROT_CCW) {
			GPIOD_PDOR = 0x36;
			for(i = 0; i < delay; i++);
			GPIOD_PDOR = 0x35;
			for(i = 0; i < delay; i++);
			GPIOD_PDOR = 0x39;
			for(i = 0; i < delay; i++);
			GPIOD_PDOR = 0x3A;
			for(i = 0; i < delay; i++);
		}
		else if (!ROT_CW && ROT_CCW) {
			GPIOD_PDOR = 0x3A;
			for(i = 0; i < delay; i++);
			GPIOD_PDOR = 0x39;
			for(i = 0; i < delay; i++);
			GPIOD_PDOR = 0x35;
			for(i = 0; i < delay; i++);
			GPIOD_PDOR = 0x36;
			for(i = 0; i < delay; i++);
		}

	}

	return 0;
}
