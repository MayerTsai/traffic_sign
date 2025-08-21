#include "traffic_sign.h"
#include <Arduino.h>

ptr_traffic_sign_t create_traffic_sign(ptr_traffic_light_t light,
                                       unsigned long yellow_time,
                                       unsigned long green_time,
                                       unsigned long red_time,
                                       traffic_sign_color_t color,
                                       unsigned long current_time)
{
  ptr_traffic_sign_t traffic_sign = (ptr_traffic_sign_t)malloc(sizeof(traffic_sign_t));
  if (traffic_sign == NULL)
    return NULL;
  traffic_sign->light = light;
  traffic_sign->yellow_interval = yellow_time;
  traffic_sign->green_interval = green_time;
  traffic_sign->red_interval = red_time;
  traffic_sign->current_color = color;
  traffic_sign->last_change_time = current_time;
  set_traffic_light_state(traffic_sign->light, color == GREEN_SIGN ? GREEN : RED);
  return traffic_sign;
}

void destroy_traffic_sign(ptr_traffic_sign_t traffic_sign)
{
  if (traffic_sign != NULL)
  {
    destroy_traffic_light(traffic_sign->light);
    free(traffic_sign);
  }
}

void update_traffic_sign(ptr_traffic_sign_t traffic_sign, unsigned long current_time)
{
  unsigned long time_in_state = current_time - traffic_sign->last_change_time;

  switch (traffic_sign->current_color)
  {
  case GREEN_SIGN:
    if (time_in_state >= traffic_sign->green_interval)
    {
      traffic_sign->current_color = RED_SIGN;
      traffic_sign->last_change_time = current_time;
      set_traffic_light_state(traffic_sign->light, YELLOW);
      delay(traffic_sign->yellow_interval);
      set_traffic_light_state(traffic_sign->light, RED);
    }
    break;
  case RED_SIGN:
    if (time_in_state >= traffic_sign->red_interval)
    {
      traffic_sign->current_color = GREEN_SIGN;
      traffic_sign->last_change_time = current_time;
      set_traffic_light_state(traffic_sign->light, GREEN);
    }
    break;
  }
}
