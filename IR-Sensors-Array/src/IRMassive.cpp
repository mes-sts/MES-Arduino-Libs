/*
 * Ардуино класс реализующий высокоуровневые API
 * для взаимодействие с массивом ИК датчиков TCRT5000
 * 
 * Даташит на TCRT5000 https://www.vishay.com/docs/83760/tcrt5000.pdf
 * 
 * Copyright (C) 2024. v1.0 / MES
 */

#include "IRMassive.h"

/* КОНСТРУКТОР */
IRMassive::IRMassive(uint8_t _s0, uint8_t _s1, uint8_t _s2, uint8_t _analog_input_pin) : HC4051(_s0, _s1, _s2) {
  _analog_input_pin_ = _analog_input_pin;
}

void IRMassive::begin(void) {
  HC4051::begin();
  pinMode(_analog_input_pin_, INPUT);
}

/* Настройка контакта для получения данных */
void IRMassive::setAnalogInputPin(uint8_t _analog_input_pin) {
  _analog_input_pin_ = _analog_input_pin;
  pinMode(_analog_input_pin_, INPUT);
}
uint8_t IRMassive::getAnalogInputPin(void) {
  return _analog_input_pin_;
}

/* Выбор каналов для получения данных отдельно */
void IRMassive::setCH1(void) {
  HC4051::setChannelY0();
}
void IRMassive::setCH2(void) {
  HC4051::setChannelY1();
}
void IRMassive::setCH3(void) {
  HC4051::setChannelY2();
}
void IRMassive::setCH4(void) {
  HC4051::setChannelY3();
}
void IRMassive::setCH5(void) {
  HC4051::setChannelY4();
}
void IRMassive::setCH6(void) {
  HC4051::setChannelY5();
}
void IRMassive::setCH7(void) {
  HC4051::setChannelY6();
}
void IRMassive::setCH8(void) {
  HC4051::setChannelY7();
}

/* Выбор каналов и получение данных из него */
word IRMassive::getValueFromChannel(IRMassiveCH_t _channel) {
  HC4051::setChannel((HC4051Channels_t)_channel);
  delay(50);
  word value = analogRead(_analog_input_pin_);
  return value;
}
void IRMassive::getValueFromChannel(IRMassiveCH_t _channel, word *_value) {
  HC4051::setChannel((HC4051Channels_t)_channel);
  delay(50);
  *_value = analogRead(_analog_input_pin_);
}

/* Получение данных из отдельно выбранного канала */
word IRMassive::getValueFromAnalogInputPin(void) {
  word value = analogRead(_analog_input_pin_);
  return value;
}
void IRMassive::getValueFromAnalogInputPin(word *_value) {
  *_value = analogRead(_analog_input_pin_);
}
