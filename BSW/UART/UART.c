#define __UART__
/*******************************************************************************
 * Title                 :   UART Initialization
 * Filename              :   UART.c
 * Author                :   Eslam Akrm
 * Origin Date           :   19/12/2021
 * Version               :   1.0.0
 * Compiler              :   /ti-cgt-arm_20.2.5.LTS
 * Target                :   TM4C123GH6PM
 * Notes                 :   None
 *******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
 *
 *    Date    Software Version    Initials   Description
 *  XX/XX/XX    XXXXXXXXXXX         JWB      Module Created.
 *
 *******************************************************************************/
/** \file UART.c
 * \brief This module contains the
 */
/******************************************************************************
 * Includes
 *******************************************************************************/

/* standard libraries */
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


/* tivaWare libraries  */
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"

/* local includes */
#include "SERVICES/CIRCULAR_BUFFER/CIR_buffer.h"

#include "UART_private.h"
#include "UART.h"
#include "UART_cfg.h"


/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/
/* constant array holding SYSCTLPERUART base address needed to initialize the UART system clock
 * input = number of the UART(0->7)
 * */
const uint32_t uart_get_sysctlPerUart[8]=
{
 SYSCTL_PERIPH_UART0,SYSCTL_PERIPH_UART1,SYSCTL_PERIPH_UART2,SYSCTL_PERIPH_UART3,SYSCTL_PERIPH_UART4,SYSCTL_PERIPH_UART5,SYSCTL_PERIPH_UART6,SYSCTL_PERIPH_UART7
};

/* constant array holding UART base address needed to initialize the UART
 * input = number of the UART(0->7)
 * */
const uint32_t uart_get_baseAddress[8]=
{
 UART0_BASE,UART1_BASE,UART2_BASE,UART3_BASE,UART4_BASE,UART5_BASE,UART6_BASE,UART7_BASE
};

/* constant array holding UART base address needed to initialize the UART
 * input = number of the UART(0->7)
 * */
const uint32_t uart_get_sysctlPerGpio[8]=
{
 SYSCTL_PERIPH_GPIOA,SYSCTL_PERIPH_GPIOB,SYSCTL_PERIPH_GPIOD,SYSCTL_PERIPH_GPIOC,SYSCTL_PERIPH_GPIOC,SYSCTL_PERIPH_GPIOE,SYSCTL_PERIPH_GPIOD,SYSCTL_PERIPH_GPIOE
};


/* constant array holding GPIO base address needed to initialize the GPIO pins that mapped to the UART needed
 * input = number of the UART(0->7)
 * */
const uint32_t uart_get_GPIO_BASE_ADDRESS[8]=
{
 GPIO_PORTA_BASE,GPIO_PORTB_BASE,GPIO_PORTD_BASE,GPIO_PORTC_BASE,GPIO_PORTC_BASE,GPIO_PORTE_BASE,GPIO_PORTD_BASE,GPIO_PORTE_BASE
};

/* constant array holding GPIO TX PIN needed to initialize the alternative function for the TX pin
 * input = number of the UART(0->7)
 * */
const uint32_t uart_get_GPIO_TX_PIN[8]=
{
 GPIO_PA1_U0TX, GPIO_PB1_U1TX,  GPIO_PD7_U2TX,GPIO_PC7_U3TX,GPIO_PC5_U4TX,GPIO_PE5_U5TX,GPIO_PD5_U6TX,GPIO_PE1_U7TX

};

/* constant array holding GPIO RX PIN needed to initialize the alternative function for the TX pin
 * input = number of the UART(0->7)
 *
 * */
const uint32_t uart_get_GPIO_RX_PIN[8]=
{
 GPIO_PA0_U0RX,GPIO_PB0_U1RX,GPIO_PD6_U2RX,GPIO_PC6_U3RX,GPIO_PC4_U4RX,GPIO_PE4_U5RX,GPIO_PD4_U6RX,GPIO_PE0_U7RX
};

/* constant array holding GPIO TX PIN needed to enable the TX PIN as output
 * input = number of the UART(0->7)
 *
 * */
const uint32_t uart_get_GPIO_PIN_A[8]=
{
 GPIO_PIN_0,GPIO_PIN_0,GPIO_PIN_6,GPIO_PIN_6,GPIO_PIN_4,GPIO_PIN_4,GPIO_PIN_4,GPIO_PIN_0
};

/* constant array holding GPIO RX PIN needed to enable the RX PIN as output
 * input = number of the UART(0->7)
 * */
const uint32_t uart_get_GPIO_PIN_B[8]=
{
 GPIO_PIN_1,GPIO_PIN_1,GPIO_PIN_7,GPIO_PIN_7,GPIO_PIN_5,GPIO_PIN_5,GPIO_PIN_5,GPIO_PIN_1
};

/* constant array holding UART INT address needed to enable the global UART interrupt for UARTX
 * input = number of the UART(0->7)
 * */
const uint32_t uart_get_UART_INT[8]=
{
 INT_UART0,INT_UART1,INT_UART2,INT_UART3,INT_UART4,INT_UART5,INT_UART6,INT_UART7
};
/**
 *Doxygen tag for documenting variables and constants
 */

/******************************************************************************
 * Module Preprocessor Macros
 *******************************************************************************/

/******************************************************************************
 * Module Typedefs
 *******************************************************************************/

/******************************************************************************
 * Module Variable Definitions
 *******************************************************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/
/******************************************************************************/



/******************************************************************************
 * Function name : uartX_ISR
 * Parameters (in): None
 * Parameters (in/out): None
 * Parameters (out): None
 * Function description :
 *               This function is the function that are registered to the UART ISR (that is called when the masked interrupt is triggered)
 *               This function calls the user's UART handler function back (to enable the application layer to write the code that will be enabled when the masked interrupt is triggered)
 *               receive_ISR : is the call back function that the application will pass to the UART_t
 *               after calling the application ISR we clear the interrupt source flag to prevent nesting
 *
 * return value : None
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  Dec 28, 2021        1.0.0         Eslam Akrm   Module Created.
 *
 * Notes : None
 *******************************************************************************/
void uart0_ISR(void)
{
    handle_ISR(UART0_BASE);
}
void uart1_ISR(void)
{
    handle_ISR(UART1_BASE);
}
void uart2_ISR(void)
{
    handle_ISR(UART2_BASE);
}
void uart3_ISR(void)
{
    handle_ISR(UART3_BASE);
}
void uart4_ISR(void)
{
    handle_ISR(UART4_BASE);
}
void uart5_ISR(void)
{
    handle_ISR(UART5_BASE);
}
void uart6_ISR(void)
{
    handle_ISR(UART6_BASE);
}
void uart7_ISR(void)
{
    handle_ISR(UART7_BASE);
}

/*************** END OF FUNCTIONS ***************************************************************************/






/******************************************************************************
 * Function name : uart_init
 * Parameters (in): UART_num_t : uart number
 * Parameters (in/out): None
 * Parameters (out): None
 * Function description : This function is used to initialize the UART
 * return value : uartErrors_t : the type of the error occurred with initialization
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  Dec 28, 2021        1.0.0         Eslam Akrm       Module Created.
 *
 * Notes : None
 *******************************************************************************/
uartErrors_t UART_init(UART_num_t uartNum)
{

    // Enable the UARTX module.
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /* get the UARTX data (
     * 1 - SYSCTLPERUART base address
     * 2 - UART base address
     * 3 - GPIO SYSCTL clock base address which is mapped to the UARTX
     * 4 - GPIO base address
     * 5 - GPIO PINA number
     * 6 - GPIO PINA number
     * 7 - GPIO TX PIN
     * 8 - GPIO RX PIN
     *  )
     *
     *
     *    */

    uint8_t uartNumIndex;

    get_uartData_index(uartNum,&uartNumIndex);

    if(uarts_data[uartNumIndex].uart_TxCirBuff == NULL){ // module was not initialized before (Cannot reinitialize)

        uarts_data[uartNumIndex].uart_TxCirBuff = (cirBuffer_t *)malloc(sizeof(cirBuffer_t));

        if(uarts_data[uartNumIndex].uart_TxCirBuff == NULL)
        {
            uarts_data[uartNumIndex].error = UARTERROR_allocationFailed;
            return UARTERROR_allocationFailed;
        }

        uarts_data[uartNumIndex].uart_RxCirBuff = (cirBuffer_t *)malloc(sizeof(cirBuffer_t));

        if(uarts_data[uartNumIndex].uart_RxCirBuff == NULL)
        {
            uarts_data[uartNumIndex].error = UARTERROR_allocationFailed;
            return UARTERROR_allocationFailed;
        }

        cirBuffer_ctor(uarts_data[uartNumIndex].uart_TxCirBuff);
        cirBuffer_ctor(uarts_data[uartNumIndex].uart_RxCirBuff);


        /////////////////////////////////////////////////////////////////////////////////////////////////////

        // Enable the UARTX module.
        SysCtlPeripheralEnable(uart_get_sysctlPerUart[uartNum]);

        // Wait for the UARTX module to be ready.
        while(!SysCtlPeripheralReady(uart_get_sysctlPerUart[uartNum]))
        {
        }

        /* Initialize the UART. Set the baud rate, number of data bits, turn off
         parity, number of stop bits, and stick mode. The UART is enabled by the
         function call.
         */
        UARTConfigSetExpClk(uart_get_baseAddress[uartNum], SysCtlClockGet(), uarts_data[uartNumIndex].baudRate,
                            (uarts_data[uartNumIndex].dataSize | uarts_data[uartNumIndex].stopBits |
                                    uarts_data[uartNumIndex].parity));


        /* enable or disable the fifo upon the Application request */

        UARTFIFOEnable(uart_get_baseAddress[uartNum]); /* enable FIFO  */

        UARTFIFOLevelSet(uart_get_baseAddress[uartNum],                /* enable interrupt generation on fifo_TX_level and fifo_RX_level */
                         UART_FIFO_TX_LEVEL_1_8,
                         UART_FIFO_RX_LEVEL_1_4);


        /* enable GPIO port which UARTX mapped to  */
        SysCtlPeripheralEnable(uart_get_sysctlPerGpio[uartNum]);

        /*special case for uart2 (unlock PD7)*/
        if(uartNum == 2)
        {
            GPIOUnlockPin(GPIO_PORTD_BASE,
                          GPIO_PIN_7);
        }


        GPIOPinTypeUART(uart_get_GPIO_BASE_ADDRESS[uartNum], uart_get_GPIO_PIN_A[uartNum] | uart_get_GPIO_PIN_B[uartNum]);   /* enable alternate function of the PINA , PINB */
        /* configure TX and RX pins */
        GPIOPinConfigure(uart_get_GPIO_RX_PIN[uartNum]);
        GPIOPinConfigure(uart_get_GPIO_TX_PIN[uartNum]);

        /* check if there is a call back function for the receive ISR */

        UARTIntRegister(uart_get_baseAddress[uartNum], UART_ISR[uartNum]); /* Registers an interrupt handler for a UART interrupt.  */
        UARTIntEnable(uart_get_baseAddress[uartNum] , UART_INT_RX | UART_INT_TX); /* enable receive interrupt */

        IntEnable(uart_get_UART_INT[uartNum]); /* enable UART global interrupt */

    } //  // module was not initialized before (Cannot reinitialize)
    else
    {
        uarts_data[uartNumIndex].error = UARTERROR_initiatedBefore;
        return UARTERROR_initiatedBefore;
    }
    uarts_data[uartNumIndex].error = UARTERROR_initSuccess;
    return UARTERROR_initSuccess;

}



/* Function : uartSendBlocking(uint8_t uartNumber,uint8_t data)
 *
 * \Description:This function sends the character data to the transmit FIFO for the specified port. If there is
                no space available in the transmit FIFO, this function waits until there is space available before
                returning.
 *
 *
 * \input :
 *                 1 - uint8_t uartNumber   = (UART0 , UART1 , UART2 , UART3 , UART4 , UART5 , UART6 or UART7)
 *                 2 - uint8_t data         = char to be sent to via the UART
 *
 *
 *
 * \return       None.
 *
 * \Example:
 * \code
 *    uartSendBlocking(UART0,'A');
 * \endcode
 *******************************************************************************/
void uartSendBlocking(UART_num_t uartNumber,uint8_t data)
{
    /* get the UART base address */
    UARTCharPut(uart_get_baseAddress[uartNumber],data);
}



/* Function : uartSendNonBlocking(uint8_t uartNumber,uint8_t data)
 *
 * \Description : This function writes the character ucData to the transmit FIFO for the specified port. This
                 function does not block, so if there is no space available, then a false is returned and the
                 application must retry the function later.
 *
 * input :
 *                 1 - uint8_t uartNumber   = (UART0 , UART1 , UART2 , UART3 , UART4 , UART5 , UART6 or UART7)
 *                 2 - uint8_t data         = char to be sent to via the UART
 *
 *
 *
 * \return       bool : True if the data has been sent successfully
 *                      False if no space in the FIFO.
 *
 * \Example:
 * \code
 *    uartSendNonBlocking(UART0,'A');
 * \endcode
 *******************************************************************************/
bool uartSendNonBlocking(UART_num_t uartNumber,uint8_t data)
{
    /* get the UART base address */
    return UARTCharPutNonBlocking(uart_get_baseAddress[uartNumber],data);
}

/* Function : uartReceive_Blocking(uint8_t uartNumber)
 *
 * \Description  : This function gets a character from the receive FIFO for the specified port. If there are no
 *                 characters available, this function waits until a character is received before returning.
 *
 * \input :
 *                 1 - uint8_t uartNumber   = (UART0 , UART1 , UART2 , UART3 , UART4 , UART5 , UART6 or UART7)
 *                 2 - uint8_t data         = char to be sent to via the UART
 *
 *
 *
 * \return  :    NONE
 *
 * \Example :
 * \code
 *   uint32_t returnedDate = uartReceive_Blocking(UART0);
 * \endcode
 *******************************************************************************/
void uartReceive_Blocking(UART_num_t uartNumber,int32_t *ret_byte)
{
    /* get the UART base address */
    *ret_byte = UARTCharGet(uart_get_baseAddress[uartNumber]);
}



/* Function : uartReceive_nonBlocking(uint8_t uartNumber)
 *
 * \Description  : This function gets a character from the receive FIFO for the specified port.
 *
 * \ inputs :
 *                 1 - uint8_t uartNumber   = (UART0 , UART1 , UART2 , UART3 , UART4 , UART5 , UART6 or UART7)
 *                 2 - uint8_t data         = char to be sent to via the UART
 *
 * \return  :    uint32_t :  Returns the character read from the specified port, cast as a int32_t. A -1 is returned if there
                            are no characters present in the receive FIFO. The UARTCharsAvail() function should be called
                            before attempting to call this function.

 * \Example :
 * \code
 *   uint32_t returnedDate = uartReceive_nonBlocking(UART0);
 * \endcode
 *******************************************************************************/
void uartReceive_nonBlocking(UART_num_t uartNumber,int32_t *ret_byte)
{
    *ret_byte = UARTCharGetNonBlocking(uart_get_baseAddress[uartNumber]);
}



uartErrors_t UART_getByte(UART_num_t uartNumber,uint8_t *ret_data) //take UART number as input
{
    cBuffErrors_t bufferError;
    uartErrors_t uartError = UARTERROR_DATA_ok;
    int32_t data;
    uint8_t uartNumIndex;
     get_uartData_index(uartNumber,&uartNumIndex);
    bufferError = cirBuffer_read(uarts_data[uartNumIndex].uart_RxCirBuff,&data);
    if(bufferError == cBuffErrors_NoData)
    {
        uartError = UARTERROR_BUFFER_EMPTY;
        *ret_data = 0;
    }
    else
    {
        *ret_data = (uint8_t)(data & 0x000000FF);
        if(CHECK_FAIL(data,UARTERROR_OVERRUN_error))
        {
            uartError = UARTERROR_OVERRUN_error;
        }
        else if(CHECK_FAIL(data,UARTERROR_BREAK_error))
        {
            uartError = UARTERROR_BREAK_error;
        }
        else if(CHECK_FAIL(data,UARTERROR_PARITY_error))
        {
            uartError = UARTERROR_PARITY_error;
        }
        else if(CHECK_FAIL(data,UARTERROR_FRAMING_error))
        {
            uartError = UARTERROR_FRAMING_error;
        }
        else
        {
            uartError = UARTERROR_DATA_ok;
        }
    }
    uarts_data[uartNumIndex].error = uartError;
    return uartError;
}


uartErrors_t UART_peekByte(UART_num_t uartNumber,uint32_t index,uint8_t *ret_data) //take uart number as input
{
    cBuffErrors_t bufferError;
    uartErrors_t uartError = UARTERROR_DATA_ok;
    int32_t data;
    uint8_t uartNumIndex;
    get_uartData_index(uartNumber,&uartNumIndex);
    bufferError = cirBuffer_peek(uarts_data[uartNumIndex].uart_RxCirBuff,index,&data);
    if(bufferError == cBuffErrors_NoData)
    {
        uartError = UARTERROR_BUFFER_EMPTY;
        *ret_data = 0;
    }
    else
    {
        *ret_data = (uint8_t)(data & 0x000000FF);
        if(CHECK_FAIL(data,UARTERROR_OVERRUN_error))
        {
            uartError = UARTERROR_OVERRUN_error;
        }
        else if(CHECK_FAIL(data,UARTERROR_BREAK_error))
        {
            uartError = UARTERROR_BREAK_error;
        }
        else if(CHECK_FAIL(data,UARTERROR_PARITY_error))
        {
            uartError = UARTERROR_PARITY_error;
        }
        else if(CHECK_FAIL(data,UARTERROR_FRAMING_error))
        {
            uartError = UARTERROR_FRAMING_error;
        }
        else
        {
            uartError = UARTERROR_DATA_ok;
        }
    }
    uarts_data[uartNumIndex].error = uartError;
    return uartError;
}


uartErrors_t UART_setByte(UART_num_t uartNumber,uint8_t data)//take uart number as input , and the data to be set
{
    cBuffErrors_t bufferError = cBuffErrors_IDLE;

    uint8_t uartNumIndex;
    get_uartData_index(uartNumber,&uartNumIndex);

    if(uarts_data[uartNumIndex].uart_TxCirBuff->empty == true){
        if(UARTSpaceAvail(uart_get_baseAddress[uartNumber])){
            UARTCharPutNonBlocking(uart_get_baseAddress[uartNumber], data);
        }else{
            bufferError = cirBuffer_write(uarts_data[uartNumIndex].uart_TxCirBuff ,  (0x000000FF&(int32_t)data));
        }
    }else{ // if cir buffer is not empty
        bufferError = cirBuffer_write(uarts_data[uartNumIndex].uart_TxCirBuff , (0x000000FF&((int32_t)data)));
    }
    if(bufferError == cBuffErrors_overWrite)
    {
        uarts_data[uartNumIndex].error = UARTERROR_OVERRUN_error;
        return UARTERROR_OVERRUN_error;
    }
    else
    {
        uarts_data[uartNumIndex].error = UARTERROR_DATA_ok;
        return UARTERROR_DATA_ok;
    }
}



void UARTS_cyclic5ms()
{
    cBuffErrors_t bufferError;
    uint8_t uartCtr;
    int32_t receivedByte;

    for(uartCtr=0;uartCtr<USED_UARTS_NUM;uartCtr++)
    {
        if(uarts_data[uartCtr].uart_RxCirBuff != NULL && uarts_data[uartCtr].uart_TxCirBuff != NULL)
        {
            //disable uart interrupt to avoid access a shared resource(cBufer) at the same time
            UARTIntDisable(uart_get_baseAddress[uarts_data[uartCtr].uartNumber] , UART_INT_RX);
            while(UARTCharsAvail(uart_get_baseAddress[uarts_data[uartCtr].uartNumber]) == true){
                receivedByte = UARTCharGetNonBlocking(uart_get_baseAddress[uarts_data[uartCtr].uartNumber]);
                bufferError = cirBuffer_write(uarts_data[uartCtr].uart_RxCirBuff, receivedByte);
                if(bufferError == cBuffErrors_overWrite){
                    UART_State = UART_State_Rx_OverFlow;
                }
            }
            UARTIntEnable(uart_get_baseAddress[uarts_data[uartCtr].uartNumber] , UART_INT_RX);
        }
    }
}
// implement UART get module state
#define BASE_TO_INDX(BASE) ((BASE-UART0_BASE)/0x1000)
inline void handle_ISR(uint32_t UART_BASE){
    int32_t Byte;
    uint32_t ui32IntStatus;
    uint8_t ctr;
    uint8_t uartNumIndex;

    get_uartData_index(BASE_TO_INDX(UART_BASE),&uartNumIndex);

    ui32IntStatus = UARTIntStatus(UART_BASE, true);

    UARTIntClear(UART_BASE , ui32IntStatus);
    // receive_ISR();
    if(ui32IntStatus & UART_INT_RX){
        for(ctr=0;ctr<4;ctr++)
        {
            if(UARTCharsAvail(UART_BASE) == true)
            {
                Byte = UARTCharGetNonBlocking(UART_BASE);

                cirBuffer_write(uarts_data[uartNumIndex].uart_RxCirBuff, Byte);
            }
        }
    }else if(ui32IntStatus & UART_INT_TX) // Tx Interrupt then Tx FIFO has one byte or less
    {

        while(UARTSpaceAvail(UART_BASE) && cirBuffer_read(uarts_data[uartNumIndex].uart_TxCirBuff,&Byte) != cBuffErrors_NoData){
            UARTCharPutNonBlocking(UART_BASE, Byte);
        }
    }else{// unexpected UART interrupt

    }
}


inline bool get_uartData_index(UART_num_t uartNum,uint8_t * ret_index)
{
    uint8_t ctr;
    for(ctr=0;ctr<USED_UARTS_NUM;ctr++)
    {
        if(uarts_data[ctr].uartNumber == uartNum){
            *ret_index = ctr;
            return true;
        }

    }
    return false;
}


void UART_get_TX_len(UART_num_t uartNum, uint32_t *len)
{
    uint8_t uartNumIndex;
    get_uartData_index(uartNum,&uartNumIndex);
    *len = uarts_data[uartNumIndex].uart_TxCirBuff->len;
}
void UART_get_RX_len(UART_num_t uartNum, uint32_t *len)
{
    uint8_t uartNumIndex;
    get_uartData_index(uartNum,&uartNumIndex);
    *len = uarts_data[uartNumIndex].uart_RxCirBuff->len;
}
void UARTS_clear(UART_num_t num){
    cirBuffer_ctor(uarts_data[num].uart_RxCirBuff);
    cirBuffer_ctor(uarts_data[num].uart_TxCirBuff);

}
