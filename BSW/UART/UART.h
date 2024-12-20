/****************************************************************************
 * Title                 :   ADC Application
 * Filename              :   adc_app.h
 * Author                :   Eslam Akrm
 * Origin Date           :   06/07/2012
 * Version               :   1.0.0
 * Compiler              :   /ti-cgt-arm_20.2.5.LTS
 * Target                :   TM4C123GH6PM
 * Notes                 :   None
 *****************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
 *
 *    Date    Software Version    Initials   Description
 *  08/17/13    XXXXXXXXXXX         JWB      Interface Created.
 *
 *****************************************************************************/
/** \file UART.h
 *  \brief This module contains continuous tasks.
 *

 */

#ifndef UART_UART_H_
#define UART_UART_H_


/******************************************************************************
 * Configuration Constants
 *******************************************************************************/



/******************************************************************************
 * Preprocessor Constants
 *******************************************************************************/
/**
 * This constant is
 */


/******************************************************************************
 * Macros
 *******************************************************************************/
//replace #defines with constants



typedef enum UART_BAUD_RATE_e{
    BAUD_RATE_9600       =      0x00002580,
    BAUD_RATE_19200      =      0x00004B00,
    BAUD_RATE_38400      =      0x00009600,
    BAUD_RATE_57600      =      0x0000E100,
    BAUD_RATE_115200     =      0x0001C200,
    BAUD_RATE_num
}UART_BAUD_RATE_t;

#define UART_PARITY_EVEN           UART_CONFIG_PAR_EVEN
#define UART_PARITY_ODD            UART_CONFIG_PAR_ODD
#define UART_PARITY_NONE           UART_CONFIG_PAR_NONE

#define UART_WORD_LENGTH_5         UART_CONFIG_WLEN_5
#define UART_WORD_LENGTH_6         UART_CONFIG_WLEN_6
#define UART_WORD_LENGTH_7         UART_CONFIG_WLEN_7
#define UART_WORD_LENGTH_8         UART_CONFIG_WLEN_8

#define UART_STOP_BIT_1            UART_CONFIG_STOP_ONE
#define UART_STOP_BIT_2            UART_CONFIG_STOP_TWO

// just naturally incrementing index, should be unsigned integer (positive natural number)

typedef enum UART_num_e{
       UART0_num          =        0x00000000,
       UART1_num          =        0x00000001,
       UART2_num          =        0x00000002,
       UART3_num          =        0x00000003,
       UART4_num          =        0x00000004,
       UART5_num          =        0x00000005,
       UART6_num          =        0x00000006,
       UART7_num          =        0x00000007,
       UART_num
}UART_num_t;

#define UART_FIFO_DIS              0x00000000
#define UART_FIFO_EN               0x00000001

#define UART_FIFO_TX_LEVEL_1_8     UART_FIFO_TX1_8
#define UART_FIFO_TX_LEVEL_1_4     UART_FIFO_TX2_8
#define UART_FIFO_TX_LEVEL_1_2     UART_FIFO_TX4_8
#define UART_FIFO_TX_LEVEL_3_4     UART_FIFO_TX6_8
#define UART_FIFO_TX_LEVEL_7_8     UART_FIFO_TX7_8

#define UART_FIFO_RX_LEVEL_1_8     UART_FIFO_RX1_8
#define UART_FIFO_RX_LEVEL_1_4     UART_FIFO_RX2_8
#define UART_FIFO_RX_LEVEL_1_2     UART_FIFO_RX4_8
#define UART_FIFO_RX_LEVEL_3_4     UART_FIFO_RX6_8
#define UART_FIFO_RX_LEVEL_7_8     UART_FIFO_RX7_8




/******************************************************************************
 * Typedefs
 *******************************************************************************/
/*
 *   UART structure that holds the uart data used to configure and handle the UART functions.
 *   UART_t structure holds
 *          {
 *          1 -  baudRate     = (BAUD_RATE_9600 , BAUD_RATE_19200 ,BAUD_RATE_38400,BAUD_RATE_57600 or BAUD_RATE_115200)
 *          2 -  dataSize     = (UART_WORD_LENGTH_5,UART_WORD_LENGTH_6,UART_WORD_LENGTH_7 or UART_WORD_LENGTH_8)
 *          3 -  parity       = (UART_PARITY_EVEN,UART_PARITY_ODD or UART_PARITY_NONE )
 *          4 -  stopBits     = (UART_STOP_BIT_1 or UART_STOP_BIT_2) use UART_STOP_BIT_2 in noisy environments
 *          5 -  uartNumber   = (UART0 , UART1 , UART2 , UART3 , UART4 , UART5 , UART6 or UART7)
 *          6 -  fifoEn       = (UART_FIFO_DIS or UART_FIFO_EN)
 *          7 - fifo_TX_level =
 *          8 - fifo_RX_level =
 *          9 - receive_ISR   = pointer the the Application ISR for receive interrupt
 *          }
 */
typedef struct UART_s
{
    UART_BAUD_RATE_t baudRate;
    UART_BAUD_RATE_t parity  ;
    uint32_t dataSize        ;
    uint32_t stopBits        ;
    UART_num_t uartNumber    ;
}UART_t;


typedef enum uartErrors_e
{
    UARTERROR_FRAMING_error = 8,
    UARTERROR_PARITY_error ,
    UARTERROR_BREAK_error ,
    UARTERROR_OVERRUN_error ,
    UARTERROR_BUFFER_overWrite_error,
    UARTERROR_BUFFER_EMPTY,
    UARTERROR_DATA_ok,
    UARTERROR_allocationFailed,
    UARTERROR_initiatedBefore,
    UARTERROR_initSuccess,
    UARTERROR_uninitialized
}uartErrors_t;



/******************************************************************************
 * Variables
 *******************************************************************************/



/******************************************************************************
 * Function Prototypes
 *******************************************************************************/
uartErrors_t UART_init(UART_num_t uartNum);
void uartSendBlocking(UART_num_t,uint8_t);
bool uartSendNonBlocking(UART_num_t,uint8_t);

void uartReceive_Blocking(UART_num_t uartNumber,int32_t *ret_byte);
void uartReceive_nonBlocking(UART_num_t uartNumber,int32_t *ret_byte);

uartErrors_t UART_getByte(UART_num_t uartNumber,uint8_t *ret_data); //take uart number as input
uartErrors_t UART_setByte(UART_num_t uartNumber,uint8_t data); //take uart number as input
uartErrors_t UART_peekByte(UART_num_t uartNumber,uint32_t,uint8_t *ret_data); //take uart number as input
void UART_get_TX_len(UART_num_t, uint32_t *len);
void UART_get_RX_len(UART_num_t, uint32_t *len);
/* used to clear the uart hardware buffer and move its data to the circular buffer */
void UARTS_cyclic5ms();
void UARTS_clear(UART_num_t num);
#endif /* UART_UART_H_ */
