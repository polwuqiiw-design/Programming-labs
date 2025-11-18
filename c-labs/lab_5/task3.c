#include <stdio.h>
#include <stdlib.h>

void copyFile(const char *source, const char *destination) {
    FILE *src = fopen(source, "rb");
    if (src == NULL) {
        perror("Ошибка открытия исходного файла");
        exit(EXIT_FAILURE);
    }

    FILE *dest = fopen(destination, "wb");
    if (dest == NULL) {
        perror("Ошибка создания файла назначения");
        fclose(src);
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);

    printf("Файл успешно скопирован из %s в %s\n", source, destination);
}

int main(void) {
    copyFile("source.txt", "destination.txt");
    return 0;
}