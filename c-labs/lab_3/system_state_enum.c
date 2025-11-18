#include <stdio.h>

enum SystemState {
    STATE_STOP,
    STATE_START,
    STATE_PAUSE
};

void print_state(enum SystemState state) {
    switch (state) {
        case STATE_STOP:
            printf("Состояние системы: STOP\n");
            break;
        case STATE_START:
            printf("Состояние системы: START\n");
            break;
        case STATE_PAUSE:
            printf("Состояние системы: PAUSE\n");
            break;
    }
}

int main(void) {
    enum SystemState state = STATE_STOP;
    int choice;

    while (1) {
        printf("\nВыберите действие:\n");
        printf("1 - START\n");
        printf("2 - PAUSE\n");
        printf("3 - STOP\n");
        printf("0 - Выйти\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                state = STATE_START;
                break;
            case 2:
                state = STATE_PAUSE;
                break;
            case 3:
                state = STATE_STOP;
                break;
            case 0:
                printf("Выход из программы.\n");
                return 0;
            default:
                printf("Некорректный выбор.\n");
                continue;
        }

        print_state(state);
    }

    return 0;
}