#include <stdio.h>
#include <stdlib.h>

void writeUserInputToFile() {
    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("Ошибка создания файла");
        exit(EXIT_FAILURE);
    }

    char line[256];
    printf("Введите строки текста (для завершения введите пустую строку):\n");

    while (1) {
        fgets(line, sizeof(line), stdin);
        // Если введена пустая строка — выходим из цикла
        if (line[0] == '\n')
            break;
        fputs(line, fp);
    }

    fclose(fp);
    printf("Данные успешно записаны в output.txt\n");
}

int main(void) {
    writeUserInputToFile();
    return 0;
}