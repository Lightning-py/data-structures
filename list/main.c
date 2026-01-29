#include <stdio.h>
#include <stdlib.h>

// typedef struct node node;

typedef struct node
{
    int value;
    struct node *prev;
    struct node *next;
} node;

typedef struct list
{
    node *head;
    node *tail;
    unsigned long long size;
} list;

void create_list(list *l)
{
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}

int push_back(list *l, int element)
{
    if (!l)
        return 1;

    node *new_node = malloc(sizeof(node));
    if (!new_node)
        return 1;

    if (!l->size)
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->value = element;

        l->head = new_node;
        l->tail = new_node;
        l->size++;
    }
    else
    {
        new_node->value = element;
        new_node->next = NULL;
        new_node->prev = l->tail;

        l->tail->next = new_node;
        l->tail = new_node;
        l->size++;
    }
}

int push_front(list *l, int element)
{
    if (!l)
        return 1;

    node *new_node = malloc(sizeof(node));
    if (!new_node)
        return 1;

    new_node->value = element;
    new_node->prev = NULL;

    if (!l->size)
    {
        new_node->next = NULL;
        l->head = new_node;
        l->tail = new_node;
    }
    else
    {
        new_node->next = l->head;
        l->head->prev = new_node;
        l->head = new_node;
    }

    l->size++;
    return 0;
}

int pop_back(list *l)
{
    if (!l || !l->size)
        return 1;

    if (l->size == 1)
    {
        free(l->tail);
        l->head = NULL;
        l->tail = NULL;
    }
    else
    {
        node *new_tail = l->tail->prev;
        free(l->tail);
        l->tail = new_tail;
        l->tail->next = NULL;
    }

    l->size--;
    return 0;
}

int pop_front(list *l, int *result)
{
    if (!l || !l->size || !result)
        return 1;

    *result = l->head->value;

    if (l->size == 1)
    {
        // В списке только один элемент
        free(l->head);
        l->head = NULL;
        l->tail = NULL;
    }
    else
    {
        // В списке больше одного элемента
        node *new_head = l->head->next;
        free(l->head);
        l->head = new_head;
        l->head->prev = NULL;
    }

    l->size--;
    return 0;
}

void free_list(list *l)
{
    if (!l)
        return;

    int temp;
    while (l->size > 0)
        pop_front(l, &temp);
}

void print_list(list *l)
{
    if (!l)
        return;

    printf("Список [размер: %llu]: ", l->size);

    node *current = l->head;
    while (current)
    {
        printf("%d", current->value);
        if (current->next)
            printf(" <-> ");
        current = current->next;
    }
    printf("\n");
}

int main()
{
    list my_list;
    create_list(&my_list);

    for (int i = 0; i < 5; i++)
    {
        push_back(&my_list, i);
    }

    print_list(&my_list);

    free_list(&my_list);
    print_list(&my_list);

    return 0;
}