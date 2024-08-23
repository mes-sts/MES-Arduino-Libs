/*
 * Ардуино класс реализующий низкоуровневые API
 * для взаимодействие с 8ми канальным мультиплексором 74HC4051
 * 
 * Даташит на микросхему https://www.ti.com/lit/ds/symlink/cd74hc4051-ep.pdf?ts=1724090204443&ref_url=https%253A%252F%252Fwww.google.com%252F
 * 
 * Copyright (C) 2024. v1.0 / MES
 */

#pragma once
#include "Arduino.h"

// Перечисление доступных каналов 74HC4051
enum HC4051Channels_t : uint8_t {
  HC4051_Y_0 = 0,
  HC4051_Y_1,
  HC4051_Y_2,
  HC4051_Y_3,
  HC4051_Y_4,
  HC4051_Y_5,
  HC4051_Y_6,
  HC4051_Y_7
};

class HC4051 {
  private:
    uint8_t _pins_[3];
    HC4051Channels_t _channel_ = HC4051_Y_0;
  
  public:
    HC4051(uint8_t _s0, uint8_t _s1, uint8_t _s2);

    void begin(void);

    void setPinS0(uint8_t _s0);
    void setPinS1(uint8_t _s1);
    void setPinS2(uint8_t _s2);

    uint8_t getPinS0(void);
    uint8_t getPinS1(void);
    uint8_t getPinS2(void);

    void setChannelY0(void);
    void setChannelY1(void);
    void setChannelY2(void);
    void setChannelY3(void);
    void setChannelY4(void);
    void setChannelY5(void);
    void setChannelY6(void);
    void setChannelY7(void);

    void setChannel(HC4051Channels_t _channel);
};
