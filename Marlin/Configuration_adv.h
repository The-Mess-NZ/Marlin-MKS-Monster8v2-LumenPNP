/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Configuration_adv.h
 *
 * Advanced settings.
 * Only change these if you know exactly what you're doing.
 * Some of these settings can damage your printer if improperly set!
 *
 * Basic settings can be found in Configuration.h
 */
#define CONFIGURATION_ADV_H_VERSION 02010206

//===========================================================================
//============================= Thermal Settings ============================
//===========================================================================
// @section temperature

/**
 * Thermocouple sensors are quite sensitive to noise.  Any noise induced in
 * the sensor wires, such as by stepper motor wires run in parallel to them,
 * may result in the thermocouple sensor reporting spurious errors.  This
 * value is the number of errors which can occur in a row before the error
 * is reported.  This allows us to ignore intermittent error conditions while
 * still detecting an actual failure, which should result in a continuous
 * stream of errors from the sensor.
 *
 * Set this value to 0 to fail on the first error to occur.
 */
#define THERMOCOUPLE_MAX_ERRORS 15

//
// Heated Bed Bang-Bang options
//
#if DISABLED(PIDTEMPBED)
  #define BED_CHECK_INTERVAL 5000   // (ms) Interval between checks in bang-bang control
  #if ENABLED(BED_LIMIT_SWITCHING)
    #define BED_HYSTERESIS 2        // (°C) Only set the relevant heater state when ABS(T-target) > BED_HYSTERESIS
  #endif
#endif

//
// Heated Chamber options
//
#if DISABLED(PIDTEMPCHAMBER)
  #define CHAMBER_CHECK_INTERVAL 5000   // (ms) Interval between checks in bang-bang control
  #if ENABLED(CHAMBER_LIMIT_SWITCHING)
    #define CHAMBER_HYSTERESIS 2        // (°C) Only set the relevant heater state when ABS(T-target) > CHAMBER_HYSTERESIS
  #endif
#endif

/**
 * Automatic Temperature Mode
 *
 * Dynamically adjust the hotend target temperature based on planned E moves.
 *
 * (Contrast with PID_EXTRUSION_SCALING, which tracks E movement and adjusts PID
 *  behavior using an additional kC value.)
 *
 * Autotemp is calculated by (mintemp + factor * mm_per_sec), capped to maxtemp.
 *
 * Enable Autotemp Mode with M104/M109 F<factor> S<mintemp> B<maxtemp>.
 * Disable by sending M104/M109 with no F parameter (or F0 with AUTOTEMP_PROPORTIONAL).
 */
#define AUTOTEMP
#if ENABLED(AUTOTEMP)
  #define AUTOTEMP_OLDWEIGHT    0.98
  // Turn on AUTOTEMP on M104/M109 by default using proportions set here
  //#define AUTOTEMP_PROPORTIONAL
  #if ENABLED(AUTOTEMP_PROPORTIONAL)
    #define AUTOTEMP_MIN_P      0 // (°C) Added to the target temperature
    #define AUTOTEMP_MAX_P      5 // (°C) Added to the target temperature
    #define AUTOTEMP_FACTOR_P   1 // Apply this F parameter by default (overridden by M104/M109 F)
  #endif
#endif

// Show Temperature ADC value
// Enable for M105 to include ADC values read from temperature sensors.
//#define SHOW_TEMP_ADC_VALUES

// @section temperature

// Calibration for AD595 / AD8495 sensor to adjust temperature measurements.
// The final temperature is calculated as (measuredTemp * GAIN) + OFFSET.
#define TEMP_SENSOR_AD595_OFFSET  0.0
#define TEMP_SENSOR_AD595_GAIN    1.0
#define TEMP_SENSOR_AD8495_OFFSET 0.0
#define TEMP_SENSOR_AD8495_GAIN   1.0

// @section fans

/**
 * Controller Fan
 * To cool down the stepper drivers and MOSFETs.
 *
 * The fan turns on automatically whenever any driver is enabled and turns
 * off (or reduces to idle speed) shortly after drivers are turned off.
 */
//#define USE_CONTROLLER_FAN
#if ENABLED(USE_CONTROLLER_FAN)
  //#define CONTROLLER_FAN_PIN -1           // Set a custom pin for the controller fan
  //#define CONTROLLER_FAN2_PIN -1          // Set a custom pin for second controller fan
  //#define CONTROLLER_FAN_USE_Z_ONLY       // With this option only the Z axis is considered
  //#define CONTROLLER_FAN_IGNORE_Z         // Ignore Z stepper. Useful when stepper timeout is disabled.
  #define CONTROLLERFAN_SPEED_MIN         0 // (0-255) Minimum speed. (If set below this value the fan is turned off.)
  #define CONTROLLERFAN_SPEED_ACTIVE    255 // (0-255) Active speed, used when any motor is enabled
  #define CONTROLLERFAN_SPEED_IDLE        0 // (0-255) Idle speed, used when motors are disabled
  #define CONTROLLERFAN_IDLE_TIME        60 // (seconds) Extra time to keep the fan running after disabling motors

  // Use TEMP_SENSOR_BOARD as a trigger for enabling the controller fan
  //#define CONTROLLER_FAN_MIN_BOARD_TEMP 40  // (°C) Turn on the fan if the board reaches this temperature

  //#define CONTROLLER_FAN_EDITABLE         // Enable M710 configurable settings
  #if ENABLED(CONTROLLER_FAN_EDITABLE)
    #define CONTROLLER_FAN_MENU             // Enable the Controller Fan submenu
  #endif
#endif

/**
 * Fan Kickstart
 * When part cooling or controller fans first start, run at a speed that
 * gets it spinning reliably for a short time before setting the requested speed.
 * (Does not work on Sanguinololu with FAN_SOFT_PWM.)
 */
//#define FAN_KICKSTART_TIME  100  // (ms)
//#define FAN_KICKSTART_POWER 180  // 64-255

// Some coolers may require a non-zero "off" state.
//#define FAN_OFF_PWM  1

/**
 * PWM Fan Scaling
 *
 * Define the min/max speeds for PWM fans (as set with M106).
 *
 * With these options the M106 0-255 value range is scaled to a subset
 * to ensure that the fan has enough power to spin, or to run lower
 * current fans with higher current. (e.g., 5V/12V fans with 12V/24V)
 * Value 0 always turns off the fan.
 *
 * Define one or both of these to override the default 0-255 range.
 */
//#define FAN_MIN_PWM 50
//#define FAN_MAX_PWM 128

/**
 * Fan Fast PWM
 *
 * Combinations of PWM Modes, prescale values and TOP resolutions are used internally
 * to produce a frequency as close as possible to the desired frequency.
 *
 * FAST_PWM_FAN_FREQUENCY
 *   Set this to your desired frequency.
 *   For AVR, if left undefined this defaults to F = F_CPU/(2*255*1)
 *            i.e., F = 31.4kHz on 16MHz micro-controllers or F = 39.2kHz on 20MHz micro-controllers.
 *   For non AVR, if left undefined this defaults to F = 1Khz.
 *   This F value is only to protect the hardware from an absence of configuration
 *   and not to complete it when users are not aware that the frequency must be specifically set to support the target board.
 *
 *   NOTE: Setting very low frequencies (< 10 Hz) may result in unexpected timer behavior.
 *         Setting very high frequencies can damage your hardware.
 *
 * USE_OCR2A_AS_TOP [undefined by default]
 *   Boards that use TIMER2 for PWM have limitations resulting in only a few possible frequencies on TIMER2:
 *   16MHz MCUs: [62.5kHz, 31.4kHz (default), 7.8kHz, 3.92kHz, 1.95kHz, 977Hz, 488Hz, 244Hz, 60Hz, 122Hz, 30Hz]
 *   20MHz MCUs: [78.1kHz, 39.2kHz (default), 9.77kHz, 4.9kHz, 2.44kHz, 1.22kHz, 610Hz, 305Hz, 153Hz, 76Hz, 38Hz]
 *   A greater range can be achieved by enabling USE_OCR2A_AS_TOP. But note that this option blocks the use of
 *   PWM on pin OC2A. Only use this option if you don't need PWM on 0C2A. (Check your schematic.)
 *   USE_OCR2A_AS_TOP sacrifices duty cycle control resolution to achieve this broader range of frequencies.
 */
//#define FAST_PWM_FAN    // Increase the fan PWM frequency. Removes the PWM noise but increases heating in the FET/Arduino
#if ENABLED(FAST_PWM_FAN)
  //#define FAST_PWM_FAN_FREQUENCY 31400  // Define here to override the defaults below
  //#define USE_OCR2A_AS_TOP
  #ifndef FAST_PWM_FAN_FREQUENCY
    #ifdef __AVR__
      #define FAST_PWM_FAN_FREQUENCY ((F_CPU) / (2 * 255 * 1))
    #else
      #define FAST_PWM_FAN_FREQUENCY 1000U
    #endif
  #endif
#endif

/**
 * Use one of the PWM fans as a redundant part-cooling fan
 */
//#define REDUNDANT_PART_COOLING_FAN 1  // Index of the fan to sync with FAN 0.

/**
 * Extruder cooling fans
 *
 * Extruder auto fans automatically turn on when their extruders'
 * temperatures go above EXTRUDER_AUTO_FAN_TEMPERATURE.
 *
 * Your board's pins file specifies the recommended pins. Override those here
 * or set to -1 to disable completely.
 *
 * Multiple extruders can be assigned to the same pin in which case
 * the fan will turn on when any selected extruder is above the threshold.
 */
#define E0_AUTO_FAN_PIN -1
#define E1_AUTO_FAN_PIN -1
#define E2_AUTO_FAN_PIN -1
#define E3_AUTO_FAN_PIN -1
#define E4_AUTO_FAN_PIN -1
#define E5_AUTO_FAN_PIN -1
#define E6_AUTO_FAN_PIN -1
#define E7_AUTO_FAN_PIN -1
#define CHAMBER_AUTO_FAN_PIN -1
#define COOLER_AUTO_FAN_PIN -1
#define COOLER_FAN_PIN -1

#define EXTRUDER_AUTO_FAN_TEMPERATURE 50
#define EXTRUDER_AUTO_FAN_SPEED 255   // 255 == full speed
#define CHAMBER_AUTO_FAN_TEMPERATURE 30
#define CHAMBER_AUTO_FAN_SPEED 255
#define COOLER_AUTO_FAN_TEMPERATURE 18
#define COOLER_AUTO_FAN_SPEED 255

/**
 * Part-Cooling Fan Multiplexer
 *
 * This feature allows you to digitally multiplex the fan output.
 * The multiplexer is automatically switched at tool-change.
 * Set FANMUX[012]_PINs below for up to 2, 4, or 8 multiplexed fans.
 */
#define FANMUX0_PIN -1
#define FANMUX1_PIN -1
#define FANMUX2_PIN -1

/**
 * @section caselight
 * M355 Case Light on-off / brightness
 */
//#define CASE_LIGHT_ENABLE
#if ENABLED(CASE_LIGHT_ENABLE)
  //#define CASE_LIGHT_PIN 4                  // Override the default pin if needed
  #define INVERT_CASE_LIGHT false             // Set true if Case Light is ON when pin is LOW
  #define CASE_LIGHT_DEFAULT_ON true          // Set default power-up state on
  #define CASE_LIGHT_DEFAULT_BRIGHTNESS 105   // Set default power-up brightness (0-255, requires PWM pin)
  //#define CASE_LIGHT_NO_BRIGHTNESS          // Disable brightness control. Enable for non-PWM lighting.
  //#define CASE_LIGHT_MAX_PWM 128            // Limit PWM duty cycle (0-255)
  //#define CASE_LIGHT_MENU                   // Add Case Light options to the LCD menu
  #if ENABLED(NEOPIXEL_LED)
    //#define CASE_LIGHT_USE_NEOPIXEL         // Use NeoPixel LED as case light
  #endif
  #if EITHER(RGB_LED, RGBW_LED)
    //#define CASE_LIGHT_USE_RGB_LED          // Use RGB / RGBW LED as case light
  #endif
  #if EITHER(CASE_LIGHT_USE_NEOPIXEL, CASE_LIGHT_USE_RGB_LED)
    #define CASE_LIGHT_DEFAULT_COLOR { 255, 255, 255, 255 } // { Red, Green, Blue, White }
  #endif
#endif

// @section endstops

// If you want endstops to stay on (by default) even when not homing
// enable this option. Override at any time with M120, M121.
//#define ENDSTOPS_ALWAYS_ON_DEFAULT

// @section extras

//#define Z_LATE_ENABLE // Enable Z the last moment. Needed if your Z driver overheats.

// Employ an external closed loop controller. Override pins here if needed.
//#define EXTERNAL_CLOSED_LOOP_CONTROLLER
#if ENABLED(EXTERNAL_CLOSED_LOOP_CONTROLLER)
  //#define CLOSED_LOOP_ENABLE_PIN        -1
  //#define CLOSED_LOOP_MOVE_COMPLETE_PIN -1
#endif

/**
 * Dual Steppers / Dual Endstops
 *
 * This section will allow you to use extra E drivers to drive a second motor for X, Y, or Z axes.
 *
 * For example, set X_DUAL_STEPPER_DRIVERS setting to use a second motor. If the motors need to
 * spin in opposite directions set INVERT_X2_VS_X_DIR. If the second motor needs its own endstop
 * set X_DUAL_ENDSTOPS. This can adjust for "racking." Use X2_USE_ENDSTOP to set the endstop plug
 * that should be used for the second endstop. Extra endstops will appear in the output of 'M119'.
 *
 * Use X_DUAL_ENDSTOP_ADJUSTMENT to adjust for mechanical imperfection. After homing both motors
 * this offset is applied to the X2 motor. To find the offset home the X axis, and measure the error
 * in X2. Dual endstop offsets can be set at runtime with 'M666 X<offset> Y<offset> Z<offset>'.
 */

//#define X_DUAL_STEPPER_DRIVERS
#if ENABLED(X_DUAL_STEPPER_DRIVERS)
  //#define INVERT_X2_VS_X_DIR    // Enable if X2 direction signal is opposite to X
  //#define X_DUAL_ENDSTOPS
  #if ENABLED(X_DUAL_ENDSTOPS)
    #define X2_USE_ENDSTOP _XMAX_
    #define X2_ENDSTOP_ADJUSTMENT  0
  #endif
#endif

//#define Y_DUAL_STEPPER_DRIVERS
#if ENABLED(Y_DUAL_STEPPER_DRIVERS)
  //#define INVERT_Y2_VS_Y_DIR   // Enable if Y2 direction signal is opposite to Y
  //#define Y_DUAL_ENDSTOPS
  #if ENABLED(Y_DUAL_ENDSTOPS)
    #define Y2_USE_ENDSTOP _YMAX_
    #define Y2_ENDSTOP_ADJUSTMENT  0
  #endif
#endif

// Activate a solenoid on the active extruder with M380. Disable all with M381.
// Define SOL0_PIN, SOL1_PIN, etc., for each extruder that has a solenoid.
//#define EXT_SOLENOID

// @section homing

/**
 * Homing Procedure
 * Homing (G28) does an indefinite move towards the endstops to establish
 * the position of the toolhead relative to the workspace.
 */

//#define SENSORLESS_BACKOFF_MM  { 2, 2, 0 }  // (mm) Backoff from endstops before sensorless homing

#define HOMING_BUMP_MM      { 5, 5, 2 }       // (mm) Backoff from endstops after first bump
#define HOMING_BUMP_DIVISOR { 2, 2, 4 }       // Re-Bump Speed Divisor (Divides the Homing Feedrate)

//#define HOMING_BACKOFF_POST_MM { 2, 2, 2 }  // (mm) Backoff from endstops after homing

//#define QUICK_HOME                          // If G28 contains XY do a diagonal move first
//#define HOME_Y_BEFORE_X                     // If G28 contains XY home Y before X
//#define HOME_Z_FIRST                        // Home Z first. Requires a Z-MIN endstop (not a probe).
//#define CODEPENDENT_XY_HOMING               // If X/Y can't home without homing Y/X first

// @section motion

#define AXIS_RELATIVE_MODES { false, false, false }

// Add a Duplicate option for well-separated conjoined nozzles
//#define MULTI_NOZZLE_DUPLICATION

// By default pololu step drivers require an active high signal. However, some high power drivers require an active low signal as step.
#define INVERT_X_STEP_PIN false
#define INVERT_Y_STEP_PIN false
#define INVERT_Z_STEP_PIN false
#define INVERT_I_STEP_PIN false
#define INVERT_J_STEP_PIN false
#define INVERT_K_STEP_PIN false
#define INVERT_U_STEP_PIN false
#define INVERT_V_STEP_PIN false
#define INVERT_W_STEP_PIN false
#define INVERT_E_STEP_PIN false

/**
 * Idle Stepper Shutdown
 * Enable DISABLE_IDLE_* to shut down axis steppers after an idle period.
 * The default timeout duration can be overridden with M18 and M84. Set to 0 for No Timeout.
 */
#define DEFAULT_STEPPER_TIMEOUT_SEC 120
#define DISABLE_IDLE_X
#define DISABLE_IDLE_Y
#define DISABLE_IDLE_Z    // Disable if the nozzle could fall onto your printed part!
//#define DISABLE_IDLE_I
//#define DISABLE_IDLE_J
//#define DISABLE_IDLE_K
//#define DISABLE_IDLE_U
//#define DISABLE_IDLE_V
//#define DISABLE_IDLE_W
#define DISABLE_IDLE_E    // Shut down all idle extruders

// Default Minimum Feedrates for printing and travel moves
#define DEFAULT_MINIMUMFEEDRATE       0.0     // (mm/s) Minimum feedrate. Set with M205 S.
#define DEFAULT_MINTRAVELFEEDRATE     0.0     // (mm/s) Minimum travel feedrate. Set with M205 T.

// Minimum time that a segment needs to take as the buffer gets emptied
#define DEFAULT_MINSEGMENTTIME        20000   // (µs) Set with M205 B.

// Slow down the machine if the lookahead buffer is (by default) half full.
// Increase the slowdown divisor for larger buffer sizes.
#define SLOWDOWN
#if ENABLED(SLOWDOWN)
  #define SLOWDOWN_DIVISOR 2
#endif

/**
 * XY Frequency limit
 * Reduce resonance by limiting the frequency of small zigzag infill moves.
 * See https://hydraraptor.blogspot.com/2010/12/frequency-limit.html
 * Use M201 F<freq> S<min%> to change limits at runtime.
 */
//#define XY_FREQUENCY_LIMIT      10 // (Hz) Maximum frequency of small zigzag infill moves. Set with M201 F<hertz>.
#ifdef XY_FREQUENCY_LIMIT
  #define XY_FREQUENCY_MIN_PERCENT 5 // (%) Minimum FR percentage to apply. Set with M201 S<min%>.
#endif

// Minimum planner junction speed. Sets the default minimum speed the planner plans for at the end
// of the buffer and all stops. This should not be much greater than zero and should only be changed
// if unwanted behavior is observed on a user's machine when running at very slow speeds.
#define MINIMUM_PLANNER_SPEED 0.05 // (mm/s)

//
// Backlash Compensation
// Adds extra movement to axes on direction-changes to account for backlash.
//
//#define BACKLASH_COMPENSATION
#if ENABLED(BACKLASH_COMPENSATION)
  // Define values for backlash distance and correction.
  // If BACKLASH_GCODE is enabled these values are the defaults.
  #define BACKLASH_DISTANCE_MM { 0, 0, 0 } // (linear=mm, rotational=°) One value for each linear axis
  #define BACKLASH_CORRECTION    0.0       // 0.0 = no correction; 1.0 = full correction

  // Add steps for motor direction changes on CORE kinematics
  //#define CORE_BACKLASH

  // Set BACKLASH_SMOOTHING_MM to spread backlash correction over multiple segments
  // to reduce print artifacts. (Enabling this is costly in memory and computation!)
  //#define BACKLASH_SMOOTHING_MM 3 // (mm)

  // Add runtime configuration and tuning of backlash values (M425)
  //#define BACKLASH_GCODE

  #if ENABLED(BACKLASH_GCODE)
    // Measure the Z backlash when probing (G29) and set with "M425 Z"
    #define MEASURE_BACKLASH_WHEN_PROBING

    #if ENABLED(MEASURE_BACKLASH_WHEN_PROBING)
      // When measuring, the probe will move up to BACKLASH_MEASUREMENT_LIMIT
      // mm away from point of contact in BACKLASH_MEASUREMENT_RESOLUTION
      // increments while checking for the contact to be broken.
      #define BACKLASH_MEASUREMENT_LIMIT       0.5   // (mm)
      #define BACKLASH_MEASUREMENT_RESOLUTION  0.005 // (mm)
      #define BACKLASH_MEASUREMENT_FEEDRATE    Z_PROBE_FEEDRATE_SLOW // (mm/min)
    #endif
  #endif
#endif

/**
 * Automatic backlash, position, and hotend offset calibration
 *
 * Enable G425 to run automatic calibration using an electrically-
 * conductive cube, bolt, or washer mounted on the bed.
 *
 * G425 uses the probe to touch the top and sides of the calibration object
 * on the bed and measures and/or correct positional offsets, axis backlash
 * and hotend offsets.
 *
 * Note: HOTEND_OFFSET and CALIBRATION_OBJECT_CENTER must be set to within
 *       ±5mm of true values for G425 to succeed.
 */
//#define CALIBRATION_GCODE
#if ENABLED(CALIBRATION_GCODE)

  //#define CALIBRATION_SCRIPT_PRE  "M117 Starting Auto-Calibration\nT0\nG28\nG12\nM117 Calibrating..."
  //#define CALIBRATION_SCRIPT_POST "M500\nM117 Calibration data saved"

  #define CALIBRATION_MEASUREMENT_RESOLUTION     0.01 // mm

  #define CALIBRATION_FEEDRATE_SLOW             60    // mm/min
  #define CALIBRATION_FEEDRATE_FAST           1200    // mm/min
  #define CALIBRATION_FEEDRATE_TRAVEL         3000    // mm/min

  // The following parameters refer to the conical section of the nozzle tip.
  #define CALIBRATION_NOZZLE_TIP_HEIGHT          1.0  // mm
  #define CALIBRATION_NOZZLE_OUTER_DIAMETER      2.0  // mm

  // Uncomment to enable reporting (required for "G425 V", but consumes flash).
  //#define CALIBRATION_REPORTING

  // The true location and dimension the cube/bolt/washer on the bed.
  #define CALIBRATION_OBJECT_CENTER     { 264.0, -22.0,  -2.0 } // mm
  #define CALIBRATION_OBJECT_DIMENSIONS {  10.0,  10.0,  10.0 } // mm

  // Comment out any sides which are unreachable by the probe. For best
  // auto-calibration results, all sides must be reachable.
  #define CALIBRATION_MEASURE_RIGHT
  #define CALIBRATION_MEASURE_FRONT
  #define CALIBRATION_MEASURE_LEFT
  #define CALIBRATION_MEASURE_BACK

  //#define CALIBRATION_MEASURE_IMIN
  //#define CALIBRATION_MEASURE_IMAX
  //#define CALIBRATION_MEASURE_JMIN
  //#define CALIBRATION_MEASURE_JMAX
  //#define CALIBRATION_MEASURE_KMIN
  //#define CALIBRATION_MEASURE_KMAX
  //#define CALIBRATION_MEASURE_UMIN
  //#define CALIBRATION_MEASURE_UMAX
  //#define CALIBRATION_MEASURE_VMIN
  //#define CALIBRATION_MEASURE_VMAX
  //#define CALIBRATION_MEASURE_WMIN
  //#define CALIBRATION_MEASURE_WMAX

  // Probing at the exact top center only works if the center is flat. If
  // probing on a screw head or hollow washer, probe near the edges.
  //#define CALIBRATION_MEASURE_AT_TOP_EDGES

  // Define the pin to read during calibration
  #ifndef CALIBRATION_PIN
    //#define CALIBRATION_PIN -1            // Define here to override the default pin
    #define CALIBRATION_PIN_INVERTING false // Set to true to invert the custom pin
    //#define CALIBRATION_PIN_PULLDOWN
    #define CALIBRATION_PIN_PULLUP
  #endif
#endif

/**
 * Adaptive Step Smoothing increases the resolution of multi-axis moves, particularly at step frequencies
 * below 1kHz (for AVR) or 10kHz (for ARM), where aliasing between axes in multi-axis moves causes audible
 * vibration and surface artifacts. The algorithm adapts to provide the best possible step smoothing at the
 * lowest stepping frequencies.
 */
//#define ADAPTIVE_STEP_SMOOTHING

/**
 * Custom Microstepping
 * Override as-needed for your setup. Up to 3 MS pins are supported.
 */
//#define MICROSTEP1 LOW,LOW,LOW
//#define MICROSTEP2 HIGH,LOW,LOW
//#define MICROSTEP4 LOW,HIGH,LOW
//#define MICROSTEP8 HIGH,HIGH,LOW
//#define MICROSTEP16 LOW,LOW,HIGH
//#define MICROSTEP32 HIGH,LOW,HIGH

// Microstep settings (Requires a board with pins named X_MS1, X_MS2, etc.)
#define MICROSTEP_MODES { 16, 16, 16, 16, 16, 16 } // [1,2,4,8,16]

/**
 *  @section  stepper motor current
 *
 *  Some boards have a means of setting the stepper motor current via firmware.
 *
 *  The power on motor currents are set by:
 *    PWM_MOTOR_CURRENT - used by MINIRAMBO & ULTIMAIN_2
 *                         known compatible chips: A4982
 *    DIGIPOT_MOTOR_CURRENT - used by BQ_ZUM_MEGA_3D, RAMBO & SCOOVO_X9H
 *                         known compatible chips: AD5206
 *    DAC_MOTOR_CURRENT_DEFAULT - used by PRINTRBOARD_REVF & RIGIDBOARD_V2
 *                         known compatible chips: MCP4728
 *    DIGIPOT_I2C_MOTOR_CURRENTS - used by 5DPRINT, AZTEEG_X3_PRO, AZTEEG_X5_MINI_WIFI, MIGHTYBOARD_REVE
 *                         known compatible chips: MCP4451, MCP4018
 *
 *  Motor currents can also be set by M907 - M910 and by the LCD.
 *    M907 - applies to all.
 *    M908 - BQ_ZUM_MEGA_3D, RAMBO, PRINTRBOARD_REVF, RIGIDBOARD_V2 & SCOOVO_X9H
 *    M909, M910 & LCD - only PRINTRBOARD_REVF & RIGIDBOARD_V2
 */
//#define PWM_MOTOR_CURRENT { 1300, 1300, 1250 }          // Values in milliamps
//#define DIGIPOT_MOTOR_CURRENT { 135,135,135,135,135 }   // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
//#define DAC_MOTOR_CURRENT_DEFAULT { 70, 80, 90, 80 }    // Default drive percent - X, Y, Z, E axis

/**
 * I2C-based DIGIPOTs (e.g., Azteeg X3 Pro)
 */
//#define DIGIPOT_MCP4018             // Requires https://github.com/felias-fogg/SlowSoftI2CMaster
//#define DIGIPOT_MCP4451
#if EITHER(DIGIPOT_MCP4018, DIGIPOT_MCP4451)
  #define DIGIPOT_I2C_NUM_CHANNELS 8  // 5DPRINT:4   AZTEEG_X3_PRO:8   MKS_SBASE:5   MIGHTYBOARD_REVE:5

  // Actual motor currents in Amps. The number of entries must match DIGIPOT_I2C_NUM_CHANNELS.
  // These correspond to the physical drivers, so be mindful if the order is changed.
  #define DIGIPOT_I2C_MOTOR_CURRENTS { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 } // AZTEEG_X3_PRO

  //#define DIGIPOT_USE_RAW_VALUES    // Use DIGIPOT_MOTOR_CURRENT raw wiper values (instead of A4988 motor currents)

  /**
   * Common slave addresses:
   *
   *                        A   (A shifted)   B   (B shifted)  IC
   * Smoothie              0x2C (0x58)       0x2D (0x5A)       MCP4451
   * AZTEEG_X3_PRO         0x2C (0x58)       0x2E (0x5C)       MCP4451
   * AZTEEG_X5_MINI        0x2C (0x58)       0x2E (0x5C)       MCP4451
   * AZTEEG_X5_MINI_WIFI         0x58              0x5C        MCP4451
   * MIGHTYBOARD_REVE      0x2F (0x5E)                         MCP4018
   */
  //#define DIGIPOT_I2C_ADDRESS_A 0x2C  // Unshifted slave address for first DIGIPOT
  //#define DIGIPOT_I2C_ADDRESS_B 0x2D  // Unshifted slave address for second DIGIPOT
#endif

//===========================================================================
//=============================Additional Features===========================
//===========================================================================
#if EITHER(SDSUPPORT, LCD_SET_PROGRESS_MANUALLY)
  #if ANY(HAS_MARLINUI_U8GLIB, EXTENSIBLE_UI, HAS_MARLINUI_HD44780, IS_TFTGLCD_PANEL)
    //#define SHOW_REMAINING_TIME         // Display estimated time to completion
    #if ENABLED(SHOW_REMAINING_TIME)
      //#define USE_M73_REMAINING_TIME    // Use remaining time from M73 command instead of estimation
      //#define ROTATE_PROGRESS_DISPLAY   // Display (P)rogress, (E)lapsed, and (R)emaining time
    #endif
  #endif

  #if EITHER(HAS_MARLINUI_U8GLIB, EXTENSIBLE_UI)
    //#define PRINT_PROGRESS_SHOW_DECIMALS // Show progress with decimal digits
  #endif

  #if EITHER(HAS_MARLINUI_HD44780, IS_TFTGLCD_PANEL)
    //#define LCD_PROGRESS_BAR            // Show a progress bar on HD44780 LCDs for SD printing
    #if ENABLED(LCD_PROGRESS_BAR)
      #define PROGRESS_BAR_BAR_TIME 2000  // (ms) Amount of time to show the bar
      #define PROGRESS_BAR_MSG_TIME 3000  // (ms) Amount of time to show the status message
      #define PROGRESS_MSG_EXPIRE   0     // (ms) Amount of time to retain the status message (0=forever)
      //#define PROGRESS_MSG_ONCE         // Show the message for MSG_TIME then clear it
      //#define LCD_PROGRESS_BAR_TEST     // Add a menu item to test the progress bar
    #endif
  #endif
#endif

#if ENABLED(SDSUPPORT)
  /**
   * SD Card SPI Speed
   * May be required to resolve "volume init" errors.
   *
   * Enable and set to SPI_HALF_SPEED, SPI_QUARTER_SPEED, or SPI_EIGHTH_SPEED
   *  otherwise full speed will be applied.
   *
   * :['SPI_HALF_SPEED', 'SPI_QUARTER_SPEED', 'SPI_EIGHTH_SPEED']
   */
  //#define SD_SPI_SPEED SPI_HALF_SPEED

  // The standard SD detect circuit reads LOW when media is inserted and HIGH when empty.
  // Enable this option and set to HIGH if your SD cards are incorrectly detected.
  //#define SD_DETECT_STATE HIGH

  //#define SD_IGNORE_AT_STARTUP            // Don't mount the SD card when starting up
  //#define SDCARD_READONLY                 // Read-only SD card (to save over 2K of flash)

  //#define GCODE_REPEAT_MARKERS            // Enable G-code M808 to set repeat markers and do looping

  #define SD_PROCEDURE_DEPTH 1              // Increase if you need more nested M32 calls

  #define SD_FINISHED_STEPPERRELEASE true   // Disable steppers when SD Print is finished
  #define SD_FINISHED_RELEASECOMMAND "M84"  // Use "M84XYE" to keep Z enabled so your bed stays in place

  // Reverse SD sort to show "more recent" files first, according to the card's FAT.
  // Since the FAT gets out of order with usage, SDCARD_SORT_ALPHA is recommended.
  #define SDCARD_RATHERRECENTFIRST

  #define SD_MENU_CONFIRM_START             // Confirm the selected SD file before printing

  //#define NO_SD_AUTOSTART                 // Remove auto#.g file support completely to save some Flash, SRAM
  //#define MENU_ADDAUTOSTART               // Add a menu option to run auto#.g files

  //#define BROWSE_MEDIA_ON_INSERT          // Open the file browser when media is inserted

  //#define MEDIA_MENU_AT_TOP               // Force the media menu to be listed on the top of the main menu

  #define EVENT_GCODE_SD_ABORT "G28XY"      // G-code to run on SD Abort Print (e.g., "G28XY" or "G27")

  #if ENABLED(PRINTER_EVENT_LEDS)
    #define PE_LEDS_COMPLETED_TIME  (30*60) // (seconds) Time to keep the LED "done" color before restoring normal illumination
  #endif

  /**
   * Sort SD file listings in alphabetical order.
   *
   * With this option enabled, items on SD cards will be sorted
   * by name for easier navigation.
   *
   * By default...
   *
   *  - Use the slowest -but safest- method for sorting.
   *  - Folders are sorted to the top.
   *  - The sort key is statically allocated.
   *  - No added G-code (M34) support.
   *  - 40 item sorting limit. (Items after the first 40 are unsorted.)
   *
   * SD sorting uses static allocation (as set by SDSORT_LIMIT), allowing the
   * compiler to calculate the worst-case usage and throw an error if the SRAM
   * limit is exceeded.
   *
   *  - SDSORT_USES_RAM provides faster sorting via a static directory buffer.
   *  - SDSORT_USES_STACK does the same, but uses a local stack-based buffer.
   *  - SDSORT_CACHE_NAMES will retain the sorted file listing in RAM. (Expensive!)
   *  - SDSORT_DYNAMIC_RAM only uses RAM when the SD menu is visible. (Use with caution!)
   */
  //#define SDCARD_SORT_ALPHA

  // SD Card Sorting options
  #if ENABLED(SDCARD_SORT_ALPHA)
    #define SDSORT_LIMIT       40     // Maximum number of sorted items (10-256). Costs 27 bytes each.
    #define SDSORT_FOLDERS     -1     // -1=above  0=none  1=below
    #define SDSORT_GCODE       false  // Enable G-code M34 to set sorting behaviors: M34 S<-1|0|1> F<-1|0|1>
    #define SDSORT_USES_RAM    false  // Pre-allocate a static array for faster pre-sorting.
    #define SDSORT_USES_STACK  false  // Prefer the stack for pre-sorting to give back some SRAM. (Negated by next 2 options.)
    #define SDSORT_CACHE_NAMES false  // Keep sorted items in RAM longer for speedy performance. Most expensive option.
    #define SDSORT_DYNAMIC_RAM false  // Use dynamic allocation (within SD menus). Least expensive option. Set SDSORT_LIMIT before use!
    #define SDSORT_CACHE_VFATS 2      // Maximum number of 13-byte VFAT entries to use for sorting.
                                      // Note: Only affects SCROLL_LONG_FILENAMES with SDSORT_CACHE_NAMES but not SDSORT_DYNAMIC_RAM.
  #endif

  // Allow international symbols in long filenames. To display correctly, the
  // LCD's font must contain the characters. Check your selected LCD language.
  //#define UTF_FILENAME_SUPPORT

  //#define LONG_FILENAME_HOST_SUPPORT    // Get the long filename of a file/folder with 'M33 <dosname>' and list long filenames with 'M20 L'
  //#define LONG_FILENAME_WRITE_SUPPORT   // Create / delete files with long filenames via M28, M30, and Binary Transfer Protocol
  //#define M20_TIMESTAMP_SUPPORT         // Include timestamps by adding the 'T' flag to M20 commands

  //#define SCROLL_LONG_FILENAMES         // Scroll long filenames in the SD card menu

  //#define SD_ABORT_NO_COOLDOWN          // Leave the heaters on after Stop Print (not recommended!)

  /**
   * Abort SD printing when any endstop is triggered.
   * This feature is enabled with 'M540 S1' or from the LCD menu.
   * Endstops must be activated for this option to work.
   */
  //#define SD_ABORT_ON_ENDSTOP_HIT
  #if ENABLED(SD_ABORT_ON_ENDSTOP_HIT)
    //#define SD_ABORT_ON_ENDSTOP_HIT_GCODE "G28XY" // G-code to run on endstop hit (e.g., "G28XY" or "G27")
  #endif

  //#define SD_REPRINT_LAST_SELECTED_FILE // On print completion open the LCD Menu and select the same file

  //#define AUTO_REPORT_SD_STATUS         // Auto-report media status with 'M27 S<seconds>'

  /**
   * Support for USB thumb drives using an Arduino USB Host Shield or
   * equivalent MAX3421E breakout board. The USB thumb drive will appear
   * to Marlin as an SD card.
   *
   * The MAX3421E can be assigned the same pins as the SD card reader, with
   * the following pin mapping:
   *
   *    SCLK, MOSI, MISO --> SCLK, MOSI, MISO
   *    INT              --> SD_DETECT_PIN [1]
   *    SS               --> SDSS
   *
   * [1] On AVR an interrupt-capable pin is best for UHS3 compatibility.
   */
  //#define USB_FLASH_DRIVE_SUPPORT
  #if ENABLED(USB_FLASH_DRIVE_SUPPORT)
    /**
     * USB Host Shield Library
     *
     * - UHS2 uses no interrupts and has been production-tested
     *   on a LulzBot TAZ Pro with a 32-bit Archim board.
     *
     * - UHS3 is newer code with better USB compatibility. But it
     *   is less tested and is known to interfere with Servos.
     *   [1] This requires USB_INTR_PIN to be interrupt-capable.
     */
    //#define USE_UHS2_USB
    //#define USE_UHS3_USB

    #define DISABLE_DUE_SD_MMC // Disable USB Host access to USB Drive to prevent hangs on block access for DUE platform

    /**
     * Native USB Host supported by some boards (USB OTG)
     */
    //#define USE_OTG_USB_HOST

    #if DISABLED(USE_OTG_USB_HOST)
      #define USB_CS_PIN    SDSS
      #define USB_INTR_PIN  SD_DETECT_PIN
    #endif
  #endif

  /**
   * When using a bootloader that supports SD-Firmware-Flashing,
   * add a menu item to activate SD-FW-Update on the next reboot.
   *
   * Requires ATMEGA2560 (Arduino Mega)
   *
   * Tested with this bootloader:
   *   https://github.com/FleetProbe/MicroBridge-Arduino-ATMega2560
   */
  //#define SD_FIRMWARE_UPDATE
  #if ENABLED(SD_FIRMWARE_UPDATE)
    #define SD_FIRMWARE_UPDATE_EEPROM_ADDR    0x1FF
    #define SD_FIRMWARE_UPDATE_ACTIVE_VALUE   0xF0
    #define SD_FIRMWARE_UPDATE_INACTIVE_VALUE 0xFF
  #endif

  /**
   * Enable this option if you have more than ~3K of unused flash space.
   * Marlin will embed all settings in the firmware binary as compressed data.
   * Use 'M503 C' to write the settings out to the SD Card as 'mc.zip'.
   * See docs/ConfigEmbedding.md for details on how to use 'mc-apply.py'.
   */
  //#define CONFIGURATION_EMBEDDING

  // Add an optimized binary file transfer mode, initiated with 'M28 B1'
  //#define BINARY_FILE_TRANSFER

  #if ENABLED(BINARY_FILE_TRANSFER)
    // Include extra facilities (e.g., 'M20 F') supporting firmware upload via BINARY_FILE_TRANSFER
    //#define CUSTOM_FIRMWARE_UPLOAD
  #endif

  /**
   * Set this option to one of the following (or the board's defaults apply):
   *
   *           LCD - Use the SD drive in the external LCD controller.
   *       ONBOARD - Use the SD drive on the control board.
   *  CUSTOM_CABLE - Use a custom cable to access the SD (as defined in a pins file).
   *
   * :[ 'LCD', 'ONBOARD', 'CUSTOM_CABLE' ]
   */
  //#define SDCARD_CONNECTION LCD

  // Enable if SD detect is rendered useless (e.g., by using an SD extender)
  //#define NO_SD_DETECT

  /**
   * Multiple volume support - EXPERIMENTAL.
   * Adds 'M21 Pm' / 'M21 S' / 'M21 U' to mount SD Card / USB Drive.
   */
  //#define MULTI_VOLUME
  #if ENABLED(MULTI_VOLUME)
    #define VOLUME_SD_ONBOARD
    #define VOLUME_USB_FLASH_DRIVE
    #define DEFAULT_VOLUME SV_SD_ONBOARD
    #define DEFAULT_SHARED_VOLUME SV_USB_FLASH_DRIVE
  #endif

#endif // SDSUPPORT


/**
 * Babystepping enables movement of the axes by tiny increments without changing
 * the current position values. This feature is used primarily to adjust the Z
 * axis in the first layer of a print in real-time.
 *
 * Warning: Does not respect endstops!
 */
//#define BABYSTEPPING
#if ENABLED(BABYSTEPPING)
  //#define INTEGRATED_BABYSTEPPING         // EXPERIMENTAL integration of babystepping into the Stepper ISR
  //#define BABYSTEP_WITHOUT_HOMING
  //#define BABYSTEP_ALWAYS_AVAILABLE       // Allow babystepping at all times (not just during movement)
  //#define BABYSTEP_XY                     // Also enable X/Y Babystepping. Not supported on DELTA!
  #define BABYSTEP_INVERT_Z false           // Change if Z babysteps should go the other way
  //#define BABYSTEP_MILLIMETER_UNITS       // Specify BABYSTEP_MULTIPLICATOR_(XY|Z) in mm instead of micro-steps
  #define BABYSTEP_MULTIPLICATOR_Z  1       // (steps or mm) Steps or millimeter distance for each Z babystep
  #define BABYSTEP_MULTIPLICATOR_XY 1       // (steps or mm) Steps or millimeter distance for each XY babystep

  //#define DOUBLECLICK_FOR_Z_BABYSTEPPING  // Double-click on the Status Screen for Z Babystepping.
  #if ENABLED(DOUBLECLICK_FOR_Z_BABYSTEPPING)
    #define DOUBLECLICK_MAX_INTERVAL 1250   // Maximum interval between clicks, in milliseconds.
                                            // Note: Extra time may be added to mitigate controller latency.
    //#define MOVE_Z_WHEN_IDLE              // Jump to the move Z menu on double-click when printer is idle.
    #if ENABLED(MOVE_Z_WHEN_IDLE)
      #define MOVE_Z_IDLE_MULTIPLICATOR 1   // Multiply 1mm by this factor for the move step size.
    #endif
  #endif

  //#define BABYSTEP_DISPLAY_TOTAL          // Display total babysteps since last G28

  //#define BABYSTEP_ZPROBE_OFFSET          // Combine M851 Z and Babystepping
  #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
    //#define BABYSTEP_HOTEND_Z_OFFSET      // For multiple hotends, babystep relative Z offsets
    //#define BABYSTEP_ZPROBE_GFX_OVERLAY   // Enable graphical overlay on Z-offset editor
  #endif
#endif

/**
 * Direct Stepping
 *
 * Comparable to the method used by Klipper, G6 direct stepping significantly
 * reduces motion calculations, increases top printing speeds, and results in
 * less step aliasing by calculating all motions in advance.
 * Preparing your G-code: https://github.com/colinrgodsey/step-daemon
 */
//#define DIRECT_STEPPING

/**
 * G38 Probe Target
 *
 * This option adds G38.2 and G38.3 (probe towards target)
 * and optionally G38.4 and G38.5 (probe away from target).
 * Set MULTIPLE_PROBING for G38 to probe more than once.
 */
//#define G38_PROBE_TARGET
#if ENABLED(G38_PROBE_TARGET)
  //#define G38_PROBE_AWAY        // Include G38.4 and G38.5 to probe away from target
  #define G38_MINIMUM_MOVE 0.0275 // (mm) Minimum distance that will produce a move.
#endif

// Moves (or segments) with fewer steps than this will be joined with the next move
#define MIN_STEPS_PER_SEGMENT 6

/**
 * Minimum delay before and after setting the stepper DIR (in ns)
 *     0 : No delay (Expect at least 10µS since one Stepper ISR must transpire)
 *    20 : Minimum for TMC2xxx drivers
 *   200 : Minimum for A4988 drivers
 *   400 : Minimum for A5984 drivers
 *   500 : Minimum for LV8729 drivers (guess, no info in datasheet)
 *   650 : Minimum for DRV8825 drivers
 *  1500 : Minimum for TB6600 drivers (guess, no info in datasheet)
 * 15000 : Minimum for TB6560 drivers (guess, no info in datasheet)
 *
 * Override the default value based on the driver type set in Configuration.h.
 */
//#define MINIMUM_STEPPER_POST_DIR_DELAY 650
//#define MINIMUM_STEPPER_PRE_DIR_DELAY 650

/**
 * Minimum stepper driver pulse width (in µs)
 *   0 : Smallest possible width the MCU can produce, compatible with TMC2xxx drivers
 *   0 : Minimum 500ns for LV8729, adjusted in stepper.h
 *   1 : Minimum for A4988 and A5984 stepper drivers
 *   2 : Minimum for DRV8825 stepper drivers
 *   3 : Minimum for TB6600 stepper drivers
 *  30 : Minimum for TB6560 stepper drivers
 *
 * Override the default value based on the driver type set in Configuration.h.
 */
//#define MINIMUM_STEPPER_PULSE 2

/**
 * Maximum stepping rate (in Hz) the stepper driver allows
 *  If undefined, defaults to 1MHz / (2 * MINIMUM_STEPPER_PULSE)
 *  5000000 : Maximum for TMC2xxx stepper drivers
 *  1000000 : Maximum for LV8729 stepper driver
 *  500000  : Maximum for A4988 stepper driver
 *  250000  : Maximum for DRV8825 stepper driver
 *  150000  : Maximum for TB6600 stepper driver
 *   15000  : Maximum for TB6560 stepper driver
 *
 * Override the default value based on the driver type set in Configuration.h.
 */
//#define MAXIMUM_STEPPER_RATE 250000

// @section temperature

// Control heater 0 and heater 1 in parallel.
//#define HEATERS_PARALLEL

//===========================================================================
//================================= Buffers =================================
//===========================================================================

// @section gcode

// The number of linear moves that can be in the planner at once.
// The value of BLOCK_BUFFER_SIZE must be a power of 2 (e.g., 8, 16, 32)
#if BOTH(SDSUPPORT, DIRECT_STEPPING)
  #define BLOCK_BUFFER_SIZE  8
#elif ENABLED(SDSUPPORT)
  #define BLOCK_BUFFER_SIZE 16
#else
  #define BLOCK_BUFFER_SIZE 16
#endif

// @section serial

// The ASCII buffer for serial input
#define MAX_CMD_SIZE 96
#define BUFSIZE 4

// Transmission to Host Buffer Size
// To save 386 bytes of flash (and TX_BUFFER_SIZE+3 bytes of RAM) set to 0.
// To buffer a simple "ok" you need 4 bytes.
// For ADVANCED_OK (M105) you need 32 bytes.
// For debug-echo: 128 bytes for the optimal speed.
// Other output doesn't need to be that speedy.
// :[0, 2, 4, 8, 16, 32, 64, 128, 256]
#define TX_BUFFER_SIZE 0

// Host Receive Buffer Size
// Without XON/XOFF flow control (see SERIAL_XON_XOFF below) 32 bytes should be enough.
// To use flow control, set this buffer size to at least 1024 bytes.
// :[0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048]
//#define RX_BUFFER_SIZE 1024

#if RX_BUFFER_SIZE >= 1024
  // Enable to have the controller send XON/XOFF control characters to
  // the host to signal the RX buffer is becoming full.
  //#define SERIAL_XON_XOFF
#endif

// Monitor RX buffer usage
// Dump an error to the serial port if the serial receive buffer overflows.
// If you see these errors, increase the RX_BUFFER_SIZE value.
// Not supported on all platforms.
//#define RX_BUFFER_MONITOR

/**
 * Emergency Command Parser
 *
 * Add a low-level parser to intercept certain commands as they
 * enter the serial receive buffer, so they cannot be blocked.
 * Currently handles M108, M112, M410, M876
 * NOTE: Not yet implemented for all platforms.
 */
//#define EMERGENCY_PARSER

/**
 * Realtime Reporting (requires EMERGENCY_PARSER)
 *
 * - Report position and state of the machine (like Grbl).
 * - Auto-report position during long moves.
 * - Useful for CNC/LASER.
 *
 * Adds support for commands:
 *  S000 : Report State and Position while moving.
 *  P000 : Instant Pause / Hold while moving.
 *  R000 : Resume from Pause / Hold.
 *
 * - During Hold all Emergency Parser commands are available, as usual.
 * - Enable NANODLP_Z_SYNC and NANODLP_ALL_AXIS for move command end-state reports.
 */
//#define REALTIME_REPORTING_COMMANDS
#if ENABLED(REALTIME_REPORTING_COMMANDS)
  //#define FULL_REPORT_TO_HOST_FEATURE   // Auto-report the machine status like Grbl CNC
#endif

/**
 * Bad Serial-connections can miss a received command by sending an 'ok'
 * Therefore some clients abort after 30 seconds in a timeout.
 * Some other clients start sending commands while receiving a 'wait'.
 * This "wait" is only sent when the buffer is empty. 1 second is a good value here.
 */
//#define NO_TIMEOUTS 1000 // (ms)

// Some clients will have this feature soon. This could make the NO_TIMEOUTS unnecessary.
//#define ADVANCED_OK

// Printrun may have trouble receiving long strings all at once.
// This option inserts short delays between lines of serial output.
#define SERIAL_OVERRUN_PROTECTION

// For serial echo, the number of digits after the decimal point
//#define SERIAL_FLOAT_PRECISION 4

// @section extras

/**
 * Extra Fan Speed
 * Adds a secondary fan speed for each print-cooling fan.
 *   'M106 P<fan> T3-255' : Set a secondary speed for <fan>
 *   'M106 P<fan> T2'     : Use the set secondary speed
 *   'M106 P<fan> T1'     : Restore the previous fan speed
 */
//#define EXTRA_FAN_SPEED

// @section tmc

// @section tmc_smart

/**
 * Trinamic Smart Drivers
 *
 * To use TMC2130, TMC2160, TMC2660, TMC5130, TMC5160 stepper drivers in SPI mode:
 *  - Connect your SPI pins to the Hardware SPI interface on the board.
 *    Some boards have simple jumper connections! See your board's documentation.
 *  - Define the required Stepper CS pins in your `pins_MYBOARD.h` file.
 *    (See the RAMPS pins, for example.)
 *  - You can also use Software SPI with GPIO pins instead of Hardware SPI.
 *
 * To use TMC220x stepper drivers with Serial UART:
 *  - Connect PDN_UART to the #_SERIAL_TX_PIN through a 1K resistor.
 *    For reading capabilities also connect PDN_UART to #_SERIAL_RX_PIN with no resistor.
 *    Some boards have simple jumper connections! See your board's documentation.
 *  - These drivers can also be used with Hardware Serial.
 *
 * The TMC26XStepper library is required for TMC26X stepper drivers.
 *   https://github.com/MarlinFirmware/TMC26XStepper
 *
 * The TMCStepper library is required for other TMC stepper drivers.
 *   https://github.com/teemuatlut/TMCStepper
 *
 * @section tmc/config
 */
#if HAS_TRINAMIC_CONFIG || HAS_TMC26X

  #define HOLD_MULTIPLIER    0.5  // Scales down the holding current from run current

  /**
   * Interpolate microsteps to 256
   * Override for each driver with <driver>_INTERPOLATE settings below
   */
  #define INTERPOLATE      true

  #if AXIS_IS_TMC_CONFIG(X)
    #define X_CURRENT       800        // (mA) RMS current. Multiply by 1.414 for peak current.
    #define X_CURRENT_HOME  X_CURRENT  // (mA) RMS current for homing. (Typically lower than *_CURRENT.)
    #define X_MICROSTEPS     16        // 0..256
    #define X_RSENSE          0.11     // Multiplied x1000 for TMC26X
    #define X_CHAIN_POS      -1        // -1..0: Not chained. 1: MCU MOSI connected. 2: Next in chain, ...
    //#define X_INTERPOLATE  true      // Enable to override 'INTERPOLATE' for the X axis
  #endif

  #if AXIS_IS_TMC_CONFIG(X2)
    #define X2_CURRENT      X_CURRENT
    #define X2_CURRENT_HOME X_CURRENT_HOME
    #define X2_MICROSTEPS   X_MICROSTEPS
    #define X2_RSENSE       X_RSENSE
    #define X2_CHAIN_POS     -1
    //#define X2_INTERPOLATE true
    //#define X2_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(Y)
    #define Y_CURRENT       800
    #define Y_CURRENT_HOME  Y_CURRENT
    #define Y_MICROSTEPS     16
    #define Y_RSENSE          0.11
    #define Y_CHAIN_POS      -1
    //#define Y_INTERPOLATE  true
    //#define Y_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(Y2)
    #define Y2_CURRENT      Y_CURRENT
    #define Y2_CURRENT_HOME Y_CURRENT_HOME
    #define Y2_MICROSTEPS   Y_MICROSTEPS
    #define Y2_RSENSE       Y_RSENSE
    #define Y2_CHAIN_POS     -1
    //#define Y2_INTERPOLATE true
    //#define Y2_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(Z)
    #define Z_CURRENT       800
    #define Z_CURRENT_HOME  Z_CURRENT
    #define Z_MICROSTEPS     16
    #define Z_RSENSE          0.11
    #define Z_CHAIN_POS      -1
    //#define Z_INTERPOLATE  true
    //#define Z_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(Z2)
    #define Z2_CURRENT      Z_CURRENT
    #define Z2_CURRENT_HOME Z_CURRENT_HOME
    #define Z2_MICROSTEPS   Z_MICROSTEPS
    #define Z2_RSENSE       Z_RSENSE
    #define Z2_CHAIN_POS     -1
    //#define Z2_INTERPOLATE true
    //#define Z2_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(Z3)
    #define Z3_CURRENT      Z_CURRENT
    #define Z3_CURRENT_HOME Z_CURRENT_HOME
    #define Z3_MICROSTEPS   Z_MICROSTEPS
    #define Z3_RSENSE       Z_RSENSE
    #define Z3_CHAIN_POS     -1
    //#define Z3_INTERPOLATE true
    //#define Z3_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(Z4)
    #define Z4_CURRENT      Z_CURRENT
    #define Z4_CURRENT_HOME Z_CURRENT_HOME
    #define Z4_MICROSTEPS   Z_MICROSTEPS
    #define Z4_RSENSE       Z_RSENSE
    #define Z4_CHAIN_POS     -1
    //#define Z4_INTERPOLATE true
    //#define Z4_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(I)
    #define I_CURRENT      800
    #define I_CURRENT_HOME I_CURRENT
    #define I_MICROSTEPS    16
    #define I_RSENSE         0.11
    #define I_CHAIN_POS     -1
    //#define I_INTERPOLATE  true
    //#define I_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(J)
    #define J_CURRENT      800
    #define J_CURRENT_HOME J_CURRENT
    #define J_MICROSTEPS    16
    #define J_RSENSE         0.11
    #define J_CHAIN_POS     -1
    //#define J_INTERPOLATE  true
    //#define J_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(K)
    #define K_CURRENT      800
    #define K_CURRENT_HOME K_CURRENT
    #define K_MICROSTEPS    16
    #define K_RSENSE         0.11
    #define K_CHAIN_POS     -1
    //#define K_INTERPOLATE  true
    //#define K_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(U)
    #define U_CURRENT      800
    #define U_CURRENT_HOME U_CURRENT
    #define U_MICROSTEPS     8
    #define U_RSENSE         0.11
    #define U_CHAIN_POS     -1
    //#define U_INTERPOLATE  true
    //#define U_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(V)
    #define V_CURRENT      800
    #define V_CURRENT_HOME V_CURRENT
    #define V_MICROSTEPS     8
    #define V_RSENSE         0.11
    #define V_CHAIN_POS     -1
    //#define V_INTERPOLATE  true
    //#define V_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(W)
    #define W_CURRENT      800
    #define W_CURRENT_HOME W_CURRENT
    #define W_MICROSTEPS     8
    #define W_RSENSE         0.11
    #define W_CHAIN_POS     -1
    //#define W_INTERPOLATE  true
    //#define W_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E0)
    #define E0_CURRENT      800
    #define E0_MICROSTEPS    16
    #define E0_RSENSE         0.11
    #define E0_CHAIN_POS     -1
    //#define E0_INTERPOLATE true
    //#define E0_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E1)
    #define E1_CURRENT      E0_CURRENT
    #define E1_MICROSTEPS   E0_MICROSTEPS
    #define E1_RSENSE       E0_RSENSE
    #define E1_CHAIN_POS     -1
    //#define E1_INTERPOLATE true
    //#define E1_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E2)
    #define E2_CURRENT      E0_CURRENT
    #define E2_MICROSTEPS   E0_MICROSTEPS
    #define E2_RSENSE       E0_RSENSE
    #define E2_CHAIN_POS     -1
    //#define E2_INTERPOLATE true
    //#define E2_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E3)
    #define E3_CURRENT      E0_CURRENT
    #define E3_MICROSTEPS   E0_MICROSTEPS
    #define E3_RSENSE       E0_RSENSE
    #define E3_CHAIN_POS     -1
    //#define E3_INTERPOLATE true
    //#define E3_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E4)
    #define E4_CURRENT      E0_CURRENT
    #define E4_MICROSTEPS   E0_MICROSTEPS
    #define E4_RSENSE       E0_RSENSE
    #define E4_CHAIN_POS     -1
    //#define E4_INTERPOLATE true
    //#define E4_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E5)
    #define E5_CURRENT      E0_CURRENT
    #define E5_MICROSTEPS   E0_MICROSTEPS
    #define E5_RSENSE       E0_RSENSE
    #define E5_CHAIN_POS     -1
    //#define E5_INTERPOLATE true
    //#define E5_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E6)
    #define E6_CURRENT      E0_CURRENT
    #define E6_MICROSTEPS   E0_MICROSTEPS
    #define E6_RSENSE       E0_RSENSE
    #define E6_CHAIN_POS     -1
    //#define E6_INTERPOLATE true
    //#define E6_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E7)
    #define E7_CURRENT      E0_CURRENT
    #define E7_MICROSTEPS   E0_MICROSTEPS
    #define E7_RSENSE       E0_RSENSE
    #define E7_CHAIN_POS     -1
    //#define E7_INTERPOLATE true
    //#define E7_HOLD_MULTIPLIER 0.5
  #endif

  // @section tmc/spi

  /**
   * Override default SPI pins for TMC2130, TMC2160, TMC2660, TMC5130 and TMC5160 drivers here.
   * The default pins can be found in your board's pins file.
   */
  //#define X_CS_PIN      -1
  //#define Y_CS_PIN      -1
  //#define Z_CS_PIN      -1
  //#define X2_CS_PIN     -1
  //#define Y2_CS_PIN     -1
  //#define Z2_CS_PIN     -1
  //#define Z3_CS_PIN     -1
  //#define Z4_CS_PIN     -1
  //#define I_CS_PIN      -1
  //#define J_CS_PIN      -1
  //#define K_CS_PIN      -1
  //#define U_CS_PIN      -1
  //#define V_CS_PIN      -1
  //#define W_CS_PIN      -1
  //#define E0_CS_PIN     -1
  //#define E1_CS_PIN     -1
  //#define E2_CS_PIN     -1
  //#define E3_CS_PIN     -1
  //#define E4_CS_PIN     -1
  //#define E5_CS_PIN     -1
  //#define E6_CS_PIN     -1
  //#define E7_CS_PIN     -1

  /**
   * Software option for SPI driven drivers (TMC2130, TMC2160, TMC2660, TMC5130 and TMC5160).
   * The default SW SPI pins are defined the respective pins files,
   * but you can override or define them here.
   */
  //#define TMC_USE_SW_SPI
  //#define TMC_SPI_MOSI  -1
  //#define TMC_SPI_MISO  -1
  //#define TMC_SPI_SCK   -1

  // @section tmc/serial

  /**
   * Four TMC2209 drivers can use the same HW/SW serial port with hardware configured addresses.
   * Set the address using jumpers on pins MS1 and MS2.
   * Address | MS1  | MS2
   *       0 | LOW  | LOW
   *       1 | HIGH | LOW
   *       2 | LOW  | HIGH
   *       3 | HIGH | HIGH
   *
   * Set *_SERIAL_TX_PIN and *_SERIAL_RX_PIN to match for all drivers
   * on the same serial port, either here or in your board's pins file.
   */
  //#define  X_SLAVE_ADDRESS 0
  //#define  Y_SLAVE_ADDRESS 0
  //#define  Z_SLAVE_ADDRESS 0
  //#define X2_SLAVE_ADDRESS 0
  //#define Y2_SLAVE_ADDRESS 0
  //#define Z2_SLAVE_ADDRESS 0
  //#define Z3_SLAVE_ADDRESS 0
  //#define Z4_SLAVE_ADDRESS 0
  //#define  I_SLAVE_ADDRESS 0
  //#define  J_SLAVE_ADDRESS 0
  //#define  K_SLAVE_ADDRESS 0
  //#define  U_SLAVE_ADDRESS 0
  //#define  V_SLAVE_ADDRESS 0
  //#define  W_SLAVE_ADDRESS 0
  //#define E0_SLAVE_ADDRESS 0
  //#define E1_SLAVE_ADDRESS 0
  //#define E2_SLAVE_ADDRESS 0
  //#define E3_SLAVE_ADDRESS 0
  //#define E4_SLAVE_ADDRESS 0
  //#define E5_SLAVE_ADDRESS 0
  //#define E6_SLAVE_ADDRESS 0
  //#define E7_SLAVE_ADDRESS 0

  // @section tmc/smart

  /**
   * Software enable
   *
   * Use for drivers that do not use a dedicated enable pin, but rather handle the same
   * function through a communication line such as SPI or UART.
   */
  //#define SOFTWARE_DRIVER_ENABLE

  // @section tmc/stealthchop

  /**
   * TMC2130, TMC2160, TMC2208, TMC2209, TMC5130 and TMC5160 only
   * Use Trinamic's ultra quiet stepping mode.
   * When disabled, Marlin will use spreadCycle stepping mode.
   */
  #if HAS_STEALTHCHOP
    #define STEALTHCHOP_XY
    #define STEALTHCHOP_Z
    #define STEALTHCHOP_I
    #define STEALTHCHOP_J
    #define STEALTHCHOP_K
    #define STEALTHCHOP_U
    #define STEALTHCHOP_V
    #define STEALTHCHOP_W
    #define STEALTHCHOP_E
  #endif

  /**
   * Optimize spreadCycle chopper parameters by using predefined parameter sets
   * or with the help of an example included in the library.
   * Provided parameter sets are
   * CHOPPER_DEFAULT_12V
   * CHOPPER_DEFAULT_19V
   * CHOPPER_DEFAULT_24V
   * CHOPPER_DEFAULT_36V
   * CHOPPER_09STEP_24V   // 0.9 degree steppers (24V)
   * CHOPPER_PRUSAMK3_24V // Imported parameters from the official Průša firmware for MK3 (24V)
   * CHOPPER_MARLIN_119   // Old defaults from Marlin v1.1.9
   *
   * Define your own with:
   * { <off_time[1..15]>, <hysteresis_end[-3..12]>, hysteresis_start[1..8] }
   */
  #define CHOPPER_TIMING CHOPPER_DEFAULT_12V        // All axes (override below)
  //#define CHOPPER_TIMING_X  CHOPPER_TIMING        // For X Axes (override below)
  //#define CHOPPER_TIMING_X2 CHOPPER_TIMING_X
  //#define CHOPPER_TIMING_Y  CHOPPER_TIMING        // For Y Axes (override below)
  //#define CHOPPER_TIMING_Y2 CHOPPER_TIMING_Y
  //#define CHOPPER_TIMING_Z  CHOPPER_TIMING        // For Z Axes (override below)
  //#define CHOPPER_TIMING_Z2 CHOPPER_TIMING_Z
  //#define CHOPPER_TIMING_Z3 CHOPPER_TIMING_Z
  //#define CHOPPER_TIMING_Z4 CHOPPER_TIMING_Z
  //#define CHOPPER_TIMING_I  CHOPPER_TIMING        // For I Axis
  //#define CHOPPER_TIMING_J  CHOPPER_TIMING        // For J Axis
  //#define CHOPPER_TIMING_K  CHOPPER_TIMING        // For K Axis
  //#define CHOPPER_TIMING_U  CHOPPER_TIMING        // For U Axis
  //#define CHOPPER_TIMING_V  CHOPPER_TIMING        // For V Axis
  //#define CHOPPER_TIMING_W  CHOPPER_TIMING        // For W Axis
  //#define CHOPPER_TIMING_E  CHOPPER_TIMING        // For Extruders (override below)
  //#define CHOPPER_TIMING_E1 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E2 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E3 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E4 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E5 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E6 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E7 CHOPPER_TIMING_E

  // @section tmc/status

  /**
   * Monitor Trinamic drivers
   * for error conditions like overtemperature and short to ground.
   * To manage over-temp Marlin can decrease the driver current until the error condition clears.
   * Other detected conditions can be used to stop the current print.
   * Relevant G-codes:
   * M906 - Set or get motor current in milliamps using axis codes X, Y, Z, E. Report values if no axis codes given.
   * M911 - Report stepper driver overtemperature pre-warn condition.
   * M912 - Clear stepper driver overtemperature pre-warn condition flag.
   * M122 - Report driver parameters (Requires TMC_DEBUG)
   */
  //#define MONITOR_DRIVER_STATUS

  #if ENABLED(MONITOR_DRIVER_STATUS)
    #define CURRENT_STEP_DOWN     50  // [mA]
    #define REPORT_CURRENT_CHANGE
    #define STOP_ON_ERROR
  #endif

  // @section tmc/hybrid

  /**
   * TMC2130, TMC2160, TMC2208, TMC2209, TMC5130 and TMC5160 only
   * The driver will switch to spreadCycle when stepper speed is over HYBRID_THRESHOLD.
   * This mode allows for faster movements at the expense of higher noise levels.
   * STEALTHCHOP_(XY|Z|E) must be enabled to use HYBRID_THRESHOLD.
   * M913 X/Y/Z/E to live tune the setting
   */
  //#define HYBRID_THRESHOLD

  #define X_HYBRID_THRESHOLD     100  // [mm/s]
  #define X2_HYBRID_THRESHOLD    100
  #define Y_HYBRID_THRESHOLD     100
  #define Y2_HYBRID_THRESHOLD    100
  #define Z_HYBRID_THRESHOLD       3
  #define Z2_HYBRID_THRESHOLD      3
  #define Z3_HYBRID_THRESHOLD      3
  #define Z4_HYBRID_THRESHOLD      3
  #define I_HYBRID_THRESHOLD       3  // [linear=mm/s, rotational=°/s]
  #define J_HYBRID_THRESHOLD       3  // [linear=mm/s, rotational=°/s]
  #define K_HYBRID_THRESHOLD       3  // [linear=mm/s, rotational=°/s]
  #define U_HYBRID_THRESHOLD       3  // [mm/s]
  #define V_HYBRID_THRESHOLD       3
  #define W_HYBRID_THRESHOLD       3
  #define E0_HYBRID_THRESHOLD     30
  #define E1_HYBRID_THRESHOLD     30
  #define E2_HYBRID_THRESHOLD     30
  #define E3_HYBRID_THRESHOLD     30
  #define E4_HYBRID_THRESHOLD     30
  #define E5_HYBRID_THRESHOLD     30
  #define E6_HYBRID_THRESHOLD     30
  #define E7_HYBRID_THRESHOLD     30

  /**
   * TMC Homing stepper phase.
   *
   * Improve homing repeatability by homing to stepper coil's nearest absolute
   * phase position. Trinamic drivers use a stepper phase table with 1024 values
   * spanning 4 full steps with 256 positions each (ergo, 1024 positions).
   * Full step positions (128, 384, 640, 896) have the highest holding torque.
   *
   * Values from 0..1023, -1 to disable homing phase for that axis.
   */
   //#define TMC_HOME_PHASE { 896, 896, 896 }

  /**
   * Step on both rising and falling edge signals (as with a square wave).
   */
  //#define SQUARE_WAVE_STEPPING

  /**
   * Enable M122 debugging command for TMC stepper drivers.
   * M122 S0/1 will enable continuous reporting.
   */
  //#define TMC_DEBUG

  /**
   * You can set your own advanced settings by filling in predefined functions.
   * A list of available functions can be found on the library github page
   * https://github.com/teemuatlut/TMCStepper
   *
   * Example:
   * #define TMC_ADV() { \
   *   stepperX.diag0_otpw(1); \
   *   stepperY.intpol(0); \
   * }
   */
  #define TMC_ADV() {  }

#endif // HAS_TRINAMIC_CONFIG || HAS_TMC26X

// @section i2cbus

//
// I2C Master ID for LPC176x LCD and Digital Current control
// Does not apply to other peripherals based on the Wire library.
//
//#define I2C_MASTER_ID  1  // Set a value from 0 to 2

/**
 * TWI/I2C BUS
 *
 * This feature is EXPERIMENTAL but may be useful for custom I2C peripherals.
 * Enable this to send and receive I2C data from slave devices on the bus.
 *
 * ; Example #1
 * ; This macro send the string "Marlin" to the slave device with address 0x63 (99)
 * ; It uses multiple M260 commands with one B<base 10> arg
 * M260 A99  ; Target slave address
 * M260 B77  ; M
 * M260 B97  ; a
 * M260 B114 ; r
 * M260 B108 ; l
 * M260 B105 ; i
 * M260 B110 ; n
 * M260 S1   ; Send the current buffer
 *
 * ; Example #2
 * ; Request 6 bytes from slave device with address 0x63 (99)
 * M261 A99 B5
 *
 * ; Example #3
 * ; Example serial output of a M261 request
 * echo:i2c-reply: from:99 bytes:5 data:hello
 */

//#define EXPERIMENTAL_I2CBUS
#if ENABLED(EXPERIMENTAL_I2CBUS)
  #define I2C_SLAVE_ADDRESS  0  // Set a value from 8 to 127 to act as a slave
#endif

// @section extras

/**
 * Power Monitor
 * Monitor voltage (V) and/or current (A), and -when possible- power (W)
 *
 * Read and configure with M430
 *
 * The current sensor feeds DC voltage (relative to the measured current) to an analog pin
 * The voltage sensor feeds DC voltage (relative to the measured voltage) to an analog pin
 */
//#define POWER_MONITOR_CURRENT   // Monitor the system current
//#define POWER_MONITOR_VOLTAGE   // Monitor the system voltage

#if ENABLED(POWER_MONITOR_CURRENT)
  #define POWER_MONITOR_VOLTS_PER_AMP    0.05000  // Input voltage to the MCU analog pin per amp  - DO NOT apply more than ADC_VREF!
  #define POWER_MONITOR_CURRENT_OFFSET   0        // Offset (in amps) applied to the calculated current
  #define POWER_MONITOR_FIXED_VOLTAGE   13.6      // Voltage for a current sensor with no voltage sensor (for power display)
#endif

#if ENABLED(POWER_MONITOR_VOLTAGE)
  #define POWER_MONITOR_VOLTS_PER_VOLT  0.077933  // Input voltage to the MCU analog pin per volt - DO NOT apply more than ADC_VREF!
  #define POWER_MONITOR_VOLTAGE_OFFSET  0         // Offset (in volts) applied to the calculated voltage
#endif

/**
 * CNC Coordinate Systems
 *
 * Enables G53 and G54-G59.3 commands to select coordinate systems
 * and G92.1 to reset the workspace to native machine space.
 */
#define CNC_COORDINATE_SYSTEMS

/**
 * Auto-report position with M154 S<seconds>
 */
#define AUTO_REPORT_POSITION

/**
 * Include capabilities in M115 output
 */
#define EXTENDED_CAPABILITIES_REPORT
#if ENABLED(EXTENDED_CAPABILITIES_REPORT)
  //#define M115_GEOMETRY_REPORT
#endif

// @section security

/**
 * Expected Printer Check
 * Add the M16 G-code to compare a string to the MACHINE_NAME.
 * M16 with a non-matching string causes the printer to halt.
 */
//#define EXPECTED_PRINTER_CHECK

// @section volumetrics

/**
 * Disable all Volumetric extrusion options
 */
//#define NO_VOLUMETRICS

#if DISABLED(NO_VOLUMETRICS)
  /**
   * Volumetric extrusion default state
   * Activate to make volumetric extrusion the default method,
   * with DEFAULT_NOMINAL_FILAMENT_DIA as the default diameter.
   *
   * M200 D0 to disable, M200 Dn to set a new diameter (and enable volumetric).
   * M200 S0/S1 to disable/enable volumetric extrusion.
   */
  //#define VOLUMETRIC_DEFAULT_ON

  //#define VOLUMETRIC_EXTRUDER_LIMIT
  #if ENABLED(VOLUMETRIC_EXTRUDER_LIMIT)
    /**
     * Default volumetric extrusion limit in cubic mm per second (mm^3/sec).
     * This factory setting applies to all extruders.
     * Use 'M200 [T<extruder>] L<limit>' to override and 'M502' to reset.
     * A non-zero value activates Volume-based Extrusion Limiting.
     */
    #define DEFAULT_VOLUMETRIC_EXTRUDER_LIMIT  0.00     // (mm^3/sec)
  #endif
#endif

// @section reporting

/**
 * Extra options for the M114 "Current Position" report
 */
//#define M114_DETAIL         // Use 'M114` for details to check planner calculations
//#define M114_REALTIME       // Real current position based on forward kinematics
//#define M114_LEGACY         // M114 used to synchronize on every call. Enable if needed.

//#define REPORT_FAN_CHANGE   // Report the new fan speed when changed by M106 (and others)

/**
 * Set the number of proportional font spaces required to fill up a typical character space.
 * This can help to better align the output of commands like `G29 O` Mesh Output.
 *
 * For clients that use a fixed-width font (like OctoPrint), leave this set to 1.0.
 * Otherwise, adjust according to your client and font.
 */
#define PROPORTIONAL_FONT_RATIO 1.0

/**
 * Spend 28 bytes of SRAM to optimize the G-code parser
 */
#define FASTER_GCODE_PARSER

#if ENABLED(FASTER_GCODE_PARSER)
  //#define GCODE_QUOTED_STRINGS  // Support for quoted string parameters
#endif

/**
 * Support for MeatPack G-code compression (https://github.com/scottmudge/OctoPrint-MeatPack)
 */
//#define MEATPACK_ON_SERIAL_PORT_1
//#define MEATPACK_ON_SERIAL_PORT_2

//#define GCODE_CASE_INSENSITIVE  // Accept G-code sent to the firmware in lowercase

//#define REPETIER_GCODE_M360     // Add commands originally from Repetier FW

/**
 * Enable this option for a leaner build of Marlin that removes all
 * workspace offsets, simplifying coordinate transformations, leveling, etc.
 *
 *  - M206 and M428 are disabled.
 *  - G92 will revert to its behavior from Marlin 1.0.
 */
//#define NO_WORKSPACE_OFFSETS

/**
 * CNC G-code options
 * Support CNC-style G-code dialects used by laser cutters, drawing machine cams, etc.
 * Note that G0 feedrates should be used with care for 3D printing (if used at all).
 * High feedrates may cause ringing and harm print quality.
 */
//#define PAREN_COMMENTS      // Support for parentheses-delimited comments
//#define GCODE_MOTION_MODES  // Remember the motion mode (G0 G1 G2 G3 G5 G38.X) and apply for X Y Z E F, etc.

// Enable and set a (default) feedrate for all G0 moves
//#define G0_FEEDRATE 3000 // (mm/min)
#ifdef G0_FEEDRATE
  //#define VARIABLE_G0_FEEDRATE // The G0 feedrate is set by F in G0 motion mode
#endif

/**
 * Startup commands
 *
 * Execute certain G-code commands immediately after power-on.
 */
//#define STARTUP_COMMANDS "M17 Z"

/**
 * G-code Macros
 *
 * Add G-codes M810-M819 to define and run G-code macros.
 * Macros are not saved to EEPROM.
 */
//#define GCODE_MACROS
#if ENABLED(GCODE_MACROS)
  #define GCODE_MACROS_SLOTS       5  // Up to 10 may be used
  #define GCODE_MACROS_SLOT_SIZE  50  // Maximum length of a single macro
#endif

/**
 * User-defined buttons to run custom G-code.
 * Up to 25 may be defined.
 */
//#define CUSTOM_USER_BUTTONS
#if ENABLED(CUSTOM_USER_BUTTONS)
  //#define BUTTON1_PIN -1
  #if PIN_EXISTS(BUTTON1)
    #define BUTTON1_HIT_STATE     LOW       // State of the triggered button. NC=LOW. NO=HIGH.
    #define BUTTON1_WHEN_PRINTING false     // Button allowed to trigger during printing?
    #define BUTTON1_GCODE         "G28"
    #define BUTTON1_DESC          "Homing"  // Optional string to set the LCD status
  #endif

  //#define BUTTON2_PIN -1
  #if PIN_EXISTS(BUTTON2)
    #define BUTTON2_HIT_STATE     LOW
    #define BUTTON2_WHEN_PRINTING false
    #define BUTTON2_GCODE         "M140 S" STRINGIFY(PREHEAT_1_TEMP_BED) "\nM104 S" STRINGIFY(PREHEAT_1_TEMP_HOTEND)
    #define BUTTON2_DESC          "Preheat for " PREHEAT_1_LABEL
  #endif

  //#define BUTTON3_PIN -1
  #if PIN_EXISTS(BUTTON3)
    #define BUTTON3_HIT_STATE     LOW
    #define BUTTON3_WHEN_PRINTING false
    #define BUTTON3_GCODE         "M140 S" STRINGIFY(PREHEAT_2_TEMP_BED) "\nM104 S" STRINGIFY(PREHEAT_2_TEMP_HOTEND)
    #define BUTTON3_DESC          "Preheat for " PREHEAT_2_LABEL
  #endif
#endif

// @section host

/**
 * Host Action Commands
 *
 * Define host streamer action commands in compliance with the standard.
 *
 * See https://reprap.org/wiki/G-code#Action_commands
 * Common commands ........ poweroff, pause, paused, resume, resumed, cancel
 * G29_RETRY_AND_RECOVER .. probe_rewipe, probe_failed
 *
 * Some features add reason codes to extend these commands.
 *
 * Host Prompt Support enables Marlin to use the host for user prompts so
 * filament runout and other processes can be managed from the host side.
 */
//#define HOST_ACTION_COMMANDS
#if ENABLED(HOST_ACTION_COMMANDS)
  //#define HOST_PAUSE_M76                // Tell the host to pause in response to M76
  //#define HOST_PROMPT_SUPPORT           // Initiate host prompts to get user feedback
  #if ENABLED(HOST_PROMPT_SUPPORT)
    //#define HOST_STATUS_NOTIFICATIONS   // Send some status messages to the host as notifications
  #endif
  //#define HOST_START_MENU_ITEM          // Add a menu item that tells the host to start
  //#define HOST_SHUTDOWN_MENU_ITEM       // Add a menu item that tells the host to shut down
#endif

// @section extras

/**
 * Cancel Objects
 *
 * Implement M486 to allow Marlin to skip objects
 */
//#define CANCEL_OBJECTS
#if ENABLED(CANCEL_OBJECTS)
  #define CANCEL_OBJECTS_REPORTING // Emit the current object as a status message
#endif

/**
 * I2C position encoders for closed loop control.
 * Developed by Chris Barr at Aus3D.
 *
 * Wiki: https://wiki.aus3d.com.au/Magnetic_Encoder
 * Github: https://github.com/Aus3D/MagneticEncoder
 *
 * Supplier: https://aus3d.com.au/products/magnetic-encoder-module
 * Alternative Supplier: https://reliabuild3d.com/
 *
 * Reliabuild encoders have been modified to improve reliability.
 * @section i2c encoders
 */

//#define I2C_POSITION_ENCODERS
#if ENABLED(I2C_POSITION_ENCODERS)

  #define I2CPE_ENCODER_CNT         1                       // The number of encoders installed; max of 5
                                                            // encoders supported currently.

  #define I2CPE_ENC_1_ADDR          I2CPE_PRESET_ADDR_X     // I2C address of the encoder. 30-200.
  #define I2CPE_ENC_1_AXIS          X_AXIS                  // Axis the encoder module is installed on.  <X|Y|Z|E>_AXIS.
  #define I2CPE_ENC_1_TYPE          I2CPE_ENC_TYPE_LINEAR   // Type of encoder:  I2CPE_ENC_TYPE_LINEAR -or-
                                                            // I2CPE_ENC_TYPE_ROTARY.
  #define I2CPE_ENC_1_TICKS_UNIT    2048                    // 1024 for magnetic strips with 2mm poles; 2048 for
                                                            // 1mm poles. For linear encoders this is ticks / mm,
                                                            // for rotary encoders this is ticks / revolution.
  //#define I2CPE_ENC_1_TICKS_REV     (16 * 200)            // Only needed for rotary encoders; number of stepper
                                                            // steps per full revolution (motor steps/rev * microstepping)
  //#define I2CPE_ENC_1_INVERT                              // Invert the direction of axis travel.
  #define I2CPE_ENC_1_EC_METHOD     I2CPE_ECM_MICROSTEP     // Type of error error correction.
  #define I2CPE_ENC_1_EC_THRESH     0.10                    // Threshold size for error (in mm) above which the
                                                            // printer will attempt to correct the error; errors
                                                            // smaller than this are ignored to minimize effects of
                                                            // measurement noise / latency (filter).

  #define I2CPE_ENC_2_ADDR          I2CPE_PRESET_ADDR_Y     // Same as above, but for encoder 2.
  #define I2CPE_ENC_2_AXIS          Y_AXIS
  #define I2CPE_ENC_2_TYPE          I2CPE_ENC_TYPE_LINEAR
  #define I2CPE_ENC_2_TICKS_UNIT    2048
  //#define I2CPE_ENC_2_TICKS_REV   (16 * 200)
  //#define I2CPE_ENC_2_INVERT
  #define I2CPE_ENC_2_EC_METHOD     I2CPE_ECM_MICROSTEP
  #define I2CPE_ENC_2_EC_THRESH     0.10

  #define I2CPE_ENC_3_ADDR          I2CPE_PRESET_ADDR_Z     // Encoder 3.  Add additional configuration options
  #define I2CPE_ENC_3_AXIS          Z_AXIS                  // as above, or use defaults below.

  #define I2CPE_ENC_4_ADDR          I2CPE_PRESET_ADDR_E     // Encoder 4.
  #define I2CPE_ENC_4_AXIS          E_AXIS

  #define I2CPE_ENC_5_ADDR          34                      // Encoder 5.
  #define I2CPE_ENC_5_AXIS          E_AXIS

  // Default settings for encoders which are enabled, but without settings configured above.
  #define I2CPE_DEF_TYPE            I2CPE_ENC_TYPE_LINEAR
  #define I2CPE_DEF_ENC_TICKS_UNIT  2048
  #define I2CPE_DEF_TICKS_REV       (16 * 200)
  #define I2CPE_DEF_EC_METHOD       I2CPE_ECM_NONE
  #define I2CPE_DEF_EC_THRESH       0.1

  //#define I2CPE_ERR_THRESH_ABORT  100.0                   // Threshold size for error (in mm) error on any given
                                                            // axis after which the printer will abort. Comment out to
                                                            // disable abort behavior.

  #define I2CPE_TIME_TRUSTED        10000                   // After an encoder fault, there must be no further fault
                                                            // for this amount of time (in ms) before the encoder
                                                            // is trusted again.

  /**
   * Position is checked every time a new command is executed from the buffer but during long moves,
   * this setting determines the minimum update time between checks. A value of 100 works well with
   * error rolling average when attempting to correct only for skips and not for vibration.
   */
  #define I2CPE_MIN_UPD_TIME_MS     4                       // (ms) Minimum time between encoder checks.

  // Use a rolling average to identify persistent errors that indicate skips, as opposed to vibration and noise.
  #define I2CPE_ERR_ROLLING_AVERAGE

#endif // I2C_POSITION_ENCODERS

/**
 * Mechanical Gantry Calibration
 * Modern replacement for the Průša TMC_Z_CALIBRATION.
 * Adds capability to work with any adjustable current drivers.
 * Implemented as G34 because M915 is deprecated.
 * @section calibrate
 */
//#define MECHANICAL_GANTRY_CALIBRATION
#if ENABLED(MECHANICAL_GANTRY_CALIBRATION)
  #define GANTRY_CALIBRATION_CURRENT          600     // Default calibration current in ma
  #define GANTRY_CALIBRATION_EXTRA_HEIGHT      15     // Extra distance in mm past Z_###_POS to move
  #define GANTRY_CALIBRATION_FEEDRATE         500     // Feedrate for correction move
  //#define GANTRY_CALIBRATION_TO_MIN                 // Enable to calibrate Z in the MIN direction

  //#define GANTRY_CALIBRATION_SAFE_POSITION XY_CENTER // Safe position for nozzle
  //#define GANTRY_CALIBRATION_XY_PARK_FEEDRATE 3000  // XY Park Feedrate - MMM
  //#define GANTRY_CALIBRATION_COMMANDS_PRE   ""
  #define GANTRY_CALIBRATION_COMMANDS_POST  "G28"     // G28 highly recommended to ensure an accurate position
#endif

/**
 * Ethernet. Use M552 to enable and set the IP address.
 * @section network
 */
#if HAS_ETHERNET
  #define MAC_ADDRESS { 0xDE, 0xAD, 0xBE, 0xEF, 0xF0, 0x0D }  // A MAC address unique to your network
#endif

/**
 * Native ESP32 board with WiFi or add-on ESP32 WiFi-101 module
 */
//#define WIFISUPPORT         // Marlin embedded WiFi management. Not needed for simple WiFi serial port.
//#define ESP3D_WIFISUPPORT   // ESP3D Library WiFi management (https://github.com/luc-github/ESP3DLib)

/**
 * Extras for an ESP32-based motherboard with WIFISUPPORT
 * These options don't apply to add-on WiFi modules based on ESP32 WiFi101.
 */
#if ANY(WIFISUPPORT, ESP3D_WIFISUPPORT)
  //#define WEBSUPPORT          // Start a webserver (which may include auto-discovery) using SPIFFS
  //#define OTASUPPORT          // Support over-the-air firmware updates
  //#define WIFI_CUSTOM_COMMAND // Accept feature config commands (e.g., WiFi ESP3D) from the host

  /**
   * To set a default WiFi SSID / Password, create a file called Configuration_Secure.h with
   * the following defines, customized for your network. This specific file is excluded via
   * .gitignore to prevent it from accidentally leaking to the public.
   *
   *   #define WIFI_SSID "WiFi SSID"
   *   #define WIFI_PWD  "WiFi Password"
   */
  //#include "Configuration_Secure.h" // External file with WiFi SSID / Password
#endif

/**
 * Advanced Print Counter settings
 * @section stats
 */
#if ENABLED(PRINTCOUNTER)
  #define SERVICE_WARNING_BUZZES  3
  // Activate up to 3 service interval watchdogs
  //#define SERVICE_NAME_1      "Service S"
  //#define SERVICE_INTERVAL_1  100 // print hours
  //#define SERVICE_NAME_2      "Service L"
  //#define SERVICE_INTERVAL_2  200 // print hours
  //#define SERVICE_NAME_3      "Service 3"
  //#define SERVICE_INTERVAL_3    1 // print hours
#endif

// @section develop

//
// M100 Free Memory Watcher to debug memory usage
//
//#define M100_FREE_MEMORY_WATCHER

//
// M42 - Set pin states
//
#define DIRECT_PIN_CONTROL

//
// M43 - display pin status, toggle pins, watch pins, watch endstops & toggle LED, test servo probe
//
#define PINS_DEBUGGING

// Enable Marlin dev mode which adds some special commands
//#define MARLIN_DEV_MODE

#if ENABLED(MARLIN_DEV_MODE)
  /**
   * D576 - Buffer Monitoring
   * To help diagnose print quality issues stemming from empty command buffers.
   */
  //#define BUFFER_MONITORING
#endif

/**
 * Postmortem Debugging captures misbehavior and outputs the CPU status and backtrace to serial.
 * When running in the debugger it will break for debugging. This is useful to help understand
 * a crash from a remote location. Requires ~400 bytes of SRAM and 5Kb of flash.
 */
//#define POSTMORTEM_DEBUGGING

/**
 * Software Reset options
 */
//#define SOFT_RESET_VIA_SERIAL         // 'KILL' and '^X' commands will soft-reset the controller
//#define SOFT_RESET_ON_KILL            // Use a digital button to soft-reset the controller after KILL

// Report uncleaned reset reason from register r2 instead of MCUSR. Supported by Optiboot on AVR.
//#define OPTIBOOT_RESET_REASON
