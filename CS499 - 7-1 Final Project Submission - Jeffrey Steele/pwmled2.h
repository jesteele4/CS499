///////////////////////////////////////////////////////////////////////////////
// pwmled2.h
// ============
//  AUTHOR: Jeffrey Steele
///////////////////////////////////////////////////////////////////////////////

#ifndef PWMLED2_H
#define PWMLED2_H

#include <ti/drivers/PWM.h>

// Structure to manage a PWM-controlled LED
typedef struct {
    PWM_Handle handle;
    uint32_t pwmIndex;
    uint16_t period;
} PWMLED2;

// Initializes the PWM LED with a given index and period
void PWMLED2_init(PWMLED2 *led, uint32_t pwmIndex, uint16_t period);

// Sets the LED brightness by changing the duty cycle (0-100%)
void PWMLED2_setBrightness(PWMLED2 *led, uint32_t dutyCycle);

// Turns the LED off by setting the duty cycle to 0
void PWMLED2_turnOff(PWMLED2 *led);

// Turns the LED on with full brightness (100%)
void PWMLED2_turnOn(PWMLED2 *led);

#endif