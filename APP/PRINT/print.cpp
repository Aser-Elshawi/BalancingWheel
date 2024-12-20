/*
 * print.cpp
 *
 *  Created on: Dec 16, 2024
 *      Author: aser_
 */
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "UART.hpp"
#include <print.hpp>

void print_Init(){

}

void print_Cyclic(){
    UART::cyclic();
}
