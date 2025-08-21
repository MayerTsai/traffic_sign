#include "traffic_sign.h"
#include <Arduino.h>

ptr_traffic_sign_t create_traffic_sign(ptr_traffic_light_t light,
                                       unsigned long delay_time,
                                       unsigned long green_time,
                                       unsigned long red_time,
                                       traffic_sign_state_t initial_sign_state,
                                       unsigned long current_time)
{
  ptr_traffic_sign_t traffic_sign = (ptr_traffic_sign_t)malloc(sizeof(traffic_sign_t));
  if (traffic_sign == NULL)
    return NULL;
  traffic_sign->light = light;
  traffic_sign->green_interval = green_time;
  traffic_sign->delay_interval = delay_time;
  traffic_sign->red_interval = red_time;
  traffic_sign->current_sign_state = initial_sign_state;
  traffic_sign->last_change_time = current_time;
  set_traffic_light_state(traffic_sign->light, initial_sign_state == GREEN_SIGN ? GREEN_STATE : RED_STATE);
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

void update_traffic_sign(ptr_traffic_sign_t traffic_sign,
                         unsigned long current_time)
{
  unsigned long time_in_state = current_time - traffic_sign->last_change_time;

  switch (traffic_sign->current_sign_state)
  {
  case GREEN_SIGN:
    if (time_in_state >= traffic_sign->green_interval)
    {
      traffic_sign->current_sign_state = RED_SIGN;
      traffic_sign->last_change_time = current_time;
      set_traffic_light_state(traffic_sign->light, YELLOW_STATE);
      delay(traffic_sign->delay_interval);
      set_traffic_light_state(traffic_sign->light, RED_STATE);
    }
    break;
  case RED_SIGN:
    if (time_in_state >= traffic_sign->red_interval)
    {
      traffic_sign->current_sign_state = GREEN_SIGN;
      traffic_sign->last_change_time = current_time;
      set_traffic_light_state(traffic_sign->light, GREEN_STATE);
    }
    break;
  }
}
