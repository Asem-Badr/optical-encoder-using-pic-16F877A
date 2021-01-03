/*
 * File:   main.c
 * Author: Asem Badr
 * This project uses pic 16f877A 
 * It calculates the rps of a motor using an optical encoder and displays it on PORTC as a binary number
 * Created on September 16, 2020, 12:09 AM
 */


#include <xc.h>
#include "config.h"
#include <stdint.h>

#define _XTAL_FREQ 4000000
#define num_of_sluts 30
void Timer1_preloading(int time);
void Timer1_init(void);
void Interrupt_init(void);
void Timer0_init(void);
unsigned char counter=0;
unsigned char overflows=0 ;
/********************  main  ***********************/
void main(void) {
    TRISB=0;
    TRISC=0;
    PORTC=0;
    PORTB=0;
    RB0=0;
    Interrupt_init();
    Timer1_init();
    Timer1_preloading(15536);
    Timer0_init();
    while (1) {
 
    }
    return;
}
/********************  main  ***********************/
void Timer1_preloading(int time)
{
    TMR1=15536; 
}
void Interrupt_init(void)
{
    PEIE=1;
    GIE=1;
}
void Timer1_init(void)
{
    //clock source selection  
    TMR1CS=0;
    //timer pre-scaler configurations
    T1CKPS0=0;
    T1CKPS1=0;
    //timer enable
    TMR1ON=1;
    //timer interrupt enable 
    TMR1IE=1;
    //timer interrupt flag initialize
    TMR1IF = 0;
    //peripheral and global interrupt enable
   
}
void Timer0_init(void)
{
    //timer value initialization
    TMR0 = 0;
    //timer interrupt enable 
    TMR0IE = 1;
    //clock source selection
    T0CS = 1;
    //positive edge
    T0SE = 0;
    //timer pre-scaler configurations
    PSA = 0;
    PS2 = 0;
    PS1 = 0;
    PS0 = 0;
    //timer interrupt flag initialization
    TMR0IF = 0;
    
}
void __interrupt()ISR(void){
    if(TMR1IF)
    {
        Timer1_preloading(15536);
        counter++;
        if (counter==5)
        {
            RB0=~RB0;
            counter=0;
            PORTC = TMR0 << 1;//*2 because of the 2cycle sync
            TMR0 = 0;
            overflows = 0;
        }
    
        TMR1IF=0;
    }
    if(TMR0IF)
    {
        TMR0IF = 0;
        overflows ++; 
        TMR0 = 0 ;
    }
}
