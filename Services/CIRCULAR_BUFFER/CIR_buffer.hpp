/*
 * CIR_buffer.h
 *
 *  Created on: Dec 22, 2021
 *      Author: Jessy
 */

#ifndef UART_CIRCULAR_BUFFER_CIR_BUFFER_H_
#define UART_CIRCULAR_BUFFER_CIR_BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BUFFER_SIZE 500



class cirBuffer_t
{
public:
    uint8_t buffer[BUFFER_SIZE];
    uint8_t read_index;
    uint8_t write_index;
    bool overWrite;
    bool empty;
    uint8_t len;
    uint8_t magicNumber;
};

typedef enum cBuffErrors_e
{
    cBuffErrors_overWrite,
    cBuffErrors_BecomeEmpty,
    cBuffWrite_OK,
    cBuffErrors_IDLE,
    cBuffErrors_NoData //no error
}cBuffErrors_t;

//constructor
void cirBuffer_ctor(cirBuffer_t * const me);
cBuffErrors_t cirBuffer_read(cirBuffer_t * const rCirBuff,int32_t * ret_data); //data_frame = errors + data;
cBuffErrors_t cirBuffer_write(cirBuffer_t * const me , const int32_t); // return = if cBuffErrors_overWrite happen or not
cBuffErrors_t cirBuffer_peek(cirBuffer_t * const me ,uint32_t,int32_t * ret_data);
void cirBuffer_clear(cirBuffer_t * const me);

#ifdef __cplusplus
}
#endif

#endif /* UART_CIRCULAR_BUFFER_CIR_BUFFER_H_ */
