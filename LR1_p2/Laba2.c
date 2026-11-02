#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 100000
#define ROWS_PER_PAGE 20

// (Variant 7)     f(x)=-0.5(x-64)^3-3x^2+10
double function(double x)
{
    return -0.5 * pow(x - 64.0, 3) - 3.0 * pow(x, 2) + 10.0;
}

void pauseOutput(int firstPause)
{
    if (firstPause)
    {
        printf("\nPress ENTER to continue...");
        getchar();

        printf("\r                              \r");
    }
    else
    {
        getchar();
    }
}

int main()
{
    double x1, x2, delta;
    double x, y, previousY, previousX;
    double ratio;

    unsigned int n;
    unsigned int i;
    unsigned int mode;
    unsigned int pageCounter = 0;

    int firstPause = 1;
    int hasPrevious = 0;
    int foundIntervals = 0;

    printf("========================================\n");
    printf("       LABORATORY WORK 1 - PART 2\n");
    printf("               VARIANT 7\n");
    printf("========================================\n\n");

    do
    {
        printf("Choose input method:\n");
        printf("1 - Enter X1, X2 and number of points N\n");
        printf("2 - Enter X1, X2 and step delta\n");
        printf("Your choice: ");

        if (scanf("%u", &mode) != 1)
        {
            printf("Input error!\n");
            return 1;
        }

        if (mode != 1 && mode != 2)
        {
            printf("Invalid choice! Enter 1 or 2.\n\n");
        }

    } while (mode != 1 && mode != 2);

    printf("\nEnter initial value X1: ");
    if (scanf("%lf", &x1) != 1)
    {
        printf("Input error!\n");
        return 1;
    }

    printf("Enter final value X2: ");
    if (scanf("%lf", &x2) != 1)
    {
        printf("Input error!\n");
        return 1;
    }

    if (x2 <= x1)
    {
        printf("Error: X2 must be greater than X1.\n");
        return 1;
    }

    if (mode == 1)
    {
        printf("Enter number of points N (2-%d): ", MAX_POINTS);

        if (scanf("%u", &n) != 1 || n < 2 || n > MAX_POINTS)
        {
            printf("Error: invalid number of points.\n");
            return 1;
        }

        delta = (x2 - x1) / (n - 1);
    }
    else
    {
        printf("Enter step delta: ");

        if (scanf("%lf", &delta) != 1 || delta <= 0.0)
        {
            printf("Error: delta must be positive.\n");
            return 1;
        }

        if (delta > x2 - x1)
        {
            printf("Error: delta is greater than the interval.\n");
            return 1;
        }

        ratio = (x2 - x1) / delta;
        n = (unsigned int)floor(ratio + 1e-10) + 1;

        if (n > MAX_POINTS)
        {
            printf("Error: too many points. Maximum is %d.\n",
                MAX_POINTS);
            return 1;
        }
    }

    getchar();

    printf("\n========================================\n");
    printf("INITIAL DATA\n");
    printf("========================================\n");

    printf("Variant: %u\n", 7);
    printf("X1 = %.6lf\n", x1);
    printf("X2 = %.6lf\n", x2);
    printf("Delta = %.6lf\n", delta);
    printf("Number of points N = %u\n", n);

    printf("\nFunction:\n");
    printf("f(x) = -0.5 * (x - 64)^3 - 3 * x^2 + 10\n");

    printf("\n========================================\n");
    printf("FUNCTION TABLE\n");
    printf("========================================\n");

    printf("%-10s | %-15s | %-20s\n",
        "Point", "X", "f(X)");

    printf("-----------|-----------------|----------------------\n");

    for (i = 0; i < n; i++)
    {
        x = x1 + i * delta;

        y = function(x);

        printf("%-10u | %-15.6lf | %-20.6lf\n",
            i + 1, x, y);

        // Proverka smeny znaka
        if (hasPrevious)
        {
            if (previousY * y < 0.0)
            {
                printf("           | SIGN CHANGE: [%.6lf; %.6lf]\n",
                    previousX, x);

                foundIntervals++;
            }
            else if (y == 0.0)
            {
                printf("           | ROOT FOUND: x = %.6lf\n", x);
                foundIntervals++;
            }
            else if (previousY == 0.0)
            {
                // Predydushchaya tochka uzhe yavlyaetsya kornem
            }
        }

        previousX = x;
        previousY = y;
        hasPrevious = 1;

        pageCounter++;

        if (pageCounter == ROWS_PER_PAGE && i + 1 < n)
        {
            pauseOutput(firstPause);
            firstPause = 0;
            pageCounter = 0;
        }
    }

    printf("\n========================================\n");
    printf("SIGN CHANGE ANALYSIS\n");
    printf("========================================\n");

    if (foundIntervals == 0)
    {
        printf("No sign changes found in the selected interval.\n");
    }
    else
    {
        printf("Number of detected intervals/roots: %d\n",
            foundIntervals);
    }

    printf("\nTable calculation completed.\n");

    return 0;
}
