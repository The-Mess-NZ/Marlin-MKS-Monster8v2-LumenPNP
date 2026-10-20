/**
 * Marlin 3D Printer Firmware
 * M703 - Vacuum Solenoid Boolean Control for Pick and Place
 */

#include "../../inc/MarlinConfig.h"

#include "../gcode.h"

/**
 * M703: Set vacuum pump PWM
 *
 * P<pump> - Pump solenoid index (0 or 1)
 * S<pwm>  - Boolean value (0 or 1)
 *
 * P0 uses HEATER_1_PIN - "HE1" hotend 1 output
 * P1 uses HEATER_2_PIN - "HE2" hotend 2 output
 */
void GcodeSuite::M703() {
  const int8_t pump = parser.intval('P', -1);
  if (pump < 0 || pump > 1) {
    SERIAL_ECHOLNPGM("M703: P must be 0 or 1");
    return;
  }

  if (!parser.seenval('S')) {
    SERIAL_ECHOLNPGM("M703: S parameter required (0-1)");
    return;
  }

  const int value = parser.value_int();
  if (value < 0 || value > 1) {
    SERIAL_ECHOLNPGM("M703: S must be 0 or 1");
    return;
  }

  const pin_t pin = (pump == 0) ? HEATER_1_PIN : HEATER_2_PIN;

  // Initialize PWM mode if needed
  if (PWM_PIN(pin)) {
    SET_PWM(pin);
  }

  // Set PWM duty cycle
  hal.set_pwm_duty(pin_t(pin), value ? 255 : 0);

  SERIAL_ECHOPGM("M703 P");
  SERIAL_ECHO(pump);
  SERIAL_ECHOPGM(" S");
  SERIAL_ECHO(value);
  SERIAL_ECHOLNPGM(" OK");
}
