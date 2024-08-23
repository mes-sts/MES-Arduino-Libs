/*
 * Ардуино класс реализующий высокоуровневые API
 * для взаимодействие с массивом ИК датчиков TCRT5000
 * 
 * Даташит на TCRT5000 https://www.vishay.com/docs/83760/tcrt5000.pdf
 * 
 * Copyright (C) 2024. v1.0 / MES
 */

#pragma once
#include "74HC4051.h"

// Перечисление доступных каналов массива ИК датчиков
enum IRMassiveCH_t : uint8_t {
  IR_MASSIVE_CH_1 = 0,
  IR_MASSIVE_CH_2,
  IR_MASSIVE_CH_3,
  IR_MASSIVE_CH_4,
  IR_MASSIVE_CH_5,
  IR_MASSIVE_CH_6,
  IR_MASSIVE_CH_7,
  IR_MASSIVE_CH_8
};

class IRMassive : public HC4051 {
  private:
    uint8_t _analog_input_pin_;

  public:
    IRMassive(uint8_t _s0, uint8_t _s1, uint8_t _s2, uint8_t _analog_input_pin);

    void begin(void);

    void setAnalogInputPin(uint8_t _analog_input_pin);
    uint8_t getAnalogInputPin(void);

    void setCH1(void);
    void setCH2(void);
    void setCH3(void);
    void setCH4(void);
    void setCH5(void);
    void setCH6(void);
    void setCH7(void);
    void setCH8(void);

    word getValueFromChannel(IRMassiveCH_t _channel);
    void getValueFromChannel(IRMassiveCH_t _channel, word *_value);

    word getValueFromAnalogInputPin(void);
    void getValueFromAnalogInputPin(word *_value);
};
