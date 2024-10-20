///////////////////////////////////////////////////////////////////////////////
// main_nortos.c
// ============
//  AUTHOR: Jeffrey Steele
///////////////////////////////////////////////////////////////////////////////

/*
 * Copyright (c) 2017-2020, Texas Instruments Incorporated
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

/*
 *  ======== main_nortos.c ========
 */

#include "pwmled2.h"
#include "Timer.h"
#include "config.h"

// Initialize PWMLED2 instances
PWMLED2 led1, led2;
Timer timer;

void setup() {
    PWM_init();  // Initialize PWM drivers

    // Initialize LEDs with their respective PWM channels
    PWMLED2_init(&led1, CONFIG_PWM_0, PWM_PERIOD);
    PWMLED2_init(&led2, CONFIG_PWM_1, PWM_PERIOD);

    // Start with both LEDs off
    PWMLED2_turnOff(&led1);
    PWMLED2_turnOff(&led2);

    // Start the timer with the on-time interval
    startTimer(BLINK_ON_TIME);
}

void loop() {
    if (isTimeUp()) {
        static int isFirstState = 1;

        if (isFirstState) {
            PWMLED2_setBrightness(&led1, PWM_DUTY_90);  // LED1 90% brightness
            PWMLED2_turnOff(&led2);  // Turn off LED2
        } else {
            PWMLED2_turnOff(&led1);  // Turn off LED1
            PWMLED2_setBrightness(&led2, PWM_DUTY_90);  // LED2 90% brightness
        }

        // Toggle state and restart timer
        isFirstState = !isFirstState;
        startTimer(BLINK_INTERVAL);
    }
}

int main() {
    setup();
    while (1) {
        loop();  // Run the main loop
    }
    return 0;
}