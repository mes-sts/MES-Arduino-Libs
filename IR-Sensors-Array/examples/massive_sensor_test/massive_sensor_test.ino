/*
 * massive_sensor_test
 * 
 * Тест работы массива инфракрасных датчиков
 *
 * Вариант для Arduino STM32 и котроллера HL Ультра
 * 
 * Инструменты → Плата → STM32 Boards Groups → Generic STM32F1 series
 * Инструменты → Board part number → Generic F103RCTx
 * Инструменты → U(S)ART support → Enable (generic 'Serial')
 * Инструменты → USB support (if available) → CDC (generic 'Serial' supersede U(S)ART)
 * Инструменты → Upload method → HID Bootloader 2.2
 * 
 * Copyright (C) 2024. v1.0 / MES
 */

// Подключение библиотеки для работы с массивом ИК датчиков
#include <IRMassive.h>

// Выводы селектирования каналов
const uint8_t S0 = PA5;
const uint8_t S1 = PB7;
const uint8_t S2 = PB6;

// Вывод чтения значений с каждого аналогового ИК датчика
const uint8_t ANALOG_INPUT_PIN = PA4;

// Создание объекта для работы с массивом ИК датчиков
IRMassive MASSIVE(S0, S1, S2, ANALOG_INPUT_PIN);

void setup() {
  // Настройка разрешения АЦП (Актуально для STM32)
  analogReadResolution(10);
  // Настройка скорости отладочного порта
  Serial.begin(115200);
  // Запуск массива датчиков
  MASSIVE.begin();
}

void loop() {
  // Переменные для хранения значений датчиков каналов
  word value1, value2, value3, value4, value5, value6, value7, value8;

  // Получение значений от каждого датчика
  value1 = MASSIVE.getValueFromChannel(IR_MASSIVE_CH_1);
  value2 = MASSIVE.getValueFromChannel(IR_MASSIVE_CH_2);
  value3 = MASSIVE.getValueFromChannel(IR_MASSIVE_CH_3);
  value4 = MASSIVE.getValueFromChannel(IR_MASSIVE_CH_4);
  value5 = MASSIVE.getValueFromChannel(IR_MASSIVE_CH_5);
  value6 = MASSIVE.getValueFromChannel(IR_MASSIVE_CH_6);
  value7 = MASSIVE.getValueFromChannel(IR_MASSIVE_CH_7);
  value8 = MASSIVE.getValueFromChannel(IR_MASSIVE_CH_8);

  // Вывод значений в "Монитор порта"
  Serial.print("CH1: ");
  Serial.println(value1);
  Serial.print("CH2: ");
  Serial.println(value2);
  Serial.print("CH3: ");
  Serial.println(value3);
  Serial.print("CH4: ");
  Serial.println(value4);
  Serial.print("CH5: ");
  Serial.println(value5);
  Serial.print("CH6: ");
  Serial.println(value6);
  Serial.print("CH7: ");
  Serial.println(value7);
  Serial.print("CH8: ");
  Serial.println(value8);
  Serial.println();
}
