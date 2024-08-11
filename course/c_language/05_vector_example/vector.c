#include "vector.h"

Vector new_vec()
{
    Vector vec = {(ItemType *)malloc(sizeof(ItemType) * DEFAULT_INIT_CAPACITY), 0, DEFAULT_INIT_CAPACITY};
    if (vec.data == NULL)
    {
        vec.capacity = 0;
    }
    return vec;
}

Vector new_vec_with_capacity(size_t cap)
{
    Vector vec = {(ItemType *)malloc(sizeof(ItemType) * cap), 0, cap};
    if (vec.data == NULL)
    {
        vec.capacity = 0;
    }
    return vec;
}

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

void drop_vec(Vector *vec)
{
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

ItemType vec_pop(Vector *vec)
{
    if (vec_is_empty(vec))
    {
        return ERROR;
    }
    vec->size--;
    return vec->data[vec->size];
}

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

void vec_push(Vector *vec, ItemType val)
{
    vec_mem_prepare(vec, 1);
    vec->data[vec->size] = val;
    vec->size++;
}

void vec_append(Vector *dest, Vector *src)
{
    vec_cat(dest, src);
    src->size = 0;
}

bool vec_is_empty(const Vector *const vec)
{
    return vec->size == 0;
}

void vec_insert(Vector *vec, size_t index, ItemType val)
{
    vec_mem_prepare(vec, 1);
    memmove(&vec->data[index + 1], &vec->data[index], sizeof(ItemType) * (vec->size - index));
    vec->data[index] = val;
    vec->size++;
}

ItemType vec_remove(Vector *vec, size_t index)
{
    if (index >= vec->size)
    {
        return ERROR;
    }
    int val = vec->data[index];
    memcpy(&vec->data[index], &vec->data[index + 1], sizeof(ItemType) * (vec->size - index - 1));
    vec->size--;
    return val;
}

ItemType vec_get(const Vector *const vec, size_t index)
{
    if (index >= vec->size)
    {
        return ERROR;
    }
    return vec->data[index];
}

#ifdef ITEM_TYPE_ADDITIVE

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

void vec_cat(Vector *dest, const Vector *const src)
{
    vec_mem_prepare(dest, src->size);
    memcpy(
        &dest->data[dest->size],
        &src->data[0],
        src->size * sizeof(ItemType));
    dest->size += src->size;
}

Vector *vec_map(Vector *vec, Mapper f)
{
    for (int i = 0; i < (int)vec->size; i++)
    {
        vec->data[i] = f(vec->data[i]);
    }

    return vec;
}

Vector *vec_filter(Vector *vec, Filter f)
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

#ifdef ITEM_TYPE_ORDER

bool vec_eq(const Vector *const v1, const Vector *const v2)
{
    if (v1->size != v2->size)
    {
        return false;
    }
    for (int i = 0; i < (int)v1->size; i++)
    {
        if (v1->data[i] != v2->data[i])
        {
            return false;
        }
    }
    return true;
}

int vec_cmp(const Vector *const v1, const Vector *const v2)
{
    size_t min_size;
    if (v1->size < v2->size)
    {
        min_size = v1->size;
    }
    else
    {
        min_size = v2->size;
    }

    for (int i = 0; i < (int)min_size; i++)
    {
        if (v1->data[i] != v2->data[i])
        {
            return v1->data[i] - v2->data[i];
        }
    }

    return v1->size - v2->size;
}

Vector *vec_dedup(Vector *vec)
{
    ItemType temp = vec->data[0];

    for (int i = 1; i < (int)vec->size; i++)
    {
        if (vec->data[i] == temp)
        {
            vec_remove(vec, i);
            i--;
        }
        else
        {
            temp = vec->data[i];
        }
    }

    return vec;
}
#endif

ItemType vec_swap_remove(Vector *vec, size_t index)
{
    if (index >= vec->size)
    {
        return ERROR;
    }
    ItemType ret = vec->data[index];
    vec->data[index] = vec->data[vec->size - 1];
    vec->size--;
    return ret;
}

Vector vec_split_off(Vector *vec, size_t at)
{
    if (at >= vec->size)
    {
        return new_vec();
    }
    Vector ret = new_vec_with_capacity(vec->size - at);
    memcpy(&ret.data[0], &vec->data[at], sizeof(ItemType) * (vec->size - at));
    ret.size = vec->size - at;
    vec->size = at;

    return ret;
}

bool vec_truncate(Vector *vec, size_t len)
{
    if (len > vec->size)
    {
        return false;
    }
    vec->size = len;
    return true;
}

Vector vec_drain(Vector *vec, size_t from, size_t to)
{
    if (from > to)
    {
        return new_vec();
    }
    if (to > vec->size)
    {
        return new_vec();
    }
    size_t ret_vec_len = to - from;
    Vector ret = new_vec_with_capacity(ret_vec_len);
    memcpy(&ret.data[0], &vec->data[from], sizeof(ItemType) * ret_vec_len);
    memcpy(&vec->data[from], &vec->data[to], sizeof(ItemType) * (vec->size - to));
    ret.size = ret_vec_len;
    vec->size -= ret_vec_len;
    return ret;
}

ItemType vec_reduce(Vector *vec, Reducer reducer)
{
    if (vec->size <= 1)
    {
        return ERROR;
    }
    ItemType a = vec->data[0];
    for (int i = 1; i < vec->size; i++)
    {
        ItemType b = vec->data[i];
        a = reducer(a, b);
    }

    return a;
}