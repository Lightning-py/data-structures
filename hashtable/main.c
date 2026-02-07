#include "list.h"
#include "vector.h"
#include "hashtable.h"

int main()
{
    hashtable h;
    int status;

    status = hashtable_create(&h);
    if (status != OK)
    {
        printf("Не получилось создать хеш таблицу\n");
        return ERR;
    }

    for (int i = 0; i < 10; ++i)
    {
        status = hashtable_set_value(&h, i, i * i);
        if (status != OK)
        {
            printf("Не получилось вставить элемент %d\n", i);

            hashtable_free(&h);

            return ERR;
        }
    }

    int result;
    for (int i = 0; i < 10; ++i)
    {
        status = hashtable_get_value(&h, i, &result);
        if (status != OK && status != NOTEXISTS)
        {
            printf("Не получилось вытащить элемент %d\n", i);
            hashtable_free(&h);
            return ERR;
        }
        else if (status == NOTEXISTS)
        {
            printf("Не нашлось элемента по индексу %d\n", i);
        }
        else
        {
            printf("%d : %d\n", i, result);
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        status = hashtable_set_value(&h, i, (10 - i) * (10 - i));
        if (status != OK)
        {
            printf("Не получилось вставить элемент %d\n", i);

            hashtable_free(&h);

            return ERR;
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        status = hashtable_get_value(&h, i, &result);
        if (status != OK && status != NOTEXISTS)
        {
            printf("Не получилось вытащить элемент %d\n", i);
            hashtable_free(&h);
            return ERR;
        }
        else if (status == NOTEXISTS)
        {
            printf("Не нашлось элемента по индексу %d\n", i);
        }
        else
        {
            printf("%d : %d\n", i, result);
        }
    }

    hashtable_free(&h);

    return 0;
}