#ifndef HASHTABLE
#define HASHTABLE

#include "common.h"
#include "list.h"
#include "vector.h"

#define HASHTABLE_START_SIZE 10000

typedef struct hashtable {
    vector data;
    ull size;
    ull hash_mult;
    ull hash_plus;
} hashtable;

int create_hashtable(hashtable* h) {
    int status;
    status = create_vector(&(h->data), HASHTABLE_START_SIZE);
    for (ull i = 0; i < HASHTABLE_START_SIZE; ++i) {
        list* lst = malloc(sizeof(list));

        if (!lst) {
            for (ull j = 0; j < i; ++j) free(h->data.data[i]);
            return ERR;
        }

        create_list(lst);
        h->data.data[i] = lst;
    }

    if (status != OK) return ERR;

    h->size = 0;

    h->hash_mult = rand();
    h->hash_plus = rand();

    return OK;
}

int hashtable_set_value(hashtable* h, int index, int value) {
    ull hashtable_index =
        (((ull)index) * h->hash_mult + h->hash_plus) % h->data.size;

    push_back(h->data.data[hashtable_index], index, value);
}

int hashtable_get_value(hashtable* h, int index, int* result) {
    ull hashtable_index =
        (((ull)index) * h->hash_mult + h->hash_plus) % h->data.size;

    node* now = ((list*)h->data.data[hashtable_index])->head;
    node* end = ((list*)h->data.data[hashtable_index])->tail;
    while (now != NULL && now->index != index) now = now->next;

    if (now != NULL) {
        *result = now->value;
        return OK;
    }
    return ERR;
}

int hashtable_resize(hashtable* h, ull new_size) {
    vector* new_data = malloc(sizeof(vector));
    create_vector(new_data, new_size);

    for (ull i = 0; i < h->data.size; ++i) {
        node* now = ((list*)h->data.data[i])->head;
        while (now != NULL) {
        }
    }
}

#endif  // HASHTABLE
