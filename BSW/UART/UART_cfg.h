/*******************************************************************************
 * Title                 :   UART Driver
 * Module                :   UART
 * Filename              :   UART_cfg.h
 * Author                :   Mohamed Taha
 * Origin Date           :   12/23/2021
 * Version               :   1.0.0
 * Compiler              :   Texas Instruments v20.2.5 LTS
 * Target                :   TM4C123GH6PM
 * Notes                 :   None
 *******************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
 *
 *    Date    Software Version    Initials   Description
 *  12/23/21       1.0.0            MT      Module Created.
 *
*****************************************************************************/

#ifndef UART_UART_CFG_H_
#define UART_UART_CFG_H_

/******************************************************************************
 * Preprocessor Macros (Definitions and static Configurations)
 *******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros (Functions)
*******************************************************************************/

/******************************************************************************
 * User-defined Types
 *******************************************************************************/

/******************************************************************************
* Extern for Public Global Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/



#define USED_UARTS_NUM 8




//number of used uarts
typedef struct UART_cfg_e
{
    const uint8_t uartNumber       ;
    const UART_BAUD_RATE_t baudRate        ;
    const uint32_t parity          ;
    const uint32_t dataSize        ;
    const uint32_t stopBits        ;
    cirBuffer_t * uart_TxCirBuff;
    cirBuffer_t * uart_RxCirBuff;
    uartErrors_t error       ;//save the last state of the uart
}UART_cfg_t;

UART_cfg_t uarts_data[USED_UARTS_NUM] = {
{.uartNumber = UART0_num,.baudRate = BAUD_RATE_9600,.parity = UART_PARITY_NONE,.dataSize = UART_WORD_LENGTH_8,.stopBits = UART_STOP_BIT_1,NULL,NULL,UARTERROR_uninitialized},
{.uartNumber = UART1_num,.baudRate = BAUD_RATE_9600,.parity = UART_PARITY_NONE,.dataSize = UART_WORD_LENGTH_8,.stopBits = UART_STOP_BIT_1,NULL,NULL,UARTERROR_uninitialized},
{.uartNumber = UART2_num,.baudRate = BAUD_RATE_9600,.parity = UART_PARITY_NONE,.dataSize = UART_WORD_LENGTH_8,.stopBits = UART_STOP_BIT_1,NULL,NULL,UARTERROR_uninitialized},
{.uartNumber = UART3_num,.baudRate = BAUD_RATE_9600,.parity = UART_PARITY_NONE,.dataSize = UART_WORD_LENGTH_8,.stopBits = UART_STOP_BIT_1,NULL,NULL,UARTERROR_uninitialized},
{.uartNumber = UART4_num,.baudRate = BAUD_RATE_9600,.parity = UART_PARITY_NONE,.dataSize = UART_WORD_LENGTH_8,.stopBits = UART_STOP_BIT_1,NULL,NULL,UARTERROR_uninitialized},
{.uartNumber = UART5_num,.baudRate = BAUD_RATE_9600,.parity = UART_PARITY_NONE,.dataSize = UART_WORD_LENGTH_8,.stopBits = UART_STOP_BIT_1,NULL,NULL,UARTERROR_uninitialized},
{.uartNumber = UART6_num,.baudRate = BAUD_RATE_9600,.parity = UART_PARITY_NONE,.dataSize = UART_WORD_LENGTH_8,.stopBits = UART_STOP_BIT_1,NULL,NULL,UARTERROR_uninitialized},
{.uartNumber = UART7_num,.baudRate = BAUD_RATE_9600,.parity = UART_PARITY_NONE,.dataSize = UART_WORD_LENGTH_8,.stopBits = UART_STOP_BIT_1,NULL,NULL,UARTERROR_uninitialized}
};


static volatile UART_State_t UART_State;
#endif /* UART_UART_CFG_H_ */

/*** End of File **************************************************************/
