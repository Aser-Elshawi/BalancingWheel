
#ifdef __UART__

#ifndef UART_UART_PRIVATE_H_
#define UART_UART_PRIVATE_H_

// implement UART get module state
#define BASE_TO_INDX(BASE) ((BASE-UART0_BASE)/0x1000)


#define CHECK_FAIL(data,err) (data & (1<<err))

typedef enum UART_State_s{
    UART_State_Tx_OverFlow,
    UART_State_Rx_OverFlow,
    UART_State_OK
}UART_State_t;


void uart0_ISR(void);
void uart1_ISR(void);
void uart2_ISR(void);
void uart3_ISR(void);
void uart4_ISR(void);
void uart5_ISR(void);
void uart6_ISR(void);
void uart7_ISR(void);
void (*UART_ISR[8])(void) =
{
 uart0_ISR,
 uart1_ISR,
 uart2_ISR,
 uart3_ISR,
 uart4_ISR,
 uart5_ISR,
 uart6_ISR,
 uart7_ISR
};

//get the corresponding index for the rigth data for the uart number
//inline bool get_uartData_index(uint8_t,uint8_t *);
inline void handle_ISR(uint32_t UART_BASE);

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

#endif /* UART_UART_PRIVATE_H_ */
#endif /* __UART__ */
