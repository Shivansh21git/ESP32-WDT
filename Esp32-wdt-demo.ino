#include <esp_task_wdt.h>

#define LED_PIN 2  // Built-in LED on ESP32
#define WDT_TIMEOUT 5  // Watchdog timeout in seconds

void setup() {
    Serial.begin(115200);

    // Initialize and configure the watchdog timer
    esp_task_wdt_config_t wdtConfig = {
        .timeout_ms = WDT_TIMEOUT * 1000,  // Convert seconds to milliseconds
        .idle_core_mask = 0,               // Use on core 0
        .trigger_panic = true              // Trigger panic on timeout
    };
    esp_task_wdt_init(&wdtConfig);
    esp_task_wdt_add(NULL);  // Add the current task to the watchdog

    pinMode(LED_PIN, OUTPUT);
    Serial.println("ESP32 Watchdog Test with Race Condition");
}

// Simulated race condition variable
volatile bool blockWDTReset = false;

void loop() {
    if (!blockWDTReset) {
        Serial.println("Resetting WDT...");
        esp_task_wdt_reset();
    } else {
        Serial.println("Race condition triggered! WDT will not reset...");
    }

    digitalWrite(LED_PIN, HIGH);
    Serial.println("Running normal computations...");
    computePrimes(50);
    computeFibonacci(10);
    floatComputation();
    digitalWrite(LED_PIN, LOW);

    // Simulate a race condition: Occasionally enter an infinite loop
    if (random(0, 5) == 3) {  // Random chance to cause a deadlock
        Serial.println("Triggering a CPU lock! System should reboot soon...");
        blockWDTReset = true;
        while (1);  // Infinite loop, preventing WDT reset
    }

    delay(1000);  // Allow time before the next loop iteration
}

void computePrimes(int limit) {
    for (int num = 2; num <= limit; num++) {
        bool isPrime = true;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            Serial.print(num);
            Serial.print(" ");
        }
    }
    Serial.println();
}

void floatComputation() {
    float result = 0.0;
    for (float i = 1.0; i < 10.0; i += 0.1) {
        result += (i * i) / 2.5;
    }
    Serial.print("Floating-point computation result: ");
    Serial.println(result);
}

void computeFibonacci(int terms) {
    int a = 0, b = 1, nextTerm;
    Serial.print("Fibonacci: ");
    for (int i = 0; i < terms; i++) {
        Serial.print(a);
        Serial.print(" ");
        nextTerm = a + b;
        a = b;
        b = nextTerm;
    }
    Serial.println();
}
