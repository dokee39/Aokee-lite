#include <cmath>
#include <cstdint>

#include "BMI088driver.h"
#include "FreeRTOS.h"
#include "MahonyAHRS.h"
#include "imu.hpp"
#include "task.h"

// #warning "DEBUG"
// #include "bsp_usart.h"

namespace Dev {
void Imu::task(void* arg) {
    TickType_t xLastWakeTime;

    vTaskDelay(pdMS_TO_TICKS(10));

#warning "DEBUG"
    while (true) {
    uint8_t ret = BMI088_init();
        if (ret == 0) {
            break;
        } else {
            // usart1_printf("%d\r\n", ret);
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }

    xLastWakeTime = xTaskGetTickCount();

    for (;;) {
        BMI088_read(gyro, acc, &temp);

        MahonyAHRSupdateIMU(quat, gyro[0], gyro[1], gyro[2], acc[0], acc[1], acc[2]);
        calc_angle();

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1));
    }
}

void Imu::calc_angle() {
    angle[0] = atan2f(
        2.0f * (quat[0] * quat[3] + quat[1] * quat[2]),
        2.0f * (quat[0] * quat[0] + quat[1] * quat[1]) - 1.0f
    );
    angle[1] = asinf(-2.0f * (quat[1] * quat[3] - quat[0] * quat[2]));
    angle[2] = atan2f(
        2.0f * (quat[0] * quat[1] + quat[2] * quat[3]),
        2.0f * (quat[0] * quat[0] + quat[3] * quat[3]) - 1.0f
    );
}
} // namespace Dev
