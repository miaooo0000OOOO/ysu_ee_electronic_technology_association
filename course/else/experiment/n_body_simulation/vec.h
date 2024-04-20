#ifndef __VEC_H__
#define __VEC_H__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI acos(-1)

// 三维计算 DIMENSIONAL3
// 二维计算 DIMENSIONAL2
#define DIMENSIONAL2
#ifndef DIMENSIONAL2
#define DIMENSIONAL3
#endif

// 浮点精度64位 F64
// 浮点精度32位 F32
#define F64
#ifndef F64
#define F32
#endif

#ifdef F64
typedef double f64;
typedef f64 Float;
#else
typedef float f32;
typedef f32 Float;
#endif

#ifdef DIMENSIONAL2
typedef struct Vec2
{
    Float x;
    Float y;
} Vec2;
typedef Vec2 Vec;
#else
typedef struct Vec3
{
    Float x;
    Float y;
    Float z;
} Vec3;

typedef Vec3 Vec;
#endif

Vec vadd(Vec a, Vec b);

void vaddassign(Vec *const a, Vec b);

Vec vsub(Vec a, Vec b);

Float vdot(Vec a, Vec b);

Vec fvmul(Float a, Vec b);

Vec vfmul(Vec a, Float b);

Vec fvdiv(Float a, Vec b);

Vec vfdiv(Vec a, Float b);

#ifdef DIMENSIONAL3
Vec cross(Vec a, Vec b);
#endif

Vec zeros();

Vec ones();

// L2距离 sqrt(dx^2 + dy^2)
Float l2(Vec a, Vec b);

// 向量模长
Float len(Vec v);

#ifdef DIMENSIONAL2
/// @brief 随机方向的单位向量
/// @return 返回一个随机方向的单位向量
Vec uvrand();
#endif

char *str_vec(Vec const *const v);

#endif