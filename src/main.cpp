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
const unsigned long DELAY_INTERVAL = 1000;
const unsigned long GREEN_INTERVAL = 5000;
const unsigned long RED_INTERVAL = 5000;
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
  traffic_sign_A = create_traffic_sign(light_led_A, DELAY_INTERVAL, GREEN_INTERVAL, RED_INTERVAL, GREEN_SIGN, current_time);
  traffic_sign_B = create_traffic_sign(light_led_B, DELAY_INTERVAL, RED_INTERVAL, GREEN_INTERVAL, RED_SIGN, current_time);
}

void loop()
{
  unsigned long current_time = millis();
  update_traffic_sign(traffic_sign_A, current_time);
  update_traffic_sign(traffic_sign_B, current_time);
}
