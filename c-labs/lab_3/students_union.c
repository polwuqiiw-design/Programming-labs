#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum AgeType {
    AGE_INT,
    AGE_STRING
};

union Age {
    int num;
    char str[50];
};

struct Student {
    char name[50];
    enum AgeType type;
    union Age age;
};

void print_student(struct Student s) {
    printf("Имя: %s\n", s.name);
    if (s.type == AGE_INT) {
        printf("Возраст: %d\n", s.age.num);
    } else {
        printf("Возраст: %s\n", s.age.str);
    }
    printf("----------------------\n");
}

int main(void) {
    int n;
    printf("Введите количество студентов: ");
    scanf("%d", &n);
    getchar(); 

    struct Student *students = malloc(n * sizeof(struct Student));

    for (int i = 0; i < n; i++) {
        printf("\nСтудент #%d\n", i + 1);

        printf("Введите имя: ");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0';

        int choice;
        printf("Как задать возраст? (1 - числом, 2 - словами): ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            students[i].type = AGE_INT;
            printf("Введите возраст (число): ");
            scanf("%d", &students[i].age.num);
            getchar();
        } else {
            students[i].type = AGE_STRING;
            printf("Введите возраст (словами): ");
            fgets(students[i].age.str, sizeof(students[i].age.str), stdin);
            students[i].age.str[strcspn(students[i].age.str, "\n")] = '\0';
        }
    }

    printf("\nСписок студентов:\n\n");
    for (int i = 0; i < n; i++) {
        print_student(students[i]);
    }

    free(students);
    return 0;
}