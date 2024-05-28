#ifndef BSP_RC_H
#define BSP_RC_H
#include "main.h"
#include <stdint.h>

#define huart_dbus huart5
extern UART_HandleTypeDef huart_dbus;

extern void RC_Init(uint8_t* rx1_buf, uint8_t* rx2_buf, uint16_t dma_buf_num);
extern void RC_unable(void);
extern void RC_restart(uint16_t dma_buf_num);
#endif
