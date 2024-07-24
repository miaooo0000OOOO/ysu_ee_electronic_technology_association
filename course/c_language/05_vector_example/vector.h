#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DEFAULT_INIT_CAPACITY 1
#define ERROR (-1)

#define ITEM_TYPE_ADDITIVE // 数组内的元素是可加的
#define ITEM_TYPE_IS_INT   // 数组内的元素是整数

// 如果数组元素是整数，那么它一定可加
#ifdef ITEM_TYPE_IS_INT
#ifndef ITEM_TYPE_ADDITIVE
#define ITEM_TYPE_ADDITIVE
#endif
#endif

typedef int ItemType;

typedef ItemType (*MapperFunc)(ItemType);
typedef bool (*FilterFunc)(ItemType);

typedef struct Vector
{
    ItemType *data;
    size_t size;
    size_t capacity;
} Vector;

Vector new_vec();

Vector new_vec_with_capacity(size_t cap);

Vector new_vec_all_with_size(ItemType val, size_t cap);

void drop_vec(Vector *vec);

ItemType vec_pop(Vector *vec);

void vec_mem_prepare(Vector *vec, size_t size);

void vec_append(Vector *vec, ItemType val);

bool vec_empty(const Vector *const vec);

void vec_insert(Vector *vec, size_t index, ItemType val);

ItemType vec_remove(Vector *vec, size_t index);

ItemType vec_get(const Vector *const vec, size_t index);

#ifdef ITEM_TYPE_ADDITIVE

ItemType vec_sum(const Vector *const vec);

#endif

int vec_find(const Vector *const vec, ItemType val);

void vec_cat(Vector *dest, const Vector *const src);

Vector *vec_map(Vector *vec, MapperFunc f);

Vector *vec_filter(Vector *vec, FilterFunc f);

#ifdef ITEM_TYPE_IS_INT

void print_vec(const Vector *const vec);

#endif

#endif