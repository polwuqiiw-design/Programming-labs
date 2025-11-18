#include <stdio.h>

struct Sample {
    int (*action)(int, int);  
};

int add(int a, int b) {
    return a + b;
}

int mul(int a, int b) {
    return a * b;
}

int main(void) {
    struct Sample s;

    s.action = add;
    printf("Результат сложения: %d\n", s.action(3, 4));

    s.action = mul;
    printf("Результат умножения: %d\n", s.action(3, 4));

    return 0;
}