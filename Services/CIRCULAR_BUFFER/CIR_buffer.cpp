/*
 * CIR_buffer.c
 *
 *  Created on: Dec 22, 2021
 *      Author: Jessy
 */



#include <stdbool.h>
#include <stdint.h>
#include <CIR_buffer.hpp>

#define INC_INDX(INDX) (INDX = (INDX == BUFFER_SIZE-1)?0:(INDX+1))

void cirBuffer_ctor(cirBuffer_t * rCirBuff)
{
    rCirBuff->read_index = 0;
    rCirBuff->write_index = 0;
    rCirBuff->overWrite = false;
    rCirBuff->empty = true;
    rCirBuff->len = 0;
}

//returns if buffer is empty or not
cBuffErrors_t cirBuffer_read(cirBuffer_t * const rCirBuff, int32_t * ret_data)
{
    cBuffErrors_t ret = cBuffErrors_IDLE;
    //*overFlow = false;
    // check if buffer is overwritten
    if(rCirBuff->overWrite){
        //*overFlow = true;
        rCirBuff->overWrite = false;
        * ret_data = rCirBuff->buffer[rCirBuff->read_index];
        --rCirBuff->len;
        // increment circular index, 0 when reaches the end
        INC_INDX(rCirBuff->read_index);
    }else if(rCirBuff->empty == false){ // data available in the buffer
        *ret_data = rCirBuff->buffer[rCirBuff->read_index];
        --rCirBuff->len;
        //cirBuff->read_index = (cirBuff->read_index == BUFFER_SIZE-1)?0:(cirBuff->read_index+1);
        // increment circular index, 0 when reaches the end
        INC_INDX(rCirBuff->read_index);
        if(rCirBuff->read_index == rCirBuff->write_index)
        {
            rCirBuff->empty = true;
            ret = cBuffErrors_BecomeEmpty;
            //--rCirBuff->len;
        }
    }else{
        *ret_data = -2;
        ret = cBuffErrors_NoData;
        // no data in the buffer

    }
    //return rCirBuff->empty;
    return ret;
}

// return = if cBuffErrors_overWrite happen or not
cBuffErrors_t cirBuffer_write(cirBuffer_t * const cirBuff , const int32_t data)
{
    cBuffErrors_t ret = cBuffErrors_IDLE;
    //  add data in buffer
    //if(cirBuff->magicNumber == MagicNumbersArr[cirBuff->read_index])
    cirBuff->buffer[cirBuff->write_index] = data;

    // is read on next ?
    if((cirBuff->write_index == cirBuff->read_index)&&(cirBuff->empty == false))
    {
        // increment circular index, 0 when reaches the end



        INC_INDX(cirBuff->write_index);
        cirBuff->read_index = cirBuff->write_index;
        cirBuff->overWrite = true;
        ret = cBuffErrors_overWrite;

        //return true;
    }else{
        // increment circular index, 0 when reaches the end
        INC_INDX(cirBuff->write_index);
        ret = cBuffWrite_OK;
        ++cirBuff->len;

    }
    cirBuff->empty = false;

    return ret;
    //return cirBuff->overWrite;
}


cBuffErrors_t cirBuffer_peek(cirBuffer_t * const rCirBuff ,uint32_t index,int32_t * ret_data)
{
    cBuffErrors_t ret = cBuffErrors_IDLE;
    uint32_t i=0;
    uint32_t readIndex = rCirBuff->read_index;
    for(i=0;i<index;i++)
        INC_INDX(readIndex);
     // check if buffer is overwritten
/*
   if(readIndex < rCirBuff->write_index){ // data available in the buffer

         //cirBuff->read_index = (cirBuff->read_index == BUFFER_SIZE-1)?0:(cirBuff->read_index+1);
         // increment circular index, 0 when reaches the end
      *ret_data = rCirBuff->buffer[readIndex];

     }else if( (rCirBuff->overWrite == true) && readIndex == rCirBuff->write_index ){
         *ret_data = rCirBuff->buffer[readIndex];

     }else{
         ret = cBuffErrors_NoData;
     }
*/


    if( (readIndex != rCirBuff->write_index) || ( (readIndex == rCirBuff->write_index) && rCirBuff->overWrite == true  ) ){
        *ret_data = rCirBuff->buffer[readIndex];
    }else{
        ret = cBuffErrors_NoData;
    }

     return ret;
}

void cirBuffer_clear(cirBuffer_t * const cirBuff)
{
    cirBuff->empty = true;
    cirBuff->overWrite = false;
    cirBuff->read_index = 0;
    cirBuff->write_index = 0;
}


