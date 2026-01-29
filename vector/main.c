#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned long long size;
    unsigned long long occupied;
    int *data;
} vector;

int create_vector(vector *v, unsigned long long size)
{
    if (!v || size == 0)
        return 1;

    int *a = calloc(size, sizeof(int));
    if (!a)
        return 1;

    v->data = a;
    v->size = size;
    v->occupied = 0;

    return 0;
}

void free_vector(vector *v)
{
    if (!v)
        return;

    free(v->data);
}

int resize_vector(vector *v, unsigned long long new_size)
{
    if (!v || new_size == 0 || !v->data)
        return 1;

    int *a = realloc(v->data, sizeof(int) * new_size);
    if (!a)
        return 1;

    v->data = a;
    v->size = new_size;

    if (v->occupied > new_size)
        v->occupied = new_size;

    return 0;
}

int push_back(vector *v, int element)
{
    if (!v || !v->data)
        return 1;

    if (v->occupied == v->size)
    { // resize
        int status = resize_vector(v, v->size * 2);
        if (!status)
            return 1;
    }

    v->data[v->occupied] = element;
    v->occupied++;

    return 0;
}

void print_vector(vector *v)
{
    if (!v || !v->data)
        return;

    for (unsigned long long i = 0; i < v->occupied; ++i)
        printf("%d ", v->data[i]);
    printf("\n");
}

int main()
{
    int status;
    int number;
    vector v;

    status = create_vector(&v, 10);
    if (status)
    {
        printf("Не удалось выделить место под вектор\n");
        return 1;
    }

    scanf("%d", &number);
    while (number != 0)
    {
        status = push_back(&v, number);

        if (status)
        {
            printf("Не получилось вставить элемент\n");
            free_vector(&v);
            return 1;
        }

        scanf("%d", &number);
    }

    print_vector(&v);

    free_vector(&v);

    return 0;
}