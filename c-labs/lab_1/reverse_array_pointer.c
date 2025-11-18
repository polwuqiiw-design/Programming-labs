#include <stdio.h>
#include <stdlib.h>

void reverse(int *arr, int n) {
    int *left = arr;
    int *right = arr + n - 1;

    while (left < right) {
        int temp = *left;
        *left = *right;
        *right = temp;

        left++;
        right--;
    }
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

    reverse(arr, n);

    printf("Массив после реверса:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    free(arr);
    return 0;
}