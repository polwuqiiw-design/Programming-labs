#include <stdio.h>

struct Weather {
    unsigned temperature : 7; 
    unsigned humidity : 7;    
};

int main(void) {
    struct Weather w;
    int input_temp, input_hum;

    printf("Введите температуру (-50...+50): ");
    scanf("%d", &input_temp);

    if (input_temp < -50 || input_temp > 50) {
        printf("Ошибка: температура вне диапазона.\n");
        return 1;
    }

    printf("Введите влажность (0...100): ");
    scanf("%d", &input_hum);

    if (input_hum < 0 || input_hum > 100) {
        printf("Ошибка: влажность вне диапазона.\n");
        return 1;
    }

    w.temperature = input_temp + 50;
    w.humidity = input_hum;

    printf("\nСохраненные данные:\n");
    printf("Температура: %d°C\n", (int)w.temperature - 50);
    printf("Влажность: %d%%\n", w.humidity);

    printf("\nРазмер структуры: %lu байт\n", sizeof(w));

    return 0;
}