
#include <stdio.h>
#include <math.h>

#define A 0.0
#define B 1.0
#define MAX_N 10000000

// Pidintegralna funktsiya variantu 7
double integrand(double x)
{
    return x * sqrt(1.0 + x);
}

double leftRectangles(double a, double b, unsigned int n)
{
    double h = (b - a) / n;
    double sum = 0.0;
    unsigned int i;

    for (i = 0; i < n; i++)
    {
        sum += integrand(a + i * h);
    }

    return sum * h;
}

double rightRectangles(double a, double b, unsigned int n)
{
    double h = (b - a) / n;
    double sum = 0.0;
    unsigned int i;

    for (i = 1; i <= n; i++)
    {
        sum += integrand(a + i * h);
    }

    return sum * h;
}

double trapezoids(double a, double b, unsigned int n)
{
    double h = (b - a) / n;
    double sum = (integrand(a) + integrand(b)) / 2.0;
    unsigned int i;

    for (i = 1; i < n; i++)
    {
        sum += integrand(a + i * h);
    }

    return sum * h;
}

// Metod parabol (Simpsona)
double simpson(double a, double b, unsigned int n)
{
    double h;
    double sum;
    unsigned int i;

    if (n % 2 != 0)
    {
        n++;
    }

    h = (b - a) / n;

    sum = integrand(a) + integrand(b);

    for (i = 1; i < n; i++)
    {
        if (i % 2 == 0)
        {
            sum += 2.0 * integrand(a + i * h);
        }
        else
        {
            sum += 4.0 * integrand(a + i * h);
        }
    }

    return sum * h / 3.0;
}

double calculateIntegral(
    unsigned int method,
    double a,
    double b,
    unsigned int n)
{
    switch (method)
    {
        case 1:
            return leftRectangles(a, b, n);

        case 2:
            return rightRectangles(a, b, n);

        case 3:
            return trapezoids(a, b, n);

        case 4:
            return simpson(a, b, n);

        default:
            return 0.0;
    }
}

double exactIntegral()
{
    return 4.0 * (sqrt(2.0) + 1.0) / 15.0;
}

void findRequiredN(
    unsigned int method,
    double a,
    double b,
    double epsilon)
{
    unsigned int n = 10;

    double I1, I2, delta;

    printf("\nACCURACY CALCULATION\n");
    printf("------------------------------\n");

    while (n <= MAX_N - 2)
    {
        I1 = calculateIntegral(method, a, b, n);
        I2 = calculateIntegral(method, a, b, n + 2);

        delta = fabs(I1 - I2);

        if (delta <= epsilon)
        {
            printf("N = %u\n", n);
            printf("N + 2 = %u\n", n + 2);
            printf("I1 = %.12lf\n", I1);
            printf("I2 = %.12lf\n", I2);
            printf("Delta = %.12lf\n", delta);
            printf("Required error = %.12lf\n", epsilon);
            return;
        }

        n += 2;
    }

    printf("Required accuracy was not reached.\n");
}

void printGraphData(
    unsigned int method,
    double a,
    double b)
{
    unsigned int i;
    unsigned int n;

    printf("\nGRAPH DATA\n");
    printf("------------------------------\n");
    printf("%-15s | %-20s\n", "N", "Integral");
    printf("------------------------------\n");

    for (i = 1; i <= 9; i++)
    {
        n = i * 10;

        printf("%-15u | %-20.12lf\n",
            n, calculateIntegral(method, a, b, n));
    }
}

int main()
{
    unsigned int method;
    unsigned int i;

    unsigned int values[] = { 10, 100, 1000, 10000 };
    unsigned int numberOfValues = 4;

    double epsilon;

    printf("========================================\n");
    printf("       LABORATORY WORK 2 - PART 2\n");
    printf("               VARIANT 7\n");
    printf("========================================\n\n");

    printf("Integral: integral from 0 to 1 of x * sqrt(1+x) dx\n");
    printf("A = %.2lf\n", A);
    printf("B = %.2lf\n\n", B);

    printf("Choose calculation method for accuracy:\n");
    printf("1 - Left rectangles\n");
    printf("2 - Right rectangles\n");
    printf("3 - Trapezoids\n");
    printf("4 - Simpson (parabolas)\n");

    printf("Your choice: ");

    if (scanf("%u", &method) != 1 ||
        method < 1 || method > 4)
    {
        printf("Invalid method!\n");
        return 1;
    }

    printf("\nEnter required error epsilon ");
    printf("(from 0.00001 to 0.001): ");

    if (scanf("%lf", &epsilon) != 1 ||
        epsilon < 0.00001 || epsilon > 0.001)
    {
        printf("Invalid epsilon!\n");
        return 1;
    }

    printf("\n========================================\n");
    printf("INTEGRAL CALCULATION TABLE\n");
    printf("========================================\n");

    printf("%-10s | %-15s | %-15s | %-15s | %-15s\n",
        "N", "Left", "Right", "Trapezoid", "Simpson");

    printf("-----------|-----------------|-----------------|"
        "-----------------|-----------------\n");

    for (i = 0; i < numberOfValues; i++)
    {
        unsigned int n = values[i];

        printf("%-10u | %-15.8lf | %-15.8lf | %-15.8lf | %-15.8lf\n",
            n,
            leftRectangles(A, B, n),
            rightRectangles(A, B, n),
            trapezoids(A, B, n),
            simpson(A, B, n));
    }

    printf("\nReference integral value = %.12lf\n",
        exactIntegral());

    findRequiredN(method, A, B, epsilon);

    printGraphData(method, A, B);

    printf("\n========================================\n");
    printf("Calculation completed.\n");

    return 0;
}
