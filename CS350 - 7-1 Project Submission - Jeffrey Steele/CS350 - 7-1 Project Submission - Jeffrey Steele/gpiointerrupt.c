/*
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
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

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

 /* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/Timer.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* Constants */
#define DEBOUNCE_TIME 50 // Debounce time in milliseconds for button press
#define BUTTON_CHECK_PERIOD 200 // Button check period in milliseconds
#define TEMP_CHECK_PERIOD 500 // Temperature check period in milliseconds
#define DISPLAY_CHECK_PERIOD 1000 // Display update period in milliseconds
#define TIMER_PERIOD 100 // Timer period in milliseconds

/* Global Variables */
volatile int leftButtonPressed = 0;
volatile int rightButtonPressed = 0;
UART_Handle uart;
I2C_Handle i2c;
Timer_Handle timer0;
char outputBuffer[64];

/* Function Prototypes */
void initUART(void);
void initI2C(void);
void initTimer(void);
void gpioButtonFxn0(uint_least8_t index);
void gpioButtonFxn1(uint_least8_t index);
void timerCallback(Timer_Handle myHandle, int_fast16_t status);
int16_t readTemperature(void);
void displayTemperature(int16_t temperature, int setpoint, int heat, int seconds);

/* Main program function */
void* mainThread(void* arg0) {
    int setpoint = 25; // Default setpoint
    int heat = 0; // Heating status: 0 is off, 1 is on
    int seconds = 0; // Elapsed time in seconds
    int16_t temperature = 0; // Current temperature

    // Initialize peripherals
    GPIO_init();
    initUART();
    initI2C();
    initTimer();

    // Configure LED and Button GPIOs
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

    // Install button callbacks and enable interrupts
    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, gpioButtonFxn0);
    GPIO_setCallback(CONFIG_GPIO_BUTTON_1, gpioButtonFxn1);
    GPIO_enableInt(CONFIG_GPIO_BUTTON_0);
    GPIO_enableInt(CONFIG_GPIO_BUTTON_1);

    // Enable LED
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    // Timing control variables
    unsigned long lastButtonCheck = 0, lastTempCheck = 0, lastDisplayCheck = 0;

    // Main loop
    while (1) {
        unsigned long currentTime = Timer_getCount(timer0);

        // Button check with debouncing
        if ((currentTime - lastButtonCheck) >= BUTTON_CHECK_PERIOD) {
            if (rightButtonPressed) {
                setpoint += 1;
                rightButtonPressed = 0;
            }
            if (leftButtonPressed) {
                setpoint -= 1;
                leftButtonPressed = 0;
            }
            lastButtonCheck = currentTime;
        }

        // Temperature check and LED control
        if ((currentTime - lastTempCheck) >= TEMP_CHECK_PERIOD) {
            temperature = readTemperature();
            if (temperature < setpoint) {
                GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
                heat = 1;
            }
            else {
                GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
                heat = 0;
            }
            lastTempCheck = currentTime;
        }

        // Display temperature and control settings
        if ((currentTime - lastDisplayCheck) >= DISPLAY_CHECK_PERIOD) {
            displayTemperature(temperature, setpoint, heat, seconds);
            seconds++;
            lastDisplayCheck = currentTime;
        }
    }
}

/* Initialization and callback functions */
void initUART(void) {
    UART_Params uartParams;
    UART_init();
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.baudRate = 115200;
    uart = UART_open(CONFIG_UART_0, &uartParams);
    if (uart == NULL) {
        // Error handling: UART failed to open
        while (1);
    }
}

void initI2C(void) {
    I2C_Params i2cParams;
    I2C_init();
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    i2c = I2C_open(CONFIG_I2C_0, &i2cParams);
    if (i2c == NULL) {
        // Error handling: I2C failed to open
        while (1);
    }
}

void initTimer(void) {
    Timer_Params params;
    Timer_init();
    Timer_Params_init(&params);
    params.period = TIMER_PERIOD * 1000; // Convert ms to us
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.periodUnits = Timer_PERIOD_US;
    params.timerCallback = timerCallback;
    timer0 = Timer_open(CONFIG_TIMER_0, &params);
    if (timer0 == NULL || Timer_start(timer0) == Timer_STATUS_ERROR) {
        // Error handling: Timer failed to start
        while (1);
    }
}

void gpioButtonFxn0(uint_least8_t index) {
    static unsigned long lastPress = 0;
    unsigned long currentTime = Timer_getCount(timer0);
    if (currentTime - lastPress > DEBOUNCE_TIME) {
        leftButtonPressed = 1;
        lastPress = currentTime;
    }
}

void gpioButtonFxn1(uint_least8_t index) {
    static unsigned long lastPress = 0;
    unsigned long currentTime = Timer_getCount(timer0);
    if (currentTime - lastPress > DEBOUNCE_TIME) {
        rightButtonPressed = 1;
        lastPress = currentTime;
    }
}

void timerCallback(Timer_Handle myHandle, int_fast16_t status) {
    // Placeholder for timer callback; currently no specific action needed
}

int16_t readTemperature(void) {
    // Placeholder for actual temperature reading logic
    return 25; // Simulated temperature value
}

void displayTemperature(int16_t temperature, int setpoint, int heat, int seconds) {
    snprintf(outputBuffer, sizeof(outputBuffer), "<%02d,%02d,%d,%04d>\n", temperature, setpoint, heat, seconds);
    UART_write(uart, outputBuffer, strlen(outputBuffer));
}