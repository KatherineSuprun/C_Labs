
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define Name "Katherine"
#define LastName "Suprun"
#define GroupName "PI-з61"
#define Faculty "RTF"
#define University "Igor Sikorsky KPI"

#define SUBJECTS_COUNT 5

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    unsigned int age;
    unsigned int semestr;
    float admissionScore;

    int grade1, grade2, grade3, grade4, grade5;
    double averageGrade;

    // Введення даних
    printf("%s %s, enter your data.\n\n", Name, LastName);

    printf("Enter your age: ");
    if (scanf("%u", &age) != 1) {
        printf("Input error!\n");
        return 1;
    }

    printf("Enter semester: ");
    if (scanf("%u", &semestr) != 1) {
        printf("Input error!\n");
        return 1;
    }

    printf("Enter admission score: ");
    if (scanf("%f", &admissionScore) != 1) {
        printf("Input error!\n");
        return 1;
    }

    printf("Enter grade #1: ");
    if (scanf("%d", &grade1) != 1) return 1;

    printf("Enter grade #2: ");
    if (scanf("%d", &grade2) != 1) return 1;

    printf("Enter grade #3: ");
    if (scanf("%d", &grade3) != 1) return 1;

    printf("Enter grade #4: ");
    if (scanf("%d", &grade4) != 1) return 1;

    printf("Enter grade #5: ");
    if (scanf("%d", &grade5) != 1) return 1;

    // Розрахунок середнього балу за п'ять предметів
    averageGrade = (double)(
        grade1 + grade2 + grade3 + grade4 + grade5
    ) / SUBJECTS_COUNT;

    // Очищення екрану
    system("cls");

    // Виведення інформації
    printf("***************\n");
    printf("===============\n\n");

    printf("%s\n", University);
    printf("Faculty: %s\n", Faculty);
    printf("Group: %s\n", GroupName);

    printf("-------------------------------\n");

    printf("Student: %s %s\n", Name, LastName);
    printf("Age: %u\n", age);
    printf("Semester: %u\n", semestr);

    printf("-------------------------------\n");

    printf("Admission score: %.1f\n", admissionScore);
    printf("Average grade: %.2f\n", averageGrade);

    printf("\nGrades: %d, %d, %d, %d, %d\n",
        grade1, grade2, grade3, grade4, grade5);

    printf("===============\n");
    printf("***************\n");

    return 0;
}
