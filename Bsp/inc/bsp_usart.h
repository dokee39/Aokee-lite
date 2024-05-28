#ifndef BSP_USART_H
#define BSP_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define USART1_TX_BUF_LEN 128

void usart1_printf(const char* fmt, ...);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
