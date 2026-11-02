
#include <stdio.h>
#include <stdlib.h>

void fill_int_array(unsigned int *A, unsigned int Size)
{
    unsigned int j;

    for (j = 0; j < Size; j++)
    {
        A[j] = Size - (j + 1);
    }
}

void fill_float_array(float *B, unsigned int Size)
{
    unsigned int j;

    for (j = 0; j < Size; j++)
    {
        B[j] = 5.0 * j + 5.0;
    }
}

void print_int_array(const unsigned int *A, unsigned int Size)
{
    unsigned int j;

    for (j = 0; j < Size; j++)
    {
        printf("%u ", A[j]);
    }

    printf("\n");
}

void print_float_array(const float *B, unsigned int Size)
{
    unsigned int j;

    for (j = 0; j < Size; j++)
    {
        printf("%.2f ", B[j]);
    }

    printf("\n");
}

double mean_value(const unsigned int *A, unsigned int Size)
{
    unsigned int j;
    double sum = 0.0;

    for (j = 0; j < Size; j++)
    {
        sum += A[j];
    }

    return sum / Size;
}

unsigned int find_min(const unsigned int *A, unsigned int Size)
{
    unsigned int j;
    unsigned int min_value = A[0];

    for (j = 1; j < Size; j++)
    {
        if (A[j] < min_value)
        {
            min_value = A[j];
        }
    }

    return min_value;
}

float find_max(const float *B, unsigned int Size)
{
    unsigned int j;
    float max_value = B[0];

    for (j = 1; j < Size; j++)
    {
        if (B[j] > max_value)
        {
            max_value = B[j];
        }
    }

    return max_value;
}

int main(void)
{
    unsigned int Size;

    unsigned int *A;
    float *B;

    double average_value;
    unsigned int min_value;
    float max_value;

    printf("LABORATORY WORK 4 - PART 1\n");
    printf("Variant 7\n\n");

    printf("Enter array size: ");

    if (scanf("%u", &Size) != 1 || Size == 0 || Size > 100000)
    {
        printf("Incorrect array size!\n");
        return 1;
    }

    A = (unsigned int*)calloc(Size, sizeof(unsigned int));
    B = (float*)malloc(Size * sizeof(float));

    if (A == NULL || B == NULL)
    {
        printf("Memory allocation error!\n");

        free(A);
        free(B);

        return 1;
    }

    fill_int_array(A, Size);
    fill_float_array(B, Size);

    printf("\nArray A:\n");
    print_int_array(A, Size);

    printf("\nArray B:\n");
    print_float_array(B, Size);

    average_value = mean_value(A, Size);
    min_value = find_min(A, Size);
    max_value = find_max(B, Size);

    printf("\nRESULTS:\n");
    printf("Average value of array A: %.2f\n", average_value);
    printf("Minimum value of array A: %u\n", min_value);
    printf("Maximum value of array B: %.2f\n", max_value);

    free(A);
    free(B);

    return 0;
}
