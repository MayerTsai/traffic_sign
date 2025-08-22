#include "traffic_sign.h"
#include <Arduino.h>

ptr_traffic_sign_t create_traffic_sign(ptr_traffic_light_t light,
                                       unsigned long green_time,
                                       unsigned long yellow_time,
                                       unsigned long red_time,
                                       traffic_light_state_t initial_state,
                                       unsigned long current_time)
{
  ptr_traffic_sign_t traffic_sign = (ptr_traffic_sign_t)malloc(sizeof(traffic_sign_t));
  if (traffic_sign == NULL)
    return NULL;
  traffic_sign->light = light;
  traffic_sign->green_interval = green_time;
  traffic_sign->yellow_interval = yellow_time;
  traffic_sign->red_interval = red_time;
  traffic_sign->current_state = initial_state;
  traffic_sign->last_change_time = current_time;
  set_traffic_light_state(traffic_sign->light, initial_state == GREEN_STATE ? GREEN_STATE : RED_STATE);
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

  switch (traffic_sign->current_state)
  {
  case GREEN_STATE:
    if (time_in_state >= traffic_sign->green_interval)
    {
      traffic_sign->current_state = YELLOW_STATE;
      traffic_sign->last_change_time = current_time;
      set_traffic_light_state(traffic_sign->light, YELLOW_STATE);
    }
    break;
  case YELLOW_STATE:
    if (time_in_state >= traffic_sign->yellow_interval)
    {
      traffic_sign->current_state = RED_STATE;
      traffic_sign->last_change_time = current_time;
      set_traffic_light_state(traffic_sign->light, RED_STATE);
    }
    break;
  case RED_STATE:
    if (time_in_state >= traffic_sign->red_interval)
    {
      traffic_sign->current_state = GREEN_STATE;
      traffic_sign->last_change_time = current_time;
      set_traffic_light_state(traffic_sign->light, GREEN_STATE);
    }
    break;
  }
}
