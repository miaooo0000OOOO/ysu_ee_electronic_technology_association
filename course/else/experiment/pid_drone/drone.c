#include "drone.h"

/// @brief 初始化无人机
/// @param h 初始高度(向上为正)
/// @param v 初始速度(向上为正)
/// @param m 初始质量
/// @return 初始化的无人机结构体
Drone new_drone(Float h, Float v, Float m)
{
    assert(h > 0);
    assert(m > 0);
    Drone d = {h, v, m};
    return d;
}