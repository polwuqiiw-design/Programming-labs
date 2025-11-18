#include <stdio.h>

struct Date {
    unsigned day   : 5;  
    unsigned month : 4;  
    unsigned year  : 12; 
};

void print_date(struct Date d) {
    printf("%02u.%02u.%04u\n", d.day, d.month, d.year);
}

int main(void) {
    struct Date birthday;

    birthday.day = 15;
    birthday.month = 7;
    birthday.year = 2002;

    printf("Дата рождения: ");
    print_date(birthday);

    return 0;
}