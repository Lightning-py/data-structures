#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int *data;
    unsigned long long size;
} array;

int create_arr(array *a, unsigned long long size)
{
    if (size == 0 || !a)
        return -1;
    a->size = size;

    int *arr = calloc(size, sizeof(int));

    if (!arr)
        return -1;

    a->data = arr;

    return 0;
}

void free_arr(array *a)
{
    if (a->data)
        free(a->data);
}

int main()
{
    int status;
    unsigned long long size;
    array arr;

    scanf("%llu", &size);

    status = create_arr(&arr, size);

    if (status)
    {
        printf("Недостаточно места для массива\n");
        return 1;
    }

    for (int i = 0; i < size; ++i)
    {
        arr.data[i] = (i + 1) * (i + 1);
    }

    for (int i = 0; i < size; ++i)
    {
        printf("%d ", arr.data[i]);
    }

    printf("\n");

    free_arr(&arr);

    return 0;
}