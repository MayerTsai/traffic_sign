#include "traffic_light.h"
#include <Arduino.h>

ptr_traffic_light_t create_traffic_light(int g, int y, int r)
{
  pinMode(g, OUTPUT);
  pinMode(y, OUTPUT);
  pinMode(r, OUTPUT);
  ptr_traffic_light_t light = (ptr_traffic_light_t)malloc(sizeof(traffic_light_t));
  if (light == NULL)
  {
    return NULL;
  }
  light->green_pin = g;
  light->yellow_pin = y;
  light->red_pin = r;
  set_traffic_light_state(light, YELLOW);
  return light;
}

void destroy_traffic_light(ptr_traffic_light_t light)
{
  // Could also set pins to INPUT here if desired
  free(light);
}

void set_traffic_light_state(ptr_traffic_light_t light, traffic_state_t state)
{
  digitalWrite(light->green_pin, state == GREEN ? HIGH : LOW);
  digitalWrite(light->yellow_pin, state == YELLOW ? HIGH : LOW);
  digitalWrite(light->red_pin, state == RED ? HIGH : LOW);
}
