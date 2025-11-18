#include <stdio.h>

union Data {
    int i;
    float f;
    char c;
};

int main(void) {
    union Data data;        
    union Data *ptr = &data; 

    ptr->i = 42;
    printf("Целое значение: %d\n", ptr->i);

    ptr->f = 3.14f;
    printf("Вещественное значение: %.2f\n", ptr->f);

    ptr->c = 'A';
    printf("Символьное значение: %c\n", ptr->c);

    printf("\nРазмер объединения: %lu байт\n", sizeof(union Data));

    return 0;
}
