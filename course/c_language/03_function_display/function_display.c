/// @brief 只要稍加带动示例中显示函数的程序就可以让它变得更通用

// 其中使用的函数指针和结构体等会在之后的章节学习到

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// x轴方向的字符数
#define X_CHARS 20
// y轴方向的字符数
#define Y_CHARS 20
// x轴缩放倍率的倒数
// #define X_SCALE_INV (2 * M_PI)
#define X_SCALE_INV (3.4)
// y轴缩放倍率的倒数
// #define Y_SCALE_INV (4)
#define Y_SCALE_INV (3.4)
// 容许误差半径
#define EPSILON (12 / (double)Y_CHARS / Y_SCALE_INV)

typedef double (*Equation)(double x, double y);
typedef void (*Shader)(double val);

bool in_radius(double x, double y) // 两个浮点数`差不多`相等
{
    return fabs(x - y) <= EPSILON;
}

// 圆方程
double circle(double x, double y) // x^2 + y^2 = 1 变换为 F(x,y) = x^2 + y^2 - 1
{
    return sqrt(pow(x, 2) + pow(y, 2)) - 1;
}

// 正弦函数方程
double wave(double x, double y) // y = sin(x) 变换为 F(x,y) = sin(x) - y
{
    return sin(x) - y;
}

double elliptic(double x, double y)
{
    return y * y - (pow(x, 3) - x + 1);
}

double heart(double x, double y)
{
    return pow((x * x + y * y - 1), 3) - x * x * pow(y, 3);
}

void bin_shader(double val)
{
    if (in_radius(val, 0))
    {
        printf("*");
    }
    else
    {
        printf(" ");
    }
}

void gray_shader(double val)
{
    int index = (int)(fabs(val) * 7);
    if (index > 8)
    {
        printf(" ");
        return;
    }
    printf("%c", "@#%^    "[index]);
}

void inner_shader(double val)
{
    if (val < 0)
    {
        printf("*");
    }
    else
    {
        printf(" ");
    }
}

typedef struct Camera
{
    unsigned short width;
    unsigned short height;
    double x_scale_inv;
    double y_scale_inv;
    double x_shift;
    double y_shift;
} Camera;

void display_func_in_chars(const Camera *const cam, Equation f, Shader disp_shader)
{
    double x, y;
    for (int i = 0; i < cam->height + 1; i++)
    {
        for (int j = 0; j < cam->width * 2 + 1; j++)
        {
            x = (j - cam->width) / (double)(cam->height * 2) * cam->x_scale_inv + cam->x_shift;
            y = -(i - cam->height / 2) / (double)(cam->height) * cam->y_scale_inv - cam->y_shift;
            disp_shader(f(x, y));
        }
        printf("\n");
    }
}

void disp_heart()
{
    Camera c = {20, 20, 3.4, 3.4, 0, 0};
    display_func_in_chars(&c, heart, inner_shader);
}

void disp_donut()
{
    Camera c = {20, 20, 3, 3, 0, 0};
    display_func_in_chars(&c, circle, gray_shader);
}

void disp_elliptic()
{
    Camera c = {20, 20, 4.5, 4.5, 0, 0};
    display_func_in_chars(&c, elliptic, bin_shader);
}

int main()
{
    disp_heart();
    // disp_donut();
    // disp_elliptic();
    return 0;
}