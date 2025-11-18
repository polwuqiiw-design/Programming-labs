#include <stdio.h>

int count_spaces(const char *str) {
    int count = 0;
    const char *p = str;

    while (*p) {
        if (*p == ' ') {
            count++;
        }
        p++;
    }

    return count;
}

int main(void) {
    char str[200];

    printf("Введите строку: ");
    fgets(str, sizeof(str), stdin);

    for (char *p = str; *p; p++) {
        if (*p == '\n') { *p = '\0'; break; }
    }

    int result = count_spaces(str);
    printf("Количество пробелов: %d\n", result);

    return 0;
}