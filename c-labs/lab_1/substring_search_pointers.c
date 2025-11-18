#include <stdio.h>

char* find_substr(const char *str, const char *substr) {
    if (!*substr) return (char*)str; 

    for (const char *p = str; *p != '\0'; p++) {
        const char *p1 = p;
        const char *p2 = substr;

        while (*p1 && *p2 && (*p1 == *p2)) {
            p1++;
            p2++;
        }

        if (*p2 == '\0') {
            return (char*)p; 
        }
    }
    return NULL;
}

int main(void) {
    char str[100], substr[100];
    printf("Введите строку: ");
    fgets(str, sizeof(str), stdin);

    printf("Введите подстроку: ");
    fgets(substr, sizeof(substr), stdin);

    for (char *p = str; *p; p++) {
        if (*p == '\n') { *p = '\0'; break; }
    }
    for (char *p = substr; *p; p++) {
        if (*p == '\n') { *p = '\0'; break; }
    }

    char *res = find_substr(str, substr);
    if (res) {
        printf("Подстрока найдена: \"%s\"\n", res);
    } else {
        printf("Подстрока не найдена.\n");
    }

    return 0;
}