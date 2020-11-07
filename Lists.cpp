#include "Lists.h"

//===================================================================================================================

void List_graph(struct List* list)
{
    Null_check(list);

    FILE* text = fopen("graph.dot", "w");

    fprintf(text, "digraph G {\n"            
                  "graph [bgcolor = Snow2]\n"  
                  "rankdir = LR;\n");

    fprintf(text, "\t%lu [shape = record, label = \" %lg | { %ld | %ld | %ld }\", style = filled, color = dodgerblue4, fillcolor = mediumaquamarine]\n", 
                    0, (list->data)[0].value, (list->data)[0].prev, 0, (list->data)[0].next);

    for (size_t i = 1; i <= list->capacity; ++i)
    {   
        if ((!isnan((list->data)[i].value)) && ((list->data)[i].next != -1) && ((list->data)[i].prev != -1))
        {
            fprintf(text, "\t%lu [shape = record, label = \" %lg | { %ld | %ld | %ld }\", style = filled, color = deepskyblue2, fillcolor = lightskyblue]\n", 
                    i, (list->data)[i].value, (list->data)[i].prev, i, (list->data)[i].next);
        }

        else if (((isnan((list->data)[i].value)) && ((list->data)[i].next != -1) && ((list->data)[i].prev == -1)))
        {
            fprintf(text, "\t%lu [shape = record, label = \" %lg | { %ld | %ld | %ld }\", style = filled, color = darkgreen, fillcolor = lightgreen]\n", 
                    i, (list->data)[i].value, (list->data)[i].prev, i, (list->data)[i].next);
        }

        else
        {
            fprintf(text, "\t%lu [shape = record, label = \" %lg | { %ld | %ld | %ld }\", style = filled, color = red,  fillcolor = lightcoral]\n", 
                    i, (list->data)[i].value, (list->data)[i].prev, i, (list->data)[i].next);
        }
    }

    fprintf(text, "\t%ld -> %ld [color = dodgerblue4]; \n", 0, (list->data)[0].next);
    fprintf(text, "\t%ld -> %ld [color = dodgerblue4]; \n", 0, (list->data)[0].prev);


    for (size_t i = 1; i <= list->capacity; ++i)
    {   
        if ((isnan((list->data)[i].value)) && (isnan((list->data)[(list->data)[i].next].value)) && \
            ((list->data)[i].prev == -1)   && (((list->data)[(list->data)[i].next].prev == -1) || ((list->data)[(list->data)[i].next].prev == 0)))
        {
            fprintf(text, "\t%ld -> %ld [color = darkgreen]; \n", i, (list->data)[i].next);
        }
        
        else if ((!isnan((list->data)[i].value)) && (!isnan((list->data)[(list->data)[i].next].value)) && ((list->data)[(list->data)[i].next].prev == i))
        {
            fprintf(text, "\t%ld -> %ld [color = deepskyblue2]; \n", i, (list->data)[i].next);
        }

        else if ((!isnan((list->data)[i].value)) && ((list->data)[i].next == 0) && (i == list->tail))
        {
            fprintf(text, "\t%ld -> %ld [color = deepskyblue2]; \n", i, (list->data)[i].next);
        }

        else 
        {
            fprintf(text, "\t%ld -> %ld [color = darkred]; \n", i, (list->data)[i].next);
        }
    }

    fprintf(text, "\tHEAD [style = filled, color = black, fillcolor = salmon1]; \n");
    fprintf(text, "\tTAIL [style = filled, color = black, fillcolor = salmon1]; \n");
    fprintf(text, "\tFREE [style = filled, color = black, fillcolor = salmon1]; \n");

    fprintf(text, "\tHEAD -> %ld [color = deeppink]; \n", list->head);
    fprintf(text, "\tTAIL -> %ld [color = deeppink]; \n", list->tail);
    fprintf(text, "\tFREE -> %ld [color = deeppink]; \n", list->first_free);

    fprintf(text, "}\n");

    fclose(text);

    system("dot -Tjpeg -ograph.jpeg graph.dot");
    system("gwenview graph.jpeg");
}

void List_construct(struct List* list, size_t initial_capacity)
{
    Null_check(list);

    if (initial_capacity < 0)
    {
        list->error = NEGATIVE_CAPACITY;
        ASSERT_OK(list);
    }

    else if (initial_capacity == 0)
    {
        list->capacity = initial_capacity;

        list->data = (List_t*) calloc(1, sizeof(List_t));

        list->error = 0;
        list->head  = 0;
        list->tail  = 0;
        list->size  = 0;
        list->first_free  = 0;

        (list->data)[0].value = Poison;
        (list->data)[0].next = 0;
        (list->data)[0].prev = 0;
    }

    else
    {
        list->capacity = initial_capacity;

        list->data = (List_t*) calloc(1 + list->capacity, sizeof(List_t));

        List_clear(list);
    }
    
    ASSERT_OK(list);
}

size_t List_insert_before(struct List* list, size_t number, element_t value)
{
    if (list->size == list->capacity)
    {   
        List_resize(list);
        List_graph(list);
    }

    if (number == list->head)
    {
        return List_insert_end(list, value);
    }

    else
    {
        size_t newpos = List_free_mem(list);
        
        list->first_free = (list->data)[newpos].next;

        (list->data)[newpos].prev = (list->data)[number].prev;
        (list->data)[List_prev_element(list, number)].next = newpos;

        (list->data)[newpos].next = number;
        (list->data)[number].prev = newpos;
    

        (list->data)[newpos].value = value;

        ++(list->size);

        return newpos;
    }
}

size_t List_insert_after(struct List* list, size_t number, element_t value)
{   
    if (list->size == list->capacity)
    {   
        List_resize(list);
        List_graph(list);
    }

    if (number == list->head)
    {
        return List_insert_begin(list, value);
    }

    else
    {
        size_t newpos = List_free_mem(list);
        
        list->first_free = (list->data)[newpos].next;

        (list->data)[newpos].next = (list->data)[number].next;
        (list->data)[List_next_element(list, number)].prev = newpos;

        (list->data)[newpos].prev = number;
        (list->data)[number].next = newpos;
    

        (list->data)[newpos].value = value;

        ++(list->size);

        return newpos;
    }
}

size_t List_insert_begin(struct List* list, element_t value)
{
    if (list->size == list->capacity)
    {
        List_resize(list);
    }

    size_t newpos = List_free_mem(list);
    
    list->first_free = (list->data)[newpos].next;

    (list->data)[newpos].prev = (list->data)[List_head_element(list)].prev;
    (list->data)[newpos].next = List_head_element(list);

    if (list->size != 0)
    {
        (list->data)[List_head_element(list)].prev = newpos;
    }

    (list->data)[newpos].value = value;

    ++(list->size);
    
    list->head = newpos;

    if (list->size == 1)
    {
        list->tail = newpos;
    }

    return newpos;
}

size_t List_insert_end(struct List* list, element_t value)
{
    if (list->size == list->capacity)
    {
        List_resize(list);
    }

    size_t newpos = List_free_mem(list);
    
    list->first_free = (list->data)[newpos].next;

    (list->data)[newpos].prev = List_tail_element(list);
    (list->data)[newpos].next = 0;

    if (list->size != 0)
    {
        (list->data)[List_tail_element(list)].next = newpos;
    }
    
    (list->data)[newpos].value = value;

    ++(list->size);
    
    list->tail = newpos;

    if (list->size == 1)
    {
        list->head = newpos;
    }

    return newpos;
}

void List_delete_element(struct List* list, size_t number)
{
    (list->data)[List_prev_element(list, number)].next = List_next_element(list, number);
    (list->data)[List_next_element(list, number)].prev = List_prev_element(list, number);

    (list->data)[number].next = list->first_free;
    (list->data)[number].prev = -1;
    (list->data)[number].value = Poison;

    list->first_free = number;
}

element_t List_find_element(struct List* list, element_t number)
{
    size_t current_element = List_head_element(list);

    for (size_t index = 1; index < number; ++index)
    {
        current_element = List_next_element(list, current_element);
    }

    return (list->data)[current_element].value;
}

void List_clear(struct List* list)
{   
    list->error = 0;
    list->head  = 0;
    list->tail  = 0;
    list->size  = 0;
    list->first_free  = 1;

    (list->data)[0].value = Poison;
    (list->data)[0].next  = 0;
    (list->data)[0].prev  = 0;

    List_free_filling(list, 1, list->capacity);
}

void List_resize(struct List* list)
{
    Null_check(list);

    if (list->capacity <= 10)
    {   
        List_t* new_pointer = (List_t*) realloc(list->data, (20 + 1) * sizeof(List_t));

        if (new_pointer == nullptr)
        {
            list->error = OUT_OF_MEMORY;
            ASSERT_OK(list);
        }

        else
        {
            list->data = new_pointer;

            List_free_filling(list, list->capacity + 1, 20);

            list->first_free = list->capacity + 1;
            list->capacity   = 20;
        }
    }

    else
    {
        List_t* new_pointer = (List_t*) realloc(list->data, (2 * list->capacity + 1) * sizeof(List_t));

        if (new_pointer == nullptr)
        {
            new_pointer = (List_t*) realloc(list->data, (1.5 * list->capacity + 1) * sizeof(List_t));

            if (new_pointer == nullptr)
            {
                new_pointer = (List_t*) realloc(list->data, (list->capacity + 1 + 1) * sizeof(List_t));

                if (new_pointer == nullptr)
                {
                    list->error = OUT_OF_MEMORY;
                    ASSERT_OK(list);
                }
                
                else
                {   
                    list->data = new_pointer;

                    List_free_filling(list, list->capacity + 1, list->capacity + 1);

                    list->first_free = list->capacity + 1;
                    list->capacity   = list->capacity + 1;
                }
            }

            else
            {
                list->data = new_pointer;

                List_free_filling(list, (list->capacity) + 1, 1.5 * (list->capacity));

                list->first_free = list->capacity + 1;
                list->capacity   = 1.5 * list->capacity;
            }
        }

        else
        {
            list->data = new_pointer;

            List_free_filling(list, (list->capacity) + 1, 2 * (list->capacity));

            list->first_free = list->capacity + 1;
            list->capacity   = 2 * list->capacity;
        }
    }
}

void List_sorted(struct List* list)
{

}

size_t List_find_first_value(struct List* list, element_t value)
{
    size_t current_element = List_head_element(list);

    for (size_t index = 1; index <= list->size; ++index)
    {
        if ((list->data)[index].value == value)
        {
            return current_element;
        }

        current_element = List_next_element(list, current_element);
    }

    return -1;
}

size_t List_find_number(struct List* list, size_t number)
{
    size_t current_element = List_head_element(list);

    for (size_t index = 1; index < number; ++index)
    {
        current_element = List_next_element(list, current_element);
    }

    return current_element;
}

size_t List_free_mem(struct List* list)
{
    Null_check(list);

    return list->first_free;
}

size_t List_next_element(struct List* list, size_t current_element)
{
    Null_check(list);

    return (list->data)[current_element].next;
}

size_t List_prev_element(struct List* list, size_t current_element)
{
    Null_check(list);

    return (list->data)[current_element].prev;
}

size_t List_head_element(struct List* list)
{
    Null_check(list);

    return list->head;
}

size_t List_tail_element(struct List* list)
{
    Null_check(list);

    return list->tail;
}

void List_destruct(struct List* list)
{
    free(list->data);

    list->capacity   = -1;
    list->error      = -1;
    list->first_free = -1;
    list->head       = -1;
    list->tail       = -1;
    list->size       = -1;

    list->data = nullptr;
}

void Null_check(struct List* list)
{
    if (list == nullptr)
    {
        FILE* log = fopen("log.txt", "a");

        fprintf(log, "List (ERROR NULL PTR) [0x000000] \n");
        fflush(log);

        abort();
    }
}

void Hack(struct List* list)
{
    (list->data)[1].value = NAN;

    ASSERT_OK(list);
}

void List_dump(struct List* list, FILE* file)
{
    Null_check(list);
    
    const char* code = Text_ERROR(list);

    fprintf(file, "List (ERROR #%d: %s [0x%x] \"%s\" \n"
                  "{\n"
                  "\tsize = %u\n" 
                  "\tcapacity = %u\n"
                  "\thead = %u\n" 
                  "\ttail = %u\n"  
                  "\tdata[0x%x]\n"
                  "\tfirst_free = %u\n"
                  "}\n\n\n",  
                  list->error, code, list, (list->name + 1), list->size,  
                  list->capacity, list->head, list->tail, list->data, list->first_free);

    fflush(file);
}

const char* Text_ERROR(struct List* list)
{
    switch (list->error)
    {
    case 0: return "OK";
    case_of_switch(NEGATIVE_CAPACITY)
    case_of_switch(NEGATIVE_SIZE)
    case_of_switch(NEGATIVE_HEAD)
    case_of_switch(NEGATIVE_TAIL)
    case_of_switch(SIZE_MORE_CAPACITY)
    case_of_switch(HEAD_MORE_CAPACITY)
    case_of_switch(TAIL_MORE_CAPACITY)
    case_of_switch(NULLPTR_DATA)
    case_of_switch(DAMADED_SERVICE_CELL)
    case_of_switch(WRONG_HEAD)
    case_of_switch(WRONG_VALUE)
    case_of_switch(WRONG_SIZE_NEXT)
    case_of_switch(WRONG_SIZE_PREV)
    case_of_switch(WRONG_LINK_NEXT)
    case_of_switch(WRONG_LINK_PREV)
    case_of_switch(WRONG_DOUBLE_LINK)
    case_of_switch(WRONG_FREE_LINK)
    case_of_switch(WRONG_NUMBER_POISON_NEXT)
    case_of_switch(WRONG_NUMBER_POISON_PREV)
    case_of_switch(OUT_OF_MEMORY)
    default: return "Unknown ERROR";
    }
}

void List_free_filling(struct List* list, size_t begin, size_t end)
{
    for (size_t index = begin; index < end; ++index)
    {
        (list->data)[index].value = Poison;
        (list->data)[index].next  = index + 1;
        (list->data)[index].prev  = -1;
    }

    (list->data)[end].value = Poison;
    (list->data)[end].next  = 0;
    (list->data)[end].prev  = -1;
}

int List_ERROR(struct List* list)
{
    if (list->error != 0)
    {
        return list->error;
    }

    if (list->capacity < 0)
    {
        list->error = NEGATIVE_CAPACITY;
        return NEGATIVE_CAPACITY;
    }

    if (list->size < 0)
    {
        list->error = NEGATIVE_SIZE;
        return NEGATIVE_SIZE;
    }

    if (list->head < 0)
    {
        list->error = NEGATIVE_HEAD;
        return NEGATIVE_HEAD;
    }

    if (list->tail < 0)
    {
        list->error = NEGATIVE_TAIL;
        return NEGATIVE_TAIL;
    }

    if (list->data == nullptr)
    {
        list->error = NULLPTR_DATA;
        return NULLPTR_DATA;
    }

    if (list->size > list->capacity)
    {
        list->error = SIZE_MORE_CAPACITY;
        return SIZE_MORE_CAPACITY;
    }

    if (list->head > list->capacity)
    {
        list->error = HEAD_MORE_CAPACITY;
        return HEAD_MORE_CAPACITY;
    }

    if (list->tail > list->capacity)
    {
        list->error = TAIL_MORE_CAPACITY;
        return TAIL_MORE_CAPACITY;
    }

    if ((!isnan((list->data)[0].value)) || ((list->data)[0].next != 0) || ((list->data)[0].prev != 0))
    {
        list->error = DAMADED_SERVICE_CELL;
        return DAMADED_SERVICE_CELL;
    }

    for (size_t index = 1; index <= list->capacity; ++index)
    {
        if (isnan((list->data)[index].value))
        {
            if ((list->data)[index].prev != -1)
            {
                list->error = WRONG_VALUE;
                return WRONG_VALUE;
            }
        }
    }

    if (list->head != 0)
    {
        if ((list->data)[list->head].prev != 0)
        {
            list->error = WRONG_HEAD;
            return WRONG_HEAD;
        }

        for (size_t size_next = 1; size_next <= list->capacity; size_next)
        {   
            size_t current_element = list->head;

            if (((list->data)[current_element].next == 0) &&  (size_next != list->size))
            {
                if (size_next != list->size)
                {
                    list->error = WRONG_SIZE_NEXT;
                    return WRONG_SIZE_NEXT;
                }

            }

            if (size_next == list->size)
            {
                if ((list->data)[current_element].next != 0)
                {
                    list->error = WRONG_SIZE_NEXT;
                    return WRONG_SIZE_NEXT;
                }

                else
                {
                    break;
                }
                
            }

            if ((list->data)[current_element].next < 0)
            {
                list->error = WRONG_LINK_NEXT;
                return WRONG_LINK_NEXT;
            }

            current_element = (list->data)[current_element].next;
        }

    }

    if (list->tail != 0)
    {
        if ((list->data)[list->tail].next != 0)
        {
            list->error = WRONG_TAIL;
            return WRONG_TAIL;
        }

        for (size_t size_prev = 1, current_element = list->tail; size_prev <= list->capacity; size_prev)
        {   
            if (((list->data)[current_element].prev == 0) &&  (size_prev != list->size))
            {
                if (size_prev != list->size)
                {
                    list->error = WRONG_SIZE_PREV;
                    return WRONG_SIZE_PREV;
                }
            }

            if (size_prev == list->size)
            {
                if ((list->data)[current_element].prev != 0)
                {
                    list->error = WRONG_SIZE_PREV;
                    return WRONG_SIZE_PREV;
                }

                else
                {
                    break;
                }
            }

            if ((list->data)[current_element].prev < 0)
            {
                list->error = WRONG_LINK_PREV;
                return WRONG_LINK_PREV;
            }

            current_element = (list->data)[current_element].prev;
        }

    }

    for (size_t index = 1, current_element = list->head; index <= list->size; ++index)
    {
        if ((list->data)[(list->data)[current_element].next].prev != current_element)
        {
            list->error = WRONG_DOUBLE_LINK;
            return WRONG_DOUBLE_LINK;
        }

        current_element = (list->data)[current_element].next;
    }


    if (list->first_free > 0)
    {
        for (size_t index = 0, current_element = list->first_free; index < list->capacity - list->size; ++index)
        {
            if ((list->data)[current_element].next < 0)
            {
                list->error = WRONG_FREE_LINK;
                return WRONG_FREE_LINK;
            }

            if (list->data[current_element].prev != -1)
            {
                list->error = WRONG_FREE_LINK;
                return WRONG_FREE_LINK;
            }

            if (!isnan((list->data[current_element].value)))
            {
                list->error = WRONG_FREE_LINK;
                return WRONG_FREE_LINK;
            }

            current_element = (list->data)[current_element].next;
        }
    }

    size_t count_poison_next = 0;

    for (size_t index = 1; index <= list->capacity; ++index)
    {
        if ((list->data)[index].next == -1) ++count_poison_next;
    }

    if (count_poison_next != 0)
    {
        list->error = WRONG_NUMBER_POISON_NEXT;
        return WRONG_NUMBER_POISON_NEXT;
    }

    size_t count_poison_prev = 0;

    for (size_t index = 1; index <= list->capacity; ++index)
    {
        if ((list->data)[index].prev == -1) ++count_poison_prev;
    }

    if (count_poison_prev != list->capacity - list->size)
    {
        list->error = WRONG_NUMBER_POISON_PREV;
        return WRONG_NUMBER_POISON_PREV;
    }

    return 0;
}