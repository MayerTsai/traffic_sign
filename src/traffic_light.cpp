#include "traffic_light.h"
#include <Arduino.h>

ptr_traffic_light_t create_traffic_light(int green_pin, int yellow_pin, int red_pin)
{
  pinMode(green_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);
  ptr_traffic_light_t light = (ptr_traffic_light_t)malloc(sizeof(traffic_light_t));
  if (light == NULL)
  {
    return NULL;
  }
  light->green_pin = green_pin;
  light->yellow_pin = yellow_pin;
  light->red_pin = red_pin;
  set_traffic_light_state(light, RED_STATE);
  return light;
}

void destroy_traffic_light(ptr_traffic_light_t light)
{
  free(light);
}

void set_traffic_light_state(ptr_traffic_light_t light, traffic_light_state_t state)
{
  digitalWrite(light->green_pin, state == GREEN_STATE ? HIGH : LOW);
  digitalWrite(light->yellow_pin, state == YELLOW_STATE ? HIGH : LOW);
  digitalWrite(light->red_pin, state == RED_STATE ? HIGH : LOW);
}
