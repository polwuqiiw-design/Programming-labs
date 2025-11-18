#include <stdio.h>
#include <stdlib.h>

int* find_max(int *arr, int n) {
    int *max_ptr = arr; 
    for (int i = 1; i < n; i++) {
        if (*(arr + i) > *max_ptr) {
            max_ptr = arr + i;
        }
    }
    return max_ptr;
}

int main(void) {
    int n;
    printf("Введите количество элементов массива: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Введите %d элементов массива:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", (arr + i));
    }

    int *max_ptr = find_max(arr, n);

    printf("Максимальный элемент массива: %d\n", *max_ptr);

    free(arr);
    return 0;
}