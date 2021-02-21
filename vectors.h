typedef struct {
    void** data;
    int used;
    int allocated;
} vector;

int vector_init(vector *vec, unsigned int initalSize);
int vector_push(vector *vec, void* data);
int vector_pop(vector *vec, void* val);