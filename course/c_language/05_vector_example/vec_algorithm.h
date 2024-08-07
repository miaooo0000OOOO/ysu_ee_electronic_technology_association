#ifndef __VEC_ALGORITHM_H__
#define __VEC_ALGORITHM_H__

#include "vector.h"

typedef int (*Order)(ItemType, ItemType);
typedef int (*OrderRef)(const void *, const void *);

#ifdef ITEM_TYPE_ORDER

typedef Vector OrdVector; // 有序(从小到大)动态数组

/// @brief 冒泡排序
/// @param vec 动态数组
/// @return 有序的原址动态数组
OrdVector *vec_bubble_sort(Vector *vec);

#endif

/// @brief 以指定顺序冒泡排序
/// @param vec 动态数组
/// @param cmp_it 自定义比较函数指针
/// @return 原址动态数组
Vector *vec_bubble_sort_by(Vector *vec, Order cmp_it);

/// @brief 反转动态数组
/// @param vec 动态数组
/// @return 反转的原址动态数组
Vector *vec_reverse(Vector *vec);

#ifdef ITEM_TYPE_ORDER

/// @brief 快速排序
/// @param vec 动态数组
/// @return 有序的原址动态数组
OrdVector *vec_qsort(Vector *vec);

#endif

/// @brief 以指定顺序快速排序
/// @param vec 动态数组
/// @param cmp_it 自定义比较函数指针
/// @return 原址动态数组
Vector *vec_qsort_by(Vector *vec, OrderRef cmp_it);

#endif