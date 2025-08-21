#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H
typedef enum
{
  GREEN_STATE,
  YELLOW_STATE,
  RED_STATE
} traffic_light_state_t;
typedef struct
{
  int green_pin;
  int yellow_pin;
  int red_pin;
} traffic_light_t, *ptr_traffic_light_t;

ptr_traffic_light_t create_traffic_light(int g, int y, int r);
void destroy_traffic_light(ptr_traffic_light_t);
void set_traffic_light_state(ptr_traffic_light_t light, traffic_light_state_t state);

#endif // TRAFFIC_LIGHT_H