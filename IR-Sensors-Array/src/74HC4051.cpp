/*
 * Ардуино класс реализующий низкоуровневые API
 * для взаимодействие с 8ми канальным мультиплексором 74HC4051
 * 
 * Даташит на микросхему https://www.ti.com/lit/ds/symlink/cd74hc4051-ep.pdf?ts=1724090204443&ref_url=https%253A%252F%252Fwww.google.com%252F
 * 
 * Copyright (C) 2024. v1.0 / MES
 */

#include "74HC4051.h"

/* КОНСТРУКТОР */
HC4051::HC4051(uint8_t _s0, uint8_t _s1, uint8_t _s2) {
  _pins_[0] = _s0;
  _pins_[1] = _s1;
  _pins_[2] = _s2;
}

/* Настройка всех выводов */
void HC4051::begin(void) {
  pinMode(_pins_[0], OUTPUT);
  pinMode(_pins_[1], OUTPUT);
  pinMode(_pins_[2], OUTPUT);
}

/* Настройка выводов раздельно */
void HC4051::setPinS0(uint8_t _s0) {
  _pins_[0] = _s0;
  pinMode(_pins_[0], OUTPUT);
}
void HC4051::setPinS1(uint8_t _s1) {
  _pins_[1] = _s1;
  pinMode(_pins_[1], OUTPUT);
}
void HC4051::setPinS2(uint8_t _s2) {
  _pins_[2] = _s2;
  pinMode(_pins_[2], OUTPUT);
}

/* Получение настроенных выводов */
uint8_t HC4051::getPinS0(void) {
  return _pins_[0];
}
uint8_t HC4051::getPinS1(void) {
  return _pins_[1];
}
uint8_t HC4051::getPinS2(void) {
  return _pins_[2];
}

/* Выбор каналов отдельно */
void HC4051::setChannelY0(void) {
  digitalWrite(_pins_[0], LOW);
  digitalWrite(_pins_[1], LOW);
  digitalWrite(_pins_[2], LOW);

  _channel_ = HC4051_Y_0;
}
void HC4051::setChannelY1(void) {
  digitalWrite(_pins_[0], HIGH);
  digitalWrite(_pins_[1], LOW);
  digitalWrite(_pins_[2], LOW);

  _channel_ = HC4051_Y_1;
}
void HC4051::setChannelY2(void) {
  digitalWrite(_pins_[0], LOW);
  digitalWrite(_pins_[1], HIGH);
  digitalWrite(_pins_[2], LOW);

  _channel_ = HC4051_Y_2;
}
void HC4051::setChannelY3(void) {
  digitalWrite(_pins_[0], HIGH);
  digitalWrite(_pins_[1], HIGH);
  digitalWrite(_pins_[2], LOW);

  _channel_ = HC4051_Y_3;
}
void HC4051::setChannelY4(void) {
  digitalWrite(_pins_[0], LOW);
  digitalWrite(_pins_[1], LOW);
  digitalWrite(_pins_[2], HIGH);

  _channel_ = HC4051_Y_4;
}
void HC4051::setChannelY5(void) {
  digitalWrite(_pins_[0], HIGH);
  digitalWrite(_pins_[1], LOW);
  digitalWrite(_pins_[2], HIGH);

  _channel_ = HC4051_Y_5;
}
void HC4051::setChannelY6(void) {
  digitalWrite(_pins_[0], LOW);
  digitalWrite(_pins_[1], HIGH);
  digitalWrite(_pins_[2], HIGH);

  _channel_ = HC4051_Y_6;
}
void HC4051::setChannelY7(void) {
  digitalWrite(_pins_[0], HIGH);
  digitalWrite(_pins_[1], HIGH);
  digitalWrite(_pins_[2], HIGH);

  _channel_ = HC4051_Y_7;
}

/* Выбор канала по номеру */
void HC4051::setChannel(HC4051Channels_t _channel) {
  HC4051Channels_t new_channel = _channel;
  
  if (new_channel != _channel_) {
    if (_channel == HC4051_Y_0) {
      setChannelY0();
    }
    else if (_channel == HC4051_Y_1) {
      setChannelY1();
    }
    else if (_channel == HC4051_Y_2) {
      setChannelY2();
    }
    else if (_channel == HC4051_Y_3) {
      setChannelY3();
    }
    else if (_channel == HC4051_Y_4) {
      setChannelY4();
    }
    else if (_channel == HC4051_Y_5) {
      setChannelY5();
    }
    else if (_channel == HC4051_Y_6) {
      setChannelY6();
    }
    else if (_channel == HC4051_Y_7) {
      setChannelY7();
    }

    _channel_ = new_channel;
  }    
}
