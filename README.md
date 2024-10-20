### **Example Summary**
This application controls two LEDs using the PWM driver to demonstrate how to manage LED brightness and blinking through modular design. It uses non-blocking timers to alternate LED states, ensuring smooth operation without relying on an RTOS.

### **Peripherals & Pin Assignments**
When the project is built, the **SysConfig tool** generates TI-Driver configurations into the `ti_drivers_config.c` and `ti_drivers_config.h` files. These files contain information on the pins and resources used. You can also open the `.syscfg` file in SysConfig’s graphical interface to view and modify the pins and peripherals.

- **`CONFIG_PWM_0`**: PWM instance for controlling the first LED’s brightness  
- **`CONFIG_PWM_1`**: PWM instance for controlling the second LED’s brightness  

### **Board Resources & Jumper Settings**
Refer to the **Board.html** file in your project directory for board-specific jumper settings, resources, and any necessary BoosterPack modifications.

If using **Code Composer Studio (CCS)** or IAR, you can find the Board.html file in:

    <SDK_INSTALL_DIR>/source/ti/boards/<BOARD>

### **Example Usage**
1. Build and upload the project to your board.
2. The onboard LEDs connected to **`CONFIG_PWM_0`** and **`CONFIG_PWM_1`** will alternate their brightness.
3. One LED will turn on with 90% brightness while the other turns off, then they will switch states after a delay.

### **Application Design Details**
This project uses **one thread**, implemented in `main_nortos.cpp`, with the following logic:

1. **PWM Drivers**: Initializes PWM channels for controlling LED brightness.  
2. **Timer Control**: Uses a non-blocking timer to manage on/off intervals for the LEDs.  
3. **Modular Design**: Encapsulates PWM logic within the `PWMController` class and timing logic within the `Timer` class.  
4. **Main Loop**: Alternates the LED states based on the configured timing intervals.

### **Project Files**
- **`main_nortos.cpp`**: Main logic controlling the LEDs using PWM and timers.
- **`PWMController.h` / `PWMController.cpp`**: Manages PWM setup and LED brightness control.
- **`Timer.h` / `Timer.cpp`**: Implements non-blocking timers for interval management.
- **`config.h`**: Stores configuration parameters like PWM periods and blink intervals.

### **Configuration**
Modify the following parameters in `config.h` to customize the application:

- **`PWM_PERIOD`**: Sets the PWM period in microseconds.  
- **`PWM_DUTY_90`**: Sets the duty cycle to 90% of the PWM period.  
- **`BLINK_INTERVAL`**: Controls the delay between LED state changes.  

### **Building the Application**
This project is designed for non-RTOS environments and uses **Code Composer Studio (CCS)** or **IAR**. The SysConfig tool will generate the necessary driver configurations.

1. Connect the two LEDs to the appropriate PWM channels.
2. Adjust parameters in `config.h` as needed.
3. Upload the code to your board using CCS or IAR.

### **Expected Behavior**
- **PWM Channel 0** (CONFIG_PWM_0): LED will switch between 90% brightness and off.
- **PWM Channel 1** (CONFIG_PWM_1): LED will switch between 90% brightness and off.
- The LEDs alternate their states every second, controlled by the non-blocking timer.

### **Switching to RTOS (Optional)**
If you need to use **RTOS-based logic** in the future, you can migrate the logic to a **main.cpp** thread using **FreeRTOS**. For FreeRTOS-specific configurations, refer to the `FreeRTOSConfig.h` file in your SDK.
