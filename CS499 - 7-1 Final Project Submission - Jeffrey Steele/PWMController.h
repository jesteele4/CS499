///////////////////////////////////////////////////////////////////////////////
// PWMController.h
// ============
//  AUTHOR: Jeffrey Steele
///////////////////////////////////////////////////////////////////////////////

#ifndef PWMCONTROLLER_H
#define PWMCONTROLLER_H

#include <ti/drivers/PWM.h>

// Initializes PWM with given parameters
PWM_Handle setupPWM(uint32_t pwmIndex, uint32_t dutyCycle, uint16_t period);

// Sets the PWM duty cycle
void setPWMDuty(uint32_t pwmIndex, uint32_t dutyCycle);

#endif