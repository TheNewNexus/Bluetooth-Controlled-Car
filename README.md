# Bluetooth-Controlled Car Project

A wireless robotic vehicle controlled via Bluetooth using HC-05 module and TM4C123GXL microcontroller. Supports multiple operation modes including free navigation and predefined geometric patterns.

## Key Features
- **Dual Operation Modes**:
  - **Free Ride Mode**: Manual control via smartphone (2m range)
  - **Custom Shapes Mode**: Autonomous execution of geometric patterns
- **Bluetooth Configuration**: AT command setup for HC-05 module
- **Motor Control**: PWM-driven DRV8838 motor driver for precise movement
- **Expandable Architecture**: Optional IR/ultrasonic sensors for obstacle avoidance

## Hardware Components
| Component              | Specification         |
|------------------------|-----------------------|
| Microcontroller        | TM4C123GXL            |
| Bluetooth Module       | HC-05                 |
| Motor Driver           | DRV8838                |
| DC Motors              | 4x (Differential Drive)|
| Power Source           | 6x AA batteries     |

## Bluetooth Setup
```c
// Example AT commands from setupbluetooth.c
void configureBluetooth() {
    sendATCommand("AT+NAME=BluetoothCar");
    sendATCommand("AT+PSWD=1234");
    sendATCommand("AT+UART=9600,0,0");
}
```
**Required Tools**:
- USB-TTL converter for AT command configuration
- Terminal software (Putty/CoolTerm)

## Operation Modes

### Mode 1: Custom Shapes
| Pattern    | Command | Parameters       |
|------------|---------|------------------|
| Circle     | C       | Radius (10-50cm) |
| Square     | S       | Side length      |
| Figure 8   | 8       | Scale factor     |
| Zig-Zag    | Z       | Amplitude        |

### Mode 2: Free Ride Control
**Movement Commands**:
- `F`: Forward
- `B`: Backward 
- `L`: Left turn
- `R`: Right turn
- `S`: Emergency stop

## Software Architecture
```
main.c
├── bluetooth_handler.c
├── motor_control.c
├── pattern_generator.c
└── setupbluetooth.c
```

## Getting Started
1. Flash `setupbluetooth.c` to configure HC-05 module
2. Upload main firmware to TM4C123GXL
3. Pair with Android device using PIN 1234
4. Use terminal app or custom Android controller

- **Battery Monitoring**: Integrated voltage sensing
- **LED Status Indicators**: System state visualization

