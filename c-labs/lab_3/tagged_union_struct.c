#include <stdio.h>
#include <stdlib.h>

enum ValueType {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
};

union Value {
    int i;
    float f;
    char *s;
};

struct Item {
    enum ValueType type;
    union Value data;
};

void print_item(struct Item item) {
    switch (item.type) {
        case TYPE_INT:
            printf("INT: %d\n", item.data.i);
            break;
        case TYPE_FLOAT:
            printf("FLOAT: %.2f\n", item.data.f);
            break;
        case TYPE_STRING:
            printf("STRING: %s\n", item.data.s);
            break;
    }
}

int main(void) {
    int n = 3;
    struct Item *items = malloc(n * sizeof(struct Item));

    items[0].type = TYPE_INT;
    items[0].data.i = 42;

    items[1].type = TYPE_FLOAT;
    items[1].data.f = 3.14f;

    items[2].type = TYPE_STRING;
    items[2].data.s = "Привет, мир!";

    printf("Содержимое массива структур:\n\n");
    for (int i = 0; i < n; i++) {
        print_item(items[i]);
    }

    free(items);
    return 0;
}