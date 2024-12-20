
#define __UART__
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
using namespace std;

/* tivaWare libraries  */
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include <OS.h>
//#include <tm4c123gh6pm.h> // Device-specific header file
/* local includes */
#include <CIR_buffer.hpp>

#include "UART_private.h"
#include "UART.hpp"
#include "UART_cfg.h"


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
 *  Dec 28, 2024        1.0.1         Aser Elshawi   Module Created.
 *
 * Notes : None
 *******************************************************************************/
void uart0_ISR(void)
{
    UART::handle_ISR(UART0_BASE);
}
void uart1_ISR(void)
{
    UART::handle_ISR(UART1_BASE);
}
void uart2_ISR(void)
{
    UART::handle_ISR(UART2_BASE);
}
void uart3_ISR(void)
{
    UART::handle_ISR(UART3_BASE);
}
void uart4_ISR(void)
{
    UART::handle_ISR(UART4_BASE);
}
void uart5_ISR(void)
{
    UART::handle_ISR(UART5_BASE);
}
void uart6_ISR(void)
{
    UART::handle_ISR(UART6_BASE);
}
void uart7_ISR(void)
{
    UART::handle_ISR(UART7_BASE);
}

/*************** END OF ISR FUNCTIONS ***************************************************************************/



void UART::begin(UART_num_t uartNum) {
    uartErrors_t status;
    status = initUART(uartNum);
    if(status == UARTERROR_initSuccess)
        initialized = true; // Set flag to true after successful initialization
}

uartErrors_t UART::initUART(UART_num_t uartNum) {
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
    uartNumber = uartNum;
    uint8_t uartNumIndex;

    get_uartData_index(uartNum,&uartNumIndex);

    if(uarts_data[uartNumIndex].uart_TxCirBuff == NULL){ // module was not initialized before (Cannot reinitialize)

        uarts_data[uartNumIndex].uart_TxCirBuff = new cirBuffer_t;

        if(uarts_data[uartNumIndex].uart_TxCirBuff == NULL)
        {
            uarts_data[uartNumIndex].error = UARTERROR_allocationFailed;
            return UARTERROR_allocationFailed;
        }

        uarts_data[uartNumIndex].uart_RxCirBuff = new cirBuffer_t;

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

size_t UART::write(char data) {
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
    //return 1;                        // Return number of bytes written
}

size_t UART::write(const std::string &str) {
    for (char c : str) {
        write(c); // Send each character in the string
    }
    return str.size(); // Return number of bytes written
}

int UART::available() {
        uint8_t uartNumIndex;
        uint32_t len;
        get_uartData_index(uartNumber,&uartNumIndex);
        len = uarts_data[uartNumIndex].uart_RxCirBuff->len;
    return len; // Return 1 if data is available, 0 otherwise
}

char UART::read() {
    cBuffErrors_t bufferError;
        uartErrors_t uartError = UARTERROR_DATA_ok;
        int32_t data;
        char ret_data;
        uint8_t uartNumIndex;
         get_uartData_index(uartNumber,&uartNumIndex);
        bufferError = cirBuffer_read(uarts_data[uartNumIndex].uart_RxCirBuff,&data);
        if(bufferError == cBuffErrors_NoData)
        {
            uartError = UARTERROR_BUFFER_EMPTY;
            ret_data = 0;
        }
        else
        {
            ret_data = (uint8_t)(data & 0x000000FF);
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
    return static_cast<char>(ret_data & 0xFF); // Read and return the received character
}

void UART::print(const std::string &str) {
    write(str);
    delay(30); // wait after reset
}
void UART::print(const int num) {
    write(std::to_string(num)); // Append newline and carriage return
    delay(30); // wait after reset
}

void UART::println(const std::string &str) {
    write(str + "\r\n"); // Append newline and carriage return
    delay(30); // wait after reset
}

void UART::println(const uint8_t num) {
    write(std::to_string(num) + "\r\n"); // Append newline and carriage return
    delay(30);
}

void UART::println(const int8_t num) {
    write(std::to_string(num) + "\r\n"); // Append newline and carriage return
    delay(30);
}

void UART::println(const int num) {
    write(std::to_string(num) + "\r\n"); // Append newline and carriage return
    delay(30);
}

UART::operator bool() const {
    return initialized; // Return whether UART has been initialized
}
void UART::cyclic(void){
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
inline bool UART::get_uartData_index(UART_num_t uartNum,uint8_t * ret_index)
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

inline void UART::handle_ISR(uint32_t UART_BASE){
    int32_t Byte;
    uint32_t ui32IntStatus;
    uint8_t ctr;
    uint8_t uartNumIndex;

    get_uartData_index((UART_num_t)BASE_TO_INDX(UART_BASE),&uartNumIndex);

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
