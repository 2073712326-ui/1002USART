/**
******************************************************************************
 * @file    remote.cpp/h
 * @brief   Remote control. 遥控器
 ******************************************************************************
 * Copyright (c) 2026 Team JiaoLong-SJTU
 * All rights reserved.
 ******************************************************************************
 */

#include "remote.h"
#include "string.h"

constexpr uint16_t REMOTE_CONNECT_TIMEOUT = 500u; 
// Constructor 构造函数
Remote::Remote(UART_HandleTypeDef *huart): huart_(huart), connect_(REMOTE_CONNECT_TIMEOUT){
    switch_.l = RCSwitchState_e::DOWN;
    switch_.r = RCSwitchState_e::DOWN;
}

// Start UART(SBUS) receive. 打开UART接收
void Remote::init() {
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buf, 18);
}

// Reset RC data. 重置遥控器数据
void Remote::reset() {
    memset(rx_buf, 0, 18);
    channel_.l_row =1024;
    channel_.l_col =1024;
    channel_.r_row =1024;
    channel_.r_col =1024;
    channel_.dial_wheel =1024;
    switch_.l = RCSwitchState_e::MID;
    switch_.r = RCSwitchState_e::MID;
}

// Check for uart correspondence. 检查串口是否匹配
void Remote::rxMsgCheck(UART_HandleTypeDef *huart) const {
    if (huart ==&huart3)
    {
        return;
    }

}

// Update connect status, restart UART(SBUS) receive.
// 更新连接状态，重新打开UART(SBUS)接收
void Remote::rxMsgCallback(uint8_t* rx_data_){
    connect_. refresh();
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buf, 18);

}

// Unpack data. 数据解包
void Remote::handle() {
    channel_.r_row = (rx_buf[0] | (rx_buf[1] << 8)) & 0x07FF;
    channel_.r_col = ((rx_buf[1] >> 3) | (rx_buf[2] << 5)) & 0x07FF;
    channel_.l_row = ((rx_buf[2] >> 6) | (rx_buf[3] << 2) | (rx_buf[4] << 10)) & 0x07FF;
    channel_.l_col = ((rx_buf[4] >> 1) | (rx_buf[5] << 7)) & 0x07FF;
    switch_.r = static_cast<RCSwitchState_e>((rx_buf[5] >> 4) & 0x0003);
    switch_.l = static_cast<RCSwitchState_e>((rx_buf[5] >> 6) & 0x0003);

}

