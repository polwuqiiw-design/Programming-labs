#include <stdio.h>
#include <stdlib.h>

void tempFileDemo() {
    FILE *fp = tmpfile();
    if (fp == NULL) {
        perror("Ошибка создания временного файла");
        exit(EXIT_FAILURE);
    }

    // Запись данных во временный файл
    fprintf(fp, "Строка 1: Пример работы с tmpfile()\n");
    fprintf(fp, "Строка 2: Временный файл будет удален после закрытия\n");

    // Перемещаемся в начало файла
    fseek(fp, 0, SEEK_SET);

    // Считываем и выводим содержимое файла
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    fclose(fp); // Временный файл удаляется автоматически
}

int main(void) {
    tempFileDemo();
    return 0;
}