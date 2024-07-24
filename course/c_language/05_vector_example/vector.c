#include "vector.h"

/// @brief 创建动态数组
/// @return 返回创建的动态数组，容量为`DEFAULT_INIT_CAPACITY`
Vector new_vec()
{
    Vector vec = {(ItemType *)malloc(sizeof(ItemType) * DEFAULT_INIT_CAPACITY), 0, DEFAULT_INIT_CAPACITY};
    if (vec.data == NULL)
    {
        vec.capacity = 0;
    }
    return vec;
}

/// @brief 创建指定容量的动态数组
/// @param cap 容量
/// @return 返回容量为`cap`的动态数组
Vector new_vec_with_capacity(size_t cap)
{
    Vector vec = {(ItemType *)malloc(sizeof(ItemType) * cap), 0, cap};
    if (vec.data == NULL)
    {
        vec.capacity = 0;
    }
    return vec;
}

/// @brief 创建指定长度的动态数组，并初始化
/// @param val 元素的初始值
/// @param size 动态数组长度
/// @return 返回长度为`size`，值均为`val`的动态数组
Vector new_vec_all_with_size(ItemType val, size_t size)
{
    Vector vec = {(ItemType *)malloc(sizeof(ItemType) * size), size, size};
    if (vec.data == NULL)
    {
        vec.capacity = 0;
        vec.size = 0;
        return vec;
    }
    for (int i = 0; i < (int)size; i++)
    {
        vec.data[i] = val;
    }
    return vec;
}

/// @brief 销毁动态数组，释放内存
/// @param vec 要销毁的动态数组
void drop_vec(Vector *vec)
{
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

/// @brief 弹出动态数组的最后一个元素并作为函数的返回值
/// @param vec 动态数组
/// @return 动态数组被弹出的最后一个值，如果数组为空，返回`ERROR`
ItemType vec_pop(Vector *vec)
{
    if (vec_empty(vec))
    {
        return ERROR;
    }
    vec->size--;
    return vec->data[vec->size];
}

/// @brief 使动态数组的空闲内存可以存下`size`个元素
/// @param vec 动态数组
/// @param size 使空闲内存的大小 >= `size`
void vec_mem_prepare(Vector *vec, size_t size)
{
    for (size_t available_space = vec->capacity - vec->size;
         available_space < size;
         available_space = vec->capacity - vec->size)
    {
        ItemType *data = (ItemType *)realloc(vec->data, vec->capacity * 2 * sizeof(ItemType));
        vec->data = data;
        vec->capacity *= 2;
    }
}

/// @brief 在动态数组的末尾添加元素
/// @param vec 动态数组
/// @param val 元素的值
void vec_append(Vector *vec, ItemType val)
{
    vec_mem_prepare(vec, 1);
    vec->data[vec->size] = val;
    vec->size++;
}

/// @brief 动态数组是否为空
/// @param vec 动态数组
/// @return 动态数组是否为空
bool vec_empty(const Vector *const vec)
{
    return vec->size == 0;
}

/// @brief 在动态数组中插入元素
/// @param vec 动态数组
/// @param index 新元素插入到的索引
/// @param val 插入的值
void vec_insert(Vector *vec, size_t index, ItemType val)
{
    vec_mem_prepare(vec, 1);
    memmove(&vec->data[index + 1], &vec->data[index], sizeof(ItemType) * (vec->size - index));
    vec->data[index] = val;
    vec->size++;
}

/// @brief 移除动态数组索引位置的值，并作为返回值
/// @param vec 动态数组
/// @param index 要移除元素的索引
/// @return 被移除元素的值，如果索引超出数组范围，返回`ERROR`
ItemType vec_remove(Vector *vec, size_t index)
{
    if (index >= vec->size)
    {
        return ERROR;
    }
    int val = vec->data[index];
    memmove(&vec->data[index], &vec->data[index + 1], sizeof(ItemType) * (vec->size - index - 1));
    vec->size--;
    return val;
}

/// @brief 获取动态数组索引处的值
/// @param vec 动态数组
/// @param index 要获取元素的索引
/// @return 动态数组索引处的值，如果索引超出数组范围，就返回`ERROR`
ItemType vec_get(const Vector *const vec, size_t index)
{
    if (index >= vec->size)
    {
        return ERROR;
    }
    return vec->data[index];
}

#ifdef ITEM_TYPE_ADDITIVE

/// @brief 求动态数组中所有元素的和
/// @param vec 动态数组
/// @return 动态数组中所有元素的和
ItemType vec_sum(const Vector *const vec)
{
    ItemType sum = 0;

    for (int i = 0; i < (int)vec->size; i++)
    {
        sum += vec->data[i];
    }

    return sum;
}

#endif

/// @brief 查找值对应的索引
/// @param vec 动态数组
/// @param val 值
/// @return 查找值对应的索引，找不到返回-1，如果查找到多个值，返回索引的最小值
int vec_find(const Vector *const vec, ItemType val)
{
    for (int i = 0; i < (int)vec->size; i++)
    {
        if (vec->data[i] == val)
        {
            return i;
        }
    }
    return -1;
}

/// @brief 将`src`动态数组拼接到`dest`动态数组尾部
/// @param dest 目标动态数组
/// @param src 原动态数组
void vec_cat(Vector *dest, const Vector *const src)
{
    vec_mem_prepare(dest, src->size);
    memmove(
        &dest->data[dest->size],
        &src->data[0],
        src->size * sizeof(ItemType));
    dest->size += src->size;
}

/// @brief 对动态数组内的元素用`f`作变换
/// @param vec 动态数组
/// @param f 变换函数
/// @return 变换后的指向动态数组的指针
Vector *vec_map(Vector *vec, MapperFunc f)
{
    for (int i = 0; i < (int)vec->size; i++)
    {
        vec->data[i] = f(vec->data[i]);
    }

    return vec;
}

/// @brief 过滤出动态数组中满足条件`f`的元素
/// @param vec 动态数组
/// @param f 过滤函数
/// @return 过滤后的指向动态数组的指针
Vector *vec_filter(Vector *vec, FilterFunc f)
{
    int j = 0;
    size_t size = 0;
    for (int i = 0; i < (int)vec->size; i++)
    {
        if (f(vec->data[i]))
        {
            vec->data[j] = vec->data[i];
            j++;
            size++;
        }
    }
    vec->size = size;

    return vec;
}

#ifdef ITEM_TYPE_IS_INT

/// @brief 打印动态数组
/// @param vec 动态数组
void print_vec(const Vector *const vec)
{
    printf("[");
    for (int i = 0; i < (int)vec->size - 1; i++)
    {
        printf("%d, ", vec->data[i]);
    }
    printf("%d]\n", vec->data[vec->size - 1]);
}

#endif