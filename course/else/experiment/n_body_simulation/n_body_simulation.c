#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "vec.h"

#define LINE "--------\n"

typedef long long i64;
typedef int i32;

typedef i64 Int;

/// @brief 星球 看作质点
typedef struct Star
{
    Vec p;   // 位置
    Vec v;   // 速度
    Float m; // 质量
} Star;

/// @brief N体运动模拟环境
typedef struct Env
{
    Float time;            // 经历的时间
    Int n;                 // 星球的数量
    Star *const stars;     // 星球
    Float const G;         // 引力常数
    Float const dis_limit; // 碰撞距离
    // 星球数量只能减少不能增加
} Env;

/// @brief 初始化环境
/// @param n 星球数量
/// @param stars 星球数组，长度为n
/// @param G 引力常数
/// @param dis_limit 碰撞距离
/// @return 初始化的环境结构体
Env new_env(Int n, Star *const stars, Float G, Float dis_limit)
{
    Env e = {0, n, stars, G, dis_limit};
    return e;
}

/// @brief 初始化星球
/// @param p 位置向量
/// @param v 速度向量
/// @param m 质量
/// @return 初始化的星球结构体
Star new_star(Vec p, Vec v, Float m)
{
    assert(m > 0);
    Star s = {p, v, m};
    return s;
}

/// @brief 仿真星球在合外力F作用下在一个时间步长dt内的运动
/// @param s 星球
/// @param F_sum 合外力
/// @param dt 时间步长
void star_step(Star *const s, Vec F_sum, Float dt)
{
    Vec a;
    // a = F_sum / m
    a = vfdiv(F_sum, s->m);
    // v += a * dt
    vaddassign(&s->v, vfmul(a, dt));
    // p += v * dt
    vaddassign(&s->p, vfmul(s->v, dt));
}

/// @brief 星球的碰撞与合并
/// @param e 环境
/// @param dis_limit 碰撞距离
/// @return 发生碰撞返回true，否则返回false
bool collision_merge_one(Env *e)
{
    Int i, j;
    Vec r;
    Star *const s = e->stars;
    Star *si, *sj;
    Float l;
    for (i = 0; i < e->n; i++)
    {
        si = &s[i];
        for (j = 0; j < e->n; j++)
        {
            if (i == j)
                continue;
            sj = &s[j];
            r = vsub(sj->p, si->p);
            l = len(r);
            if (l >= e->dis_limit)
                continue;
            Star s = new_star(
                vfdiv(vadd(si->p, sj->p), 2),                                         // (pi + pj) / 2
                vfdiv(vadd(vfmul(si->v, si->m), vfmul(sj->v, sj->m)), si->m + sj->m), // (vi * mi + vj * mj) / (mi + mj)
                si->m + sj->m                                                         // mi + mj
            );
            *si = s;
            // delete sj
            memcpy(sj, sj + 1, (e->n - j - 1) * sizeof(Star));
            e->n -= 1;
            return true;
        }
    }
    return false;
}

/// @brief 星球的碰撞与合并
/// @param e 环境
/// @param dis_limit 当两个星球距离小于dis_limit时合并
void collision_merge(Env *e)
{
    while (collision_merge_one(e))
        ;
}

/// @brief 仿真环境在一个时间步长dt内的运动
/// @param e 环境
/// @param dt 时间步长
void env_step(Env *const e, Float dt)
{
    Int i, j;
    Vec F_sum, F;
    Vec r;
    Star *const s = e->stars;
    Star *si, *sj;
    Float l;
    collision_merge(e);
    for (i = 0; i < e->n; i++)
    {
        F_sum = zeros();
        si = &s[i];
        for (j = 0; j < e->n; j++)
        {
            if (i == j)
                continue;
            sj = &s[j];
            // F_sum += gravitation = G * M * m / |r|^3 * r
            // r为从star_i指向star_j的向量
            r = vsub(sj->p, si->p);
            l = len(r);
            F = fvmul(e->G * si->m * sj->m / (l * l * l), r);
            vaddassign(&F_sum, F); // F_sum += F
        }

        star_step(si, F_sum, dt);
    }
    e->time += dt;
}

/// @brief 打印星球
/// @param s 星球
void star_log(Star const *const s)
{
    char *str_p, *str_v;
    str_p = str_vec(&s->p);
    str_v = str_vec(&s->v);
    printf("p:%s\n", str_p);
    printf("v:%s\n", str_v);
    free(str_p);
    free(str_v);
    printf("m:%lf\n", s->m);
}

/// @brief 打印环境
/// @param e 环境
void env_log(Env const *const e)
{
    printf(LINE);
    printf("time:%lf\n", e->time);
    printf("n:%lld\n", e->n);
    printf("G:%lf\n", e->G);
    printf("stars:\n");
    Int i;
    for (i = 0; i < e->n; i++)
    {
        star_log(&e->stars[i]);
    }
    printf("stars end\n");
    printf(LINE);
}

/// @brief [0, 1)平均分布的随机数
/// @return [0, 1)平均分布的随机数
Float r()
{
    return (Float)rand() / RAND_MAX;
}

/// @brief [-1, 1)平均分布的随机数
/// @return [-1, 1)平均分布的随机数
Float ur()
{
    return (Float)rand() / RAND_MAX * 2 - 1;
}

/// @brief 随机生成星球
/// @param n 星球数量
/// @return 有所有权的随机生成的星球数组
Star *random_generate_stars(Int n)
{
    Star *stars = malloc(n * sizeof(Star));
    int i;
    for (i = 0; i < n; i++)
    {
        stars[i].p = fvmul(7 + 7 * ur(), uvrand());
        stars[i].v = fvmul(1, uvrand()),
        stars[i].m = 1;
    }
    return stars;
}

int main()
{
    srand((unsigned)time(NULL));
    int n, i, ratio;
    Float end_time, dt, display_dt;
    // scanf("%d", &n);         // 星球的数量
    // scanf("%lf", &end_time); // 模拟的时间
    // scanf("%lf", &dt);       // 时间步长
    n = 20;
    end_time = 60;
    dt = 0.001;
    display_dt = 0.2;
    ratio = (int)(display_dt / dt);
    Env e = new_env(n, random_generate_stars(n), 1, 0.1);
    env_log(&e);
    i = 0;
    while (e.time < end_time)
    {
        env_step(&e, dt);
        if (i % ratio == 0)
            env_log(&e);
        i++;
    }
}