///////////////////////////////////////////////////////////////////////////////
// pwmled2.c
// ============
//  AUTHOR: Jeffrey Steele
///////////////////////////////////////////////////////////////////////////////

/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Driver Header files */
#include <ti/drivers/PWM.h>

/* Driver configuration */
#include "ti_drivers_config.h"

#include "pwmled2.h"
#include <stddef.h>  // For NULL handling

void PWMLED2_init(PWMLED2 *led, uint32_t pwmIndex, uint16_t period) {
    PWM_Params params;
    PWM_Params_init(&params);

    params.dutyUnits = PWM_DUTY_US;
    params.periodUnits = PWM_PERIOD_US;
    params.periodValue = period;

    led->pwmIndex = pwmIndex;
    led->period = period;
    led->handle = PWM_open(pwmIndex, &params);

    if (led->handle == NULL) {
        while (1);  // Handle error if PWM fails to open
    }

    PWM_start(led->handle);  // Start PWM on this channel
}

void PWMLED2_setBrightness(PWMLED2 *led, uint32_t dutyCycle) {
    if (led->handle) {
        PWM_setDuty(led->handle, dutyCycle);
    }
}

void PWMLED2_turnOff(PWMLED2 *led) {
    PWMLED2_setBrightness(led, 0);  // Set duty cycle to 0%
}

void PWMLED2_turnOn(PWMLED2 *led) {
    PWMLED2_setBrightness(led, led->period);  // Set to full brightness (100%)
}