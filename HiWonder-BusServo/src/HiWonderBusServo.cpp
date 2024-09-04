/*
 * Класс для Arduino IDE реализующий взаимодействие
 * с программируемыми сервоприводами Hiwonder https://www.hiwonder.com/
 * 
 * Copyright (C) 2024. v1.0 / MES
 */


#include "HiWonderBusServo.h"

// ########## CONSTRUCTOR ##########
/*
 * @brief: конструктор с использованием HardwareSerial, контакта переключения приема/передачи
 * @param _h_serial: доступ к методам объекта класса HardwareSerial
 * @param _dir_pin: контакт перключения приема/передачи полудуплексного режима
 */
HiWonderBusServo::HiWonderBusServo(HardwareSerial *_h_serial, uint8_t _dir_pin) {
  _h_serial_ = _h_serial;
  _pin_direction_ = _dir_pin;
}


// ########## PROTECTED ##########
/*
 * @brief: передача пакета данных приводу через полудуплексный UART
 * @param _send_pack: массив байтов (пакет) для передачи приводу
 * @param _pack_length: длина массива (пакета)
 */
void HiWonderBusServo::HW_BS_SendPacket(unsigned char *_send_pack, unsigned int _pack_length) {
  while (_h_serial_->available()) {
    _h_serial_->read();
  }

  digitalWrite(_pin_direction_, HIGH);
  _h_serial_->write(_send_pack, _pack_length); // Отправка пакета побайтово
  _h_serial_->flush(); // Очистка буфера приема
  digitalWrite(_pin_direction_, LOW);
}
/*
 * @brief: прием пакета данных от привода через полудуплексный UART
 * @param _return_data: адрес массива для передачи полезных данных от привода
 * @param _answer_lenght: длина пакета данных от привода
 *   HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_4 - 4 байта
 *   HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_5 - 5 байт
 *   HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_7 - 7 байт
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 */
void HiWonderBusServo::HW_BS_ReceivePacket(uint8_t *_return_data, uint8_t _answer_lenght, uint8_t _id) {
  uint8_t attempts = 0;
  uint8_t receive_buffer[10];

  while((_h_serial_->available() < HW_SERVO_RECIEVED_BYTE_BUFFER_MIN) & (attempts < HW_SERVO_ATTEMPTS_COUNT_MAX)) {
		attempts++;
		delayMicroseconds(HW_SERVO_TIMEOUT_CHEKING_BUFFER);
	}

  while (_h_serial_->available() > 0) {
    receive_buffer[0] = _h_serial_->read();
    if (receive_buffer[0] == HW_SERVO_PACKET_HEADER) { // Первый байт заголовка
      receive_buffer[1] = _h_serial_->read();
      if (receive_buffer[1] == HW_SERVO_PACKET_HEADER) { // Второй байт заголовка
        receive_buffer[2] = _h_serial_->read(); // ID
        if (receive_buffer[2] == _id) {
          receive_buffer[3] = _h_serial_->read(); // Длина команды
          receive_buffer[4] = _h_serial_->read(); // Номер команды

          if (_answer_lenght == HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_4) {
            receive_buffer[5] = _h_serial_->read(); // Запрошенное значение
            receive_buffer[6] = _h_serial_->read(); // Контрольная сумма
            // Вычисление контрольной суммы полученого пакета
            uint8_t calc_crc = (~(receive_buffer[2] + receive_buffer[3] + receive_buffer[4] + receive_buffer[5])) & 0xFF;
            if (receive_buffer[6] != calc_crc) { // Если ошибка
              _return_data[0] = 0;
            }
            else {
              _return_data[0] = receive_buffer[5];
            }
          }
          if (_answer_lenght == HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_5) {
            receive_buffer[5] = _h_serial_->read(); // Запрошенное значение (младший байт)
            receive_buffer[6] = _h_serial_->read(); // Запрошенное значение (старший байт)
            receive_buffer[7] = _h_serial_->read(); // Контрольная сумма
            // Вычисление контрольной суммы полученого пакета
            uint8_t calc_crc = (~(receive_buffer[2] + receive_buffer[3] + receive_buffer[4] + receive_buffer[5] + receive_buffer[6])) & 0xFF;
            if (receive_buffer[7] != calc_crc) { // Если ошибка
              _return_data[0] = 0;
              _return_data[1] = 0;
            }
            else {
              _return_data[0] = receive_buffer[6]; // Старший
              _return_data[1] = receive_buffer[5]; // Младший
            }
          }
          if (_answer_lenght == HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_7) {
            receive_buffer[5] = _h_serial_->read(); // Запрошенное значение 1 (младший байт)
            receive_buffer[6] = _h_serial_->read(); // Запрошенное значение 1 (старший байт)
            receive_buffer[7] = _h_serial_->read(); // Запрошенное значение 2 (младший байт)
            receive_buffer[8] = _h_serial_->read(); // Запрошенное значение 2 (старший байт)
            receive_buffer[9] = _h_serial_->read(); // Контрольная сумма
            // Вычисление контрольной суммы полученого пакета
            uint8_t calc_crc = (~(receive_buffer[2] + receive_buffer[3] + receive_buffer[4] + receive_buffer[5] + receive_buffer[6] + receive_buffer[7] + receive_buffer[8])) & 0xFF;
            if (receive_buffer[9] != calc_crc) { // Если ошибка
              _return_data[0] = 0;
              _return_data[1] = 0;
              _return_data[2] = 0;
              _return_data[3] = 0;
            }
            else {
              _return_data[0] = receive_buffer[6]; // Старший 1
              _return_data[1] = receive_buffer[5]; // Младший 1
              _return_data[2] = receive_buffer[8]; // Старший 2
              _return_data[3] = receive_buffer[7]; // Младший 2
            }
          }
        }
      }
    }
  }
}


// ########## PUBLIC ##########
/* 
 * @brief: начать соединение с приводом со скоростью 115200
 * @note: по умолчанию включается прием данных от шины
 */
void HiWonderBusServo::begin(void) {
  pinMode(_pin_direction_, OUTPUT); // Вывод направления настроен на выход
  digitalWrite(_pin_direction_, LOW); // Переключение на прием данных
  _h_serial_->begin(HW_SERVO_SERIAL_BAUDRATE);
  _h_serial_->flush(); // Очистка буфера приема
}
/* 
 * @brief: завершить соединение с приводом
 */
void HiWonderBusServo::end(void) {
  _pin_direction_ = 0;
  _h_serial_->end();
}
/*
 * @brief: поворот вала привода в желаемое положение за желаемое время
 *   Запускает привод сразу!
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @param _position: желаемое положенение вала
 *   0 - 1000 (1500)
 * @param _time: время за которое вал должен переместиться в _position
 *   0 - 30000мс (0 - 30сек)
 * @note:
 *   SERVO_MOVE_TIME_WRITE
 */
void HiWonderBusServo::setServoMoveTime(uint8_t _id, uint16_t _position, uint16_t _time) {
  // Фильтр максимального значения положения. 0 - 1000 (1500)
  if (_position > HW_SERVO_SHAFT_POSITION_MAX) {
    _position = HW_SERVO_SHAFT_POSITION_MAX;
  }
  // Фильтр максимального значения времени. 0 - 30сек
  if (_time > HW_SERVO_MOVE_TIME_VALUE_MAX) {
    _time = HW_SERVO_MOVE_TIME_VALUE_MAX;
  }
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_MOVE_TIME_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_MOVE_TIME_WRITE;
  packet[4] = HW_CMD_SERVO_MOVE_TIME_WRITE;
  packet[5] = _position;
  packet[6] = (_position >> 8);
  packet[7] = _time;
  packet[8] = (_time >> 8);
  packet[9] = (~(_id + packet[3] + packet[4] + packet[5] + packet[6] + packet[7] + packet[8])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_MOVE_TIME_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: получение поворота вала привода в желаемое положение за желаемое время
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @param *_position: установленное желаемое положение вала
 *   0 - 1000 (1500)
 * @param *_time: установленное желаемое время перемещения
 *   0 - 30000мс (0 - 30сек)
 * @note: получение через ссылку
 *   SERVO_MOVE_TIME_READ
 */
void HiWonderBusServo::getServoMoveTime(uint8_t _id, uint16_t *_position, uint16_t *_time) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_MOVE_TIME_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_MOVE_TIME_READ;
  packet[4] = HW_CMD_SERVO_MOVE_TIME_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_MOVE_TIME_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_7, _id);

  *_position = (packet[0] << 8) | packet[1];
  *_time = (packet[2] << 8) | packet[3];
}
/*
 * @brief: поворот вала привода в желаемое положение за желаемое время
 *   Запускает привод не сразу! Связан с servoMoveStart и servoMoveStop!
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @param _position: желаемое положенение вала
 *   0 - 1000 (1500)
 * @param _time: время за которое вал должен переместиться в _position
 *   0 - 30000мс (0 - 30сек)
 * @note:
 *   SERVO_MOVE_TIME_WAIT_WRITE
 */
void HiWonderBusServo::setServoMoveTimeWait(uint8_t _id, uint16_t _position, uint16_t _time) {
  // Фильтр максимального значения положения. 0 - 1000 (1500)
  if (_position > HW_SERVO_SHAFT_POSITION_MAX) {
    _position = HW_SERVO_SHAFT_POSITION_MAX;
  }
  // Фильтр максимального значения времени. 0 - 30сек
  if (_time > HW_SERVO_MOVE_TIME_VALUE_MAX) {
    _time = HW_SERVO_MOVE_TIME_VALUE_MAX;
  }
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_MOVE_TIME_WAIT_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_MOVE_TIME_WAIT_WRITE;
  packet[4] = HW_CMD_SERVO_MOVE_TIME_WAIT_WRITE;
  packet[5] = _position;
  packet[6] = (_position >> 8);
  packet[7] = _time;
  packet[8] = (_time >> 8);
  packet[9] = (~(_id + packet[3] + packet[4] + packet[5] + packet[6] + packet[7] + packet[8])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_MOVE_TIME_WAIT_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: получение поворота вала привода в желаемое положение за желаемое время
 *   Значения из регистра ожидания в связке с методами servoMoveStart и servoMoveStop!
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @param *_position: установленное желаемое положение вала
 *   0 - 1000 (1500)
 * @param *_time: установленное желаемое время перемещения
 *   0 - 30000мс (0 - 30сек)
 * @note: получение через ссылку
 *   SERVO_MOVE_TIME_WAIT_READ
 */
void HiWonderBusServo::getServoMoveTimeWait(uint8_t _id, uint16_t *_position, uint16_t *_time) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_MOVE_TIME_WAIT_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_MOVE_TIME_WAIT_READ;
  packet[4] = HW_CMD_SERVO_MOVE_TIME_WAIT_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_MOVE_TIME_WAIT_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_7, _id);

  *_position = (packet[0] << 8) | packet[1];
  *_time = (packet[2] << 8) | packet[3];
}
/*
 * @brief: разрешить приводу начать движение
 *   Связан с servoMoveTimeWait!
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @note:
 *   SERVO_MOVE_START
 */
void HiWonderBusServo::setServoMoveStart(uint8_t _id) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_MOVE_START + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_MOVE_START;
  packet[4] = HW_CMD_SERVO_MOVE_START;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_MOVE_START + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: зарпетить приводу продолжать движение
 *   Связан с servoMoveTimeWait!
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @note:
 *   SERVO_MOVE_STOP
 */
void HiWonderBusServo::setServoMoveStop(uint8_t _id) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_MOVE_STOP + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_MOVE_STOP;
  packet[4] = HW_CMD_SERVO_MOVE_STOP;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_MOVE_STOP + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: установка нового номера привода
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @param _new_id: новый номер для выбранного привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @note:
 *   SERVO_ID_WRITE
 */
void HiWonderBusServo::setServoID(uint8_t _id, uint8_t _new_id) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_ID_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_ID_WRITE;
  packet[4] = HW_CMD_SERVO_ID_WRITE;
  packet[5] = _new_id;
  packet[6] = (~(_id + packet[3] + packet[4] + packet[5])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_ID_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: получение номера привода на шине
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @return: номер привода
 * @note:
 *   SERVO_ID_READ
 */
uint8_t HiWonderBusServo::getServoID(uint8_t _id) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_ID_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_ID_READ;
  packet[4] = HW_CMD_SERVO_ID_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_ID_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_4, _id);

  return (packet[0]); // 0 - если ошибка
}
/*
 * @brief: подстройка угла смещения
 *   сбрасывается после отключения питания
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @param _offset_adjust: значение подстройки угла смещения
 *   от -125 до 125
 * @note:
 *   SERVO_ANGLE_OFFSET_ADJUST
 */
void HiWonderBusServo::setServoAngleOffsetAdjust(uint8_t _id, int8_t _offset_adjust) {
  // Фильтр минимального и максимального значения подстройки угла смещения. +-125
  if (_offset_adjust < HW_SERVO_ANGLE_OFFSET_MIN) {
    _offset_adjust = HW_SERVO_ANGLE_OFFSET_MIN;
  }
  if (_offset_adjust > HW_SERVO_ANGLE_OFFSET_MAX) {
    _offset_adjust = HW_SERVO_ANGLE_OFFSET_MAX;
  }
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_ANGLE_OFFSET_ADJUST + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_ANGLE_OFFSET_ADJUST;
  packet[4] = HW_CMD_SERVO_ANGLE_OFFSET_ADJUST;
  packet[5] = _offset_adjust;
  packet[6] = (~(_id + packet[3] + packet[4] + packet[5])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_ANGLE_OFFSET_ADJUST + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: подстройка угла смещения
 *   сохраняется после отключения питания
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @param _offset: значение угла смещения
 *   от -125 до 125
 * @note:
 *   SERVO_ANGLE_OFFSET_WRITE
 */
void HiWonderBusServo::setServoAngleOffset(uint8_t _id, int8_t _offset) {
  // Фильтр минимального и максимального значения угла смещения. +-125
  if (_offset < HW_SERVO_ANGLE_OFFSET_MIN) {
    _offset = HW_SERVO_ANGLE_OFFSET_MIN;
  }
  if (_offset > HW_SERVO_ANGLE_OFFSET_MAX) {
    _offset = HW_SERVO_ANGLE_OFFSET_MAX;
  }
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_ANGLE_OFFSET_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_ANGLE_OFFSET_WRITE;
  packet[4] = HW_CMD_SERVO_ANGLE_OFFSET_WRITE;
  packet[5] = _offset;
  packet[6] = (~(_id + packet[3] + packet[4] + packet[5])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_ANGLE_OFFSET_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: получение угла смещения
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @return: угол смещения
 * @note:
 *   SERVO_ANGLE_OFFSET_READ
 */
int8_t HiWonderBusServo::getServoAngleOffset(uint8_t _id) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_ANGLE_OFFSET_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_ANGLE_OFFSET_READ;
  packet[4] = HW_CMD_SERVO_ANGLE_OFFSET_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_ANGLE_OFFSET_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_4, _id);

  return ((int8_t)packet[0]); // 0 - если ошибка или отсутствует смещение
}
/*
 * @brief: ограничение максимального и минимального угла поворота вала
 *   сохраняется после отключения питания
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @param _angle_min_limit: минимальное значение угла
 *   0 - 1000 (1500)
 * @param _angle_max_limit: минимальное значение угла
 *   0 - 1000 (1500)
 * @note:
 *   SERVO_ANGLE_LIMIT_WRITE
 */
void HiWonderBusServo::setServoAngleLimit(uint8_t _id, uint16_t _angle_min_limit, uint16_t _angle_max_limit) {
  // Фильтр минимального и максимального угла поворота вала. 0 - 1000 (1500)
  if (_angle_min_limit > HW_SERVO_SHAFT_POSITION_MAX) {
    _angle_min_limit = HW_SERVO_SHAFT_POSITION_MAX;
  }
  if (_angle_max_limit > HW_SERVO_SHAFT_POSITION_MAX) {
    _angle_max_limit = HW_SERVO_SHAFT_POSITION_MAX;
  }
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_ANGLE_LIMIT_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_ANGLE_LIMIT_WRITE;
  packet[4] = HW_CMD_SERVO_ANGLE_LIMIT_WRITE;
  packet[5] = _angle_min_limit;
  packet[6] = (_angle_min_limit >> 8);
  packet[7] = _angle_max_limit;
  packet[8] = (_angle_max_limit >> 8);
  packet[9] = (~(_id + packet[3] + packet[4] + packet[5] + packet[6] + packet[7] + packet[8])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_ANGLE_LIMIT_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: получение ограничения максимального и минимального угла поворота вала
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @param *_angle_min_limit: значение минимального угла
 *   0 - 1000 (1500)
 * @param *_angle_max_limit: значение максимального угла
 *   0 - 1000 (1500)
 * @note: получение через ссылку
 *   SERVO_ANGLE_LIMIT_READ
 */
void HiWonderBusServo::getServoAngleLimit(uint8_t _id, uint16_t *_angle_min_limit, uint16_t *_angle_max_limit) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_ANGLE_LIMIT_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_ANGLE_LIMIT_READ;
  packet[4] = HW_CMD_SERVO_ANGLE_LIMIT_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_ANGLE_LIMIT_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_7, _id);

  *_angle_min_limit = (packet[0] << 8) | packet[1];
  *_angle_max_limit = (packet[2] << 8) | packet[3];
}
/*
 * @brief: установка ограничения максимального и минимального значения напряжения питания
 *   сохраняется после отключения питания
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @param _voltage_min_limit: минимальное значение напряжения
 *   4500 - 14000
 * @param _voltage_max_limit: максимальное значение напряжения
 *   4500 - 14000
 * @note:
 *   SERVO_VIN_LIMIT_WRITE
 */
void HiWonderBusServo::setServoVoltageLimit(uint8_t _id, uint16_t _voltage_min_limit, uint16_t _voltage_max_limit) {
  // Фильтр минимального и максимального значения напряжения питания. 4500 - 14000
  if (_voltage_min_limit < HW_SERVO_VIN_LIMIT_MIN) {
    _voltage_min_limit = HW_SERVO_VIN_LIMIT_MIN;
  }
  if (_voltage_min_limit > HW_SERVO_VIN_LIMIT_MAX) {
    _voltage_min_limit = HW_SERVO_VIN_LIMIT_MAX;
  }
  if (_voltage_max_limit < HW_SERVO_VIN_LIMIT_MIN) {
    _voltage_max_limit = HW_SERVO_VIN_LIMIT_MIN;
  }
  if (_voltage_max_limit > HW_SERVO_VIN_LIMIT_MAX) {
    _voltage_max_limit = HW_SERVO_VIN_LIMIT_MAX;
  }
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_VIN_LIMIT_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_VIN_LIMIT_WRITE;
  packet[4] = HW_CMD_SERVO_VIN_LIMIT_WRITE;
  packet[5] = _voltage_min_limit;
  packet[6] = (_voltage_min_limit >> 8);
  packet[7] = _voltage_max_limit;
  packet[8] = (_voltage_max_limit >> 8);
  packet[9] = (~(_id + packet[3] + packet[4] + packet[5] + packet[6] + packet[7] + packet[8])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_VIN_LIMIT_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: получение ограничения максимального и минимального значения напряжения питания
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @param *_voltage_min_limit: значение минимального напряжения
 *   4500 - 14000
 * @param *_voltage_max_limit: значение максимального напряжения
 *   4500 - 14000
 * @note: получение через ссылку
 *   SERVO_VIN_LIMIT_READ
 */
void HiWonderBusServo::getServoVoltageLimit(uint8_t _id, uint16_t *_voltage_min_limit, uint16_t *_voltage_max_limit) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_VIN_LIMIT_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_VIN_LIMIT_READ;
  packet[4] = HW_CMD_SERVO_VIN_LIMIT_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_VIN_LIMIT_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_7, _id);

  *_voltage_min_limit = (packet[0] << 8) | packet[1];
  *_voltage_max_limit = (packet[2] << 8) | packet[3];
}
/*
 * @brief: ограничение максимального значения температуры привода
 *   сохраняется после отключения питания
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @param _temperature_max_limit: максимальное значение температуры
 *   50 - 100
 * @note:
 *   SERVO_TEMP_MAX_LIMIT_WRITE
 */
void HiWonderBusServo::setServoMaximumTemperatureLimit(uint8_t _id, uint8_t _temperature_max_limit) {
  // Фильтр минимального и максимального значения пороговой температуры. 50 - 100
  if (_temperature_max_limit < HW_SERVO_TEMPERATURE_LIMIT_MIN) {
    _temperature_max_limit = HW_SERVO_TEMPERATURE_LIMIT_MIN;
  }
  if (_temperature_max_limit > HW_SERVO_TEMPERATURE_LIMIT_MAX) {
    _temperature_max_limit = HW_SERVO_TEMPERATURE_LIMIT_MAX;
  }
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_TEMP_MAX_LIMIT_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_TEMP_MAX_LIMIT_WRITE;
  packet[4] = HW_CMD_SERVO_TEMP_MAX_LIMIT_WRITE;
  packet[5] = _temperature_max_limit;
  packet[6] = (_temperature_max_limit >> 8);
  packet[7] = (~(_id + packet[3] + packet[4] + packet[5] + packet[6])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_TEMP_MAX_LIMIT_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: получение ограничения максимальноой температуры привода
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @return: максимальная температура привода в град. С
 * @note:
 *   SERVO_TEMP_MAX_LIMIT_READ
 */
uint8_t HiWonderBusServo::getServoMaximumTemperatureLimit(uint8_t _id) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_TEMP_MAX_LIMIT_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_TEMP_MAX_LIMIT_READ;
  packet[4] = HW_CMD_SERVO_TEMP_MAX_LIMIT_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_TEMP_MAX_LIMIT_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_4, _id);

  return (packet[0]); // 0 - если ошибка
}
/*
 * @brief: получение температуры привода в реальном времени
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @return: температура привода в град. С
 * @note:
 *   SERVO_TEMP_READ
 */
uint8_t HiWonderBusServo::getServoRealTimeTemperature(uint8_t _id) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_TEMP_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_TEMP_READ;
  packet[4] = HW_CMD_SERVO_TEMP_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_TEMP_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_4, _id);

  return (packet[0]); // 0 - если ошибка
}
/*
 * @brief: получение напряжения питания привода в реальном времени
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @return: напряжение питания привода в мВ
 * @note:
 *   SERVO_VIN_READ
 */
uint16_t HiWonderBusServo::getServoInputVoltage(uint8_t _id) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_VIN_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_VIN_READ;
  packet[4] = HW_CMD_SERVO_VIN_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_VIN_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_5, _id);

  return ((packet[0] << 8) | packet[1]); // 0 - если ошибка
}
/*
 * @brief: получение положения вала привода
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @return: положение вала привода
 * @note:
 *   SERVO_POS_READ
 */
uint16_t HiWonderBusServo::getServoPosition(uint8_t _id) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_POS_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_POS_READ;
  packet[4] = HW_CMD_SERVO_POS_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_POS_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_5, _id);

  return ((packet[0] << 8) | packet[1]); // 0 - если ошибка
}
/*
 * @brief: выбор режима работы привода
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @param _servo_motor_mode: режим работы привода. Серва или Мотор
 *   HW_SERVO_MODE
 *   HW_MOTOR_MODE
 * @param _servo_motor_mode: скорость и направление врещения. Только в режиме МОТОР!
 *   от -1000 до 1000
 * @note:
 *   SERVO_OR_MOTOR_MODE_WRITE
 */
void HiWonderBusServo::setServoOrMotorMode(uint8_t _id, HWServoOrMotorMode _servo_motor_mode, int16_t _motor_speed) {
  // Фильтр минимального и максимального значения скорости. +-1000 (+ прямое направление, - обратное направление)
  if (_motor_speed < HW_SERVO_OR_MOTOR_MODE_SPEED_MIN) {
    _motor_speed = HW_SERVO_OR_MOTOR_MODE_SPEED_MIN;
  }
  if (_motor_speed > HW_SERVO_OR_MOTOR_MODE_SPEED_MAX) {
    _motor_speed = HW_SERVO_OR_MOTOR_MODE_SPEED_MAX;
  }
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_OR_MOTOR_MODE_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_OR_MOTOR_MODE_WRITE;
  packet[4] = HW_CMD_SERVO_OR_MOTOR_MODE_WRITE;
  packet[5] = _servo_motor_mode;
  packet[6] = 0; // NULL по документации
  packet[7] = _motor_speed;
  packet[8] = (_motor_speed >> 8);
  packet[9] = (~(_id + packet[3] + packet[4] + packet[5] + 0 + packet[7] + packet[8])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_OR_MOTOR_MODE_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: получение режима работы привода и скорости вращения в рижиме мотора
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @param *_servo_motor_mode: рижим работы привода
 *   HW_SERVO_MODE
 *   HW_MOTOR_MODE
 * @param *_motor_speed: скорость и направление вращения в рижиме мотора
 *   от -1000 до 1000
 * @note: получение через ссылку
 *   SERVO_OR_MOTOR_MODE_READ
 */
void HiWonderBusServo::getServoOrMotorMode(uint8_t _id, HWServoOrMotorMode *_servo_motor_mode, int16_t *_motor_speed) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_OR_MOTOR_MODE_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_OR_MOTOR_MODE_READ;
  packet[4] = HW_CMD_SERVO_OR_MOTOR_MODE_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_OR_MOTOR_MODE_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_7, _id);

  *_servo_motor_mode = (HWServoOrMotorMode)packet[1]; // Не packet[0] потому что перестановка порядка старший младший байты в методе HW_ReceivePacket
  *_motor_speed = (int16_t)((packet[2] << 8) | packet[3]);
}
/*
 * @brief: нагрузить или разгрузить вал при включении питания
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @param _load_state: вал нагружен\разгружен
 *   HW_SERVO_LOAD_STATE
 *   HW_SERVO_UNLOAD_STATE
 * @note:
 *   SERVO_LOAD_OR_UNLOAD_WRITE
 */
void HiWonderBusServo::setServoLoadOrUnloadState(uint8_t _id, HWLoadOrUnloadState _load_state) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_LOAD_OR_UNLOAD_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_LOAD_OR_UNLOAD_WRITE;
  packet[4] = HW_CMD_SERVO_LOAD_OR_UNLOAD_WRITE;
  packet[5] = _load_state;
  packet[6] = (~(_id + packet[3] + packet[4] + packet[5])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_LOAD_OR_UNLOAD_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: узнать будет вал нагружен или разгрузужен при включении питания
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @return: состояние вала
 *   HW_SERVO_UNLOAD_STATE
 *   HW_SERVO_LOAD_STATE
 * @note:
 *   SERVO_LOAD_OR_UNLOAD_READ
 */
HWLoadOrUnloadState HiWonderBusServo::getServoLoadOrUnloadState(uint8_t _id) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_LOAD_OR_UNLOAD_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_LOAD_OR_UNLOAD_READ;
  packet[4] = HW_CMD_SERVO_LOAD_OR_UNLOAD_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_LOAD_OR_UNLOAD_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_4, _id);

  return ((HWLoadOrUnloadState)packet[0]);
}
/*
 * @brief: управление состоянием встроенного светодиода
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @param _state_led: светодиод включен\выключен
 *   HW_SERVO_LED_ON
 *   HW_SERVO_LED_OFF
 * @note:
 *   SERVO_LED_CTRL_WRITE
 */
void HiWonderBusServo::setServoControlLED(uint8_t _id, HWControlLED _led_state) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_LED_CTRL_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_LED_CTRL_WRITE;
  packet[4] = HW_CMD_SERVO_LED_CTRL_WRITE;
  packet[5] = _led_state;
  packet[6] = (~(_id + packet[3] + packet[4] + packet[5])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_LED_CTRL_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: получение состояния встроенного светодиода
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @return: состояние светодиода
 *   HW_SERVO_LED_ON
 *   HW_SERVO_LED_OFF
 * @note:
 *   SERVO_LED_CTRL_READ
 */
HWControlLED HiWonderBusServo::getServoControlLED(uint8_t _id) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_LED_CTRL_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_LED_CTRL_READ;
  packet[4] = HW_CMD_SERVO_LED_CTRL_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_LED_CTRL_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_4, _id);

  return ((HWControlLED)packet[0]);
}
/*
 * @brief: настроить встроенный светодиод мигать по одному из заделарированных событий
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD), 0xFE широковещательный
 * @param _led_error_code: код события для мигания встроенного светодиода
 *   HW_SERVO_ERROR_LED_NO_ALARM
 *   HW_SERVO_ERROR_LED_OVER_TEMPERATURE
 *   HW_SERVO_ERROR_LED_OVER_VOLTAGE
 *   HW_SERVO_ERROR_LED_OVER_TEMPERATURE_AND_VOLTAGE
 *   HW_SERVO_ERROR_LED_LOKED_ROTOR
 *   HW_SERVO_ERROR_LED_OVER_TEMPERATURE_AND_STALLED
 *   HW_SERVO_ERROR_LED_OVER_VOLTAGE_AND_STALLED
 *   HW_SERVO_ERROR_LED_OVER_TEMPERATURE_AND_OVER_VOLTAGE_AND_STALLED
 * @note:
 *   SERVO_LED_ERROR_WRITE
 */
void HiWonderBusServo::setServoErrorLED(uint8_t _id, HWErorCodeLED _led_error_code) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_LED_ERROR_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_LED_ERROR_WRITE;
  packet[4] = HW_CMD_SERVO_LED_ERROR_WRITE;
  packet[5] = _led_error_code;
  packet[6] = (~(_id + packet[3] + packet[4] + packet[5])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_LED_ERROR_WRITE + HW_PACKET_LENGHT_FACTOR_CORRECTION);
}
/*
 * @brief: получение кода ошибки привода
 * @param _id: номер привода на шине
 *   0 - 253 (0x00 ~ 0xFD)
 * @return: код ошибки
 *   HW_SERVO_ERROR_LED_NO_ALARM
 *   HW_SERVO_ERROR_LED_OVER_TEMPERATURE
 *   HW_SERVO_ERROR_LED_OVER_VOLTAGE
 *   HW_SERVO_ERROR_LED_OVER_TEMPERATURE_AND_VOLTAGE
 *   HW_SERVO_ERROR_LED_LOKED_ROTOR
 *   HW_SERVO_ERROR_LED_OVER_TEMPERATURE_AND_STALLED
 *   HW_SERVO_ERROR_LED_OVER_VOLTAGE_AND_STALLED
 *   HW_SERVO_ERROR_LED_OVER_TEMPERATURE_AND_OVER_VOLTAGE_AND_STALLED
 * @note:
 *   SERVO_LED_ERROR_READ
 */
HWErorCodeLED HiWonderBusServo::getServoErrorLED(uint8_t _id) {
  // Создание массива пакета
  uint8_t packet[HW_CMD_LENGHT_SERVO_LED_ERROR_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION];
  // Заполнение масива пакета данными
  packet[0] = HW_SERVO_PACKET_HEADER;
  packet[1] = HW_SERVO_PACKET_HEADER;
  packet[2] = _id;
  packet[3] = HW_CMD_LENGHT_SERVO_LED_ERROR_READ;
  packet[4] = HW_CMD_SERVO_LED_ERROR_READ;
  packet[5] = (~(_id + packet[3] + packet[4])) & 0xFF;
  // Передача пакета с данными приводу
  HW_BS_SendPacket(packet, HW_CMD_LENGHT_SERVO_LED_ERROR_READ + HW_PACKET_LENGHT_FACTOR_CORRECTION);
  // Получение данных от привода с проверками
  HW_BS_ReceivePacket(packet, HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_4, _id);

  return ((HWErorCodeLED)packet[0]);
}
