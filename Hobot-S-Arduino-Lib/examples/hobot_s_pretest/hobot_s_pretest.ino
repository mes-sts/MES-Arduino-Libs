/*
 * hs_color_sensor_firmware
 * 
 * Тестово-экпериментальный пример для контроллера Hobots S
 * 
 * Tools → Board → STM32 Boards Groups → Generic STM32F4 series
 * Tools → Board part number → Generic F413ZGTx
 * Tools → U(S)ART support → Enable (generic 'Serial')
 * Tools → USB support (if available) → CDC (generic 'Serial' supersed U(S)ART)
 * Tools → Upload method → HID Bootloader 2.2
 * 
 * Copyright (C) 2024. v1.0 / MES
 */


#include <HobotS.h>


void setup() {
  HobotS.allSetup();
  //HobotS.enablePowerMatrix(); // Включенние питания матрицы (disablePowerMatrix())
  //HobotS.enablePowerAudio(); // Включенние питания аудио усилителя (disablePowerAudio())
  //HobotS.enablePowerMotors(); // Включенние питания моторов (disablePowerMotors())
}

void loop() {
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

  /*
  HobotS.portAMotorSpeed(105);
  HobotS.portAMotorCW();
  delay(1000);
  HobotS.portAMotorCCW();
  delay(1000);
  */

  /*
  HobotS.portBMotorSpeed(105);
  HobotS.portBMotorCW();////
  delay(1000);
  HobotS.portBMotorCCW();////
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
  HobotS.portFMotorCW();////
  delay(1000);
  HobotS.portFMotorCCW();////
  delay(1000);
  */

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
  delay(500);
  */
}
