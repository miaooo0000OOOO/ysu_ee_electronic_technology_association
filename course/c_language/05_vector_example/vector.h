#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DEFAULT_INIT_CAPACITY 1
#define ERROR (-1)

// 数组内的元素是可加的
#define ITEM_TYPE_ADDITIVE

// 数组内的元素是整数
#define ITEM_TYPE_IS_INT

// 数组的元素是可比较的
#define ITEM_TYPE_ORDER

// 如果数组元素是整数，那么它一定可加
#ifdef ITEM_TYPE_IS_INT
#ifndef ITEM_TYPE_ADDITIVE
#define ITEM_TYPE_ADDITIVE
#endif
#endif

#ifndef ITEM_TYPE_ORDER
// 数组的元素是不可比较的
#define ITEM_TYPE_UNORDER
#endif

typedef int ItemType;

typedef ItemType (*Mapper)(ItemType);
typedef bool (*Filter)(ItemType);

typedef struct Vector
{
    ItemType *data;
    size_t size;
    size_t capacity;
} Vector;

/// @brief 创建动态数组
/// @return 返回创建的动态数组，容量为`DEFAULT_INIT_CAPACITY`
Vector new_vec();

/// @brief 创建指定容量的动态数组
/// @param cap 容量
/// @return 返回容量为`cap`的动态数组
Vector new_vec_with_capacity(size_t cap);

/// @brief 创建指定长度的动态数组，并初始化
/// @param val 元素的初始值
/// @param size 动态数组长度
/// @return 返回长度为`size`，值均为`val`的动态数组
Vector new_vec_all_with_size(ItemType val, size_t cap);

/// @brief 销毁动态数组，释放内存
/// @param vec 要销毁的动态数组
void drop_vec(Vector *vec);

/// @brief 弹出动态数组的最后一个元素并作为函数的返回值
/// @param vec 动态数组
/// @return 动态数组被弹出的最后一个值，如果数组为空，返回`ERROR`
ItemType vec_pop(Vector *vec);

/// @brief 使动态数组的空闲内存可以存下`size`个元素
/// @param vec 动态数组
/// @param size 使空闲内存的大小 >= `size`
void vec_mem_prepare(Vector *vec, size_t size);

/// @brief 在动态数组的末尾添加元素
/// @param vec 动态数组
/// @param val 元素的值
void vec_push(Vector *vec, ItemType val);

/// @brief 将`src`的所有元素移动到`dest`的尾部，`src`留空
/// @param dest 目标动态数组
/// @param src 原动态数组
void vec_append(Vector *dest, Vector *src);

/// @brief 动态数组是否为空
/// @param vec 动态数组
/// @return 动态数组是否为空
bool vec_is_empty(const Vector *const vec);

/// @brief 在动态数组中插入元素
/// @param vec 动态数组
/// @param index 新元素插入到的索引
/// @param val 插入的值
void vec_insert(Vector *vec, size_t index, ItemType val);

/// @brief 移除动态数组索引位置的值，并作为返回值
/// @param vec 动态数组
/// @param index 要移除元素的索引
/// @return 被移除元素的值，如果索引超出数组范围，返回`ERROR`
ItemType vec_remove(Vector *vec, size_t index);

/// @brief 获取动态数组索引处的值
/// @param vec 动态数组
/// @param index 要获取元素的索引
/// @return 动态数组索引处的值，如果索引超出数组范围，就返回`ERROR`
ItemType vec_get(const Vector *const vec, size_t index);

#ifdef ITEM_TYPE_ADDITIVE

/// @brief 求动态数组中所有元素的和
/// @param vec 动态数组
/// @return 动态数组中所有元素的和
ItemType vec_sum(const Vector *const vec);

#endif

/// @brief 查找值对应的索引
/// @param vec 动态数组
/// @param val 值
/// @return 查找值对应的索引，找不到返回-1，如果查找到多个值，返回索引的最小值
int vec_find(const Vector *const vec, ItemType val);

/// @brief 将`src`动态数组拼接到`dest`动态数组尾部
/// @param dest 目标动态数组
/// @param src 原动态数组
void vec_cat(Vector *dest, const Vector *const src);

/// @brief 对动态数组内的元素用`f`作变换
/// @param vec 动态数组
/// @param f 变换函数
/// @return 变换后的指向动态数组的指针
Vector *vec_map(Vector *vec, Mapper f);

/// @brief 过滤出动态数组中满足条件`f`的元素
/// @param vec 动态数组
/// @param f 过滤函数
/// @return 过滤后的指向动态数组的指针
Vector *vec_filter(Vector *vec, Filter f);

#ifdef ITEM_TYPE_IS_INT

/// @brief 打印动态数组
/// @param vec 动态数组
void print_vec(const Vector *const vec);

#endif

#ifdef ITEM_TYPE_ORDER

/// @brief 判断两动态数组是否相等
/// @param v1 动态数组
/// @param v2 动态数组
/// @return 两动态数组是否相等
bool vec_eq(const Vector *const v1, const Vector *const v2);

/// @brief 比较两动态数组的大小
/// @param v1 动态数组
/// @param v2 动态数组
/// @return 字典序 v1 > v2 返回正数; v1 < v2 返回负数; v1 = v2 返回零
int vec_cmp(const Vector *const v1, const Vector *const v2);

/// @brief 删除相邻重复元素，对有序数组使用会删除所有重复项
/// @param vec 动态数组
/// @return 删除相邻重复元素后的动态数组
Vector *vec_dedup(Vector *vec);

#endif

/// @brief 删除指定索引的元素，不保证元素顺序
/// @param vec 动态数组
/// @param index 要删除元素的索引
/// @return 被删除的元素
ItemType vec_swap_remove(Vector *vec, size_t index);

/// @brief 在给定索引处将动态数组一分为二，`vec`保留索引为`[0, at)`的元素；返回新分配的动态数组，包含`vec`中索引为`[at, vec.size)`的元素
/// @param vec 动态数组
/// @param at 分割动态数组的索引
/// @return 新分配的动态数组，包含`vec`中索引为`[at, vec.size)`的元素
Vector vec_split_off(Vector *vec, size_t at);

/// @brief 截断动态数组，保留前面的`len`个元素
/// @param vec 动态数组
/// @param len 保留元素的个数
/// @return 当`len > vec.size`时，无法完成截断操作，返回`false`，否则截断数组并返回`true`
bool vec_truncate(Vector *vec, size_t len);

/// @brief 从向量里删除指定范围，并将已删除的元素作为动态数组返回
/// @param vec 动态数组
/// @param from 范围的起始(包含)
/// @param to 范围结束(不包含)
/// @return 从原动态数组[from, to)中删除的元素组成的动态数组，如果`from`和`to`超出数组索引会什么都不做并返回空数组
Vector vec_drain(Vector *vec, size_t from, size_t to);

#endif