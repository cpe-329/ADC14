/*
 * uart.c
 * 
 * Danica Fujiwara & Spencer Shaw
 * 
 * CPE 329-17/18 Spring 2019
 */

#include <stdint.h>

#include "msp.h"
#include "led.h"
#include "delay.h"
#include "my_msp.h"
#include "uart.h"

inline void uart_init(){
    // Configure UART pins
    //P1->SEL0 |= BIT2 | BIT3;                // set 2-UART pin as secondary function
    has_new = FALSE;
    new_char = 0;
}

inline void uart_write(unsigned char c){
    while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG)){}
    EUSCI_A0->TXBUF = c;
    while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG)){}
}

void uart_write_int(unsigned int acc){
    rgb_set(RGB_RED);
    if(acc >= 10){
        uart_write_int(acc/10);
    }
    uart_write((uint8_t)((acc%10) + '0'));
}

void uart_write_nl(){
    uart_write('\n');
    uart_write(0xD);
}

unsigned int uart_get_int(){
    int accumulator = 0;
    new_char = 255;
    rgb_set(RGB_BLUE);
    while(new_char != ESCAPE_VAL){
        if (has_new){
            if (new_char == ESCAPE_VAL){
                break;
            } else if (new_char >= '0' && new_char <= '9'){
                accumulator = (10 * accumulator) + (new_char - '0');
            }
            has_new = FALSE;
        }
    }
    has_new = FALSE;
    new_char = 0;
    return accumulator;
}
