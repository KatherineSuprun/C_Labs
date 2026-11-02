
#include <stdio.h>
#include <math.h>

// Функція розрахунку y відповідно до варіанту № 7
double calculateY(double x)
{
    double y;

    if (x >= -3 && x < 0)
    {
        y = fabs(x + 4) - fabs(pow(x, 3) - 4);
    }
    else if (x >= 9 && x < 15)
    {
        y = 2 * x;
    }
    else if (x >= 27 && x < 50)
    {
        y = x / (pow(cos(x), 2) + 1);
    }
    else
    {
        y = x / 4.0 + sin(x) / 3.0;
    }

    return y;
}

int main()
{
    double x;
    double y;

    printf("Laboratory work 2 - Part 1\n");
    printf("Variant 7\n\n");

    printf("Enter x: ");

    if (scanf("%lf", &x) != 1)
    {
        printf("Input error!\n");
        return 1;
    }

    y = calculateY(x);

    printf("\n-----------------------------\n");
    printf("Input x = %.4lf\n", x);
    printf("Result y = %.6lf\n", y);
    printf("-----------------------------\n");

    return 0;
}
