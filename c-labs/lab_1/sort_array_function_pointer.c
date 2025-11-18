#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sort(int *arr, int n, int (*compare)(int, int)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(arr[j], arr[j + 1])) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int compare_asc(int a, int b) {
    return a > b;  
}

int compare_desc(int a, int b) {
    return a < b;  
}

int main(void) {
    int n;
    printf("Введите количество элементов массива: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Введите %d элементов массива:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Сортировка по возрастанию:\n");
    sort(arr, n, compare_asc);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Сортировка по убыванию:\n");
    sort(arr, n, compare_desc);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}