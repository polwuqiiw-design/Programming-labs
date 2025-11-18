#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int age;
    float grade;
};

void writeStudents(const char *filename, struct Student students[], int count) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Ошибка создания бинарного файла");
        exit(EXIT_FAILURE);
    }

    fwrite(students, sizeof(struct Student), count, fp);
    fclose(fp);
}

void readStudents(const char *filename, struct Student students[], int count) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Ошибка открытия бинарного файла");
        exit(EXIT_FAILURE);
    }

    fread(students, sizeof(struct Student), count, fp);
    fclose(fp);
}

int main(void) {
    struct Student studentsToWrite[2] = {
        {"Иванов", 20, 4.5f},
        {"Петров", 22, 3.8f}
    };

    writeStudents("students.bin", studentsToWrite, 2);

    struct Student studentsRead[2];
    readStudents("students.bin", studentsRead, 2);

    for (int i = 0; i < 2; i++) {
        printf("Студент: %s, Возраст: %d, Оценка: %.2f\n",
               studentsRead[i].name, studentsRead[i].age, studentsRead[i].grade);
    }

    return 0;
}