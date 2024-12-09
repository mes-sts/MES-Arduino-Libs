/*
 * HobotS_defines.h
 * 
 * Ардуино совместимое расширение описания выводов для облегченного взаимодействия с контроллером Hobots S
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


#ifndef _HOBOT_S_DEFINES_H_INC
#define _HOBOT_S_DEFINES_H_INC

// Переименование USB Serial
#define SerialDebug Serial
// Выводы кнопок
const uint8_t BLE_BTN_PIN = PC9;
const uint8_t LEFT_BTN_PIN = PE6;
const uint8_t CENTER_BTN_PIN = PE5;
const uint8_t RIGHT_BTN_PIN = PE4;
// Выводы светодиодов кнопок
const uint8_t LED_BTN_RED_PIN = PC15;
const uint8_t LED_BTN_GREEN_PIN = PC14;
const uint8_t LED_BTN_BLUE_PIN = PC13;
// Выводы управления питаниями
const uint8_t MAIN_3V3_EN_PIN = PD2;
const uint8_t BLE_3V3_EN_PIN = PD3;
const uint8_t LEDS_5V_EN_PIN = PD8;
const uint8_t AUDIO_5V_EN_PIN = PB9;
const uint8_t DRV_5V_EN_PIN = PB15;
// Вывод матрицы адресных светодиодов
const uint8_t WS2812_DATA_PIN = PB14;
// Количество адресных светодиодов в матрице
const uint8_t WS2812_MATRIX_COUNT = 25;
// Выводы управления моторами
const uint8_t TB_MA_IN1_PIN = PE15; //A
const uint8_t TB_MA_IN2_PIN = PB10;
const uint8_t TB_MA_PWM_PIN = PB11;
const uint8_t TB_MB_IN1_PIN = PD7; //B
const uint8_t TB_MB_IN2_PIN = PD6;
const uint8_t TB_MB_PWM_PIN = PB4;
const uint8_t TB_MC_IN1_PIN = PE14; //C
const uint8_t TB_MC_IN2_PIN = PE13;
const uint8_t TB_MC_PWM_PIN = PE12;
const uint8_t TB_MD_IN1_PIN = PG9; //D
const uint8_t TB_MD_IN2_PIN = PG10;
const uint8_t TB_MD_PWM_PIN = PB3;
const uint8_t TB_ME_IN1_PIN = PC4; //E
const uint8_t TB_ME_IN2_PIN = PC5;
const uint8_t TB_ME_PWM_PIN = PB0;
const uint8_t TB_MF_IN1_PIN = PA7; //F
const uint8_t TB_MF_IN2_PIN = PA6;
const uint8_t TB_MF_PWM_PIN = PA5;
// Скорость uart порта блютуз
#define STM_USART1_BAUD_RATE 9600
// Выводы uart блютуз
const uint8_t STM_USART1_RX_PIN = PA10;
const uint8_t STM_USART1_TX_PIN = PA9;
// Вывод переключения в реим AT команд
const uint8_t POWERC_AT_EN_PIN = PA8;
// Скорость портов uart датчиков
#define STM_UARTS_BAUD_RATE 115200
// Выводы uart портов датчиков
const uint8_t STM_UART5_RX_PIN = PB12; //A
const uint8_t STM_UART5_TX_PIN = PB13;
const uint8_t STM_UART4_RX_PIN = PD0; //B
const uint8_t STM_UART4_TX_PIN = PD1;
const uint8_t STM_UART9_RX_PIN = PG0; //C
const uint8_t STM_UART9_TX_PIN = PG1;
const uint8_t STM_UART8_RX_PIN = PE0; //D
const uint8_t STM_UART8_TX_PIN = PE1;
const uint8_t STM_UART7_RX_PIN = PF6; //E
const uint8_t STM_UART7_TX_PIN = PF7;
const uint8_t STM_UART10_RX_PIN = PE2; //F
const uint8_t STM_UART10_TX_PIN = PE3;
// Выводы гироскопа/акселерометра (IIC)
const uint8_t STM_I2C2_SDA_PIN = PF0;
const uint8_t STM_I2C2_SCL_PIN = PF1;
const uint8_t MPU_INT_PIN = PF2;
// Выводы памяти SPI FLASH
const uint8_t STM_SPI3_NSS_PIN = PA15;
const uint8_t STM_SPI3_SCK_PIN = PC10;
const uint8_t STM_SPI3_MISO_PIN = PC11;
const uint8_t STM_SPI3_MOSI_PIN = PC12;
// Вывод выхода аудио сигнала
const uint8_t AUDIO_OUT_PIN = PA4;
// Вывод отслеживания подключенного USB
const uint8_t STM_USB_DETECT_PIN = PA13;

#endif
