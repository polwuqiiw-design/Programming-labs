#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void countFileStats(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    int lines = 0, words = 0, chars = 0;
    int inWord = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        chars++;
        if (ch == '\n')
            lines++;
        if (isspace(ch))
            inWord = 0;
        else if (!inWord) {
            inWord = 1;
            words++;
        }
    }

    fclose(fp);
    printf("Строк: %d\nСлов: %d\nСимволов: %d\n", lines, words, chars);
}

int main(void) {
    countFileStats("input.txt");
    return 0;
}