/*
 * HobotS_sensor_commands.h
 * 
 * Ардуино совместимое расширение описания команд датчиков и приводов для облегченного взаимодействия с контроллером Hobots S
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


#ifndef _HOBOT_S_SENSOR_COMMANDS_H_INC
#define _HOBOT_S_SENSOR_COMMANDS_H_INC

enum hs_uart_commands: uint8_t {
  HS_SENSOR_NAME,
  HS_SENSOR_VERSION,
  HS_COLOR_GET_RED_CH,
  HS_COLOR_GET_GREEN_CH,
  HS_COLOR_GET_BLUE_CH,
  HS_COLOR_GET_CLEAR_CH,
  HS_COLOR_SET_LED_BRIGHTNESS,
  HS_SONAR_GET_DISTANCE_CM,
  HS_SONAR_SET_LED_RGB_AND_PIXEL,
  HS_FORCE_GET_RAW_VALUE,
  HS_FORCE_GET_ACTIVE_MODE_VALUE,
  HS_FORCE_SET_TOUCH_MODE,
  HS_FORCE_SET_TAP_MODE,
  HS_FORCE_SET_FORCE_MODE,
  HS_FORCE_GET_TOUCH_VALUE,
  HS_FORCE_GET_TAP_VALUE,
  HS_FORCE_GET_FORCE_VALUE,
  HS_MOTOR_SMALL_GET_VALUE,
  HS_MOTOR_MEDIUM_GET_VALUE,
  HS_MOTOR_LARGE_GET_VALUE,
};

#endif
