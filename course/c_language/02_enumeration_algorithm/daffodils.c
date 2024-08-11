#include <stdio.h>
#include <math.h> // 使用数学库math.h中的幂运算函数pow

int main()
{
    int number, digit, sum;
    printf("三位数的水仙花数有：\n");

    for (number = 100; number <= 999; number++)
    {
        int temp = number;
        sum = 0;

        while (temp != 0)
        {
            digit = temp % 10;    // 获取最后一位数字
            sum += pow(digit, 3); // 计算数字的立方和
            // pow(x, 3) 等同于 x * x * x
            temp /= 10; // 去掉最后一位数字
        }

        if (sum == number)
        {
            printf("%d\n", number); // 输出水仙花数
        }
    }

    return 0;
}