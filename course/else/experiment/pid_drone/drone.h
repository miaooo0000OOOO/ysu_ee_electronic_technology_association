#ifndef __DRONE_H__
#define __DRONE_H__

#include "float.h"
#include <assert.h>

/// @brief 无人机
typedef struct Drone
{
    Float h;
    Float v;
    Float m;
} Drone;

Drone new_drone(Float h, Float v, Float m);

#endif