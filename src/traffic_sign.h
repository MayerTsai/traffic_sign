#ifndef TRAFFIC_SIGN_H
#define TRAFFIC_SIGN_H

#include "traffic_light.h"

typedef struct
{
  ptr_traffic_light_t light;  
  unsigned long green_interval;
  unsigned long yellow_interval;
  unsigned long red_interval;
   
  traffic_light_state_t current_state;
  unsigned long last_change_time;
} traffic_sign_t, *ptr_traffic_sign_t;

ptr_traffic_sign_t create_traffic_sign(ptr_traffic_light_t light,
                                       unsigned long green_time,
                                       unsigned long yellow_time,
                                       unsigned long red_time,
                                       traffic_light_state_t initial_sign_state,
                                       unsigned long current_time);
void destroy_traffic_sign(ptr_traffic_sign_t traffic_sign);
void update_traffic_sign(ptr_traffic_sign_t traffic_sign,
                         unsigned long current_time);

#endif // TRAFFIC_SIGN_H