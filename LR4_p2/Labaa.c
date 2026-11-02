
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NA 7

int** create_matrix(int rows, int cols)
{
    int i;
    int** matrix = (int**)malloc(rows * sizeof(int*));

    if (matrix == NULL)
        return NULL;

    for (i = 0; i < rows; i++)
    {
        matrix[i] = (int*)malloc(cols * sizeof(int));

        if (matrix[i] == NULL)
        {
            while (i > 0)
            {
                i--;
                free(matrix[i]);
            }

            free(matrix);
            return NULL;
        }
    }

    return matrix;
}

void free_matrix(int** matrix, int rows)
{
    int i;

    if (matrix == NULL)
        return;

    for (i = 0; i < rows; i++)
        free(matrix[i]);

    free(matrix);
}

void fill_matrix(int** matrix, int rows, int cols, int mode)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (mode == 1)
            {
                printf("Enter element [%d][%d]: ", i, j);
                scanf("%d", &matrix[i][j]);
            }
            else if (mode == 2)
            {
                matrix[i][j] = rand() % 100;
            }
            else
            {
                matrix[i][j] = i + j;
            }
        }
    }
}

void print_matrix(int** matrix, int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
            printf("%6d", matrix[i][j]);

        printf("\n");
    }
}

void max_min(int** A, int n, int* max_a, int* min_a)
{
    int i, j;
    int first = 1;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (first)
            {
                *max_a = A[i][j];
                *min_a = A[i][j];
                first = 0;
            }
            else
            {
                if (A[i][j] > *max_a)
                    *max_a = A[i][j];

                if (A[i][j] < *min_a)
                    *min_a = A[i][j];
            }
        }
    }
}

int** transpose_b(int** B, int rows, int cols)
{
    int i, j;
    int** T = create_matrix(cols, rows);

    if (T == NULL)
        return NULL;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            T[j][i] = B[i][j];
        }
    }

    return T;
}

// Множення матриць A и B
// A має розмір n x n
// B має розмір n x m
int** mult_a_b(int** A, int** B, int n, int m)
{
    int i, j, k;
    int** C = create_matrix(n, m);

    if (C == NULL)
        return NULL;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            C[i][j] = 0;

            for (k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

void sort_matrix(int** A, int n)
{
    int i, j, k;
    int temp;
    int total = n * n;

    for (i = 0; i < total - 1; i++)
    {
        for (j = 0; j < total - i - 1; j++)
        {
            int row1 = j / n;
            int col1 = j % n;
            int row2 = (j + 1) / n;
            int col2 = (j + 1) % n;

            if (A[row1][col1] > A[row2][col2])
            {
                temp = A[row1][col1];
                A[row1][col1] = A[row2][col2];
                A[row2][col2] = temp;
            }
        }
    }
}

void sort_row(int** A, int n, int row)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (A[row][j] > A[row][j + 1])
            {
                temp = A[row][j];
                A[row][j] = A[row][j + 1];
                A[row][j + 1] = temp;
            }
        }
    }
}

void sum_rows(int** A, int n)
{
    int i, j;
    int sum;

    for (i = 0; i < n; i++)
    {
        sum = 0;

        for (j = 0; j < n; j++)
            sum += A[i][j];

        printf("Row %d: %d\n", i + 1, sum);
    }
}

void sum_columns(int** B, int rows, int cols)
{
    int i, j;
    int sum;

    for (j = 0; j < cols; j++)
    {
        sum = 0;

        for (i = 0; i < rows; i++)
            sum += B[i][j];

        printf("Column %d: %d\n", j + 1, sum);
    }
}

int main(void)
{
    int** A;
    int** B;
    int** T;
    int** C;

    int nb = NA;
    int mb;
    int mode;
    int choice;
    int max_a, min_a;
    int row;
    int running = 1;

    srand((unsigned int)time(NULL));

    printf("LABORATORY WORK 4 - PART 2\n");
    printf("Variant 7\n\n");

    printf("Matrix A size: %d x %d\n", NA, NA);

    printf("Enter number of columns for matrix B (1-20): ");

    if (scanf("%d", &mb) != 1 || mb < 1 || mb > 20)
    {
        printf("Incorrect number of columns!\n");
        return 1;
    }

    printf("\nChoose matrix filling method:\n");
    printf("1 - Keyboard input\n");
    printf("2 - Random numbers\n");
    printf("3 - Formula (i + j)\n");
    printf("Your choice: ");

    if (scanf("%d", &mode) != 1 || mode < 1 || mode > 3)
    {
        printf("Incorrect choice!\n");
        return 1;
    }

    A = create_matrix(NA, NA);
    B = create_matrix(nb, mb);

    if (A == NULL || B == NULL)
    {
        printf("Memory allocation error!\n");
        free_matrix(A, NA);
        free_matrix(B, nb);
        return 1;
    }

    printf("\nFilling matrix A:\n");
    fill_matrix(A, NA, NA, mode);

    printf("\nFilling matrix B:\n");
    fill_matrix(B, nb, mb, mode);

    printf("\nMatrix A:\n");
    print_matrix(A, NA, NA);

    printf("\nMatrix B:\n");
    print_matrix(B, nb, mb);

    while (running)
    {
        printf("\n========== MENU ==========\n");
        printf("1. Find max and min above main diagonal in A\n");
        printf("2. Transpose matrix B\n");
        printf("3. Multiply matrices A x B\n");
        printf("4. Sort entire matrix A\n");
        printf("5. Sort one row of matrix A\n");
        printf("6. Calculate sums of rows of A\n");
        printf("7. Calculate sums of columns of B\n");
        printf("0. Exit\n");
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Input error!\n");
            break;
        }

        switch (choice)
        {
        case 1:
            max_min(A, NA, &max_a, &min_a);

            printf("\nMaximum above main diagonal: %d\n", max_a);
            printf("Minimum above main diagonal: %d\n", min_a);
            break;

        case 2:
            T = transpose_b(B, nb, mb);

            if (T == NULL)
            {
                printf("Memory allocation error!\n");
                break;
            }

            printf("\nTransposed matrix B (%d x %d):\n", mb, nb);
            print_matrix(T, mb, nb);

            free_matrix(T, mb);
            break;

        case 3:
            C = mult_a_b(A, B, NA, mb);

            if (C == NULL)
            {
                printf("Memory allocation error!\n");
                break;
            }

            printf("\nProduct matrix C = A x B (%d x %d):\n", NA, mb);
            print_matrix(C, NA, mb);

            free_matrix(C, NA);
            break;

        case 4:
            sort_matrix(A, NA);

            printf("\nMatrix A after sorting:\n");
            print_matrix(A, NA, NA);
            break;

        case 5:
            printf("Enter row number (1-%d): ", NA);

            if (scanf("%d", &row) != 1 || row < 1 || row > NA)
            {
                printf("Incorrect row number!\n");
                break;
            }

            sort_row(A, NA, row - 1);

            printf("\nMatrix A after sorting row %d:\n", row);
            print_matrix(A, NA, NA);
            break;

        case 6:
            printf("\nSums of rows of matrix A:\n");
            sum_rows(A, NA);
            break;

        case 7:
            printf("\nSums of columns of matrix B:\n");
            sum_columns(B, nb, mb);
            break;

        case 0:
            running = 0;
            break;

        default:
            printf("Unknown menu option!\n");
        }
    }

    free_matrix(A, NA);
    free_matrix(B, nb);

    printf("\nProgram finished. Memory released.\n");

    return 0;
}
