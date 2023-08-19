#include <stdio.h>

struct node
{
    int data;
    struct node *next;
};

int main()
{
    struct node *head;
    struct node *one = NULL;
    struct node *two = NULL;
    struct node *three = NULL;

    one = malloc(sizeof(struct node));
    two = malloc(sizeof(struct node));
    three = malloc(sizeof(struct node));

    one->data = 1;
    two->data = 2;
    three->data = 3;

    one->next = two;
    two->next = three;
    three->next = NULL;

    head = one;
    struct node *temp = head;

    while (temp != NULL)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }
}