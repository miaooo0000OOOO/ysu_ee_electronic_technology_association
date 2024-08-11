#include <stdio.h>

int main()
{
    float c, f; // 定义了两个变量，摄氏度c和华氏度f
    printf("请输入需要转换的摄氏度：");
    scanf("%f", &c);                 // 读取一个浮点数，存到变量c中
    f = (c + 32) * 9 / 5;            // 计算华氏度并赋值到变量f中
    printf("华氏度为：%.2f°F\n", f); // %.2f可以保留小数点后两位小数
    return 0;
}