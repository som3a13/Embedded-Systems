/*
 * Main.c
 *
 * Author: Mohamed Ismail
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define SevenSegmentDelay 4

volatile struct Time
{
	unsigned char seconds_count ;
	unsigned char minutes_count ;
	unsigned char hours_count ;
};
struct Time currentTime={0,0,0};
struct Time *TimeCalc=&currentTime;

// timer flag
unsigned char incrementFlag = 0;

// Interrupt Service Routine for timer1 compare mode channel A
ISR(TIMER1_COMPA_vect)
{

	incrementFlag = 1;
}

void Timer1_CTC_Init(unsigned short tick)
{
	TCNT1 = 0; // Set Timer1 initial value to 0
	OCR1A  = tick; // Set Timer compare value to tick
	TIMSK |= (1<<OCIE1A); // Enable Timer1 Compare Interrupt for Channel A
	/* Configure timer1 control register
	 * 1. Non PWM mode FOC1A for Register A =1
	 * 2. CTC Mode WGM012 where Top value = OCR1A
	 * 3. No need for OC0
	 * 4. clock = F_CPU/1024 CS12=1 CSCS11=0 CS10=1
	 */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12);
}

// External INT0 Interrupt Service Routine
ISR(INT0_vect)
{
	TimeCalc->seconds_count = 0;
	TimeCalc->minutes_count = 0;
	TimeCalc->hours_count = 0;
}

// External INT1 Interrupt Service Routine
ISR(INT1_vect)
{
	//Stop Watch time should be paused. by making CS10 = 0 and CS12 = 0
	TCCR1B &= ~(1 << CS10) & ~(1 << CS12);
}

// External INT2 Interrupt Service Routine
ISR(INT2_vect)
{
	//Stop Watch time should be Resume. by making CS10 = 1 and CS12 = 1.
	TCCR1B |= (1<<CS10) | (1<<CS12);
}

// External INT0 configurations
void INT0_Init(void)
{

	DDRD  &= (~(1<<PD2)); // Configure INT0/PD2 as input pin
	PORTD |= (1<<PD2); // Enable internal pull up resistor
	// Trigger INT0 with the falling edge
	MCUCR &= ~(1<<ISC00);
	MCUCR |= (1<<ISC01);
	// Enable external interrupt pin INT0
	GICR  |= (1<<INT0);
}

// External INT1 configurations
void INT1_Init(void)
{

	DDRD  &= (~(1<<PD3)); // Set INT1/PD3 as input pin
	MCUCR |= (1 << ISC11) | (1 << ISC10); // Configure INT1 with the raising edge
	GICR  |= (1<<INT1); // Enable external interrupt pin INT1
}

// External INT2 configurations
void INT2_Init(void)
{
	DDRB &= (~(1<<PB2)); //Set INT2/PB2 as input pin
    PORTB|= (1<<PB2); // Enable internal pull up resistor PB2 pin
    GICR|= (1<<INT2); // Enable external interrupt pin INT2
	MCUCSR &= !(1<<ISC2); 	// Trigger INT2 with the falling edge

}

int main(void)
{

    DDRA |= 0x3F; // configure first 6 pins in PORTA as output pins
	DDRC |= 0x0F; // configure first four pins of PORTC as output pins
	// Enable the 7-Segments
	PORTA |= 0x3F;
	// initialize  them with 0 value
	PORTC &= 0xF0;
	// Enable global interrupts in MC.
	SREG  |= (1<<7);

	Timer1_CTC_Init(1000); // 1000Ms = 1sec
	INT0_Init();
	INT1_Init();
	INT2_Init();

    while(1)
    {
    	//Every timer interrupt flag
    	if(incrementFlag == 1)
    	{

    		//increment Seconds Counter
    		TimeCalc->seconds_count++;

    		if(TimeCalc->seconds_count == 60)
    		{
    			TimeCalc->seconds_count = 0;
    			TimeCalc->minutes_count++;
    		}
    		if(TimeCalc->minutes_count == 60)
    		{
    			TimeCalc->minutes_count = 0;
    			TimeCalc->hours_count++;
    		}
    		if(TimeCalc->hours_count == 24)
    		{
    			TimeCalc->hours_count = 0;
    		}
    	    // reset the flag
    	    incrementFlag = 0;
    	}
    	else
    	{
    		// Applying Multiplexing method

    		PORTA = (PORTA & 0xC0) | 0x01;
    		PORTC = (PORTC & 0xF0) | (TimeCalc->seconds_count%10);


    		_delay_ms(SevenSegmentDelay);

    		PORTA = (PORTA & 0xC0) | 0x02;
    		PORTC = (PORTC & 0xF0) | (TimeCalc->seconds_count/10);

    		_delay_ms(SevenSegmentDelay);

    		// out the number of minutes
    		PORTA = (PORTA & 0xC0) | 0x04;
    		PORTC = (PORTC & 0xF0) | (TimeCalc->minutes_count%10);

    		_delay_ms(SevenSegmentDelay);

    		PORTA = (PORTA & 0xC0) | 0x08;
    	    PORTC = (PORTC & 0xF0) | (TimeCalc->minutes_count/10);

    	    _delay_ms(SevenSegmentDelay);


    	    PORTA = (PORTA & 0xC0) | 0x10;
    	    PORTC = (PORTC & 0xF0) | (TimeCalc->hours_count%10);

    	    _delay_ms(SevenSegmentDelay);

    	    PORTA = (PORTA & 0xC0) | 0x20;
    	    PORTC = (PORTC & 0xF0) | (TimeCalc->hours_count/10);

    	    _delay_ms(SevenSegmentDelay);
    	}
    }
}
