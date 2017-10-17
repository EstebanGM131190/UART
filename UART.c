#include "UART.h"
#include "MK64F12.h"

UART_MailBoxType UART0_MailBox;

void UART0_Status_IRQHandler(){
	UART0_MailBox.flag = TRUE;			//a data has been received
	UART0_MailBox.mailBox = UART0->D; 	//the received data is stored in the mailbox
	UART_clearInterrupt();				//it runs the function to clear the mailbox
}

void UART_init(UART_ChannelType uartChannel, uint32 systemClk, UART_BaudRateType baudRate){
	UART_clockGating(uartChannel);		//selected uart clock gating enabled

	uint16 sbr = systemClk/(16*baudRate);	//sbr calculated
	uint16 brfa = 32*( (systemClk/(16*baudRate))-sbr );	//brfa calculated
	UART0->C2 &= ~(UART_C2_TE_MASK);	//uart0 transmitter disabled
	UART0->C2 &= ~(UART_C2_RE_MASK);	//uart0 receiver disabled
	UART0->BDH |= ((sbr & UART_BDH_SBR_MASK) >> 8);
	UART0->BDL |= (sbr & UART_BDL_SBR_MASK);
	UART0->C4 |= UART_C4_BRFA(brfa);	//brfa loaded in c4 register brfa field
	UART0->C2 |= UART_C2_TE_MASK;		//uart0 transmitter enabled
	UART0->C2 |= UART_C2_RE_MASK;		//uart0 receiver enabled
}

void UART0_interruptEnable(UART_ChannelType uartChannel){
	while(!(UART0->S1 & UART_S1_TC_MASK)){ //checks if there isnt anything being transmitted
		UART0->C2 |= UART_C2_RIE_MASK;	//receiver interrupt enabled
	}
}


void UART_putChar (UART_ChannelType uartChannel, uint8 character){
	switch(uartChannel){
	case UART_0:
		while(!(UART0->S1 & UART_S1_TDRE_MASK));
		UART0->D = character;						//sends the character
		break;
	case UART_1:
		if(FALSE == (UART1->S1 & UART_S1_TDRE_MASK)>>7){	//if uart1 s1 register tdre field is false,
				UART1->D = character;						//sends the character
		}
		break;
	case UART_2:
		if(FALSE == (UART2->S1 & UART_S1_TDRE_MASK)>>7){	//if uart2 s1 register tdre field is false,
				UART2->D = character;						//sends the character
		}
		break;
	case UART_3:
		if(FALSE == (UART3->S1 & UART_S1_TDRE_MASK)>>7){	//if uart3 s1 register tdre field is false,
				UART3->D = character;						//sends the character
		}
		break;
	case UART_4:
		if(FALSE == (UART4->S1 & UART_S1_TDRE_MASK)>>7){	//if uart4 s1 register tdre field is false,
				UART4->D = character;						//sends the character
		}
		break;
	case UART_5:
		if(FALSE == (UART5->S1 & UART_S1_TDRE_MASK)>>7){	//if uart5 s1 register tdre field is false,
				UART5->D = character;						//sends the character
		}
		break;
	}
}

void UART_putString(UART_ChannelType uartChannel, sint8* string){	//todo check if it works properly
	while (*string)		//while there is a char remaining to be transmitted
		  UART_putChar(uartChannel,*string++);	//calls the put char function
}

void UART_clockGating(UART_ChannelType uartChannel){
	switch(uartChannel){
	case UART_0:
		SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
		break;
	case UART_1:
		SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
		break;
	case UART_2:
		SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
		break;
	case UART_3:
		SIM->SCGC4 |= SIM_SCGC4_UART3_MASK;
		break;
	case UART_4:
		SIM->SCGC1 |= SIM_SCGC1_UART4_MASK;
		break;
	case UART_5:
		SIM->SCGC1 |= SIM_SCGC1_UART5_MASK;
		break;
	}
}

void UART_clearInterrupt(){
	UART0_MailBox.flag = FALSE;	//it clears the received data flag
	UART0_MailBox.mailBox = 0;	//it clears the mailbox
}
