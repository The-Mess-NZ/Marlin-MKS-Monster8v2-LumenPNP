#pragma once

#include "../inc/MarlinConfig.h"

#if ENABLED(XGZP6859D_ENABLE)

class XGZP6859D {

public:

  XGZP6859D(const pin_t scl_pin, const pin_t sda_pin);

  void begin();

  /**
   * Perform one combined temperature + pressure conversion.
   *
   * Returns true on success.
   */
  bool read();

  int32_t pressure_pa() const { return _pressure_pa; }
  int16_t temperature_c_x100() const { return _temperature_c_x100; }

  bool online() const { return _online; }

private:

  static constexpr uint8_t ADDRESS = XGZP6859D_I2C_ADDRESS;

  static constexpr uint8_t REG_PRESSURE_MSB = 0x06;
  static constexpr uint8_t REG_TEMPERATURE_MSB = 0x09;
  static constexpr uint8_t REG_COMMAND = 0x30;

  static constexpr uint8_t COMMAND_COMBINED_CONVERSION = 0x0A;
  static constexpr uint8_t COMMAND_SCO = 0x08;

  pin_t _scl;
  pin_t _sda;

  int32_t _pressure_pa = 0;
  int16_t _temperature_c_x100 = 0;

  bool _online = false;

  void scl_low();
  void scl_high();
  void sda_low();
  void sda_release();

  bool write_byte(const uint8_t value);
  uint8_t read_byte(const bool ack);

  bool start();
  void stop();

  bool write_register(const uint8_t reg, const uint8_t value);
  bool read_register(const uint8_t reg, uint8_t &value);

  bool read_registers(
    const uint8_t reg,
    uint8_t *buffer,
    const uint8_t length
  );

  bool wait_for_conversion();

  int32_t convert_pressure(const uint8_t *data) const;
  int16_t convert_temperature(const uint8_t *data) const;
};

extern XGZP6859D xgzp_sensor_0;
extern XGZP6859D xgzp_sensor_1;

#endif
