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
                                    abort();                                                                            \
                                }

#define LIST_CONSTRUCT(list, capacity) (list)->name = #list;               \
                                    List_construct(list, capacity)

#define case_of_switch(enum_const) case enum_const: return #enum_const;

//======================================================================================================================

typedef double element_t;
const double Poison = NAN;

//======================================================================================================================

enum ERRORS
{
    NEGATIVE_CAPACITY = 1,
    NEGATIVE_SIZE     = 2,
    NEGATIVE_HEAD     = 3, 
    NEGATIVE_TAIL     = 4,

    SIZE_MORE_CAPACITY = 5,
    HEAD_MORE_CAPACITY = 6,
    TAIL_MORE_CAPACITY = 7,

    NULLPTR_DATA = 8,

    DAMADED_SERVICE_CELL = 9,

    WRONG_HEAD = 10,
    WRONG_TAIL = 11,
    
    WRONG_VALUE = 12,

    WRONG_SIZE_NEXT = 13,
    WRONG_SIZE_PREV = 14,

    WRONG_LINK_NEXT   = 15,
    WRONG_LINK_PREV   = 16,
    WRONG_DOUBLE_LINK = 17,
    WRONG_FREE_LINK   = 18,

    WRONG_SORTED = 19,
    
    WRONG_NUMBER_POISON_NEXT = 20,
    WRONG_NUMBER_POISON_PREV = 21,

    OUT_OF_MEMORY = 22,
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

    int sorted;

    int error; 
};

//===================================================================================================================

void List_construct(struct List* list, size_t initial_capacity);

void List_resize(struct List* list);

void List_free_filling(struct List_t* data, size_t begin, size_t end);

void List_clear(struct List* list);

void List_sorted(struct List* list);

void List_destruct(struct List* list);

size_t List_insert_first(struct List* list, element_t value);

size_t List_insert_before(struct List* list, size_t number, element_t value);

size_t List_insert_after(struct List* list, size_t number, element_t value);

size_t List_insert_begin(struct List* list, element_t value);

size_t List_insert_end(struct List* list, element_t value);

void List_delete_element(struct List* list, size_t number);

element_t List_find_value_by_logical_index(struct List* list, size_t number);

size_t List_find_value(struct List* list, element_t value);

size_t List_find_phys_number_by_logical_index(struct List* list, size_t number);

size_t List_find_logical_index_by_phys_number(struct List* list, size_t number);

size_t List_free_mem(struct List* list);

size_t List_next_element(struct List* list, size_t current_element);

size_t List_prev_element(struct List* list, size_t current_element);

size_t List_head_element(struct List* list);

size_t List_tail_element(struct List* list);

//===================================================================================================================

void Null_check(struct List* list);

int List_ERROR(struct List* list);

int List_validator(struct List* list);

void List_dump(struct List* list, FILE* file);

const char* Text_ERROR(struct List* list);

void List_graph(struct List* list);

void Hack(struct List* list);

