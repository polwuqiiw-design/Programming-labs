#include <stdio.h>
#include <string.h>

enum DataType {
    TYPE_INT,
    TYPE_STRING
};

union Data {
    int i;
    char str[100];
};

void print_data(enum DataType type, union Data data) {
    if (type == TYPE_INT) {
        printf("Вы ввели число: %d\n", data.i);
    } else if (type == TYPE_STRING) {
        printf("Вы ввели строку: %s\n", data.str);
    }
}

int main(void) {
    union Data data;
    enum DataType type;
    int choice;

    printf("Выберите тип данных:\n");
    printf("1 - Число (int)\n");
    printf("2 - Строка (char[])\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);
    getchar(); 

    if (choice == 1) {
        type = TYPE_INT;
        printf("Введите целое число: ");
        scanf("%d", &data.i);
    } else if (choice == 2) {
        type = TYPE_STRING;
        printf("Введите строку: ");
        fgets(data.str, sizeof(data.str), stdin);
        data.str[strcspn(data.str, "\n")] = '\0'; 
    } else {
        printf("Ошибка: неверный выбор.\n");
        return 1;
    }

    printf("\nРезультат:\n");
    print_data(type, data);

    return 0;
}