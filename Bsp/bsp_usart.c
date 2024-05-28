#include "bsp_usart.h"
#include "main.h"

#include "printf.h"

#include <stdarg.h>

extern UART_HandleTypeDef huart1;

void usart1_printf(const char *fmt, ...)
{
    static char tx_buf[USART1_TX_BUF_LEN] = {0};        // 必须使用static
    char *ptx_buf                         = &tx_buf[0]; // 不能使用static
    static va_list args;                                // 必须使用static
    static uint16_t len;                                // 必须使用static
    va_start(args, fmt);

    if (HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY)
        return;
    // return length of string
    // 返回字符串长度
    len = vsnprintf(ptx_buf, USART1_TX_BUF_LEN, fmt, args);
    va_end(args);
    HAL_UART_Transmit_DMA(&huart1, (uint8_t *)tx_buf, len);
    __HAL_DMA_DISABLE_IT(huart1.hdmatx, DMA_IT_HT);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart1) {
        // 要改变 UART 的标志位为 READY (这可能是 HAL 库的 BUG)
        huart->gState = HAL_UART_STATE_READY;
    }
}

