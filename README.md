# ESP32 Watchdog Timer Example

This repository contains an example implementation of a watchdog timer on the ESP32 using the `esp_task_wdt` library in the Arduino IDE. The watchdog timer prevents the system from getting stuck by resetting the ESP32 if the main loop hangs for too long.

## Features
- Implements a software watchdog timer using `esp_task_wdt.h`
- Configurable timeout period (default: 15 seconds)
- Prevents system hangs by forcing a reset when the watchdog is not fed

## Hardware Requirements
- ESP32 development board
- USB cable for programming
- Arduino IDE with ESP32 board support installed

## Installation
1. Clone this repository:
   ```sh
   git clone https://github.com/yourusername/ESP32-Watchdog-Timer.git
   cd ESP32-Watchdog-Timer
   ```
2. Open the `.ino` file in Arduino IDE.
3. Ensure you have installed the ESP32 board support package in Arduino IDE.
4. Select the correct ESP32 board and port.
5. Upload the code to your ESP32.

## Code Overview
```cpp
#include <esp_task_wdt.h>

void setup() {
  Serial.begin(115200);
  esp_task_wdt_config_t wdtConfig = {
    .timeout_ms = 15000,  // 15-second timeout
    .idle_core_mask = ESP_TASK_WDT_IDLE_CORE_ALL,
    .trigger_panic = true
  };

  esp_task_wdt_init(&wdtConfig);
  esp_task_wdt_add(NULL); // Add current task to the watchdog
}

void loop() {
  esp_task_wdt_reset(); // Reset watchdog timer to prevent reset
  delay(1000);
}
```

## How It Works
1. **Initialize the Watchdog Timer** – The `esp_task_wdt_init()` function sets a timeout of 15 seconds.
2. **Register the Main Task** – `esp_task_wdt_add(NULL);` adds the loop function to the watchdog.
3. **Feed the Watchdog** – `esp_task_wdt_reset();` resets the watchdog timer in each loop iteration.
4. **System Reset on Timeout** – If `esp_task_wdt_reset();` is not called within the timeout period, the ESP32 will reset.

## Testing the Watchdog
To see the watchdog in action, remove or comment out `esp_task_wdt_reset();` inside the `loop()` function. The ESP32 will restart after 15 seconds due to the watchdog timeout.

```cpp
void loop() {
  // No watchdog reset here
  delay(1000);
}
```

## License
This project is open-source and available under the MIT License.

## Contributions
Feel free to submit pull requests for improvements or new examples!

---
Happy coding! 🚀

