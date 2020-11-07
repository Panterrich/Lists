#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

//=======================================================================================================================

#define ASSERT_OK(list) if (List_ERROR(list))                                                                           \
                            {                                                                                           \
                                FILE* log = fopen("log.txt", "a");                                                      \
                                assert(log != nullptr);                                                                 \
                                                                                                                        \
                                fprintf(log, "ERROR: file %s line %d function %s\n", __FILE__, __LINE__, __FUNCTION__); \
                                List_dump(list, log);                                                                   \
                                fflush(log);                                                                            \
                                                                                                                        \
                                if (list->data != nullptr)                                                              \
                                {                                                                                       \
                                    List_graph(list);                                                                   \
                                            }                                                                                       \
                                                                                                                                    \
                                            abort();                                                                                \
                                            }

            #define LIST_CONSTUCT(list, capacity) (list)->name = #list;               \
                                                List_construct(list, capacity)

            #define case_of_switch(enum_const) case enum_const: return #enum_const;

            //======================================================================================================================

typedef double element_t;
const double Poison = NAN;

//======================================================================================================================

enum ERRORS
{
    NEGATIVE_CAPACITY = 1,
    NEGATIVE_SIZE,
    NEGATIVE_HEAD, 
    NEGATIVE_TAIL,

    SIZE_MORE_CAPACITY,
    HEAD_MORE_CAPACITY,
    TAIL_MORE_CAPACITY,

    NULLPTR_DATA,

    DAMADED_SERVICE_CELL,

    WRONG_HEAD,
    WRONG_TAIL,
    
    WRONG_VALUE,

    WRONG_SIZE_NEXT,
    WRONG_SIZE_PREV,

    WRONG_LINK_NEXT,
    WRONG_LINK_PREV,
    WRONG_DOUBLE_LINK,
    WRONG_FREE_LINK,
    
    WRONG_NUMBER_POISON_NEXT,
    WRONG_NUMBER_POISON_PREV,

    OUT_OF_MEMORY,
};

//======================================================================================================================

struct List_t
{
    element_t value;

    size_t next;
    size_t prev;
};

struct List
{
    const char* name;

    size_t capacity;
    size_t size;

    size_t head;
    size_t tail;

    struct List_t* data; 

    size_t first_free;

    int error; 
};

//===================================================================================================================

void List_construct(struct List* list, size_t initial_capacity);

void List_resize(struct List* list);

void List_free_filling(struct List* list, size_t begin, size_t end);

void List_clear(struct List* list);

void List_sorted(struct List* list);

void List_destruct(struct List* list);

size_t List_insert_before(struct List* list, size_t number, element_t value);

size_t List_insert_after(struct List* list, size_t number, element_t value);

size_t List_insert_begin(struct List* list, element_t value);

size_t List_insert_end(struct List* list, element_t value);

void List_delete_element(struct List* list, size_t number);

element_t List_find_element(struct List* list, element_t number);

size_t List_find_value(struct List* list, element_t value);

size_t List_find_number(struct List* list, size_t number);

size_t List_free_mem(struct List* list);

size_t List_next_element(struct List* list, size_t current_element);

size_t List_prev_element(struct List* list, size_t current_element);

size_t List_head_element(struct List* list);

size_t List_tail_element(struct List* list);

//===================================================================================================================

void Null_check(struct List* list);

int List_ERROR(struct List* list);

void List_dump(struct List* list, FILE* file);

const char* Text_ERROR(struct List* list);

void List_graph(struct List* list);

void Hack(struct List* list);
