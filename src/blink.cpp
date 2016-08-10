#include <Arduino.h>

// Pin 13 has an LED connected on most Arduino boards
#define PIN_LED 13

void loop() {
    Serial.println("LED on");
    digitalWrite(PIN_LED, HIGH);   // Set the LED on
    delay(1000);                   // Wait for one second

    Serial.println("LED off");
    digitalWrite(PIN_LED, LOW);    // Set the LED off
    delay(1000);                   // Wait for one second
} 

int main(void)
{
    // Mandatory init
    init();

    // set LED pin mode as output
    pinMode(PIN_LED, OUTPUT);

    while (true)
        loop();

    return 0;
}
