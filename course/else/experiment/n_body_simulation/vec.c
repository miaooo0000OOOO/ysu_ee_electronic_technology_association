#include "vec.h"

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

void vaddassign(Vec *const a, Vec b)
{
    Vec sum = vadd(*a, b);
    *a = sum;
}

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

Float vdot(Vec a, Vec b)
{
#ifdef DIMENSIONAL2
    return a.x * b.x + a.y * b.y;
#else
    return a.x * b.x + a.y * b.y + a.z * b.z;
#endif
}

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

Vec cross(Vec a, Vec b)
{
    Vec v;
    v.x = a.y * b.z - a.z * b.y;
    v.y = a.z * b.x - a.x * b.z;
    v.z = a.x * b.y - a.y * b.x;
    return v;
}
#endif

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

// L2距离 sqrt(dx^2 + dy^2)
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

// 向量模长
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