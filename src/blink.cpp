#include <Arduino.h>
#include <stdio.h>

#define PIN_OUT_EN 9

#define PIN_OUT1 8
#define PIN_OUT2 7

#define PIN_POT_PULSE 3
#define PIN_POT_TIMING 4

#define PULSE_WIDTH_MIN_MS 10
#define PULSE_WIDTH_MAX_MS 100

#define TIMING_DELTA_MIN_MS 100
#define TIMING_DELTA_MAX_MS 2000

#define POT_MIN_VAL 10
#define POT_MAX_VAL 1000

#define MSG_MAX_LEN 20

char g_msg[MSG_MAX_LEN] = {'\0'};
int g_pot_in = 0;

int g_pulse_ms = 30;
int g_dt_ms = 1000;

inline int scale_int(const int in_min, const int in_max, 
              const int out_min, const int out_max, 
              int in) {

    if (in < in_min) {
        in = in_min;
    } else if  (in > in_max) {
        in = in_max;
    }
    float scale = ((float) (in - in_min)) / ((float) (in_max - in_min));
    return ((int) ((float) (out_max - out_min)) * scale) + out_min;

}


void loop() {

    // g_ef = digitalRead(PIN_IN_EF);   // read ef
    digitalWrite(PIN_OUT1, LOW);   // Set the LED on
    delay(g_pulse_ms);              // Wait
    digitalWrite(PIN_OUT1, HIGH);   // Set the LED on

    Serial.println("Switch state 1");
    // if (!g_ef) {
    //     Serial.println("EF Error!");
    // }
    delay(g_dt_ms);              // Wait for three seconds

    // g_ef = digitalRead(PIN_IN_EF);   // read ef
    digitalWrite(PIN_OUT2, LOW);   // Set the LED on
    delay(g_pulse_ms);              // Wait for three seconds
    digitalWrite(PIN_OUT2, HIGH);   // Set the LED on

    // snprintf(g_msg, MSG_MAX_LEN, "EF code: %d", g_val);
    // Serial.println(g_msg);
    Serial.println("Switch state 2");
    // if (!g_ef) {
    //     Serial.println("EF Error!");
    // }
    delay(g_dt_ms);              // Wait for three seconds

    // scale potentiometers
    g_pot_in = analogRead(PIN_POT_PULSE);    // read the value from the sensor
    g_pulse_ms = scale_int(POT_MIN_VAL, POT_MAX_VAL, 
                           PULSE_WIDTH_MIN_MS, PULSE_WIDTH_MAX_MS, 
                           g_pot_in);

    g_pot_in = analogRead(PIN_POT_TIMING);    // read the value from the sensor
    g_dt_ms = scale_int(POT_MIN_VAL, POT_MAX_VAL, 
                        TIMING_DELTA_MIN_MS, TIMING_DELTA_MAX_MS, 
                        g_pot_in);

    // if (g_pot_in < POT_MIN_VAL) {
    //     g_pot_in = POT_MIN_VAL;
    // } else if  (g_pot_in > POT_MAX_VAL) {
    //     g_pot_in = POT_MAX_VAL;
    // }
    // g_pulse_scale = ((float) (g_pot_in - POT_MIN_VAL)) / ((float) (POT_MAX_VAL - POT_MIN_VAL));
    // g_pulse_ms = ((int) ((float) (PULSE_WIDTH_MAX_MS - PULSE_WIDTH_MIN_MS)) * g_pulse_scale)
    //              + PULSE_WIDTH_MIN_MS;

    snprintf(g_msg, MSG_MAX_LEN, "Pot: %d", g_pot_in);
    Serial.println(g_msg);
    snprintf(g_msg, MSG_MAX_LEN, "Pulse: %d", g_pulse_ms);
    Serial.println(g_msg);

}

int main(void)
{
    // Mandatory init
    init();

    Serial.begin(115200);

    // Pin 13 has an LED connected on most Arduino boards
    pinMode(PIN_OUT1, OUTPUT);
    pinMode(PIN_OUT2, OUTPUT);
    pinMode(PIN_OUT_EN, OUTPUT);

    digitalWrite(PIN_OUT2, HIGH);   // Set the LED on
    digitalWrite(PIN_OUT1, HIGH);   // Set the LED on
    digitalWrite(PIN_OUT_EN, HIGH); 

    while (true)
        loop();

    return 0;
}
