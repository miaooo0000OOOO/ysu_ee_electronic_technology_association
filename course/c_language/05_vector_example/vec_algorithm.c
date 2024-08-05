#include "vec_algorithm.h"

void swap_it(ItemType *a, ItemType *b)
{
    ItemType temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

#ifdef ITEM_TYPE_ORDER

int default_cmp_it(const void *it1, const void *it2)
{
    return (int)(*(ItemType *)it1 - *(ItemType *)it2);
}

OrdVector *vec_bubble_sort(Vector *vec)
{
    int len = (int)vec->size;
    ItemType *arr = &vec->data[0];

    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap_it(&arr[j], &arr[j + 1]);
            }
        }
    }

    return vec;
}

#endif

Vector *vec_bubble_sort_by(Vector *vec, Order cmp_it)
{
    int len = (int)vec->size;
    ItemType *arr = &vec->data[0];

    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            if (cmp_it(arr[j], arr[j + 1]) > 0)
            {
                swap_it(&arr[j], &arr[j + 1]);
            }
        }
    }

    return vec;
}

Vector *vec_reverse(Vector *vec)
{
    for (int i = 0; i < (int)vec->size / 2; i++)
    {
        swap_it(&vec->data[i], &vec->data[vec->size - i - 1]);
    }

    return vec;
}

#ifdef ITEM_TYPE_ORDER

OrdVector *vec_qsort(Vector *vec)
{
    qsort(&vec->data[0], vec->size, sizeof(ItemType), default_cmp_it);

    return vec;
}

int binary_search(const OrdVector *const vec, ItemType target)
{
    int left = 0;
    int right = vec->size - 1;

    ItemType *arr = &vec->data[0];

    while (left <= right)
    {
        int middle = left + ((right - left) / 2); // 等同于 (left + right) / 2，防止溢出
        if (arr[middle] > target)
        {
            right = middle - 1;
        }
        else if (arr[middle] < target)
        {
            left = middle + 1;
        }
        else
        {
            return middle;
        }
    }
    return -1;
}

#endif

Vector *vec_qsort_by(Vector *vec, OrderRef cmp_it)
{
    qsort(&vec->data[0], vec->size, sizeof(ItemType), cmp_it);

    return vec;
}