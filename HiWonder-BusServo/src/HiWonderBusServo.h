/*
 * Класс для Arduino IDE реализующий взаимодействие
 * с программируемыми сервоприводами Hiwonder https://www.hiwonder.com/
 * 
 * Copyright (C) 2024. v1.0 / MES
 */


#pragma once
#include "Arduino.h"
#include <HardwareSerial.h>

// Скорость UART. Для этих приводов она не изменяется
const uint32_t HW_SERVO_SERIAL_BAUDRATE = 115200;

// Широковещательный ID
const uint8_t HW_SERVO_BROADCAST_ID = 0xFE; // 254

// Заголовок пакета. Используется дважды
const uint8_t HW_SERVO_PACKET_HEADER = 0x55;

// Максимальное количество попыток проверки данных в применом буфере
const uint8_t HW_SERVO_ATTEMPTS_COUNT_MAX = 10;

// Время ожидания между проверками буфера примема (микросекунды)
const uint16_t HW_SERVO_TIMEOUT_CHEKING_BUFFER = 1000;

// Минимальное количество байт в применом буфере
const uint8_t HW_SERVO_RECIEVED_BYTE_BUFFER_MIN = 7;

// Количество байтов запрашиваемых данных в принимаем пакете
const uint8_t HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_4 = 4;
const uint8_t HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_5 = 5;
const uint8_t HW_SERVO_LENGHT_PACKET_LENGHT_BYTES_7 = 7;

// Коэффициен длинны пакета. Включает в себя два HEADER и CRC
const uint8_t HW_PACKET_LENGHT_FACTOR_CORRECTION = 3;

// Значения команд
const uint8_t HW_CMD_SERVO_MOVE_TIME_WRITE = 1;
const uint8_t HW_CMD_SERVO_MOVE_TIME_READ = 2;
const uint8_t HW_CMD_SERVO_MOVE_TIME_WAIT_WRITE = 7;
const uint8_t HW_CMD_SERVO_MOVE_TIME_WAIT_READ = 8;
const uint8_t HW_CMD_SERVO_MOVE_START = 11;
const uint8_t HW_CMD_SERVO_MOVE_STOP = 12;
const uint8_t HW_CMD_SERVO_ID_WRITE = 13;
const uint8_t HW_CMD_SERVO_ID_READ = 14;
const uint8_t HW_CMD_SERVO_ANGLE_OFFSET_ADJUST = 17;
const uint8_t HW_CMD_SERVO_ANGLE_OFFSET_WRITE = 18;
const uint8_t HW_CMD_SERVO_ANGLE_OFFSET_READ = 19;
const uint8_t HW_CMD_SERVO_ANGLE_LIMIT_WRITE = 20;
const uint8_t HW_CMD_SERVO_ANGLE_LIMIT_READ = 21;
const uint8_t HW_CMD_SERVO_VIN_LIMIT_WRITE = 22;
const uint8_t HW_CMD_SERVO_VIN_LIMIT_READ = 23;
const uint8_t HW_CMD_SERVO_TEMP_MAX_LIMIT_WRITE = 24;
const uint8_t HW_CMD_SERVO_TEMP_MAX_LIMIT_READ = 25;
const uint8_t HW_CMD_SERVO_TEMP_READ = 26;
const uint8_t HW_CMD_SERVO_VIN_READ = 27;
const uint8_t HW_CMD_SERVO_POS_READ = 28;
const uint8_t HW_CMD_SERVO_OR_MOTOR_MODE_WRITE = 29;
const uint8_t HW_CMD_SERVO_OR_MOTOR_MODE_READ = 30;
const uint8_t HW_CMD_SERVO_LOAD_OR_UNLOAD_WRITE = 31;
const uint8_t HW_CMD_SERVO_LOAD_OR_UNLOAD_READ = 32;
const uint8_t HW_CMD_SERVO_LED_CTRL_WRITE = 33;
const uint8_t HW_CMD_SERVO_LED_CTRL_READ = 34;
const uint8_t HW_CMD_SERVO_LED_ERROR_WRITE = 35;
const uint8_t HW_CMD_SERVO_LED_ERROR_READ = 36;

// Значения длины команд
const uint8_t HW_CMD_LENGHT_SERVO_MOVE_TIME_WRITE = 7;
const uint8_t HW_CMD_LENGHT_SERVO_MOVE_TIME_READ = 3;
const uint8_t HW_CMD_LENGHT_SERVO_MOVE_TIME_WAIT_WRITE = 7;
const uint8_t HW_CMD_LENGHT_SERVO_MOVE_TIME_WAIT_READ = 3;
const uint8_t HW_CMD_LENGHT_SERVO_MOVE_START = 3;
const uint8_t HW_CMD_LENGHT_SERVO_MOVE_STOP = 3;
const uint8_t HW_CMD_LENGHT_SERVO_ID_WRITE = 4;
const uint8_t HW_CMD_LENGHT_SERVO_ID_READ = 3;
const uint8_t HW_CMD_LENGHT_SERVO_ANGLE_OFFSET_ADJUST = 4;
const uint8_t HW_CMD_LENGHT_SERVO_ANGLE_OFFSET_WRITE = 3;
const uint8_t HW_CMD_LENGHT_SERVO_ANGLE_OFFSET_READ = 3;
const uint8_t HW_CMD_LENGHT_SERVO_ANGLE_LIMIT_WRITE = 7;
const uint8_t HW_CMD_LENGHT_SERVO_ANGLE_LIMIT_READ = 3;
const uint8_t HW_CMD_LENGHT_SERVO_VIN_LIMIT_WRITE = 7;
const uint8_t HW_CMD_LENGHT_SERVO_VIN_LIMIT_READ = 3;
const uint8_t HW_CMD_LENGHT_SERVO_TEMP_MAX_LIMIT_WRITE = 4;
const uint8_t HW_CMD_LENGHT_SERVO_TEMP_MAX_LIMIT_READ = 3;
const uint8_t HW_CMD_LENGHT_SERVO_TEMP_READ = 3;
const uint8_t HW_CMD_LENGHT_SERVO_VIN_READ = 3;
const uint8_t HW_CMD_LENGHT_SERVO_POS_READ = 3;
const uint8_t HW_CMD_LENGHT_SERVO_OR_MOTOR_MODE_WRITE = 7;
const uint8_t HW_CMD_LENGHT_SERVO_OR_MOTOR_MODE_READ = 3;
const uint8_t HW_CMD_LENGHT_SERVO_LOAD_OR_UNLOAD_WRITE = 4;
const uint8_t HW_CMD_LENGHT_SERVO_LOAD_OR_UNLOAD_READ = 3;
const uint8_t HW_CMD_LENGHT_SERVO_LED_CTRL_WRITE = 4;
const uint8_t HW_CMD_LENGHT_SERVO_LED_CTRL_READ = 3;
const uint8_t HW_CMD_LENGHT_SERVO_LED_ERROR_WRITE = 4;
const uint8_t HW_CMD_LENGHT_SERVO_LED_ERROR_READ = 3;

// Значения длины ответов на команды чтения
const uint8_t HW_ANS_LENGHT_SERVO_MOVE_TIME_READ = 7;
const uint8_t HW_ANS_LENGHT_SERVO_MOVE_TIME_WAIT_READ = 7;
const uint8_t HW_ANS_LENGHT_SERVO_ID_READ = 4;
const uint8_t HW_ANS_LENGHT_SERVO_ANGLE_OFFSET_READ = 4;
const uint8_t HW_ANS_LENGHT_SERVO_ANGLE_LIMIT_READ = 7;
const uint8_t HW_ANS_LENGHT_SERVO_VIN_LIMIT_READ = 7;
const uint8_t HW_ANS_LENGHT_SERVO_TEMP_MAX_LIMIT_READ = 4;
const uint8_t HW_ANS_LENGHT_SERVO_TEMP_READ = 4;
const uint8_t HW_ANS_LENGHT_SERVO_VIN_READ = 5;
const uint8_t HW_ANS_LENGHT_SERVO_POS_READ = 5;
const uint8_t HW_ANS_LENGHT_SERVO_OR_MOTOR_MODE_READ = 7;
const uint8_t HW_ANS_LENGHT_SERVO_LOAD_OR_UNLOAD_READ = 4;
const uint8_t HW_ANS_LENGHT_SERVO_LED_CTRL_READ = 4;
const uint8_t HW_ANS_LENGHT_SERVO_LED_ERROR_READ = 4;

// Режимы привода - Серва, Мотор
enum HWServoOrMotorMode : uint8_t {
  HW_SERVO_MODE,
  HW_MOTOR_MODE,
};

// Нагрузить или разгрузить вал привода
enum HWLoadOrUnloadState : uint8_t {
  HW_SERVO_UNLOAD_STATE,
  HW_SERVO_LOAD_STATE,
};

// Включение или выключение встроенного светодиода
enum HWControlLED : uint8_t {
  HW_SERVO_LED_ON,
  HW_SERVO_LED_OFF,
};

// Коды ошибок привода
enum HWErorCodeLED : uint8_t {
  HW_SERVO_ERROR_LED_NO_ALARM,
  HW_SERVO_ERROR_LED_OVER_TEMPERATURE,
  HW_SERVO_ERROR_LED_OVER_VOLTAGE,
  HW_SERVO_ERROR_LED_OVER_TEMPERATURE_AND_VOLTAGE,
  HW_SERVO_ERROR_LED_LOKED_ROTOR,
  HW_SERVO_ERROR_LED_OVER_TEMPERATURE_AND_STALLED,
  HW_SERVO_ERROR_LED_OVER_VOLTAGE_AND_STALLED,
  HW_SERVO_ERROR_LED_OVER_TEMPERATURE_AND_OVER_VOLTAGE_AND_STALLED,
};

// Максимальное положение вала в режиме серопривода. Для некоторых серв 1000
const uint16_t HW_SERVO_SHAFT_POSITION_MAX = 1500;
// Максимальное время перемещения вала в рижиме сервопривода
const uint16_t HW_SERVO_MOVE_TIME_VALUE_MAX = 30000;
// Минимальное значение смещения угла
const int8_t HW_SERVO_ANGLE_OFFSET_MIN = -125;
// Максимальное значение смещения угла
const int8_t HW_SERVO_ANGLE_OFFSET_MAX = 125;
// Минимальное значение ограничения напряжения питания
const uint16_t HW_SERVO_VIN_LIMIT_MIN = 4500;
// Максимальное значение ограничения напряжения питания
const uint16_t HW_SERVO_VIN_LIMIT_MAX = 14000;
// Минимальное значение ограничения температуры привода
const uint8_t HW_SERVO_TEMPERATURE_LIMIT_MIN = 50;
// Максимальное значение ограничения температуры привода
const uint8_t HW_SERVO_TEMPERATURE_LIMIT_MAX = 100;

// Скорость по умолчанию для режимов серво и мотор
const int8_t HW_SERVO_OR_MOTOR_MODE_SPEED_DEFAULT = 0;
// Минимальная скорость для режимов серво и мотор
const int16_t HW_SERVO_OR_MOTOR_MODE_SPEED_MIN = -1000;
// Максимальная скорость для режимов серво и мотор
const int16_t HW_SERVO_OR_MOTOR_MODE_SPEED_MAX = 1000;


class HiWonderBusServo {
  private:
    HardwareSerial *_h_serial_;
    uint8_t _pin_direction_;

  protected:
    virtual void HW_BS_SendPacket(unsigned char *_packet, unsigned int _length);
    virtual void HW_BS_ReceivePacket(uint8_t *_return_data, uint8_t _answer_lenght, uint8_t _id);

  public:
    HiWonderBusServo(HardwareSerial *_h_serial, uint8_t _dir_pin);

    virtual void begin(void);
    virtual void end(void);

    // SERVO_MOVE_TIME_WRITE
    virtual void setServoMoveTime(uint8_t _id, uint16_t _position, uint16_t _time);
    // SERVO_MOVE_TIME_READ
    virtual void getServoMoveTime(uint8_t _id, uint16_t *_position, uint16_t *_time);

    // SERVO_MOVE_TIME_WAIT_WRITE
    virtual void setServoMoveTimeWait(uint8_t _id, uint16_t _position, uint16_t _time);
    // SERVO_MOVE_TIME_WAIT_READ
    virtual void getServoMoveTimeWait(uint8_t _id, uint16_t *_position, uint16_t *_time);

    // SERVO_MOVE_START
    virtual void setServoMoveStart(uint8_t _id);

    // SERVO_MOVE_STOP
    virtual void setServoMoveStop(uint8_t _id);

    // SERVO_ID_WRITE
    virtual void setServoID(uint8_t _id, uint8_t _new_id);
    // SERVO_ID_READ
    virtual uint8_t getServoID(uint8_t _id);

    // SERVO_ANGLE_OFFSET_ADJUST
    virtual void setServoAngleOffsetAdjust(uint8_t _id, int8_t _offset_adjust);

    // SERVO_ANGLE_OFFSET_WRITE
    virtual void setServoAngleOffset(uint8_t _id, int8_t _offset);
    // SERVO_ANGLE_OFFSET_READ
    virtual int8_t getServoAngleOffset(uint8_t _id);

    // SERVO_ANGLE_LIMIT_WRITE
    virtual void setServoAngleLimit(uint8_t _id, uint16_t _angle_min_limit, uint16_t _angle_max_limit);
    // SERVO_ANGLE_LIMIT_READ
    virtual void getServoAngleLimit(uint8_t _id, uint16_t *_angle_min_limit, uint16_t *_angle_max_limit);

    // SERVO_VIN_LIMIT_WRITE
    virtual void setServoVoltageLimit(uint8_t _id, uint16_t _voltage_min_limit, uint16_t _voltage_max_limit);
    // SERVO_VIN_LIMIT_READ
    virtual void getServoVoltageLimit(uint8_t _id, uint16_t *_voltage_min_limit, uint16_t *_voltage_max_limit);

    // SERVO_TEMP_MAX_LIMIT_WRITE
    virtual void setServoMaximumTemperatureLimit(uint8_t _id, uint8_t _temperature_max_limit);
    // SERVO_TEMP_MAX_LIMIT_READ
    virtual uint8_t getServoMaximumTemperatureLimit(uint8_t _id);

    // SERVO_TEMP_READ
    virtual uint8_t getServoRealTimeTemperature(uint8_t _id);
    // SERVO_VIN_READ
    virtual uint16_t getServoInputVoltage(uint8_t _id);
    // SERVO_POS_READ
    virtual uint16_t getServoPosition(uint8_t _id);

    // SERVO_OR_MOTOR_MODE_WRITE
    virtual void setServoOrMotorMode(uint8_t _id, HWServoOrMotorMode _servo_motor_mode, int16_t _motor_speed = HW_SERVO_OR_MOTOR_MODE_SPEED_DEFAULT);
    // SERVO_OR_MOTOR_MODE_READ
    virtual void getServoOrMotorMode(uint8_t _id, HWServoOrMotorMode *_servo_motor_mode, int16_t *_motor_speed);

    // SERVO_LOAD_OR_UNLOAD_WRITE
    virtual void setServoLoadOrUnloadState(uint8_t _id, HWLoadOrUnloadState _load_state);
    // SERVO_LOAD_OR_UNLOAD_READ
    virtual HWLoadOrUnloadState getServoLoadOrUnloadState(uint8_t _id);

    // SERVO_LED_CTRL_WRITE
    virtual void setServoControlLED(uint8_t _id, HWControlLED _led_state);
    // SERVO_LED_CTRL_READ
    virtual HWControlLED getServoControlLED(uint8_t _id);

    // SERVO_LED_ERROR_WRITE
    virtual void setServoErrorLED(uint8_t _id, HWErorCodeLED _led_error_code);
    // SERVO_LED_ERROR_READ
    virtual HWErorCodeLED getServoErrorLED(uint8_t _id);
};
