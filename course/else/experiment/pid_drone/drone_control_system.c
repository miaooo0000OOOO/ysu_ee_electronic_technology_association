#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "drone.h"
#include "pid.h"
#include "float.h"

#define MAX_F 20
#define g 9.8          // 重力加速度
#define DRAG_COEFF 1 // 空气阻力系数 (随意写的数)

/// @brief 在时间步长`dt`内，应用控制器`pid`控制无人机`drone`输出升力，使无人机达到目标高度`target_height`
/// @param drone 无人机结构体
/// @param pid PID控制器结构体
/// @param dt 时间步长
/// @param target_height 目标高度
/// @return 控制量(无人机升力)
Float update_drone(Drone *const drone, PID *const pid, Float dt, Float target_height, Float t)
{
    Float e = target_height - drone->h;
    Float F = update_pid(pid, e, dt); // 升力
    if (F > MAX_F)
    {
        F = MAX_F;
    }
    else if (F < -MAX_F)
    {
        F = -MAX_F;
    }

    Float F_lift = F;                 // 升力
    Float G = -drone->m * g;          // 重力
    Float f = -DRAG_COEFF * drone->v; // 空气阻力(不严谨的计算方法)
    Float F_wind = 2 * sin(t);        // 风力，随意添加的扰动力

    Float a = (F_lift + G + f + F_wind) / drone->m;
    drone->v += a * dt;
    drone->h += drone->v * dt;
    return F;
}

Float get_target_height(Float t)
{
    // return 8 + 0.5 * t; // 线性函数
    return (t > 5) ? 8 : 15; // 阶梯函数
}

int main()
{
    PID pid = new_pid_controller(20, 1, 5);
    Drone drone = new_drone(1, 1, 1);
    Float dt = 0.001;
    Float target_height = 10;
    Float end_time = 10;
    Float t = 0;
    Float F;
    Float display_dt = 0.01;
    int ratio = (int)(display_dt / dt);
    unsigned int i = 0;
    printf("[\n"); // json start
    bool flag = false;
    while (t < end_time)
    {
        target_height = get_target_height(t); // 如果目标高度是随时间变化的函数
        F = update_drone(&drone, &pid, dt, target_height, t);
        if (i % ratio == 0)
        {
            if (flag)
            {
                printf(",\n"); // 中间的逗号
            }
            else
            {
                flag = true;
            }
            printf("{\"t\":%.15lf, \"F\":%.15lf, \"h\":%.15lf, \"tar\":%.15f}", t, F, drone.h, target_height);
        }
        i++;
        t += dt;
    }
    printf("\n]\n"); // json end

    /*
    json output:
    [
        {"t":%f, "F":%f, "h":%f},
        ...
        {"t":%f, "F":%f, "h":%f},
        {"t":%f, "F":%f, "h":%f}
    ]
    */
}