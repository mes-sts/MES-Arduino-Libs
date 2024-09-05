/*
 * hiwonder_serial_bus_servo_check
 * 
 * Тест работы интеллектуальных сервоприводов HiWonder
 * 
 * Вариант для Arduino Mega2560 и котроллера HL Начальный
 * 
 * Интеллектуальный сервопривод подключен в любой из 12 портов, P1 - P12
 * 
 * Ссылка на библиотеку для интеллектуальных сервоприводов https://github.com/mes-sts/MES-Arduino-Libs/tree/main/HiWonder-BusServo
 * 
 * Инструменты → Плата → Arduino Mega or Mega2560
 * 
 * Copyright (C) 2024. v1.0 / MES
 */

// Подключение файла библиотеки
#include <HiWonderBusServo.h>

// Контакт микронтролера для переключения режима работы полудуплексного UART
const byte HALF_DUPLEX_DIR_PIN = 38;
// Адрес сервопривода
const byte SERVO_ID = 1;

// Начальное и конечное положение вала сервопривода
const word POS_1 = 0; // 0 - 1000
const word POS_2 = 1000; // 0 - 1000

const word TIME_POS_1 = 3000; // 0 - 30000
const word TIME_POS_2 = 2000; // 0 - 30000

// Создание объекта для работы с сервоприводом
HiWonderBusServo BusServo(&Serial1, HALF_DUPLEX_DIR_PIN);

void setup() {
  // Настройка скорости отладочного порта
  Serial.begin(115200);
  
  // Настройка интерфейса для взаимодействия с сервоприводом
  BusServo.begin();

  // Переключение сервопривода в режим:
  //HW_SERVO_MODE - контроль угла поворота вала,
  //HW_MOTOR_MODE - контроль скорости и направления вращения вала
  BusServo.setServoOrMotorMode(SERVO_ID, HW_SERVO_MODE);
}

void loop() {
  Serial.print("Move to 1st position: ");
  // Поворот вала сервопривода в позицию 1
  BusServo.setServoMoveTime(SERVO_ID, POS_1, TIME_POS_1);
  delay(4000);
  // Запрос реального положения вала сервопривода в позиции 1
  Serial.println(BusServo.getServoPosition(SERVO_ID));

  Serial.println();
  
  Serial.print("Move to 2st position: ");
  // Поворот вала сервопривода в позицию 2
  BusServo.setServoMoveTime(SERVO_ID, POS_2, TIME_POS_2);
  delay(3000);
  // Запрос реального положения вала сервопривода в позиции 2
  Serial.println(BusServo.getServoPosition(SERVO_ID));

  Serial.println();
}
