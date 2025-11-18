#include <stdio.h>
#include <stdlib.h>

struct Node {
    void *data;
    struct Node *next;
    struct Node *prev;
};

struct Node* create_node(void *data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void append(struct Node **head, void *data) {
    struct Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->prev = temp;
}

void print_forward(struct Node *head) {
    printf("Прямой обход: ");
    while (head != NULL) {
        printf("%d ", *(int*)head->data);
        head = head->next;
    }
    printf("\n");
}

void print_backward(struct Node *tail) {
    printf("Обратный обход: ");
    while (tail != NULL) {
        printf("%d ", *(int*)tail->data);
        tail = tail->prev;
    }
    printf("\n");
}

int main(void) {
    struct Node* head = NULL;

    for (int i = 1; i <= 5; i++) {
        int *val = (int*)malloc(sizeof(int));
        *val = i;
        append(&head, val);
    }

    print_forward(head);

    struct Node* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    print_backward(tail);

    return 0;
}