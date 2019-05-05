#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "tiny5351.h"
void InitADC()
{
 ADMUX |= (1<<REFS0);
 //set prescaller to 128 and enable ADC 
 ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);    
}
#if defined(__AVR_ATmega328P__) 

uint16_t ReadADC(uint8_t ADCchannel)
{
 //select ADC channel with safety mask
 ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
 //single conversion mode
 ADCSRA |= (1<<ADSC);
 // wait until ADC conversion is complete
 while( ADCSRA & (1<<ADSC) );
 return ADC;
}
#else
//ADC on ATTINY13
#define REF_AVCC (0<<REFS0) // reference = AVCC
// select the corresponding channel 0~N and set reference
uint16_t ReadADC(uint8_t ADCchannel) 
{
   ADMUX = REF_AVCC | ADCchannel;  // set reference and channel
   ADMUX |= _BV(ADLAR); // left adjust of ADC result
   ADCSRA |= (1<<ADSC);         // start conversion  
   while(ADCSRA & (1<<ADSC)){}  // wait for conversion complete  
   return ADC;
}
#endif

void setup() {
  // put your setup code here, to run once:	
  #if defined(__AVR_ATmega328P__) 	
  //set adc input pin
  DDRC &=~(1<<PC3); //input onPC3  ie A3 on Arduino Uno with Atmega328p
  #else
  DDRB &=~(1<<PB3); // For attiny it is PB3 for adc input
  #endif
  
  uint32_t frequency=10000000UL;
  uint16_t t;
  uint16_t prv_t = 0;
  InitADC();
  sei();
}
void loop() {
  // put your main code here, to run repeatedly:
    
	t = ReadADC(3);
    if (prv_t != t) {
      si5351_freq(frequency+(t<<7), 0); //multiply adc value with 128 0-1023 becomes 0-(1023*128)
      prv_t = t;
      }
}
