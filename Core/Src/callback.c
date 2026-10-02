//
// Created by qjy on 2026/10/2.
#include "main.h"
#include "usart.h"
#include "string.h"
extern uint8_t rx_msg[10];
extern uint8_t tx_msg[10];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart ==&huart1){
        memcpy(rx_msg, tx_msg, 10);
        HAL_UART_Transmit_IT(&huart1, rx_msg, 10);
        HAL_UART_Receive_DMA(&huart1, rx_msg, 10);
    }
}