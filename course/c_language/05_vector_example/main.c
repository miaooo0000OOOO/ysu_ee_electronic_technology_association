#include "vector.h"

void vec_test()
{
    Vector v = new_vec();
    vec_push(&v, 1);
    vec_push(&v, 2);
    vec_push(&v, 3);
    // [1,2,3]
    print_vec(&v);
    printf("sum: %d\n", vec_sum(&v));
    printf("\n");

    printf("pop: %d\n", vec_pop(&v));          // [1,2]
    printf("remove: %d\n", vec_remove(&v, 0)); // [2]
    vec_push(&v, 4);                           // [2,4]
    vec_insert(&v, 1, 10);                     // [2,10,4]
    vec_push(&v, 10);                          // [2,10,4,10]
    printf("\n");

    print_vec(&v);
    printf("find 10: %d\n", vec_find(&v, 10));
    printf("sum: %d\n", vec_sum(&v));

    vec_mem_prepare(&v, 19);

    drop_vec(&v);
}

ItemType sqr(ItemType x)
{
    return x * x;
}

ItemType mod_10(ItemType x)
{
    return x % 10;
}

void vec_map_test()
{
    Vector v = new_vec();
    vec_push(&v, 5);
    vec_push(&v, 6);
    vec_push(&v, 7);

    vec_map(vec_map(&v, sqr), mod_10);

    printf("\n");
    printf("map test:\n");
    print_vec(&v);
    printf("\n");

    drop_vec(&v);
}

// 奇数
bool is_odd(ItemType x)
{
    return x % 2 == 1;
}

// 不是3的倍数
bool not_mul_3(ItemType x)
{
    return x % 3 != 0;
}

void vec_filter_test()
{
    Vector v = new_vec();
    for (int i = 1; i <= 10; i++)
    {
        vec_push(&v, i);
    }

    vec_filter(vec_filter(&v, is_odd), not_mul_3); // 1到10中是奇数且不是3的倍数的数

    printf("\n");
    printf("filter test:\n");
    print_vec(&v);
    printf("\n");

    drop_vec(&v);
}

void vec_cat_test()
{
    Vector v1 = new_vec();
    for (int i = 1; i <= 4; i++)
    {
        vec_push(&v1, i);
    }

    Vector v2 = new_vec();
    for (int i = 6; i <= 12; i++)
    {
        vec_push(&v2, i);
    }

    vec_cat(&v1, &v2);

    printf("\n");
    printf("vec_cat:\n");
    print_vec(&v1);
    printf("\n");

    drop_vec(&v1);
    drop_vec(&v2);
}

void vec_dedup_test()
{
    // let mut vec = vec![1, 2, 2, 3, 2];
    // vec.dedup();
    // assert_eq!(vec, [1, 2, 3, 2]);

    Vector v = new_vec();
    vec_push(&v, 1);
    vec_push(&v, 2);
    vec_push(&v, 2);
    vec_push(&v, 3);
    vec_push(&v, 2);

    vec_dedup(&v);

    printf("\n");
    printf("vec_dedup:\n");
    print_vec(&v);
    printf("\n");

    drop_vec(&v);
}

void vec_split_off_test()
{
    // let mut vec = vec![1, 2, 3];
    // let vec2 = vec.split_off(1);
    // assert_eq!(vec, [1]);
    // assert_eq!(vec2, [2, 3]);

    Vector v = new_vec();
    vec_push(&v, 1);
    vec_push(&v, 2);
    vec_push(&v, 3);

    Vector v2 = vec_split_off(&v, 1);

    printf("\n");
    printf("vec_split_off:\n");
    print_vec(&v);
    print_vec(&v2);
    printf("\n");

    drop_vec(&v);
    drop_vec(&v2);
}

void vec_drain_test()
{
    Vector v = new_vec();
    vec_push(&v, 0);
    vec_push(&v, 1);
    vec_push(&v, 2);
    vec_push(&v, 3);
    vec_push(&v, 4);

    Vector v2 = vec_drain(&v, 1, 3);

    printf("\n");
    printf("vec_drain:\n");
    print_vec(&v);
    print_vec(&v2);
    printf("\n");

    drop_vec(&v);
    drop_vec(&v2);
}

int main()
{
    vec_test();
    vec_map_test();
    vec_filter_test();
    vec_cat_test();
    vec_dedup_test();
    vec_split_off_test();
    vec_drain_test();

    return 0;
}