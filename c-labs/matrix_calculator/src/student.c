#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/student.h"

StudentList* create_student_list(int initial_capacity) {
    if (initial_capacity <= 0) {
        fprintf(stderr, "Ошибка: начальная емкость должна быть > 0\n");
        return NULL;
    }

    StudentList* list = (StudentList*)malloc(sizeof(StudentList));
    if (!list) {
        fprintf(stderr, "Ошибка выделения памяти для списка\n");
        return NULL;
    }

    list->students = (Student*)malloc(sizeof(Student) * initial_capacity);
    if (!list->students) {
        fprintf(stderr, "Ошибка выделения памяти для студентов\n");
        free(list);
        return NULL;
    }

    list->count = 0;
    list->capacity = initial_capacity;
    return list;
}

void add_student(StudentList* list, const char* id, const char* name, int age, float gpa) {
    if (!list) {
        fprintf(stderr, "Ошибка: список не инициализирован\n");
        return;
    }

    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;
        Student* new_students = (Student*)realloc(list->students, sizeof(Student) * new_capacity);
        if (!new_students) {
            fprintf(stderr, "Ошибка перевыделения памяти\n");
            return;
        }
        list->students = new_students;
        list->capacity = new_capacity;
    }

    Student* s = &list->students[list->count];

    strncpy(s->id, id, MAX_ID_LEN - 1);
    s->id[MAX_ID_LEN - 1] = '\0';

    strncpy(s->name, name, MAX_NAME_LEN - 1);
    s->name[MAX_NAME_LEN - 1] = '\0';

    s->age = age;
    s->gpa = gpa;

    list->count++;
    printf("Добавлен студент: %s - %s\n", id, name);
}

void remove_student(StudentList* list, int index) {
    if (!list || index < 0 || index >= list->count) {
        fprintf(stderr, "Ошибка: неверный индекс для удаления\n");
        return;
    }

    printf("Удален студент: %s\n", list->students[index].id);

    for (int i = index; i < list->count - 1; i++) {
        list->students[i] = list->students[i + 1];
    }

    list->count--;
}

void print_students(const StudentList* list) {
    if (!list || list->count == 0) {
        printf("Список студентов пуст\n");
        return;
    }

    printf("\n=== Список студентов ===\n");
    printf("Всего: %d студент(ов)\n\n", list->count);

    for (int i = 0; i < list->count; i++) {
        printf("%d. ID: %s\n", i + 1, list->students[i].id);
        printf("   Имя: %s\n", list->students[i].name);
        printf("   Возраст: %d\n", list->students[i].age);
        printf("   Средний балл: %.2f\n\n", list->students[i].gpa);
    }
}

void sort_students_by_gpa(StudentList* list) {
    if (!list || list->count < 2) return;

    for (int i = 0; i < list->count - 1; i++) {
        for (int j = 0; j < list->count - i - 1; j++) {
            if (list->students[j].gpa < list->students[j + 1].gpa) {
                Student temp = list->students[j];
                list->students[j] = list->students[j + 1];
                list->students[j + 1] = temp;
            }
        }
    }

    printf("Список студентов отсортирован по среднему баллу\n");
}

void free_student_list(StudentList* list) {
    if (!list) return;

    free(list->students);
    free(list);
    printf("Память списка студентов освобождена\n");
}
