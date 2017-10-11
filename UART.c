#include "UART.h"
#include "MK64F12.h"
void UART0_Status_IRQHandler(){

}


void UART_init(UART_ChannelType uartChannel, uint32 systemClk, UART_BaudRateType baudRate){

}


void UART0_interruptEnable(UART_ChannelType uartChannel){
	while(!(UART0->S1 & UART_S1_TC_MASK)){ //checa que ya no este transmitiendo nada
	       UART0->C2  |= UART_S1_RDRF_MASK;              //activa la interrupcion del receptor
	}

}


void UART_putChar (UART_ChannelType uartChannel, uint8 character){

}

