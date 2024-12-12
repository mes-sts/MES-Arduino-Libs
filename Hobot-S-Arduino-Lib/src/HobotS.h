/*
 * HobotS.h
 * 
 * Ардуино совместимымый класс для облегченного взаимодействия с контроллером Hobots S
 * 
 * Предназначен для работы с Ардуино совместимым ядром Arduino_Core_STM32 (https://github.com/stm32duino/Arduino_Core_STM32/)
 *
 * Tools → Board → STM32 Boards Groups → Generic STM32F4 series
 * Tools → Board part number → Generic F413ZGTx
 * Tools → U(S)ART support → Enable (generic 'Serial')
 * Tools → USB support (if available) → CDC (generic 'Serial' supersed U(S)ART)
 * Tools → Upload method → HID Bootloader 2.2
 * 
 * Copyright (C) 2024. v1.0 / MES
 */


#ifndef _HOBOT_S_H_INC
#define _HOBOT_S_H_INC

#include "Arduino.h"
#include <Wire.h>
#include <HardwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_MPU6050.h>
#include "HobotS_defines.h"
#include "HobotS_sensor_commands.h"


class HobotSClass {
  public:
    // Объекты связанных классов
    Adafruit_NeoPixel Pixels = Adafruit_NeoPixel(WS2812_MATRIX_COUNT, WS2812_DATA_PIN, NEO_GRB + NEO_KHZ800);
    TwoWire WireGyroAcc = TwoWire(STM_I2C2_SDA_PIN, STM_I2C2_SCL_PIN);
    Adafruit_MPU6050 GyroAcc = Adafruit_MPU6050();  
    HardwareSerial SerialBLE = HardwareSerial(STM_USART1_RX_PIN, STM_USART1_TX_PIN);
    HardwareSerial SerialA = HardwareSerial(STM_UART5_RX_PIN, STM_UART5_TX_PIN);
    HardwareSerial SerialB = HardwareSerial(STM_UART4_RX_PIN, STM_UART4_TX_PIN);
    HardwareSerial SerialC = HardwareSerial(STM_UART9_RX_PIN, STM_UART9_TX_PIN);
    HardwareSerial SerialD = HardwareSerial(STM_UART8_RX_PIN, STM_UART8_TX_PIN);
    HardwareSerial SerialE = HardwareSerial(STM_UART7_RX_PIN, STM_UART7_TX_PIN);
    HardwareSerial SerialF = HardwareSerial(STM_UART10_RX_PIN, STM_UART10_TX_PIN);

    // Конструктор класса HobotS
    HobotSClass();

    // Настройка устройства
    void setup();
    void matrixSetup();
    void gyroAccSetup();
    void powerSourcesSetup();
    void motorsSetup();
    void buttonsSetup();
    void buttonsLEDSetup();
    void sensorPortsSetup();
    void bluetoothPortSetup();
    void debugPortSetup();

    // Методы светодиодной матрицы
    uint8_t matrixGetNumPixels();
    void matrixAllClear();
    void matrixClearPixel(uint8_t _id_pixel);
    void matrixSetPixelColor(uint8_t _id_pixel, uint8_t _red_ch, uint8_t _green_ch, uint8_t _blue_ch);

    // Методы гироскопа
    float gyroGetX();
    float gyroGetY();
    float gyroGetZ();

    // Методы акселерометра
    float accelerationGetX();
    float accelerationGetY();
    float accelerationGetZ();

    // Методы управления питаниями
    void enablePowerMain();
    void disablePowerMain();
    void enablePowerBLE();
    void disablePowerBLE();
    void enablePowerMatrix();
    void disablePowerMatrix();
    void enablePowerAudio();
    void disablePowerAudio();
    void enablePowerMotors();
    void disablePowerMotors();

    // Методы управления моторами
    void portAMotorCW();
    void portAMotorCCW();
    void portAMotorSpeed(uint8_t _motor_speed);
    void portBMotorCW();
    void portBMotorCCW();
    void portBMotorSpeed(uint8_t _motor_speed);
    void portCMotorCW();
    void portCMotorCCW();
    void portCMotorSpeed(uint8_t _motor_speed);
    void portDMotorCW();
    void portDMotorCCW();
    void portDMotorSpeed(uint8_t _motor_speed);
    void portEMotorCW();
    void portEMotorCCW();
    void portEMotorSpeed(uint8_t _motor_speed);
    void portFMotorCW();
    void portFMotorCCW();
    void portFMotorSpeed(uint8_t _motor_speed);

    // Методы кнопок
    bool isBluetoothButtonPressed();
    bool isBluetoothButtonReleased();
    bool isLeftButtonPressed();
    bool isLeftButtonReleased();
    bool isCenterButtonPressed();
    bool isCenterButtonReleased();
    bool isRightButtonReleased();
    bool isRightButtonPressed();

    // Методы светодиодов кнопок
    void enableRedButtonLED();
    void disableRedButtonLED();
    void enableGreenButtonLED();
    void disableGreenButtonLED();
    void enableBlueButtonLED();
    void disableBlueButtonLED();

    // Методы датчиков порта A
    byte portADistanceSensorGetDistance();
    void portADistanceSensorSetLED(uint8_t _id_pixel, uint8_t _red_ch, uint8_t _green_ch, uint8_t _blue_ch);

    // Методы датчиков порта B
    byte portBDistanceSensorGetDistance();
    void portBDistanceSensorSetLED(uint8_t _id_pixel, uint8_t _red_ch, uint8_t _green_ch, uint8_t _blue_ch);

    // Методы датчиков порта C
    byte portCDistanceSensorGetDistance();
    void portCDistanceSensorSetLED(uint8_t _id_pixel, uint8_t _red_ch, uint8_t _green_ch, uint8_t _blue_ch);

    // Методы датчиков порта D
    byte portDDistanceSensorGetDistance();
    void portDDistanceSensorSetLED(uint8_t _id_pixel, uint8_t _red_ch, uint8_t _green_ch, uint8_t _blue_ch);

    // Методы датчиков порта E
    byte portEDistanceSensorGetDistance();
    void portEDistanceSensorSetLED(uint8_t _id_pixel, uint8_t _red_ch, uint8_t _green_ch, uint8_t _blue_ch);

    // Методы датчиков порта F
    byte portFDistanceSensorGetDistance();
    void portFDistanceSensorSetLED(uint8_t _id_pixel, uint8_t _red_ch, uint8_t _green_ch, uint8_t _blue_ch);

    // Методы взаимодействия с bluetooth

    // Методы разные
    float getTemperature();

  private:
};

extern HobotSClass HobotS;

#endif