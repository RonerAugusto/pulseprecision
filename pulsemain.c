/*
 * File:   pulsemain.c
 * Author: china
 *
 * Created on 27 de Julho de 2019, 22:01
 */
#define _XTAL_FREQ 12000000 
#include<stdio.h>
#include <xc.h>
#include "pulse.h"


/*********function */

void interrupt testtime();
void config_pins();


/*******variable*****/



void main(void) {


    config_pins();
   


    while (1) 
    {



    }




}


void config_pins()
{
     CMCON = 0x07; //disable comparator 
    OPTION_REG = 0x80   ; //disable pull upsri  and pre scale   1:2    0b1000 0000

    /************IOS map ********/

    TRISBbits.TRISB0 = 0x01; // just pin RB0 as input 
    TRISBbits.TRISB7 = 0x00; // pin RB7 as output
    TRISAbits.TRISA0 = 0x00; //just pin RA0 as output 


    /*******start of pins */
    PORTBbits.RB0 = 0x00; // start RB0 in 0 volts
    PORTBbits.RB7 = 0x00; // start RB7 in 0 volts
    PORTAbits.RA0 = 0x00; // start in zero volts




    /**************register timer0 interrupt *********/

    // overflow= prescale* 2^8 * machinecycle 
    // 10us  = 2 * TMR0* [1/(12E6 / 4)]      machinecycle = 333E-9 ;
    // TMR0= [ 10us /(2 * 333E-9]
    //TMR0= 15   in (15 - 2^8)= 241  the counter start in 241 and finished in 256;
    // 241 decimal in equal  0xf1 in hexadecimal


    INTCONbits.T0IE = 0x01; // tmr0 over flow interrupt enable
    INTCONbits.T0IF = 0x00; //clear flag over flow 
    TMR0 = 0xf1;            // value to make 10us

    /********register external interrupt*/
    INTCONbits.PEIE = 0x01; //peripheral interrupt enable 
    INTCONbits.GIE = 0x01; //global interrupt enable 
  
    
    
}

void interrupt testtime() 
{


    /*******timer interruption********/

    if (INTCONbits.T0IF == 0x01) 
    {



            INTCONbits.T0IF = 0x00; //clear flag of interruption 
           
            PORTAbits.RA0 = ~PORTAbits.RA0; //invert the state 
            
            TMR0 = 0xf1;
                

            
    }
    

}


    



    

