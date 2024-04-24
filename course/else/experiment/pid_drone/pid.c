#include "pid.h"

/// @brief 在时间步长`dt`内，输入误差`e`到PID控制器，输出控制量
/// @param pid PID控制器结构体
/// @param e 误差值
/// @param dt 时间步长
/// @return 控制量
Float update_pid(PID *const pid, Float e, Float dt)
{
    pid->integral += e * dt;
    Float ctrl = pid->kp * e + pid->ki * pid->integral + pid->kd * (e - pid->prev_e) / dt;
    pid->prev_e = e;
    return ctrl;
}

/// @brief 初始化PID控制器
/// @param kp 比例系数
/// @param ki 积分系数
/// @param kd 微分系数
/// @return 初始化的PID控制器
PID new_pid_controller(Float kp, Float ki, Float kd)
{
    PID pid = {kp, ki, kd, 0, 0};
    return pid;
}