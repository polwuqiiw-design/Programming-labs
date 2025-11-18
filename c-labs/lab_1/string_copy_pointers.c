#include <stdio.h>

void str_copy(char *dest, const char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

int main(void) {
    char src[100], dest[100];

    printf("Введите строку: ");
    fgets(src, sizeof(src), stdin);

    for (char *p = src; *p; p++) {
        if (*p == '\n') { *p = '\0'; break; }
    }

    str_copy(dest, src);

    printf("Скопированная строка: %s\n", dest);

    return 0;
}