# Aokee_lite
### \~ My Dear Balance Infantry \~

## 项目说明

- 立创硬件开源平台: http://oshwhub.com/colorful-sun/aokee-lite
- 代码仓库: https://github.com/dokee39/Aokee-lite (*编辑本项目说明时未完善*)
    - 虽然是平衡小车, 但是写代码时是以平衡步兵的标准来写的
    - 尝试使用 C++, 实现接口与解算分开的电机库, 方便移植到其他平台
    - 使用底盘与电机均为模板类, 可以实现切换不同底盘或使用不同电机仅需要更改 config.hpp 文件
    - 尝试使用 LQR
- 2024 西南大学 GKD 战队 PCB 设计教程 (*编辑本项目说明时未完成*)
- 3D 模型
    - 见嘉立创开源广场附件, 兼容两种不同大小的电机
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
    - MCU: STM32F405RGT6
    - 陀螺仪: BMI088
        - 忘记延长焊盘又忘记打钢网太难焊了, 实际测试时外接了 MPU6050
    - 控制: 蓝牙串口或大疆遥控器 DBUS (DT-07)
    - 其他: 按键, 蜂鸣器, WS2812 彩灯, SWD 调试, 串口转 USB, 冗余引脚引出

