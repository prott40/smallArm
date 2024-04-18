// backhoe controls
// Preston Rottinghuas
#include <msp430.h>

// A10 and A8 configuration for JOYSTICK
void config_ADC_JOYSTICK()
{
    // Enable Pins
    // Horizontal: P9.2 --> A10 to Digital
    P9SEL1 |= BIT2;
    P9SEL0 |= BIT2;
    // Vertical: P8.7 --> A4 to Digital
    P8SEL1 |= BIT7;
    P8SEL0 |= BIT7;
    ADC12CTL0 |= ADC12ON; //ADC enable
    ADC12CTL0 &= ~ADC12ENC; //Turn-off ENC
    //Setup ADC12CTL0
    //ADC12SHT0: control the number of cycles
    ADC12CTL0 |= ADC12ON | ADC12SHT1_10;
    //Setup ADC12CTL1
    // ADC12SHS: configure ADC12SC bit as the trigger signal
    // ADC12SHP ADC12 Sample/Hold Pulse Mode
    // ADC12DIV ADC12 Clock Divider Select: 7
    // ADC12SSEL ADC12 Clock Source Select: 0
    ADC12CTL1 = ADC12SHS_0 | ADC12SHP | ADC12DIV_7 | ADC12SSEL_0;
    ADC12CTL1 |= ADC12CONSEQ_1;
    //Setup ADC12CTL2
    // ADC12RES: 12-bit resolution
    // ADC12DF: unsigned bin-format
    ADC12CTL2 |= ADC12ENC;
    //Setup ADC12MCTL0
    // ADC12VRSEL: VR+=AVCC, VR-=AVSS
    // ADC12INCH: Channel A10
    ADC12MCTL0 |= ADC12INCH_10 | ADC12VRSEL_0;
    // ADC12INCH: Channel A4
    ADC12MCTL1 |= ADC12INCH_4 | ADC12VRSEL_0 | ADC12EOS;
    ADC12CTL0 |= ADC12ENC; //Turn-on ENC at the end
    return;
}

void pushbottomleft(){
    P1DIR &= ~BIT1; //clears port 1
    P1REN |= BIT1;  //sets as pullup
    P1OUT |= BIT1;  //sets as input

    P1IFG &=~ BIT1; //clears port 1 flag
    P1IE |= BIT1;   //enables port 1 flag
    __enable_interrupt(); //Enable maskable IRQs

}
void pushbottomright(){
    P1DIR &= ~BIT2; //clears port 2
    P1REN |= BIT2;  //sets as pullup
    P1OUT |= BIT2;  //sets as input

    P1IFG &=~ BIT2; //clears port 2 flag
    P1IE |= BIT2;   //enables port 2 flag
    __enable_interrupt(); //Enable maskable IRQs

}
void pushbottom(){
	
}
int pwmonjoyvertset(){

        TB0CTL |= TACLR;          // Clears clock value
        TB0CTL |= TASSEL__BCLK;   // Sets clock to 32KHz
        TB0CTL |= MC__CONTINUOUS; // Sets clock to continuous mode
        TB0CTL |= MC1;          // Sets to a pullup
        TB0CCR0 = 0x8000;        // Sets counter to 4096    may need to be 7FFF
        TB0CTL |= TAIE;           // enables our interrupt flag
        TB0CTL &= ~TAIFG;         // clears interrupt flag

        __enable_interrupt(); //Enable maskable IRQs
}

int pwmonjoyhorset(){

        TB1CTL |= TACLR;          // Clears clock value
        TB1CTL |= TASSEL__BCLK;   // Sets clock to 32KHz
        TB1CTL |= MC__CONTINUOUS; // Sets clock to continuous mode
        TB1CTL |= MC1;          // Sets to a pullup
        TB1CCR0 = 0x8000;        // Sets the on time
         TA0CCR1 = 0x8000;       // Sets teh off time
		TB1CTL |= TAIE;           // enables our interrupt flag
        TB1CTL &= ~TAIFG;         // clears interrupt flag

        __enable_interrupt(); //Enable maskable IRQs
}
/*
ask why when enabling pins ont he booster pack extra pins do you need
to use the J befor ethe pin call


*/

int main(void)
{

    P1DIR |= BIT0;
    P9DIR |= BIT7;
    P1OUT &= ~BIT0;
    P9OUT &= ~BIT7;


    WDTCTL = WDTPW | WDTHOLD; //Stop Watchdog Timer
    PM5CTL0 &= ~LOCKLPM5; //Enable GPIO
}