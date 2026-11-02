
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 100000
#define H 0.000001

// Прототипи функцій
double math_function(double x);
double numerical_derivative(double x);
double analytical_derivative(double x);

void print_function_table(double x1, double step, unsigned int n);
void print_derivative_table(double x1, double step, unsigned int n);
void find_isolation_intervals(double x1, double step, unsigned int n);

int main()
{
    double x1, x2, delta;
    unsigned int n, choice;
    double step;

    printf("LAB 3 - PART 1: FUNCTION RESEARCH\n");
    printf("Variant: 7\n\n");

    // Вибір способу введення даних
    printf("Choose input method:\n");
    printf("1 - Enter number of points N\n");
    printf("2 - Enter step delta\n");
    printf("Your choice: ");

    if (scanf("%u", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Invalid choice!\n");
        return 1;
    }

    // Введення меж проміжку
    printf("\nEnter X1: ");
    if (scanf("%lf", &x1) != 1) {
        printf("Invalid X1!\n");
        return 1;
    }

    printf("Enter X2: ");
    if (scanf("%lf", &x2) != 1) {
        printf("Invalid X2!\n");
        return 1;
    }

    if (x2 <= x1) {
        printf("Error: X2 must be greater than X1!\n");
        return 1;
    }

    // Перший спосіб: кількість точок
    if (choice == 1) {
        printf("Enter number of points N (2-%d): ", MAX_POINTS);

        if (scanf("%u", &n) != 1 || n < 2 || n > MAX_POINTS) {
            printf("Invalid number of points!\n");
            return 1;
        }

        step = (x2 - x1) / (n - 1);
    }

    // Другий спосіб: крок зміни аргументу
    else {
        printf("Enter step delta: ");

        if (scanf("%lf", &delta) != 1 || delta <= 0) {
            printf("Invalid delta!\n");
            return 1;
        }

        n = (unsigned int)floor((x2 - x1) / delta) + 1;

        if (n < 2 || n > MAX_POINTS) {
            printf("Invalid number of points!\n");
            return 1;
        }

        step = delta;
    }

    // Виведення початкових параметрів
    printf("\n========== INPUT DATA ==========\n");
    printf("Variant: 7\n");
    printf("X1 = %.6lf\n", x1);
    printf("X2 = %.6lf\n", x2);
    printf("Number of points: %u\n", n);
    printf("Step: %.8lf\n", step);

    printf("\nFunction:\n");
    printf("f(x) = -0.5*(x-64)^3 - 3*x^2 + 10\n");

    // Таблиця функції
    print_function_table(x1, step, n);

    // Таблиця похідної
    print_derivative_table(x1, step, n);

    // Пошук можливих проміжків ізоляції
    find_isolation_intervals(x1, step, n);

    printf("\nProgram finished.\n");

    return 0;
}

// Початкова математична функція
double math_function(double x)
{
    return -0.5 * pow(x - 64, 3) - 3 * pow(x, 2) + 10;
}

// Чисельне обчислення першої похідної
double numerical_derivative(double x)
{
    return (math_function(x + H) -
            math_function(x - H)) / (2 * H);
}

// Аналітична похідна для перевірки
double analytical_derivative(double x)
{
    return -1.5 * pow(x - 64, 2) - 6 * x;
}

// Виведення таблиці значень функції
void print_function_table(double x1, double step, unsigned int n)
{
    unsigned int i;
    double x;

    printf("\n========== FUNCTION TABLE ==========\n");
    printf("+--------+---------------+----------------------+\n");
    printf("| Point  |       X       |        f(X)          |\n");
    printf("+--------+---------------+----------------------+\n");

    for (i = 0; i < n; i++) {
        x = x1 + i * step;

        printf("| %-6u | %13.6lf | %20.6lf |\n",
               i + 1, x, math_function(x));
    }

    printf("+--------+---------------+----------------------+\n");
}

// Виведення таблиці значень похідної
void print_derivative_table(double x1, double step, unsigned int n)
{
    unsigned int i;
    double x;

    printf("\n========== DERIVATIVE TABLE ==========\n");
    printf("+--------+---------------+----------------------+\n");
    printf("| Point  |       X       |       f'(X)          |\n");
    printf("+--------+---------------+----------------------+\n");

    for (i = 0; i < n; i++) {
        x = x1 + i * step;

        printf("| %-6u | %13.6lf | %20.6lf |\n",
               i + 1, x, numerical_derivative(x));
    }

    printf("+--------+---------------+----------------------+\n");
}

// Пошук проміжків, де функція змінює знак
void find_isolation_intervals(double x1, double step, unsigned int n)
{
    unsigned int i;
    double x_prev, x_curr;
    double f_prev, f_curr;
    double d_prev, d_curr;

    int found = 0;

    printf("\n========== POSSIBLE ROOT INTERVALS ==========\n");

    for (i = 1; i < n; i++) {
        x_prev = x1 + (i - 1) * step;
        x_curr = x1 + i * step;

        f_prev = math_function(x_prev);
        f_curr = math_function(x_curr);

        d_prev = numerical_derivative(x_prev);
        d_curr = numerical_derivative(x_curr);

        if (f_prev == 0 || f_curr == 0 ||
            (f_prev < 0 && f_curr > 0) ||
            (f_prev > 0 && f_curr < 0)) {

            found = 1;

            printf("\nPossible interval: [%.6lf; %.6lf]\n",
                   x_prev, x_curr);

            if ((d_prev > 0 && d_curr > 0) ||
                (d_prev < 0 && d_curr < 0)) {
                printf("Derivative keeps the same sign at endpoints.\n");
                printf("The interval may contain one root.\n");
            }
            else {
                printf("Derivative changes sign or is zero at endpoints.\n");
                printf("Further investigation is required.\n");
            }
        }
    }

    if (!found) {
        printf("No sign changes were found in the selected interval.\n");
    }
}
