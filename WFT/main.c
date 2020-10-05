/*
 * WFT.c
 *
 * Created: 02-10-2020 11:55:36
 * Author : Karthik
 */ 
#define F_CPU	16000000
#include <avr/io.h>
#include <util/delay.h>
#include "Headers/main.h"
#include "GLCD_LIB/u8g2.h"

u8g2_t u8g2;


#define P_CPU_NS (1000000000UL / F_CPU)


#define P_CPU_NS (1000000000UL / F_CPU)
uint8_t u8x8_gpio_and_delay_template(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	uint8_t cycles;
	switch(msg)
	{
		case U8X8_MSG_GPIO_AND_DELAY_INIT:	// called once during init phase of u8g2/u8x8
			DDRB = 0xFF;
			DDRD = 0xFF;
		break;							// can be used to setup pins
		case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
		break;
		case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
			#define CALL_CYCLES 26UL
			#define CALC_CYCLES 4UL
			#define RETURN_CYCLES 4UL
			#define CYCLES_PER_LOOP 4UL

			cycles = (100UL * arg_int) / (P_CPU_NS * CYCLES_PER_LOOP);

			if(cycles > CALL_CYCLES + RETURN_CYCLES + CALC_CYCLES)
			break;

			__asm__ __volatile__ (
			"1: sbiw %0,1" "\n\t" // 2 cycles
			"brne 1b" : "=w" (cycles) : "0" (cycles) // 2 cycles
			);
		break;
		case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
			for(int i=0 ; i < arg_int ; i++)
			_delay_us(10);
		break;
		case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
				for(int i=0 ; i < arg_int ; i++)
				_delay_ms(1);
		break;
		case U8X8_MSG_DELAY_I2C:				// arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
		break;							// arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
		case U8X8_MSG_GPIO_D0:				// D0 or SPI clock pin: Output level in arg_int
			if(arg_int)
			{
				PORTA |= (1<<0);
			}
			else
			{
				PORTA &= ~(1<<0);
			}
		//case U8X8_MSG_GPIO_SPI_CLOCK:
		break;
		case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
					if(arg_int)
					{
						PORTA |= (1<<1);
					}
					else
					{
						PORTA &= ~(1<<1);
					}
		//case U8X8_MSG_GPIO_SPI_DATA:
		break;
		case U8X8_MSG_GPIO_D2:				// D2 pin: Output level in arg_int
					if(arg_int)
					{
						PORTA |= (1<<2);
					}
					else
					{
						PORTA &= ~(1<<2);
					}
		break;
		case U8X8_MSG_GPIO_D3:				// D3 pin: Output level in arg_int
					if(arg_int)
					{
						PORTA |= (1<<3);
					}
					else
					{
						PORTA &= ~(1<<3);
					}
		break;
		case U8X8_MSG_GPIO_D4:				// D4 pin: Output level in arg_int
					if(arg_int)
					{
						PORTA |= (1<<4);
					}
					else
					{
						PORTA &= ~(1<<4);
					}
		break;
		case U8X8_MSG_GPIO_D5:				// D5 pin: Output level in arg_int
					if(arg_int)
					{
						PORTA |= (1<<5);
					}
					else
					{
						PORTA &= ~(1<<5);
					}
		break;
		case U8X8_MSG_GPIO_D6:				// D6 pin: Output level in arg_int
					if(arg_int)
					{
						PORTA |= (1<<6);
					}
					else
					{
						PORTA &= ~(1<<6);
					}
		break;
		case U8X8_MSG_GPIO_D7:				// D7 pin: Output level in arg_int
					if(arg_int)
					{
						PORTA |= (1<<7);
					}
					else
					{
						PORTA &= ~(1<<7);
					}
		break;
		case U8X8_MSG_GPIO_E:				// E/WR pin: Output level in arg_int
					if(arg_int)
					{
						PORTD |= (1<<0);
					}
					else
					{
						PORTD &= ~(1<<0);
					}
		break;
		case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
					//if(arg_int)
					//{
						//PORTD |= (1<<1);
					//}
					//else
					//{
						//PORTD &= ~(1<<1);
					//}
		break;
		case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
					if(arg_int)
					{
						PORTD |= (1<<2);
					}
					else
					{
						PORTD &= ~(1<<2);
					}
		break;
		case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
		break;
		case U8X8_MSG_GPIO_CS1:				// CS1 (chip select) pin: Output level in arg_int
					if(arg_int)
					{
						PORTD |= (1<<3);
					}
					else
					{
						PORTD &= ~(1<<3);
					}
		break;
		case U8X8_MSG_GPIO_CS2:				// CS2 (chip select) pin: Output level in arg_int
					if(arg_int)
					{
						PORTD |= (1<<4);
					}
					else
					{
						PORTD &= ~(1<<4);
					}
		break;
		case U8X8_MSG_GPIO_I2C_CLOCK:		// arg_int=0: Output low at I2C clock pin
		break;							// arg_int=1: Input dir with pullup high for I2C clock pin
		case U8X8_MSG_GPIO_I2C_DATA:			// arg_int=0: Output low at I2C data pin
		break;							// arg_int=1: Input dir with pullup high for I2C data pin
		case U8X8_MSG_GPIO_MENU_SELECT:
		u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
		break;
		case U8X8_MSG_GPIO_MENU_NEXT:
		u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
		break;
		case U8X8_MSG_GPIO_MENU_PREV:
		u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
		break;
		case U8X8_MSG_GPIO_MENU_HOME:
		u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
		break;
		default:
		u8x8_SetGPIOResult(u8x8, 1);			// default return value
		break;
	}
	return 1;
}


int main(void)
{
	GPIO_INIT();
	u8g2_Setup_ks0108_128x64_f(&u8g2,U8G2_R0,&u8x8_byte_ks0108,&u8x8_gpio_and_delay_template);
	u8g2_InitDisplay(&u8g2);
	//u8g2_SetPowerSave(&u8g2, 0);
	u8g2_ClearBuffer(&u8g2);
	u8g2_SetFont(&u8g2, u8g2_font_t0_18_tr);
	u8g2_DrawStr(&u8g2, 0, 18, "Hello ");
	u8g2_SendBuffer(&u8g2);
	_delay_ms(1000);
	uint16_t cnt = 0;
    while (1) 
    {
		char buffer[20] = {0};
		sprintf(buffer,"Counter = %d",cnt);
		u8g2_ClearBuffer(&u8g2);
		u8g2_SetFont(&u8g2, u8g2_font_t0_18_tr);
		u8g2_DrawStr(&u8g2, 0, 18, buffer);
		u8g2_SendBuffer(&u8g2);
		cnt++;
		 _delay_ms(200);
    }
}


void GPIO_INIT(void)
{
	DDRB = 0xFF;
	DDRD = 0xFF;
}

