# Aokee-lite
### \~ My Dear Balance Infantry \~

## 项目说明

- [![wakatime](https://wakatime.com/badge/github/dokee39/Aokee-lite.svg?style=flat-square)](https://wakatime.com/badge/github/dokee39/Aokee-lite)
- 立创硬件开源平台: http://oshwhub.com/colorful-sun/aokee_lite
- 代码仓库: https://github.com/dokee39/Aokee-lite
    - 虽然是平衡小车, 但是写代码时是以平衡步兵的标准来写的
    - 尝试使用 C++, 实现接口与解算分开的电机库, 方便移植到其他平台
    - 使用底盘与电机均为模板类, 可以实现切换不同底盘或使用不同电机仅需要更改 `config.hpp` 文件
    - 尝试使用 LQR, 由于时间仅暂时使用的是 PID, 等做好 FOC 之后再用小无刷调 LQR 试试
- 2024 西南大学 GKD 战队 PCB 设计教程 (*编辑本项目说明时还未完成*)
- 3D 模型
    - 见嘉立创开源广场附件
    - 蓝色为底盘兼容两种不同大小的电机
    - 黄色为上方负重 (还可以倒置放置小车方便调试)
- 主要部件说明
    - 电源
        - [12V 动力电池](https://m.tb.cn/h.gXxeS5unhuaDTxu?tk=eOekWum7ekZ)供电
        - 防反接: PMOS, CSD25402Q3A, 6mΩ
        - DC-DC 转 5V: TPS54202, 2A
        - LDO 转 3.3V: TPRT9013-33GB, 500mA
    - 电机驱动: A4950
    - 电机
        - 大: 轮趣科技 MG513
        - 小: 轮趣科技 MG310
        - 实际用下来不仅背隙大而且扭矩小
    - MCU: STM32F405RGT6
    - 陀螺仪: BMI088
        - 忘记延长焊盘又忘记打钢网太难焊了, 实际测试时外接了 MPU6050
    - 控制: 蓝牙串口或大疆遥控器 DBUS (DT-07)
    - 其他: 按键, 蜂鸣器, WS2812 彩灯, SWD 调试, 串口转 USB, 冗余引脚引出

## 代码结构

使用 C++ 在 STM32 上编程, 通过 LQR 控制器平衡. 其中利用 C++ 实现了一套电机库, 抽象出不同电机, 且将控制与接口实现分开, 控制部分不依赖于平台, 非常便于移植到如 Linux 等其他平台. 另外本项目是为下个赛季平衡步兵的研发做准备, 利用了 C++ 模板类和多态的特性, 可以实现在只修改 `config.hpp` 的情况下更改电机类型或底盘类型等. 

本项目主控使用 `STM32F407RGT6`, 工具链为 `GNU Arm Embedded Toolchain`, 使用 `Makefile` 进行项目构建, 使用 `OpenOCD` 与 `cmsis-dap-link` 调试器进行代码烧录与调试. 代码仓库的结构如下: 

```
.
├── App
│   ├── chassis -> 底盘
│   │   ├── chassis_base.cc
│   │   ├── double_wheel_balance_chassis.cc
│   │   └── inc
│   │       ├── chassis_base.hpp
│   │       ├── double_wheel_balance_chassis_config.hpp
│   │       └── double_wheel_balance_chassis.hpp
│   ├── compatible.cc -> main_entry(), 用以兼容 C++
│   ├── imu.cc
│   ├── led_task.c
│   ├── remote_controller.c
│   ├── robot_ctrl.cc
│   └── inc
│       ├── config.hpp
│       └── ...
├── Bsp
│   ├── bsp_buzzer.c
│   ├── bsp_rc.c
│   ├── bsp_usart.c
│   ├── bsp_user_key.c
│   ├── mpu6050.c
│   ├── sccb.c
│   ├── sw_i2c1_port.c
│   ├── sw_i2c.c
│   ├── ws2812.c
│   └── inc
│       └── ...
├── Components
│   ├── algorithm
│   │   ├── lqr/
│   │   ├── MahonyAHRS/
│   │   ├── pid/
│   │   └── support/
│   ├── freertos/
│   ├── motor_impl_STM32 -> 电机库的实现
│   │   ├── pwm_dc_motor_impl.cc
│   │   └── inc
│   │       └── pwm_dc_motor_impl.hpp
│   ├── motor_lib -> 电机库
│   │   ├── motor_base.hpp
│   │   └── pwm_dc_motor.hpp
│   └── printf/
├── Core/
├── Drivers/
├── Makefile
├── README.md
├── startup_stm32f405xx.s
└── STM32F405RGTx_FLASH.ld

```

本项目分为初始化 (`Core`), 驱动层 (`Drivers`), 板载层 (`Bsp`), 应用层 (`App`) 与部件库 (`Components`) 组成. 
- STM32 片上外设初始化代码 (`Core`) 由 `STM32CubeMX` 生成. 
驱动层 (`Drivers`) 使用 `HAL 库`, 板载层为 LED, IMU, UART, 按键, 蜂鸣器等的控制代码. 
- 应用层 (`App`) 使用 `FreeRTOS` 开启多个线程, 执行 WS2812 彩灯闪烁 (`led_task()`), 陀螺仪姿态解算 (`robot.chassis->imu.imu_task()`), 遥控器信息读取与机器人整体状态设定 (`robot.update_set_task()`), 底盘运动学解算与控制 (`robot.chassis->task()`) 等多个任务. 
- 部件库 (`Components`) 为与主体代码没有耦合或耦合较少的通用代码库, 共有五个: 
    - `algorithm` 为各种算法, 包括 MahonyAHRS 陀螺仪姿态解算算法, LQR 控制算法, PID 控制算法以及通用库 `support`. 其中 `support` 使用了[上海交通大学交龙战队封装的矩阵库](https://github.com/SJTU-RoboMaster-Team/Matrix_and_Robotics_on_STM32), 感谢开源. 
    - `freertos` 为 `FreeROTS` 的核心部件. 
    - `motor_lib` 为自己实现的电机库的解算部分, 没有任何与平台相依赖的代码. 
    - `motor_impl_STM32` 为电机库在 STM32 上实现的代码. 
    - `printf` 为适用于嵌入式平台的轻量级的 `printf()`, 感谢 [mpaland 的开源](https://github.com/mpaland/printf). 

本套代码中的电机 (motor), 和底盘 (chassis) 都使用 C++ 的模板类继承多态基类的方法进行抽象, 实现高代码复用, 可以实现在只修改 config.hpp 的情况下更改电机类型和底盘类型. 

