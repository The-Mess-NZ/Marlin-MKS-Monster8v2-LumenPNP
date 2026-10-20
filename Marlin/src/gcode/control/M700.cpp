/**
 * Marlin 3D Printer Firmware
 * M700 - Vacuum Pump PWM Control for Pick and Place
 */

#include "../../inc/MarlinConfig.h"

#include "../gcode.h"

/**
 * M700: Set vacuum pump PWM
 *
 * P<pump> - Pump index (0 or 1)
 * S<pwm>  - PWM value (0-255)
 *
 * P0 uses HEATER_BED_PIN (PB10) - "HBED" hotbed output
 * P1 uses HEATER_0_PIN (PB1) - "HE0" hotend 0 output
 */
void GcodeSuite::M700() {
  const int8_t pump = parser.intval('P', -1);
  if (pump < 0 || pump > 1) {
    SERIAL_ECHOLNPGM("M700: P must be 0 or 1");
    return;
  }

  if (!parser.seenval('S')) {
    SERIAL_ECHOLNPGM("M700: S parameter required (0-255)");
    return;
  }

  const int pwm = parser.value_int();
  if (pwm < 0 || pwm > 255) {
    SERIAL_ECHOLNPGM("M700: S must be 0-255");
    return;
  }

  const pin_t pin = (pump == 0) ? HEATER_BED_PIN : HEATER_0_PIN;

  // Initialize PWM mode if needed
  if (PWM_PIN(pin)) {
    SET_PWM(pin);
  }

  // Set PWM duty cycle
  hal.set_pwm_duty(pin_t(pin), pwm);

  SERIAL_ECHOPGM("M700 P");
  SERIAL_ECHO(pump);
  SERIAL_ECHOPGM(" S");
  SERIAL_ECHO(pwm);
  SERIAL_ECHOLNPGM(" OK");
}
