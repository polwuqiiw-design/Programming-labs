#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    printf("Введите количество элементов массива: ");
    scanf("%d", &n);

    double *arr = (double *)malloc(n * sizeof(double));
    if (arr == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    printf("Введите %d элементов массива:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", (arr + i));
    }

    printf("Элементы массива:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", *(arr + i));
    }
    printf("\n");

    free(arr);

    return 0;
}
