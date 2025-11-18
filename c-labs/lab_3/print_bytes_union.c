#include <stdio.h>

union Data {
    unsigned long value;
    unsigned char bytes[sizeof(unsigned long)];
};

int main(void) {
    union Data data;
    unsigned long input;

    printf("Введите число (unsigned long): ");
    scanf("%lu", &input);

    data.value = input;

    unsigned char *ptr = data.bytes;

    printf("Побайтовое представление числа %lu:\n", data.value);
    for (int i = 0; i < sizeof(unsigned long); i++) {
        printf("Байт %d: 0x%02X\n", i, *(ptr + i));
    }

    return 0;
}