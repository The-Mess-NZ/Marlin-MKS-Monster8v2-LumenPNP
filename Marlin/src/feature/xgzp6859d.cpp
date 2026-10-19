#include "../inc/MarlinConfig.h"

#if ENABLED(XGZP6859D_ENABLE)

#include "xgzp6859d.h"

XGZP6859D xgzp_sensor_0(
  XGZP6859D_S0_SCL_PIN,
  XGZP6859D_S0_SDA_PIN
);

XGZP6859D xgzp_sensor_1(
  XGZP6859D_S1_SCL_PIN,
  XGZP6859D_S1_SDA_PIN
);

XGZP6859D::XGZP6859D(const pin_t scl_pin, const pin_t sda_pin)
  : _scl(scl_pin), _sda(sda_pin) {}

void XGZP6859D::begin() {
  // I2C is open-drain.
  //
  // LOW  = actively drive the line low.
  // INPUT = release the line and let the external pull-up bring it high.

  pinMode(_scl, INPUT);
  pinMode(_sda, INPUT);
}

void XGZP6859D::scl_low() {
  digitalWrite(_scl, LOW);
  pinMode(_scl, OUTPUT);
}

void XGZP6859D::scl_high() {
  pinMode(_scl, INPUT);
}

void XGZP6859D::sda_low() {
  digitalWrite(_sda, LOW);
  pinMode(_sda, OUTPUT);
}

void XGZP6859D::sda_release() {
  pinMode(_sda, INPUT);
}

bool XGZP6859D::start() {
  sda_release();
  scl_high();

  delayMicroseconds(2);

  // Bus should be idle high.
  if (digitalRead(_sda) == LOW || digitalRead(_scl) == LOW)
    return false;

  sda_low();
  delayMicroseconds(2);

  scl_low();
  delayMicroseconds(2);

  return true;
}

void XGZP6859D::stop() {
  sda_low();
  delayMicroseconds(2);

  scl_high();
  delayMicroseconds(2);

  sda_release();
  delayMicroseconds(2);
}

bool XGZP6859D::write_byte(const uint8_t value) {

  for (uint8_t bit = 0; bit < 8; ++bit) {

    if (value & (0x80 >> bit))
      sda_release();
    else
      sda_low();

    delayMicroseconds(2);

    scl_high();
    delayMicroseconds(2);

    scl_low();
    delayMicroseconds(2);
  }

  // Release SDA for ACK.
  sda_release();
  delayMicroseconds(2);

  scl_high();
  delayMicroseconds(2);

  const bool ack = digitalRead(_sda) == LOW;

  scl_low();
  delayMicroseconds(2);

  return ack;
}

uint8_t XGZP6859D::read_byte(const bool ack) {

  uint8_t value = 0;

  sda_release();

  for (uint8_t bit = 0; bit < 8; ++bit) {

    value <<= 1;

    scl_high();
    delayMicroseconds(2);

    if (digitalRead(_sda))
      value |= 1;

    scl_low();
    delayMicroseconds(2);
  }

  // Master ACK/NACK.
  if (ack)
    sda_low();
  else
    sda_release();

  delayMicroseconds(2);

  scl_high();
  delayMicroseconds(2);

  scl_low();
  delayMicroseconds(2);

  sda_release();

  return value;
}

bool XGZP6859D::write_register(
  const uint8_t reg,
  const uint8_t value
) {

  if (!start())
    return false;

  if (!write_byte((ADDRESS << 1) | 0)) {
    stop();
    return false;
  }

  if (!write_byte(reg)) {
    stop();
    return false;
  }

  if (!write_byte(value)) {
    stop();
    return false;
  }

  stop();

  return true;
}

bool XGZP6859D::read_register(
  const uint8_t reg,
  uint8_t &value
) {
  return read_registers(reg, &value, 1);
}

bool XGZP6859D::read_registers(
  const uint8_t reg,
  uint8_t *buffer,
  const uint8_t length
) {

  if (!start())
    return false;

  // Write register address.
  if (!write_byte((ADDRESS << 1) | 0)) {
    stop();
    return false;
  }

  if (!write_byte(reg)) {
    stop();
    return false;
  }

  // Repeated START.
  if (!start())
    return false;

  // Read.
  if (!write_byte((ADDRESS << 1) | 1)) {
    stop();
    return false;
  }

  for (uint8_t i = 0; i < length; ++i)
    buffer[i] = read_byte(i < length - 1);

  stop();

  return true;
}

bool XGZP6859D::wait_for_conversion() {

  // The datasheet permits simply waiting 20 ms after
  // starting a combined conversion.
  //
  // This also avoids hammering the sensor's I2C bus while
  // it is performing the conversion.
  for (uint8_t i = 0; i < 20; ++i) {
    uint8_t status;

    if (!read_register(REG_COMMAND, status))
      return false;

    if (!(status & COMMAND_SCO))
      return true;

    delay(1);
  }

  return false;
}

int32_t XGZP6859D::convert_pressure(
  const uint8_t *data
) const {

  int32_t raw =
      (int32_t(data[0]) << 16)
    | (int32_t(data[1]) << 8)
    | int32_t(data[2]);

  // 24-bit two's-complement value.
  if (raw & 0x800000)
    raw -= 0x1000000;

  return raw / XGZP6859D_PRESSURE_K;
}

int16_t XGZP6859D::convert_temperature(
  const uint8_t *data
) const {

  const int16_t raw =
      int16_t((uint16_t(data[0]) << 8) | data[1]);

  // Sensor reports °C * 256.
  //
  // Store °C * 100 for convenient integer output.
  return int16_t((int32_t(raw) * 100) / 256);
}

bool XGZP6859D::read() {

  uint8_t pressure[3];
  uint8_t temperature[2];

  // Start combined temperature + pressure conversion.
  //
  // XGZP6859D datasheet: write 0x0A to register 0x30.
  if (!write_register(REG_COMMAND, COMMAND_COMBINED_CONVERSION)) {
    _online = false;
    return false;
  }

  if (!wait_for_conversion()) {
    _online = false;
    return false;
  }

  if (!read_registers(
    REG_PRESSURE_MSB,
    pressure,
    sizeof(pressure)
  )) {
    _online = false;
    return false;
  }

  if (!read_registers(
    REG_TEMPERATURE_MSB,
    temperature,
    sizeof(temperature)
  )) {
    _online = false;
    return false;
  }

  _pressure_pa = convert_pressure(pressure);
  _temperature_c_x100 = convert_temperature(temperature);

  _online = true;

  return true;
}

#endif
