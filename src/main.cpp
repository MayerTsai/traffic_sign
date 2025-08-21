#include <Arduino.h>
#include "traffic_sign.h"

const unsigned long YELLOW_TIME_MS = 500;
const unsigned long GREEN_TIME_MS = 3000;
const unsigned long RED_TIME_MS = 2000;
// Global pointers to our traffic objects. Initialize to NULL.
ptr_traffic_light_t light_led_A = NULL;
ptr_traffic_light_t light_led_B = NULL;
ptr_traffic_sign_t traffic_sign_A = NULL;
ptr_traffic_sign_t traffic_sign_B = NULL;

void setup()
{
  // Create the traffic light hardware representations
  light_led_A = create_traffic_light(2, 3, 4);
  light_led_B = create_traffic_light(5, 6, 7);

  // Get the initial time
  unsigned long current_time = millis();

  // Create the traffic sign logic controllers
  // Ensure one starts GREEN and the other RED for a safe intersection
  traffic_sign_A = create_traffic_sign(light_led_A, YELLOW_TIME_MS, GREEN_TIME_MS, RED_TIME_MS, GREEN_SIGN, current_time);
  traffic_sign_B = create_traffic_sign(light_led_B, YELLOW_TIME_MS, RED_TIME_MS, GREEN_TIME_MS, RED_SIGN, current_time);
}

void loop()
{
  unsigned long current_time = millis();
  update_traffic_sign(traffic_sign_A, current_time);
  update_traffic_sign(traffic_sign_B, current_time);
  delay(500);
}
