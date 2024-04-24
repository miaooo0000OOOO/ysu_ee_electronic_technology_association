#include "vec.h"

/// @brief 向量相加
/// @param a 加向量
/// @param b 加向量
/// @return 向量相加之和
Vec vadd(Vec a, Vec b)
{
#ifdef DIMENSIONAL2
    Vec v;
    v.x = a.x + b.x;
    v.y = a.y + b.y;
    return v;
#else
    Vec v;
    v.x = a.x + b.x;
    v.y = a.y + b.y;
    v.z = a.z + b.z;
    return v;
#endif
}

/// @brief a += b 向量赋值相加
/// @param a 加向量
/// @param b 加向量
void vaddassign(Vec *const a, Vec b)
{
    Vec sum = vadd(*a, b);
    *a = sum;
}

/// @brief 向量相减
/// @param a 被减向量
/// @param b 减向量
/// @return 向量相减之差
Vec vsub(Vec a, Vec b)
{
#ifdef DIMENSIONAL2
    Vec v;
    v.x = a.x - b.x;
    v.y = a.y - b.y;
    return v;
#else
    Vec v;
    v.x = a.x - b.x;
    v.y = a.y - b.y;
    v.z = a.z - b.z;
    return v;
#endif
}

/// @brief 向量点乘
/// @param a 向量
/// @param b 向量
/// @return 向量点乘之积
Float vdot(Vec a, Vec b)
{
#ifdef DIMENSIONAL2
    return a.x * b.x + a.y * b.y;
#else
    return a.x * b.x + a.y * b.y + a.z * b.z;
#endif
}

/// @brief 浮点数与向量相乘
/// @param a 浮点数
/// @param b 向量
/// @return 浮点数与向量相乘之积
Vec fvmul(Float a, Vec b)
{
#ifdef DIMENSIONAL2
    Vec v;
    v.x = a * b.x;
    v.y = a * b.y;
    return v;
#else
    Vec v;
    v.x = a * b.x;
    v.y = a * b.y;
    v.z = a * b.z;
    return v;
#endif
}

/// @brief 向量与浮点数相乘
/// @param a 向量
/// @param b 浮点数
/// @return 向量与浮点数相乘之积
Vec vfmul(Vec a, Float b)
{
#ifdef DIMENSIONAL2
    Vec v;
    v.x = a.x * b;
    v.y = a.y * b;
    return v;
#else
    Vec v;
    v.x = a.x * b;
    v.y = a.y * b;
    v.z = a.z * b;
    return v;
#endif
}

/// @brief 浮点数与向量相除
/// @param a 浮点数
/// @param b 向量
/// @return 浮点数与向量相除之商
Vec fvdiv(Float a, Vec b)
{
#ifdef DIMENSIONAL2
    Vec v;
    v.x = a / b.x;
    v.y = a / b.y;
    return v;
#else
    Vec v;
    v.x = a / b.x;
    v.y = a / b.y;
    v.z = a / b.z;
    return v;
#endif
}

/// @brief 向量与浮点数相除
/// @param a 向量
/// @param b 浮点数
/// @return 向量与浮点数相除之商
Vec vfdiv(Vec a, Float b)
{
#ifdef DIMENSIONAL2
    Vec v;
    v.x = a.x / b;
    v.y = a.y / b;
    return v;
#else
    Vec v;
    v.x = a.x / b;
    v.y = a.y / b;
    v.z = a.z / b;
    return v;
#endif
}

#ifdef DIMENSIONAL3

/// @brief 向量叉乘
/// @param a 向量
/// @param b 向量
/// @return 向量叉乘之积
Vec cross(Vec a, Vec b)
{
    Vec v;
    v.x = a.y * b.z - a.z * b.y;
    v.y = a.z * b.x - a.x * b.z;
    v.z = a.x * b.y - a.y * b.x;
    return v;
}
#endif

/// @brief 零向量
/// @return 零向量
Vec zeros()
{
#ifdef DIMENSIONAL2
    Vec v = {0, 0};
    return v;
#else
    Vec v = {0, 0, 0};
    return v;
#endif
}

/// @brief 全一向量
/// @return 全一向量
Vec ones()
{
#ifdef DIMENSIONAL2
    Vec v = {1, 1};
    return v;
#else
    Vec v = {1, 1, 1};
    return v;
#endif
}

/// @brief L2距离 sqrt(dx^2 + dy^2)
/// @param a 向量
/// @param b 向量
/// @return 两向量的距离
Float l2(Vec a, Vec b)
{
#ifdef DIMENSIONAL2
    Float dx = a.x - b.x;
    Float dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
#else
    Float dx = a.x - b.x;
    Float dy = a.y - b.y;
    Float dz = a.z - b.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
#endif
}

/// @brief 向量模长
/// @param v 向量
/// @return 向量模长
Float len(Vec v)
{
#ifdef DIMENSIONAL2
    return sqrt(v.x * v.x + v.y * v.y);
#else
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
#endif
}

#ifdef DIMENSIONAL2
/// @brief 随机方向的单位向量
/// @return 返回一个随机方向的单位向量
Vec uvrand()
{
    Float theta = (Float)rand() / RAND_MAX * 2 * PI;
    Vec v = {cos(theta), sin(theta)};
    return v;
}
#endif

/// @brief 格式化显示向量
/// @param v 向量
/// @return 拥有所有权的格式化向量字符串
char *str_vec(Vec const *const v)
{
#ifdef DIMENSIONAL2
    char *str = malloc(50 * sizeof(char));
    sprintf(str, "(%.15lf, %.15lf)", v->x, v->y);
    return str;
#elif DIMENSIONAL3
    char *str = malloc(70 * sizeof(char));
    sprintf(str, "(%lf, %lf, %lf)", v->x, v->y, v->z);
    return str;
#endif
}