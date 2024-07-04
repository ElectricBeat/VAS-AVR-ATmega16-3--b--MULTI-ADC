/*
 * ADC.c
 *
 * Created: 26-04-2024 15:37:28
 * Author : SRIDHAR
 */ 

#define F_CPU 1000000UL					/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include inbuilt defined Delay header file */
#include <stdlib.h>
#include "lcd_4_bit.h"

char String[5];
int value;
uint16_t adc_value = 0;

void ADC_Init()
{
	DDRA	=	0xF0;					/* Make ADC port as input */
	PORTA	=	0X00;
	ADCSRA	=	0xE3;					/* Enable ADC, fr/8  */
//	ADMUX	=	0xc0;					/* Vref: internal 2, ADC channel: 0 */
}

uint16_t ADC_Read(uint8_t channel_num)
{
	uint16_t adc_value = 0;
	uint8_t N0_Of_Samples = 0;
	if(channel_num<=8)

	{
		ADMUX = (0XC0|channel_num);
		_delay_us(500);
		
		while(N0_Of_Samples < 10)
		{
			adc_value = (adc_value + ADC);    // adc sample 10 times modified
			_delay_ms(2);
			N0_Of_Samples++;
		}
		adc_value = (adc_value/10);
	}
	return adc_value;
}

// int ADC_Read(char channel)
// {
// 	int Ain,AinLow;
// 	
// 	ADMUX = (0XC0|channel);				/* Set input channel to read */
// 
// 	ADCSRA |= (1<<ADSC);				/* Start conversion */
// 	while((ADCSRA&(1<<ADIF))==1);		/* Monitor end of conversion interrupt */
// //	ADCSRA |= (0<<ADSC);				/* Stop conversion */
// 	
// 	_delay_us(10);
// 	AinLow = (int)ADCL;					/* Read lower byte*/
// 	Ain = (int)ADCH*256;				/* Read higher 2 bits and Multiply with weight */
// 	Ain = Ain + AinLow;
// 	return(Ain);						/* Return digital value*/
// }

int main()
{
	LCD_Init();							/* Initialize LCD */
	ADC_Init();							/* Initialization of ADC */

	while (1)
	{
		lcd_cursor(1,0);				/* Go to 1st line*/
		LCD_String("1:");				/* write string on 1st line of LCD*/
		lcd_cursor (1,2);
		value=ADC_Read(0);				/* Read ADC channel 0 */
		divider(value);
		_delay_ms(500);

		lcd_cursor(1,8);				/* Go to 1st line*/
		LCD_String("2:");				/* write string on 1st line of LCD*/
		lcd_cursor (1,10);
		value=ADC_Read(1);				/* Read ADC channel 1 */
		divider(value);
		_delay_ms(500);
	}
}