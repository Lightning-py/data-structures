#ifndef LIST
#define LIST

#include "common.h"

typedef struct node
{
    void *data;
    struct node *next;
    struct node *prev;
} node;

typedef struct list
{
    node *head;
    node *tail;
    ull size;
} list;

void create_list(list *lst)
{
    if (!lst)
        return;

    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;
}

int push_back(list *lst, void *data)
{
    if (!lst)
        return ERR;

    node *new = malloc(sizeof(node));

    if (!new)
        return ERR;

    new->data = data;
    new->next = NULL;
    new->prev = lst->tail;

    if (lst->size == 0)
        lst->head = new;
    else
        lst->tail->next = new;
    lst->tail = new;

    lst->size++;

    return OK;
}

int pop_back(list *lst)
{
    if (!lst)
        return ERR;

    if (lst->size > 1)
    {
        lst->tail = lst->tail->prev;
        free(lst->tail->next);
        lst->tail->next = NULL;
        lst->size--;
    }
    else if (lst->size == 1)
    {
        free(lst->tail);
        lst->head = NULL;
        lst->tail = NULL;
        lst->size = 0;
    }

    return OK;
}

int push_front(list *lst, void *data)
{
    if (!lst)
        return ERR;

    node *new = malloc(sizeof(node));

    if (!new)
        return ERR;

    new->data = data;
    new->prev = NULL;
    new->next = lst->head;

    if (lst->size == 0)
        lst->tail = new;
    else
        lst->head->prev = new;
    lst->head = new;

    lst->size++;

    return OK;
}

int pop_front(list *lst)
{
    if (!lst || lst->size == 0)
        return ERR;

    if (lst->size > 1)
    {
        lst->head = lst->head->next;
        free(lst->head->prev);
        lst->head->prev = NULL;
        lst->size--;
    }
    else if (lst->size == 1)
    {
        free(lst->head);
        lst->head = NULL;
        lst->tail = NULL;
        lst->size = 0;
    }

    return OK;
}

#endif // LIST
