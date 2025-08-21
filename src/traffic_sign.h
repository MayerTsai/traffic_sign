#ifndef TRAFFIC_SIGN_H
#define TRAFFIC_SIGN_H

#include "traffic_light.h"
typedef enum
{
  GREEN_SIGN,
  RED_SIGN
} traffic_sign_color_t;

typedef struct
{
  unsigned long green_interval;
  unsigned long yellow_interval;
  unsigned long red_interval;
  ptr_traffic_light_t light;
  traffic_sign_color_t current_color;
  unsigned long last_change_time;
} traffic_sign_t, *ptr_traffic_sign_t;

ptr_traffic_sign_t create_traffic_sign(ptr_traffic_light_t light,
                                       unsigned long yellow_time,
                                       unsigned long green_time,
                                       unsigned long red_time,
                                       traffic_sign_color_t color,
                                       unsigned long current_time);
void destroy_traffic_sign(ptr_traffic_sign_t traffic_sign);
void update_traffic_sign(ptr_traffic_sign_t traffic_sign,
                         unsigned long current_time);

#endif // TRAFFIC_SIGN_H