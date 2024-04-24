#ifndef __PID_H__
#define __PID_H__

#include "float.h"

typedef struct PID
{
    Float kp;
    Float ki;
    Float kd;
    Float integral;
    Float prev_e;
} PID;

Float update_pid(PID *const pid, Float e, Float dt);

PID new_pid_controller(Float kp, Float ki, Float kd);

#endif