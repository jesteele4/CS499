///////////////////////////////////////////////////////////////////////////////
// config.h
// ============
//  AUTHOR: Jeffrey Steele
///////////////////////////////////////////////////////////////////////////////

#ifndef CONFIG_H
#define CONFIG_H

// PWM configuration
#define PWM_PERIOD 3000            // PWM period in microseconds
#define PWM_DUTY_90 2700           // 90% of the PWM period
#define PWM_DUTY_OFF 0             // 0% of the PWM period (off)

// Timer intervals
#define BLINK_ON_TIME 1000000      // LED on-time in microseconds (1 second)
#define BLINK_OFF_TIME 1000000     // LED off-time in microseconds (1 second)
#define BLINK_INTERVAL 1000000     // Blink interval in microseconds (1 second)

// PWM channels (defined in ti_drivers_config.h)
#define CONFIG_PWM_0 0
#define CONFIG_PWM_1 1

#endif