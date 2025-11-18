
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n, m;
  printf("Введите количество строк и столбцов: ");
  scanf("%d %d", &n, &m);

  int **arr1 = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
      arr1[i] = (int *)malloc(m * sizeof(int));
  }

  printf("Введите элементы массива (классический способ):\n");
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
          scanf("%d", &arr1[i][j]);
      }
  }

  printf("Вывод массива (классический способ):\n");
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
          printf("%d ", arr1[i][j]);
      }
      printf("\n");
  }

  int *arr2 = (int *)malloc(n * m * sizeof(int));

  printf("Введите элементы массива (непрерывный способ):\n");
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
          scanf("%d", (arr2 + i * m + j));
      }
  }

  printf("Вывод массива (непрерывный способ):\n");
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
          printf("%d ", *(arr2 + i * m + j));
      }
      printf("\n");
  }

  for (int i = 0; i < n; i++) {
      free(arr1[i]);
  }
  free(arr1);
  free(arr2);

  return 0;
}