//
// Created by qjy on 2026/10/2.
#include "main.h"
#include "remote.h"


Remote rc(&huart3);


extern "C" {
void robotInit(void) {
    rc.init();
}
}
extern "C" {void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart == &huart3)
    {
        if (Size == 18)
        {
            rc.handle();
        }
        rc.rxMsgCallback(nullptr);
    }
}
}

