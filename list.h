typedef struct {
  int size;
  int cap;
  void **data;
} List;


List* list_new(int initial_size);
void list_free(List* list);
void list_append(List* list, void* value);
void* list_get(List *list, size_t index);
const int list_size(List *list);
void list_del(List *list, size_t index);
const int list_in(List *list, void* value);
