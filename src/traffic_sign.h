#ifndef TRAFFIC_SIGN_H
#define TRAFFIC_SIGN_H

#include "traffic_light.h"

typedef struct
{
  ptr_traffic_light_t light;
  long green_interval;
  long yellow_interval;
  long red_interval;
  traffic_light_state_t current_state;
  long last_change_time;
} traffic_sign_t, *ptr_traffic_sign_t;

ptr_traffic_sign_t create_traffic_sign(ptr_traffic_light_t light,
                                       long green_time,
                                       long yellow_time,
                                       long red_time,
                                       traffic_light_state_t initial_sign_state,
                                       long current_time);
void destroy_traffic_sign(ptr_traffic_sign_t traffic_sign);
void update_traffic_sign(ptr_traffic_sign_t traffic_sign,
                         long current_time);

#endif // TRAFFIC_SIGN_H