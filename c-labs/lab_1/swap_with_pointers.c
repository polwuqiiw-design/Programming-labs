#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main(void) {
    int a, b;
    printf("Введите два числа: ");
    scanf("%d %d", &a, &b);

    printf("До обмена: a = %d, b = %d\n", a, b);

    swap(&a, &b);

    printf("После обмена: a = %d, b = %d\n", a, b);

    return 0;
}
