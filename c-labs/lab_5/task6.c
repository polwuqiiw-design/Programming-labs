#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int age;
    float grade;
};

void updateStudentRecord(const char *filename, int index, struct Student newData) {
    FILE *fp = fopen(filename, "rb+");
    if (fp == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    // Перемещаемся к нужной записи
    fseek(fp, index * sizeof(struct Student), SEEK_SET);
    fwrite(&newData, sizeof(struct Student), 1, fp);
    fclose(fp);
}

void printStudentRecord(const char *filename, int index) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    struct Student s;
    fseek(fp, index * sizeof(struct Student), SEEK_SET);
    fread(&s, sizeof(struct Student), 1, fp);
    fclose(fp);

    printf("Обновлённая запись: %s, %d, %.2f\n", s.name, s.age, s.grade);
}

int main(void) {
    // Исходный массив записей
    struct Student students[2] = {
        {"Иванов", 20, 4.5f},
        {"Петров", 22, 3.8f}
    };

    // Записываем в файл
    FILE *fp = fopen("students.bin", "wb");
    if (fp == NULL) {
        perror("Ошибка создания файла");
        exit(EXIT_FAILURE);
    }
    fwrite(students, sizeof(struct Student), 2, fp);
    fclose(fp);

    // Обновляем вторую запись (индекс 1)
    struct Student newRecord = {"Петров", 23, 4.2f};
    updateStudentRecord("students.bin", 1, newRecord);

    // Выводим обновлённую запись
    printStudentRecord("students.bin", 1);

    return 0;
}