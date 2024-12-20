
#ifdef __UART__

#ifndef UART_UART_PRIVATE_H_
#define UART_UART_PRIVATE_H_




#define CHECK_FAIL(data,err) (data & (1<<err))

typedef enum UART_State_s{
    UART_State_Tx_OverFlow,
    UART_State_Rx_OverFlow,
    UART_State_OK
}UART_State_t;


const uint32_t uart_get_sysctlPerUart[8];
const uint32_t uart_get_baseAddress[8];
const uint32_t uart_get_sysctlPerGpio[8];
const uint32_t uart_get_GPIO_BASE_ADDRESS[8];
const uint32_t uart_get_GPIO_TX_PIN[8];
const uint32_t uart_get_GPIO_RX_PIN[8];
const uint32_t uart_get_GPIO_PIN_A[8];
const uint32_t uart_get_GPIO_PIN_B[8];

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
inline bool get_uartData_index(uint8_t,uint8_t *);
inline void handle_ISR(uint32_t UART_BASE);
#endif /* UART_UART_PRIVATE_H_ */
#endif /* __UART__ */
