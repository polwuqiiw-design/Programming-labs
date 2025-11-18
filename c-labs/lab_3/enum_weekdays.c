#include <stdio.h>

enum Weekday {
    MONDAY = 1,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

void print_day(enum Weekday day) {
    switch (day) {
        case MONDAY:    printf("Понедельник = %d\n", day); break;
        case TUESDAY:   printf("Вторник = %d\n", day); break;
        case WEDNESDAY: printf("Среда = %d\n", day); break;
        case THURSDAY:  printf("Четверг = %d\n", day); break;
        case FRIDAY:    printf("Пятница = %d\n", day); break;
        case SATURDAY:  printf("Суббота = %d\n", day); break;
        case SUNDAY:    printf("Воскресенье = %d\n", day); break;
    }
}

int main(void) {
    printf("Дни недели:\n\n");
    for (enum Weekday day = MONDAY; day <= SUNDAY; day++) {
        print_day(day);
    }
    return 0;
}