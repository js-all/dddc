#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    void** data;
    int used;
    int allocated;
} vector;
/*
initialSize: 0 -> auto (5) anything else -> that size
*/
int vector_init(vector *vec, unsigned int initalSize) {
    if(initalSize == 0) {
        vec->allocated = 5;
    } else {
        vec->allocated = initalSize;
    }
    vec->used = 0;
    vec->data = malloc(vec->allocated * sizeof(void*));
    if(!vec->data) {
        printf("ERROR: Vector, unable to allocate initial memory");
        return -1;
    }
    return 0;
}

int vector_push(vector *vec, void* data) {
    if(vec->used >= vec->allocated) { // need to reallocate
        void** tmp = realloc(vec->data, (vec->allocated *= 2) * sizeof(void*));
        if(!tmp) {
            free(vec->data);
            printf("ERROR: Vector, unable to reallocate memory");
            return -1;
        }
        vec->data = tmp;
    }
    vec->data[vec->used] = data;
    vec->used++;
    return 0;
}
// no reallocation for when it gets too small
int vector_pop(vector *vec, void* val) {
    val = vec->data[vec->used];
    vec->used--;
    return 0;
}
void vector_free(vector *vec) {
    free(vec);
}