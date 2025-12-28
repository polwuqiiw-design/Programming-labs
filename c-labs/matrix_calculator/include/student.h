#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LEN 100
#define MAX_ID_LEN 20

typedef struct {
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

typedef struct {
    Student* students;
    int count;
    int capacity;
} StudentList;

StudentList* create_student_list(int initial_capacity);
void add_student(StudentList* list, const char* id, const char* name, int age, float gpa);
void remove_student(StudentList* list, int index);
void print_students(const StudentList* list);
void free_student_list(StudentList* list);
void sort_students_by_gpa(StudentList* list);

#endif
