#include <Arduino.h>
#include "traffic_sign.h"

// Define constants for pins for clarity and easy modification
const int LIGHT_A_GREEN_PIN = 2;
const int LIGHT_A_YELLOW_PIN = 3;
const int LIGHT_A_RED_PIN = 4;

const int LIGHT_B_GREEN_PIN = 5;
const int LIGHT_B_YELLOW_PIN = 6;
const int LIGHT_B_RED_PIN = 7;

// Define timing intervals for the traffic light cycle

const long PERIOD_INTERVAL = 10000;
const long YELLOW_INTERVAL = 1000;

const long LED_A_YELLOW_INTERVAL = YELLOW_INTERVAL;
const long LED_A_GREEN_INTERVAL = 5000;
const long LED_A_RED_INTERVAL = PERIOD_INTERVAL - LED_A_GREEN_INTERVAL - LED_A_YELLOW_INTERVAL;

const long LED_B_YELLOW_INTERVAL = YELLOW_INTERVAL;
const long LED_B_GREEN_INTERVAL = LED_A_RED_INTERVAL - LED_B_YELLOW_INTERVAL;
const long LED_B_RED_INTERVAL = PERIOD_INTERVAL - LED_B_GREEN_INTERVAL - LED_B_YELLOW_INTERVAL;
const long LED_B_compensation = LED_A_RED_INTERVAL - LED_B_GREEN_INTERVAL - LED_B_YELLOW_INTERVAL;

// Global pointers to our traffic objects. Initialize to NULL.
ptr_traffic_light_t light_led_A = NULL;
ptr_traffic_light_t light_led_B = NULL;
ptr_traffic_sign_t traffic_sign_A = NULL;
ptr_traffic_sign_t traffic_sign_B = NULL;

void setup()
{
  // Create the traffic light hardware representations
  light_led_A = create_traffic_light(LIGHT_A_GREEN_PIN, LIGHT_A_YELLOW_PIN, LIGHT_A_RED_PIN);
  light_led_B = create_traffic_light(LIGHT_B_GREEN_PIN, LIGHT_B_YELLOW_PIN, LIGHT_B_RED_PIN);

  // Get the initial time
  unsigned long current_time = millis();

  // Create the traffic sign logic controllers
  // Ensure one starts GREEN and the other RED for a safe intersection
  traffic_sign_A = create_traffic_sign(light_led_A,
                                       LED_A_GREEN_INTERVAL,
                                       LED_A_YELLOW_INTERVAL,
                                       LED_A_RED_INTERVAL,
                                       GREEN_STATE,
                                       (long)current_time);

  traffic_sign_B = create_traffic_sign(light_led_B,
                                       LED_B_GREEN_INTERVAL,
                                       LED_B_YELLOW_INTERVAL,
                                       LED_B_RED_INTERVAL,
                                       RED_STATE,
                                       (long)current_time - LED_B_compensation);
  Serial.begin(9600);
  Serial.print("A's green interval: ");
  Serial.print(traffic_sign_A->green_interval);
  Serial.print("    A's yellow interval: ");
  Serial.print(traffic_sign_A->yellow_interval);
  Serial.print("    A's red interval: ");
  Serial.println(traffic_sign_A->red_interval);

  Serial.print("B's green interval: ");
  Serial.print(traffic_sign_B->green_interval);
  Serial.print("    B's yellow interval: ");
  Serial.print(traffic_sign_B->yellow_interval);
  Serial.print("    B's red interval: ");
  Serial.println(traffic_sign_B->red_interval);
}

void loop()
{
  unsigned long current_time = millis();
  // Serial.println(current_time);
  update_traffic_sign(traffic_sign_A, current_time);
  update_traffic_sign(traffic_sign_B, current_time);
  Serial.print(traffic_sign_A->current_state);
  Serial.print("      ");
  Serial.println(traffic_sign_B->current_state);
}
