/*
 * hobot_s_pretest
 * 
 * Тестово-экпериментальный пример для контроллера Hobots S
 * 
 * Tools → Board → STM32 Boards Groups → Generic STM32F4 series
 * Tools → Board part number → Generic F413ZGTx
 * Tools → U(S)ART support → Enable (generic 'Serial')
 * Tools → USB support (if available) → CDC (generic 'Serial' supersed U(S)ART)
 * Tools → Upload method → HID Bootloader 2.2
 * 
 * Copyright (C) 2024. v1.1 / MES
 */


#include <HobotS.h>


void setup() {
  HobotS.setup();
  //HobotS.enablePowerMatrix(); // Включенние питания матрицы (disablePowerMatrix())
  //HobotS.enablePowerAudio(); // Включенние питания аудио усилителя (disablePowerAudio())
  //HobotS.enablePowerMotors(); // Включенние питания моторов (disablePowerMotors())
  //pinMode(AUDIO_OUT_PIN, OUTPUT);
  //tone(AUDIO_OUT_PIN, 2000);
}

void loop() {
// ДАТЧИК ЦВЕТА
  /*
  SerialDebug.println(HobotS.portAColorSensorGetRedCh());
  delay(500);
  SerialDebug.println(HobotS.portAColorSensorGetGreenCh());
  delay(500);
  SerialDebug.println(HobotS.portAColorSensorGetBlueCh());
  delay(500);
  SerialDebug.println(HobotS.portAColorSensorGetClearCh());
  delay(500);
  HobotS.portAColorSensorSetLEDBrightness(255);
  delay(500);
  SerialDebug.println();
  */
  /*
  SerialDebug.println(HobotS.portBColorSensorGetRedCh());
  delay(500);
  SerialDebug.println(HobotS.portBColorSensorGetGreenCh());
  delay(500);
  SerialDebug.println(HobotS.portBColorSensorGetBlueCh());
  delay(500);
  SerialDebug.println(HobotS.portBColorSensorGetClearCh());
  delay(500);
  HobotS.portBColorSensorSetLEDBrightness(255);
  delay(500);
  SerialDebug.println();
  */
  /*
  SerialDebug.println(HobotS.portCColorSensorGetRedCh());
  delay(500);
  SerialDebug.println(HobotS.portCColorSensorGetGreenCh());
  delay(500);
  SerialDebug.println(HobotS.portCColorSensorGetBlueCh());
  delay(500);
  SerialDebug.println(HobotS.portCColorSensorGetClearCh());
  delay(500);
  HobotS.portCColorSensorSetLEDBrightness(255);
  delay(500);
  SerialDebug.println();
  */
  /*
  SerialDebug.println(HobotS.portDColorSensorGetRedCh());
  delay(500);
  SerialDebug.println(HobotS.portDColorSensorGetGreenCh());
  delay(500);
  SerialDebug.println(HobotS.portDColorSensorGetBlueCh());
  delay(500);
  SerialDebug.println(HobotS.portDColorSensorGetClearCh());
  delay(500);
  HobotS.portDColorSensorSetLEDBrightness(255);
  delay(500);
  SerialDebug.println();
  */
  /*
  SerialDebug.println(HobotS.portEColorSensorGetRedCh());
  delay(500);
  SerialDebug.println(HobotS.portEColorSensorGetGreenCh());
  delay(500);
  SerialDebug.println(HobotS.portEColorSensorGetBlueCh());
  delay(500);
  SerialDebug.println(HobotS.portEColorSensorGetClearCh());
  delay(500);
  HobotS.portEColorSensorSetLEDBrightness(255);
  delay(500);
  SerialDebug.println();
  */
  /*
  SerialDebug.println(HobotS.portFColorSensorGetRedCh());
  delay(500);
  SerialDebug.println(HobotS.portFColorSensorGetGreenCh());
  delay(500);
  SerialDebug.println(HobotS.portFColorSensorGetBlueCh());
  delay(500);
  SerialDebug.println(HobotS.portFColorSensorGetClearCh());
  delay(500);
  HobotS.portFColorSensorSetLEDBrightness(255);
  delay(500);
  SerialDebug.println();
  */

// ДАТЧИК РАССТОЯНИЯ
  /*
  HobotS.portADistanceSensorSetLED(0, 255, 200, 100);
  delay(100);
  HobotS.portADistanceSensorSetLED(1, 100, 15, 0);
  delay(100);
  HobotS.portADistanceSensorSetLED(2, 0, 200, 80);
  delay(100);
  HobotS.portADistanceSensorSetLED(3, 180, 0, 100);
  delay(100);
  HobotS.portADistanceSensorSetLED(0, 0, 200, 220);
  delay(100);
  HobotS.portADistanceSensorSetLED(1, 10, 0, 100);
  delay(100);
  HobotS.portADistanceSensorSetLED(2, 175, 200, 160);
  delay(100);
  HobotS.portADistanceSensorSetLED(3, 60, 150, 10);
  delay(100);
  SerialDebug.println(HobotS.portADistanceSensorGetDistance());
  delay(500);
  */
  /*
  HobotS.portBDistanceSensorSetLED(0, 255, 200, 100);
  delay(100);
  HobotS.portBDistanceSensorSetLED(1, 100, 15, 0);
  delay(100);
  HobotS.portBDistanceSensorSetLED(2, 0, 200, 80);
  delay(100);
  HobotS.portBDistanceSensorSetLED(3, 180, 0, 100);
  delay(100);
  HobotS.portBDistanceSensorSetLED(0, 0, 200, 220);
  delay(100);
  HobotS.portBDistanceSensorSetLED(1, 10, 0, 100);
  delay(100);
  HobotS.portBDistanceSensorSetLED(2, 175, 200, 160);
  delay(100);
  HobotS.portBDistanceSensorSetLED(3, 60, 150, 10);
  delay(100);
  SerialDebug.println(HobotS.portBDistanceSensorGetDistance());
  delay(500);
  */
  /*
  HobotS.portCDistanceSensorSetLED(0, 255, 200, 100);
  delay(100);
  HobotS.portCDistanceSensorSetLED(1, 100, 15, 0);
  delay(100);
  HobotS.portCDistanceSensorSetLED(2, 0, 200, 80);
  delay(100);
  HobotS.portCDistanceSensorSetLED(3, 180, 0, 100);
  delay(100);
  HobotS.portCDistanceSensorSetLED(0, 0, 200, 220);
  delay(100);
  HobotS.portCDistanceSensorSetLED(1, 10, 0, 100);
  delay(100);
  HobotS.portCDistanceSensorSetLED(2, 175, 200, 160);
  delay(100);
  HobotS.portCDistanceSensorSetLED(3, 60, 150, 10);
  delay(100);
  SerialDebug.println(HobotS.portCDistanceSensorGetDistance());
  delay(500);
  */
  /*
  HobotS.portDDistanceSensorSetLED(0, 255, 200, 100);
  delay(100);
  HobotS.portDDistanceSensorSetLED(1, 100, 15, 0);
  delay(100);
  HobotS.portDDistanceSensorSetLED(2, 0, 200, 80);
  delay(100);
  HobotS.portDDistanceSensorSetLED(3, 180, 0, 100);
  delay(100);
  HobotS.portDDistanceSensorSetLED(0, 0, 200, 220);
  delay(100);
  HobotS.portDDistanceSensorSetLED(1, 10, 0, 100);
  delay(100);
  HobotS.portDDistanceSensorSetLED(2, 175, 200, 160);
  delay(100);
  HobotS.portDDistanceSensorSetLED(3, 60, 150, 10);
  delay(100);
  SerialDebug.println(HobotS.portDDistanceSensorGetDistance());
  delay(500);
  */
  /*
  HobotS.portEDistanceSensorSetLED(0, 255, 200, 100);
  delay(100);
  HobotS.portEDistanceSensorSetLED(1, 100, 15, 0);
  delay(100);
  HobotS.portEDistanceSensorSetLED(2, 0, 200, 80);
  delay(100);
  HobotS.portEDistanceSensorSetLED(3, 180, 0, 100);
  delay(100);
  HobotS.portEDistanceSensorSetLED(0, 0, 200, 220);
  delay(100);
  HobotS.portEDistanceSensorSetLED(1, 10, 0, 100);
  delay(100);
  HobotS.portEDistanceSensorSetLED(2, 175, 200, 160);
  delay(100);
  HobotS.portEDistanceSensorSetLED(3, 60, 150, 10);
  delay(100);
  SerialDebug.println(HobotS.portEDistanceSensorGetDistance());
  delay(500);
  */
  /*
  HobotS.portFDistanceSensorSetLED(0, 255, 200, 100);
  delay(100);
  HobotS.portFDistanceSensorSetLED(1, 100, 15, 0);
  delay(100);
  HobotS.portFDistanceSensorSetLED(2, 0, 200, 80);
  delay(100);
  HobotS.portFDistanceSensorSetLED(3, 180, 0, 100);
  delay(100);
  HobotS.portFDistanceSensorSetLED(0, 0, 200, 220);
  delay(100);
  HobotS.portFDistanceSensorSetLED(1, 10, 0, 100);
  delay(100);
  HobotS.portFDistanceSensorSetLED(2, 175, 200, 160);
  delay(100);
  HobotS.portFDistanceSensorSetLED(3, 60, 150, 10);
  delay(100);
  SerialDebug.println(HobotS.portFDistanceSensorGetDistance());
  delay(500);
  */

// ВСТРОЕННАЯ МТАРИЦА СВЕТОДИОДОВ
  /*
  HobotS.matrixAllClear();
  for(uint8_t i = 0; i < HobotS.matrixGetNumPixels(); i++) {
    HobotS.matrixSetPixelColor(i, 255, 0, 0); // R G B
    delay(100);
  }
  HobotS.matrixAllClear();
  for(uint8_t i = 0; i < HobotS.matrixGetNumPixels(); i++) {
    HobotS.matrixSetPixelColor(i, 0, 255, 0); // R G B
    delay(100);
  }
  HobotS.matrixAllClear();
  for(uint8_t i = 0; i < HobotS.matrixGetNumPixels(); i++) {
    HobotS.matrixSetPixelColor(i, 0, 0, 255); // R G B
    delay(100);
  }
  */

// ВСТРОЕННЫЙ АКСЕЛЕРОМЕТР И ГОРОСКОП
  /*
  SerialDebug.print("Acceleration X: ");
  SerialDebug.print(HobotS.accelerationGetX());
  SerialDebug.print(", Y: ");
  SerialDebug.print(HobotS.accelerationGetY());
  SerialDebug.print(", Z: ");
  SerialDebug.print(HobotS.accelerationGetZ());
  SerialDebug.println(" m/s^2");
  SerialDebug.print("Rotation X: ");
  SerialDebug.print(HobotS.gyroGetX());
  SerialDebug.print(", Y: ");
  SerialDebug.print(HobotS.gyroGetY());
  SerialDebug.print(", Z: ");
  SerialDebug.print(HobotS.gyroGetZ());
  SerialDebug.println(" rad/s");
  SerialDebug.println("");
  delay(500);
  */

// ПРИВОДЫ МОТОРОВ С РЕДУКТОРАМИ
  /*
  HobotS.portAMotorSpeed(105);
  HobotS.portAMotorCW();
  delay(1000);
  HobotS.portAMotorCCW();
  delay(1000);
  */
  /*
  HobotS.portBMotorSpeed(105);
  HobotS.portBMotorCW();
  delay(1000);
  HobotS.portBMotorCCW();
  delay(1000);
  */
  /*
  HobotS.portCMotorSpeed(105);
  HobotS.portCMotorCW();
  delay(1000);
  HobotS.portCMotorCCW();
  delay(1000);
  */
  /*
  HobotS.portDMotorSpeed(105);
  HobotS.portDMotorCW();
  delay(1000);
  HobotS.portDMotorCCW();
  delay(1000);
  */
  /*
  HobotS.portEMotorSpeed(105);
  HobotS.portEMotorCW();
  delay(1000);
  HobotS.portEMotorCCW();
  delay(1000);
  */
  /*
  HobotS.portFMotorSpeed(105);
  HobotS.portFMotorCW();
  delay(1000);
  HobotS.portFMotorCCW();
  delay(1000);
  */

// ВСТРОЕННЫЕ КНОПКИ
  /*
  if (HobotS.isBluetoothButtonPressed()) {
    SerialDebug.println("BLE P");
  }
  if (HobotS.isBluetoothButtonReleased()) {
    SerialDebug.println("BLE R");
  }

  if (HobotS.isLeftButtonPressed()) {
    SerialDebug.println("LEFT P");
  }
  if (HobotS.isLeftButtonReleased()) {
    SerialDebug.println("LEFT R");
  }

  if (HobotS.isCenterButtonPressed()) {
    SerialDebug.println("CENTER P");
  }
  if (HobotS.isCenterButtonReleased()) {
    SerialDebug.println("CENTER R");
  }

  if (HobotS.isRightButtonReleased()) {
    SerialDebug.println("RIGHT P");
  }
  if (HobotS.isRightButtonPressed()) {
    SerialDebug.println("RIGHT R");
  }
  SerialDebug.println();
  delay(200);
  */

// НЕОТСОРТИРОВАННОЕ
  /*
  SerialDebug.print("Temperature: ");
  SerialDebug.println(HobotS.getTemperature());
  */
}
