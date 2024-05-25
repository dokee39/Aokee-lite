#include "bsp_rc.h"

void RC_Init(uint8_t* rx1_buf, uint8_t* rx2_buf, uint16_t dma_buf_num) {
    //enable the DMA transfer for the receiver request
    //使能DMA串口接收
    SET_BIT(huart_dbus.Instance->CR3, USART_CR3_DMAR);

    //enalbe idle interrupt
    //使能空闲中断
    __HAL_UART_ENABLE_IT(&huart_dbus, UART_IT_IDLE);

    //disable DMA
    //失效DMA
    __HAL_DMA_DISABLE(huart_dbus.hdmarx);
    while (huart_dbus.hdmarx->Instance->CR & DMA_SxCR_EN) {
        __HAL_DMA_DISABLE(huart_dbus.hdmarx);
    }

    huart_dbus.hdmarx->Instance->PAR = (uint32_t) & (USART3->DR);
    //memory buffer 1
    //内存缓冲区1
    huart_dbus.hdmarx->Instance->M0AR = (uint32_t)(rx1_buf);
    //memory buffer 2
    //内存缓冲区2
    huart_dbus.hdmarx->Instance->M1AR = (uint32_t)(rx2_buf);
    //data length
    //数据长度
    huart_dbus.hdmarx->Instance->NDTR = dma_buf_num;
    //enable double memory buffer
    //使能双缓冲区
    SET_BIT(huart_dbus.hdmarx->Instance->CR, DMA_SxCR_DBM);

    //enable DMA
    //使能DMA
    __HAL_DMA_ENABLE(huart_dbus.hdmarx);
}
void RC_unable(void) {
    __HAL_UART_DISABLE(&huart_dbus);
}
void RC_restart(uint16_t dma_buf_num) {
    __HAL_UART_DISABLE(&huart_dbus);
    __HAL_DMA_DISABLE(huart_dbus.hdmarx);

    huart_dbus.hdmarx->Instance->NDTR = dma_buf_num;

    __HAL_DMA_ENABLE(huart_dbus.hdmarx);
    __HAL_UART_ENABLE(&huart_dbus);
}
