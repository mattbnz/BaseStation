/**********************************************************************

CurrentMonitor.h
COPYRIGHT (c) 2013-2016 Gregg E. Berman

Part of DCC++ BASE STATION for the Arduino

**********************************************************************/

#ifndef CurrentMonitor_h
#define CurrentMonitor_h

#include "Arduino.h"

#define  CURRENT_SAMPLE_SMOOTHING   0.01
// This is the raw value sampled by analogRead into 1024 steps from 5V
// aka 0.0049V per step. We need different thresholds per motor driver
// as they have different V/A ratios on their current sense pins.
#if MOTOR_SHIELD_TYPE == 0
  // Arduino Motor Shield, 1.65V/A.
  #define  CURRENT_SAMPLE_MAX         300     // 890mA == 300*0.0049/1.65
#elif MOTOR_SHIELD_TYPE == 1
  #define  CURRENT_SAMPLE_MAX          95     // 890mA == 95*0.0049/0.525
#else
  #error CANNOT COMPILE - PLEASE SELECT A PROPER MOTOR SHIELD TYPE
#endif

#ifdef ARDUINO_AVR_UNO                        // Configuration for UNO
  #define  CURRENT_SAMPLE_TIME        10
#else                                         // Configuration for MEGA    
  #define  CURRENT_SAMPLE_TIME        1
#endif

struct CurrentMonitor{
  static long int sampleTime;
  int pin;
  float current;
  char *msg;
  CurrentMonitor(int, char *);
  static boolean checkTime();
  void check();
};

#endif

