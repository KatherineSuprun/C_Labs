
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Прототипи функцій
double math_function(double x);
double derivative(double x);

double bisection_method(
    double a, double b, double epsilon,
    unsigned int max_iterations, int debug,
    int *iterations, int *finished
);

double chord_method(
    double a, double b, double epsilon,
    unsigned int max_iterations, int debug,
    int *iterations, int *finished
);

int main()
{
    double a, b, epsilon;
    double root, function_value;
    unsigned int max_iterations;
    unsigned int method;
    int debug;
    int iterations = 0;
    int finished = 0;
    clock_t start_time, end_time;
    double elapsed_time;

    printf("LAB 3 - PART 2: NONLINEAR EQUATIONS\n");
    printf("Variant: 7\n\n");

    printf("Function:\n");
    printf("f(x) = -0.5*(x-64)^3 - 3*x^2 + 10\n\n");

    // Введення проміжку ізоляції
    printf("Enter left boundary A: ");
    if (scanf("%lf", &a) != 1) {
        printf("Invalid input!\n");
        return 1;
    }

    printf("Enter right boundary B: ");
    if (scanf("%lf", &b) != 1) {
        printf("Invalid input!\n");
        return 1;
    }

    if (a >= b) {
        printf("Error: A must be less than B!\n");
        return 1;
    }

    // Перевірка наявності зміни знака
    if (math_function(a) * math_function(b) > 0) {
        printf("Error: Function must have opposite signs at A and B!\n");
        printf("f(A) = %.10lf\n", math_function(a));
        printf("f(B) = %.10lf\n", math_function(b));
        return 1;
    }

    printf("\nEnter calculation accuracy (epsilon): ");
    if (scanf("%lf", &epsilon) != 1 || epsilon <= 0) {
        printf("Invalid epsilon!\n");
        return 1;
    }

    printf("Enter maximum number of iterations: ");
    if (scanf("%u", &max_iterations) != 1 ||
        max_iterations == 0) {
        printf("Invalid number of iterations!\n");
        return 1;
    }

    // Вибір методу
    printf("\nChoose calculation method:\n");
    printf("1 - Bisection method\n");
    printf("2 - Chord method\n");
    printf("Your choice: ");

    if (scanf("%u", &method) != 1 ||
        (method != 1 && method != 2)) {
        printf("Invalid method!\n");
        return 1;
    }

    // Режим налагодження
    printf("\nDebug mode:\n");
    printf("1 - Show every iteration\n");
    printf("0 - Show only final result\n");
    printf("Your choice: ");

    if (scanf("%d", &debug) != 1 ||
        (debug != 0 && debug != 1)) {
        printf("Invalid choice!\n");
        return 1;
    }

    printf("\n========== INPUT DATA ==========\n");
    printf("Variant: 7\n");
    printf("Interval: [%.8lf; %.8lf]\n", a, b);
    printf("f(A) = %.10lf\n", math_function(a));
    printf("f(B) = %.10lf\n", math_function(b));
    printf("Epsilon = %.10lf\n", epsilon);
    printf("Maximum iterations per block: %u\n", max_iterations);

    // Вимірювання часу
    start_time = clock();

    if (method == 1) {
        root = bisection_method(
            a, b, epsilon, max_iterations,
            debug, &iterations, &finished
        );
    }
    else {
        root = chord_method(
            a, b, epsilon, max_iterations,
            debug, &iterations, &finished
        );
    }

    end_time = clock();

    elapsed_time = (double)(end_time - start_time) /
                   CLOCKS_PER_SEC;

    function_value = math_function(root);

    // Підсумкові результати
    printf("\n========== RESULT ==========\n");

    if (finished) {
        printf("Root found successfully!\n");
    }
    else {
        printf("Calculation stopped by user.\n");
    }

    printf("Root x = %.12lf\n", root);
    printf("f(x) = %.12lf\n", function_value);
    printf("Iterations: %d\n", iterations);
    printf("Calculation time: %.6lf seconds\n", elapsed_time);

    return 0;
}

// Початкова функція варіанта 7
double math_function(double x)
{
    return -0.5 * pow(x - 64, 3) -
           3 * pow(x, 2) + 10;
}

// Аналітична похідна
double derivative(double x)
{
    return -1.5 * pow(x - 64, 2) - 6 * x;
}

// Метод половинного ділення
double bisection_method(
    double a, double b, double epsilon,
    unsigned int max_iterations, int debug,
    int *iterations, int *finished)
{
    double c;
    double fa, fb, fc;
    unsigned int block_iterations = 0;
    int unlimited = 0;

    fa = math_function(a);
    fb = math_function(b);

    *finished = 0;

    printf("\n========== BISECTION METHOD ==========\n");

    while (1) {
        c = (a + b) / 2.0;
        fc = math_function(c);

        (*iterations)++;
        block_iterations++;

        if (debug) {
            printf("Iteration %d: a = %.10lf, b = %.10lf, ",
                   *iterations, a, b);
            printf("x = %.10lf, f(x) = %.10lf\n", c, fc);
        }

        if (fabs(fc) <= epsilon || fabs(b - a) <= epsilon) {
            *finished = 1;
            return c;
        }

        // Визначаємо, в якій половині знаходиться корінь
        if ((fa < 0 && fc > 0) || (fa > 0 && fc < 0)) {
            b = c;
            fb = fc;
        }
        else {
            a = c;
            fa = fc;
        }

        // Перевірка ліміту ітерацій
        if (!unlimited && block_iterations >= max_iterations) {
            unsigned int choice;

            printf("\nMaximum number of iterations reached.\n");
            printf("1 - Continue with another block of iterations\n");
            printf("2 - Continue until the root is found\n");
            printf("3 - Stop and show intermediate result\n");
            printf("Your choice: ");

            if (scanf("%u", &choice) != 1) {
                *finished = 0;
                return c;
            }

            if (choice == 1) {
                block_iterations = 0;
            }
            else if (choice == 2) {
                unlimited = 1;
            }
            else {
                *finished = 0;
                return c;
            }
        }
    }
}

// Метод хорд (метод січних із збереженням меж проміжку)
double chord_method(
    double a, double b, double epsilon,
    unsigned int max_iterations, int debug,
    int *iterations, int *finished)
{
    double c;
    double fa, fb, fc;
    unsigned int block_iterations = 0;
    int unlimited = 0;

    fa = math_function(a);
    fb = math_function(b);

    *finished = 0;

    printf("\n========== CHORD METHOD ==========\n");

    while (1) {
        // Точка перетину хорди з віссю X
        if (fabs(fb - fa) < 1e-15) {
            printf("Calculation error: denominator is too small.\n");
            return a;
        }

        c = (a * fb - b * fa) / (fb - fa);
        fc = math_function(c);

        (*iterations)++;
        block_iterations++;

        if (debug) {
            printf("Iteration %d: a = %.10lf, b = %.10lf, ",
                   *iterations, a, b);
            printf("x = %.10lf, f(x) = %.10lf\n", c, fc);
        }

        if (fabs(fc) <= epsilon || fabs(b - a) <= epsilon) {
            *finished = 1;
            return c;
        }

        // Залишаємо ту частину проміжку,
        // на кінцях якої функція має протилежні знаки
        if ((fa < 0 && fc > 0) || (fa > 0 && fc < 0)) {
            b = c;
            fb = fc;
        }
        else {
            a = c;
            fa = fc;
        }

        // Перевірка ліміту ітерацій
        if (!unlimited && block_iterations >= max_iterations) {
            unsigned int choice;

            printf("\nMaximum number of iterations reached.\n");
            printf("1 - Continue with another block of iterations\n");
            printf("2 - Continue until the root is found\n");
            printf("3 - Stop and show intermediate result\n");
            printf("Your choice: ");

            if (scanf("%u", &choice) != 1) {
                *finished = 0;
                return c;
            }

            if (choice == 1) {
                block_iterations = 0;
            }
            else if (choice == 2) {
                unlimited = 1;
            }
            else {
                *finished = 0;
                return c;
            }
        }
    }
}
