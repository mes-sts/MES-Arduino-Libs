/*
 * HobotS.cpp
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


#include "HobotS.h"

HobotSClass HobotS;

/* Конструктор класса HobotS */
HobotSClass::HobotSClass() {
  // Ничего  
}

/* Настройка устройства */
void HobotSClass::allSetup() {
  HobotSClass::matrixSetup();
  HobotSClass::gyroAccSetup();  
  HobotSClass::powerSourcesSetup();
  HobotSClass::motorsSetup();
  HobotSClass::buttonsSetup();
  HobotSClass::buttonsLEDSetup();
  HobotSClass::sensorPortsSetup();
  HobotSClass::bluetoothPortSetup();
  HobotSClass::debugPortSetup();

  HobotSClass::enablePowerMain(); // Должно быть всегда включено
  HobotSClass::enablePowerBLE(); // Должно быть всегда включено

  // Принудительная очистка матрицы
  HobotSClass::matrixAllClear();

  // Сигнал что контроллер запущен
  HobotSClass::enableGreenButtonLED();
}
void HobotSClass::matrixSetup() {
  Pixels.begin();
  Pixels.setBrightness(10);
  Pixels.clear();
  Pixels.show();
}
void HobotSClass::gyroAccSetup() {
  GyroAcc.begin(MPU6050_I2CADDR_DEFAULT, &WireGyroAcc);
  GyroAcc.setAccelerometerRange(MPU6050_RANGE_8_G);
  GyroAcc.setFilterBandwidth(MPU6050_BAND_21_HZ); 
}
void HobotSClass::powerSourcesSetup() {
  pinMode(MAIN_3V3_EN_PIN, OUTPUT);
  pinMode(BLE_3V3_EN_PIN, OUTPUT);
  pinMode(LEDS_5V_EN_PIN, OUTPUT);
  pinMode(AUDIO_5V_EN_PIN, OUTPUT);
  pinMode(DRV_5V_EN_PIN, OUTPUT);
  digitalWrite(MAIN_3V3_EN_PIN, HIGH);
  digitalWrite(BLE_3V3_EN_PIN, HIGH);
  digitalWrite(LEDS_5V_EN_PIN, LOW);
  digitalWrite(AUDIO_5V_EN_PIN, LOW);
  digitalWrite(DRV_5V_EN_PIN, LOW);
}
void HobotSClass::motorsSetup() {
  pinMode(TB_MA_IN1_PIN, OUTPUT); // A
  pinMode(TB_MA_IN2_PIN, OUTPUT);
  pinMode(TB_MA_PWM_PIN, OUTPUT);
  pinMode(TB_MB_IN1_PIN, OUTPUT); // B
  pinMode(TB_MB_IN2_PIN, OUTPUT);
  pinMode(TB_MB_PWM_PIN, OUTPUT);
  pinMode(TB_MC_IN1_PIN, OUTPUT); // C
  pinMode(TB_MC_IN2_PIN, OUTPUT);
  pinMode(TB_MC_PWM_PIN, OUTPUT);
  pinMode(TB_MD_IN1_PIN, OUTPUT); // D
  pinMode(TB_MD_IN2_PIN, OUTPUT);
  pinMode(TB_MD_PWM_PIN, OUTPUT);
  pinMode(TB_ME_IN1_PIN, OUTPUT); // E
  pinMode(TB_ME_IN2_PIN, OUTPUT);
  pinMode(TB_ME_PWM_PIN, OUTPUT);
  pinMode(TB_MF_IN1_PIN, OUTPUT); // F
  pinMode(TB_MF_IN2_PIN, OUTPUT);
  pinMode(TB_MF_PWM_PIN, OUTPUT);
  digitalWrite(TB_MA_IN1_PIN, LOW); // A
  digitalWrite(TB_MA_IN2_PIN, LOW);
  analogWrite(TB_MA_PWM_PIN, 0);
  digitalWrite(TB_MB_IN1_PIN, LOW); // B
  digitalWrite(TB_MB_IN2_PIN, LOW);
  analogWrite(TB_MB_PWM_PIN, 0);
  digitalWrite(TB_MC_IN1_PIN, LOW); // C
  digitalWrite(TB_MC_IN2_PIN, LOW);
  analogWrite(TB_MC_PWM_PIN, 0);
  digitalWrite(TB_MD_IN1_PIN, LOW); // D
  digitalWrite(TB_MD_IN2_PIN, LOW);
  analogWrite(TB_MD_PWM_PIN, 0);
  digitalWrite(TB_ME_IN1_PIN, LOW); // E
  digitalWrite(TB_ME_IN2_PIN, LOW);
  analogWrite(TB_ME_PWM_PIN, 0);
  digitalWrite(TB_MF_IN1_PIN, LOW); // F
  digitalWrite(TB_MF_IN2_PIN, LOW);
  analogWrite(TB_MF_PWM_PIN, 0);
}
void HobotSClass::buttonsSetup() {
  pinMode(BLE_BTN_PIN, INPUT);
  pinMode(LEFT_BTN_PIN, INPUT);
  pinMode(CENTER_BTN_PIN, INPUT);
  pinMode(RIGHT_BTN_PIN, INPUT);
}
void HobotSClass::buttonsLEDSetup() {
  pinMode(LED_BTN_RED_PIN, OUTPUT);
  pinMode(LED_BTN_GREEN_PIN, OUTPUT);
  pinMode(LED_BTN_BLUE_PIN, OUTPUT);
  digitalWrite(LED_BTN_RED_PIN, LOW);
  digitalWrite(LED_BTN_GREEN_PIN, LOW);
  digitalWrite(LED_BTN_BLUE_PIN, LOW);
}
void HobotSClass::sensorPortsSetup() {
  SerialA.begin(STM_UARTS_BAUD_RATE);
  SerialB.begin(STM_UARTS_BAUD_RATE);
  SerialC.begin(STM_UARTS_BAUD_RATE);
  SerialD.begin(STM_UARTS_BAUD_RATE);
  SerialE.begin(STM_UARTS_BAUD_RATE);
  SerialF.begin(STM_UARTS_BAUD_RATE);
}
void HobotSClass::bluetoothPortSetup() {
  SerialBLE.begin(STM_USART1_BAUD_RATE);
}
void HobotSClass::debugPortSetup() {
  SerialDebug.begin(STM_UARTS_BAUD_RATE);
}

/* Методы светодиодной матрицы */
uint8_t HobotSClass::matrixGetNumPixels() {
  return WS2812_MATRIX_COUNT;
}
void HobotSClass::matrixAllClear() {
  Pixels.clear();
  Pixels.show();
}
void HobotSClass::matrixClearPixel(uint8_t _pixel) {
  Pixels.setPixelColor(_pixel, Pixels.Color(0, 0, 0));
  Pixels.show();
}
void HobotSClass::matrixSetPixelColor(uint8_t _num_pixel, uint8_t _red_ch, uint8_t _green_ch, uint8_t _blue_ch) {
  Pixels.setPixelColor(_num_pixel, Pixels.Color(_red_ch, _green_ch, _blue_ch));
  Pixels.show();
}

/* Методы гироскопа */
float HobotSClass::gyroGetX() {
  sensors_event_t a, g, temp;
  GyroAcc.getEvent(&a, &g, &temp);
  return g.gyro.x;
}
float HobotSClass::gyroGetY() {
  sensors_event_t a, g, temp;
  GyroAcc.getEvent(&a, &g, &temp);
  return g.gyro.y;
}
float HobotSClass::gyroGetZ() {
  sensors_event_t a, g, temp;
  GyroAcc.getEvent(&a, &g, &temp);
  return g.gyro.z;
}

/* Методы акселерометра */
float HobotSClass::accelerationGetX() {
  sensors_event_t a, g, temp;
  GyroAcc.getEvent(&a, &g, &temp);
  return a.acceleration.x;
}
float HobotSClass::accelerationGetY() {
  sensors_event_t a, g, temp;
  GyroAcc.getEvent(&a, &g, &temp);
  return a.acceleration.y;
}
float HobotSClass::accelerationGetZ() {
  sensors_event_t a, g, temp;
  GyroAcc.getEvent(&a, &g, &temp);
  return a.acceleration.z;
}

/* Методы управления питаниями */
void HobotSClass::enablePowerMain() {
  digitalWrite(MAIN_3V3_EN_PIN, LOW);
}
void HobotSClass::disablePowerMain() {
  digitalWrite(MAIN_3V3_EN_PIN, HIGH);
}
void HobotSClass::enablePowerBLE() {
  digitalWrite(BLE_3V3_EN_PIN, LOW);
}
void HobotSClass::disablePowerBLE() {
  digitalWrite(BLE_3V3_EN_PIN, HIGH);
}
void HobotSClass::enablePowerMatrix() {
  digitalWrite(LEDS_5V_EN_PIN, HIGH);
}
void HobotSClass::disablePowerMatrix() {
  digitalWrite(LEDS_5V_EN_PIN, LOW);
}
void HobotSClass::enablePowerAudio() {
  digitalWrite(AUDIO_5V_EN_PIN, HIGH);
}
void HobotSClass::disablePowerAudio() {
  digitalWrite(AUDIO_5V_EN_PIN, LOW);
}
void HobotSClass::enablePowerMotors() {
  digitalWrite(DRV_5V_EN_PIN, HIGH);
}
void HobotSClass::disablePowerMotors() {
  digitalWrite(DRV_5V_EN_PIN, LOW);
}

/* Методы управления моторами */
void HobotSClass::portAMotorCW() {
  digitalWrite(TB_MA_IN1_PIN, HIGH);
  digitalWrite(TB_MA_IN2_PIN, LOW);
}
void HobotSClass::portAMotorCCW() {
  digitalWrite(TB_MA_IN1_PIN, LOW);
  digitalWrite(TB_MA_IN2_PIN, HIGH);
}
void HobotSClass::portAMotorSpeed(uint8_t _motor_speed) {
  analogWrite(TB_MA_PWM_PIN, _motor_speed);
}
void HobotSClass::portBMotorCW() {
  digitalWrite(TB_MB_IN1_PIN, HIGH);
  digitalWrite(TB_MB_IN2_PIN, LOW);
}
void HobotSClass::portBMotorCCW() {
  digitalWrite(TB_MB_IN1_PIN, LOW);
  digitalWrite(TB_MB_IN2_PIN, HIGH);
}
void HobotSClass::portBMotorSpeed(uint8_t _motor_speed) {
  analogWrite(TB_MB_PWM_PIN, _motor_speed);
}
void HobotSClass::portCMotorCW() {
  digitalWrite(TB_MC_IN1_PIN, HIGH);
  digitalWrite(TB_MC_IN2_PIN, LOW);
}
void HobotSClass::portCMotorCCW() {
  digitalWrite(TB_MC_IN1_PIN, LOW);
  digitalWrite(TB_MC_IN2_PIN, HIGH);
}
void HobotSClass::portCMotorSpeed(uint8_t _motor_speed) {
  analogWrite(TB_MC_PWM_PIN, _motor_speed);
}
void HobotSClass::portDMotorCW() {
  digitalWrite(TB_MD_IN1_PIN, HIGH);
  digitalWrite(TB_MD_IN2_PIN, LOW);
}
void HobotSClass::portDMotorCCW() {
  digitalWrite(TB_MD_IN1_PIN, LOW);
  digitalWrite(TB_MD_IN2_PIN, HIGH);
}
void HobotSClass::portDMotorSpeed(uint8_t _motor_speed) {
  analogWrite(TB_MD_PWM_PIN, _motor_speed);
}
void HobotSClass::portEMotorCW() {
  digitalWrite(TB_ME_IN1_PIN, HIGH);
  digitalWrite(TB_ME_IN2_PIN, LOW);
}
void HobotSClass::portEMotorCCW() {
  digitalWrite(TB_ME_IN1_PIN, LOW);
  digitalWrite(TB_ME_IN2_PIN, HIGH);
}
void HobotSClass::portEMotorSpeed(uint8_t _motor_speed) {
  analogWrite(TB_ME_PWM_PIN, _motor_speed);
}
void HobotSClass::portFMotorCW() {
  digitalWrite(TB_MF_IN1_PIN, HIGH);
  digitalWrite(TB_MF_IN2_PIN, LOW);
}
void HobotSClass::portFMotorCCW() {
  digitalWrite(TB_MF_IN1_PIN, LOW);
  digitalWrite(TB_MF_IN2_PIN, HIGH);
}
void HobotSClass::portFMotorSpeed(uint8_t _motor_speed) {
  analogWrite(TB_MF_PWM_PIN, _motor_speed);
}

/* Методы кнопок */
bool HobotSClass::isBluetoothButtonPressed() {
  if (!digitalRead(BLE_BTN_PIN)) {
    return true;
  }
  else {
    return false;
  }
}
bool HobotSClass::isBluetoothButtonReleased() {
  if (digitalRead(BLE_BTN_PIN)) {
    return true;
  }
  else {
    return false;
  }
}
bool HobotSClass::isLeftButtonPressed() {
  if (!digitalRead(LEFT_BTN_PIN)) {
    return true;
  }
  else {
    return false;
  }
}
bool HobotSClass::isLeftButtonReleased() {
  if (digitalRead(LEFT_BTN_PIN)) {
    return true;
  }
  else {
    return false;
  }
}
bool HobotSClass::isCenterButtonPressed() {
  if (!digitalRead(CENTER_BTN_PIN)) {
    return true;
  }
  else {
    return false;
  }
}
bool HobotSClass::isCenterButtonReleased() {
  if (digitalRead(CENTER_BTN_PIN)) {
    return true;
  }
  else {
    return false;
  }
}
bool HobotSClass::isRightButtonReleased() {
  if (!digitalRead(RIGHT_BTN_PIN)) {
    return true;
  }
  else {
    return false;
  }
}
bool HobotSClass::isRightButtonPressed() {
  if (digitalRead(RIGHT_BTN_PIN)) {
    return true;
  }
  else {
    return false;
  }
}

/* Методы светодиодов кнопок */
void HobotSClass::enableRedButtonLED() {
  digitalWrite(LED_BTN_RED_PIN, HIGH);
}
void HobotSClass::disableRedButtonLED() {
  digitalWrite(LED_BTN_RED_PIN, LOW);
}
void HobotSClass::enableGreenButtonLED() {
  digitalWrite(LED_BTN_GREEN_PIN, HIGH);
}
void HobotSClass::disableGreenButtonLED() {
  digitalWrite(LED_BTN_GREEN_PIN, LOW);
}
void HobotSClass::enableBlueButtonLED() {
  digitalWrite(LED_BTN_BLUE_PIN, HIGH);
}
void HobotSClass::disableBlueButtonLED() {
  digitalWrite(LED_BTN_BLUE_PIN, LOW);
}

/* Методы портов датчиков */

/* Методы взаимодействия с bluetooth */

/* Методы разные */
float HobotSClass::getTemperature() {
  sensors_event_t a, g, temp;
  GyroAcc.getEvent(&a, &g, &temp);
  return temp.temperature;
}