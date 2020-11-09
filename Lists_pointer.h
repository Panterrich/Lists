#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

//=======================================================================================================================

typedef double element_t;
const double Poison = NAN;

#define LIST_POINTER_CONSTRUCT(list) (list)->name = #list;               \
                                     List_pointer_construct(list)

//======================================================================================================================

struct List_pointer_t
{
    element_t value;

    List_pointer_t* next;
    List_pointer_t* prev;
};

struct List_pointer
{
    const char* name;

    size_t size;

    List_pointer_t* head;
    List_pointer_t* tail;
};

//===================================================================================================================

void List_pointer_construct(struct List_pointer* list);

void List_pointer_clear(struct List_pointer* list);

void List_pointer_destruct(struct List_pointer* list);

List_pointer_t* List_pointer_insert_first(struct List_pointer* list, element_t value);

List_pointer_t* List_pointer_insert_before(struct List_pointer* list, size_t number, element_t value);

List_pointer_t* List_pointer_insert_after(struct List_pointer* list, size_t number, element_t value);

List_pointer_t* List_pointer_insert_begin(struct List_pointer* list, element_t value);

List_pointer_t* List_pointer_insert_end(struct List_pointer* list, element_t value);

void List_pointer_delete_element(struct List_pointer* list, size_t number);

List_pointer_t* List_pointer_find_element(struct List_pointer* list, size_t number);

List_pointer_t* List_pointer_find_value(struct List_pointer* list, element_t value);

List_pointer_t* List_pointer_next_element(struct List_pointer* list, List_pointer_t* current_element);

List_pointer_t* List_pointer_prev_element(struct List_pointer* list, List_pointer_t* current_element);

List_pointer_t* List_pointer_head_element(struct List_pointer* list);

List_pointer_t* List_pointer_tail_element(struct List_pointer* list);

void List_pointer_graph(struct List_pointer* list);