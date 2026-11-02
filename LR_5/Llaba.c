
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define BINARY_FILE "data.bin"

// Variant 7
double function(double x)
{
    return -0.5 * pow(x - 64.0, 3.0)
           - 3.0 * x * x + 10.0;
}

int main(void)
{
    FILE *input;
    FILE *output;
    FILE *binary;

    double x_start, x_end, step;
    double x, y;

    unsigned int N;
    unsigned int i;

    char group[50];
    char student[100];

    input = fopen(INPUT_FILE, "r");

    if (input == NULL)
    {
        printf("Error: cannot open input.txt\n");
        return 1;
    }

    if (fscanf(input, "%lf", &x_start) != 1 ||
        fscanf(input, "%lf", &x_end) != 1 ||
        fscanf(input, "%u", &N) != 1 ||
        fscanf(input, "%lf", &step) != 1 ||
        fscanf(input, "%49s", group) != 1)
    {
        printf("Error reading input data!\n");
        fclose(input);
        return 1;
    }

    if (fscanf(input, " %99[^\n]", student) != 1)
    {
        printf("Error reading student name!\n");
        fclose(input);
        return 1;
    }

    fclose(input);

    if (N < 2 || N > 10000 ||
        step <= 0 || x_end <= x_start)
    {
        printf("Incorrect input parameters!\n");
        return 1;
    }

    if (fabs((x_start + (N - 1) * step) - x_end) > 0.000001)
    {
        printf("Error: step and number of points do not match the interval!\n");
        return 1;
    }

    output = fopen(OUTPUT_FILE, "w");

    if (output == NULL)
    {
        printf("Error: cannot create output.txt\n");
        return 1;
    }

    binary = fopen(BINARY_FILE, "wb");

    if (binary == NULL)
    {
        printf("Error: cannot create data.bin\n");
        fclose(output);
        return 1;
    }

    if (fwrite(&N, sizeof(unsigned int), 1, binary) != 1)
    {
        printf("Error writing binary file!\n");
        fclose(output);
        fclose(binary);
        return 1;
    }

    printf("\nLABORATORY WORK 5 - VARIANT 7\n");
    printf("Function: f(x) = -0.5*(x-64)^3 - 3*x^2 + 10\n\n");

    printf("Start X: %.2f\n", x_start);
    printf("End X: %.2f\n", x_end);
    printf("Number of points: %u\n", N);
    printf("Step: %.2f\n\n", step);

    printf("%-10s %-15s %-20s\n", "Point", "X", "F(X)");
    printf("------------------------------------------------\n");

    fprintf(output, "LABORATORY WORK 5 - VARIANT 7\n");
    fprintf(output, "Function: f(x) = -0.5*(x-64)^3 - 3*x^2 + 10\n\n");

    fprintf(output, "Start X: %.2f\n", x_start);
    fprintf(output, "End X: %.2f\n", x_end);
    fprintf(output, "Number of points: %u\n", N);
    fprintf(output, "Step: %.2f\n\n", step);

    fprintf(output, "%-10s %-15s %-20s\n", "Point", "X", "F(X)");
    fprintf(output, "------------------------------------------------\n");

    for (i = 0; i < N; i++)
    {
        x = x_start + i * step;
        y = function(x);

        printf("%-10u %-15.6f %-20.6f\n", i + 1, x, y);

        // Запись в текстовый файл
        fprintf(output, "%-10u %-15.6f %-20.6f\n",
                i + 1, x, y);

        if (fwrite(&x, sizeof(double), 1, binary) != 1 ||
            fwrite(&y, sizeof(double), 1, binary) != 1)
        {
            printf("Error writing data to binary file!\n");
            fclose(output);
            fclose(binary);
            return 1;
        }
    }

    fprintf(output, "\nGroup: %s\n", group);
    fprintf(output, "Student: %s\n", student);

    fclose(output);
    fclose(binary);

    printf("\nGroup: %s\n", group);
    printf("Student: %s\n", student);

    printf("\nFiles successfully created:\n");
    printf("%s\n", OUTPUT_FILE);
    printf("%s\n", BINARY_FILE);

    return 0;
}
