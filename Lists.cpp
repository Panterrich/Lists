#include "Lists.h"

//===================================================================================================================

void List_graph(struct List* list)
{
    Null_check(list);

    FILE* text = fopen("graph_log.dot", "w");

    fprintf(text, "digraph G {\n"            
                  "rankdir = RL;\n");

    fprintf(text, "\t%lu [shape = plaintext, label =<\n"
                          "\t<table>\n"
                          "\t<tr>\n" 
                          "\t\t<td colspan=\"3\"> %lg </td>\n"
                          "\t </tr>\n"
                          "\t <tr>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t </tr>\n"
                          "\t</table>>, style = filled, color = dodgerblue4, fillcolor = mediumaquamarine]\n", 
                    0, (list->data)[0].value, (list->data)[0].prev, 0, (list->data)[0].next);

   
    for (size_t index = 1; index <= list->capacity; ++index)
    {   
        if ((!isnan((list->data)[index].value)) && ((list->data)[index].next != -1) && ((list->data)[index].prev != -1))
        {
           fprintf(text, "\t%lu [shape = plaintext, label =<\n"
                          "\t<table>\n"
                          "\t<tr>\n" 
                          "\t\t<td colspan=\"3\"> %lg </td>\n"
                          "\t </tr>\n"
                          "\t <tr>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t </tr>\n"
                          "\t</table>>, style = filled, color = deepskyblue2, fillcolor = lightskyblue]\n", 
                    index, (list->data)[index].value, (list->data)[index].prev, index, (list->data)[index].next);
        }

        else if (((isnan((list->data)[index].value)) && ((list->data)[index].next != -1) && ((list->data)[index].prev == -1)))
        {
             fprintf(text, "\t%lu [shape = plaintext, label =<\n"
                          "\t<table>\n"
                          "\t<tr>\n" 
                          "\t\t<td colspan=\"3\"> %lg </td>\n"
                          "\t </tr>\n"
                          "\t <tr>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t </tr>\n"
                          "\t</table>>, style = filled, color = darkgreen, fillcolor = lightgreen]\n", 
                    index, (list->data)[index].value, (list->data)[index].prev, index, (list->data)[index].next);
        }

        else
        {
            fprintf(text, "\t%lu [shape = plaintext, label =<\n"
                          "\t<table>\n"
                          "\t<tr>\n" 
                          "\t\t<td colspan=\"3\"> %lg </td>\n"
                          "\t </tr>\n"
                          "\t <tr>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t </tr>\n"
                          "\t</table>>, style = filled, color = red,  fillcolor = lightcoral]\n", 
                    index, (list->data)[index].value, (list->data)[index].prev, index, (list->data)[index].next);
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
        
        else if (!isnan((list->data)[i].value))
        {
            if ((!isnan((list->data)[(list->data)[i].next].value)) && ((list->data)[(list->data)[i].next].prev == i))
            {
                fprintf(text, "\t%ld -> %ld [color = deepskyblue2]; \n", i, (list->data)[i].next);
                fprintf(text, "\t%ld -> %ld [color = deepskyblue2]; \n", (list->data)[i].next, i);
            }

            else if  (((list->data)[i].next == 0) && (i == list->tail))
            {
                fprintf(text, "\t%ld -> %ld [color = deepskyblue2]; \n", i, (list->data)[i].next);
                fprintf(text, "\t%ld -> %ld [color = deepskyblue2]; \n", (list->data)[i].next, i);
            }

            else 
            {
                fprintf(text, "\t%ld -> %ld [color = darkred]; \n", i, (list->data)[i].next);
                fprintf(text, "\t%ld -> %ld [color = darkred]; \n", (list->data)[i].next, i);
            }
        }

        else 
        {
            fprintf(text, "\t%ld -> %ld [color = darkred]; \n", i, (list->data)[i].next);
            fprintf(text, "\t%ld -> %ld [color = darkred]; \n", (list->data)[i].next, i);
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

    system("dot -Tjpeg -ograph_log.jpeg graph_log.dot");

    text = fopen("graph_phys.dot", "w");

    fprintf(text, "digraph G {\n");

    fprintf(text, "\t%lu [shape = plaintext, label =<\n"
                          "\t<table>\n"
                          "\t<tr>\n" 
                          "\t\t<td colspan=\"3\"> %lg </td>\n"
                          "\t </tr>\n"
                          "\t <tr>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t </tr>\n"
                          "\t</table>>, style = filled, color = dodgerblue4, fillcolor = mediumaquamarine]\n", 
                    0, (list->data)[0].value, (list->data)[0].prev, 0, (list->data)[0].next);

   
    for (size_t index = 1; index <= list->capacity; ++index)
    {   
        if ((!isnan((list->data)[index].value)) && ((list->data)[index].next != -1) && ((list->data)[index].prev != -1))
        {
           fprintf(text, "\t%lu [shape = plaintext, label =<\n"
                          "\t<table>\n"
                          "\t<tr>\n" 
                          "\t\t<td colspan=\"3\"> %lg </td>\n"
                          "\t </tr>\n"
                          "\t <tr>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t </tr>\n"
                          "\t</table>>, style = filled, color = deepskyblue2, fillcolor = lightskyblue]\n", 
                    index, (list->data)[index].value, (list->data)[index].prev, index, (list->data)[index].next);
        }

        else if (((isnan((list->data)[index].value)) && ((list->data)[index].next != -1) && ((list->data)[index].prev == -1)))
        {
             fprintf(text, "\t%lu [shape = plaintext, label =<\n"
                          "\t<table>\n"
                          "\t<tr>\n" 
                          "\t\t<td colspan=\"3\"> %lg </td>\n"
                          "\t </tr>\n"
                          "\t <tr>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t </tr>\n"
                          "\t</table>>, style = filled, color = darkgreen, fillcolor = lightgreen]\n", 
                    index, (list->data)[index].value, (list->data)[index].prev, index, (list->data)[index].next);
        }

        else
        {
            fprintf(text, "\t%lu [shape = plaintext, label =<\n"
                          "\t<table>\n"
                          "\t<tr>\n" 
                          "\t\t<td colspan=\"3\"> %lg </td>\n"
                          "\t </tr>\n"
                          "\t <tr>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t\t <td> %ld </td>\n"
                          "\t </tr>\n"
                          "\t</table>>, style = filled, color = red,  fillcolor = lightcoral]\n", 
                    index, (list->data)[index].value, (list->data)[index].prev, index, (list->data)[index].next);
        }
    }
    
    fprintf(text, "\t{ rank = same; ");

    for (size_t index = 0; index <= list->capacity; ++index)
    {
        fprintf(text, " %ld", index);
    }

    fprintf(text, " }\n");

    for (size_t index = 0; index < list->capacity; ++index)
    {
        fprintf(text, " %ld ->", index);
    }

    fprintf(text, "%ld [style = invis]; \n");

    fprintf(text, "\t%ld -> %ld [color = dodgerblue4]; \n", 0, (list->data)[0].next);
    fprintf(text, "\t%ld -> %ld [color = dodgerblue4]; \n", 0, (list->data)[0].prev);

    for (size_t i = 1; i <= list->capacity; ++i)
    {   
        if ((isnan((list->data)[i].value)) && (isnan((list->data)[(list->data)[i].next].value)) && \
            ((list->data)[i].prev == -1)   && (((list->data)[(list->data)[i].next].prev == -1) || ((list->data)[(list->data)[i].next].prev == 0)))
        {
            fprintf(text, "\t%ld -> %ld [color = darkgreen]; \n", i, (list->data)[i].next);
        }
        
        else if (!isnan((list->data)[i].value))
        {
            if ((!isnan((list->data)[(list->data)[i].next].value)) && ((list->data)[(list->data)[i].next].prev == i))
            {
                fprintf(text, "\t%ld -> %ld [color = deepskyblue2, dir = both]; \n", i, (list->data)[i].next);
            }

            else if  (((list->data)[i].next == 0) && (i == list->tail))
            {
                fprintf(text, "\t%ld -> %ld [color = deepskyblue2, dir = both]; \n", i, (list->data)[i].next);
            }

            else 
            {
                fprintf(text, "\t%ld -> %ld [color = darkred]; \n", i, (list->data)[i].next);
                fprintf(text, "\t%ld -> %ld [color = darkred]; \n", (list->data)[i].next, i);
            }
        }

        else 
        {
            fprintf(text, "\t%ld -> %ld [color = darkred]; \n", i, (list->data)[i].next);
            fprintf(text, "\t%ld -> %ld [color = darkred]; \n", (list->data)[i].next, i);
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

    system("dot -Tjpeg -ograph_phys.jpeg graph_phys.dot");

    system("convert graph_log.jpeg graph_phys.jpeg -append graph.jpeg");
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

        list->error      = 0;
        list->head       = 0;
        list->tail       = 0;
        list->size       = 0;
        list->first_free = 0;
        list->sorted     = 1;

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
    Null_check(list);
    ASSERT_OK(list);

    if (list->size == list->capacity)
    {   
        List_resize(list);
    }

    if (list->size == 0)
    {
        return List_insert_first(list, value);
    }

    if (number == list->head)
    {
        return List_insert_begin(list, value);
    }

    size_t newpos = List_free_mem(list);
    
    list->first_free = (list->data)[newpos].next;

    (list->data)[newpos].prev = (list->data)[number].prev;
    (list->data)[List_prev_element(list, number)].next = newpos;

    (list->data)[newpos].next = number;
    (list->data)[number].prev = newpos;


    (list->data)[newpos].value = value;

    ++(list->size);

    list->sorted = 0;

    ASSERT_OK(list);

    return newpos;
}

size_t List_insert_after(struct List* list, size_t number, element_t value)
{   
    Null_check(list);
    ASSERT_OK(list);

    if (list->size == list->capacity)
    {   
        List_resize(list);
    }

    if (list->size == 0)
    {
        return List_insert_first(list, value);
    }

    if (number == list->tail)
    {
        return List_insert_end(list, value);
    }

    
    size_t newpos = List_free_mem(list);
    
    list->first_free = (list->data)[newpos].next;

    (list->data)[newpos].next = (list->data)[number].next;
    (list->data)[List_next_element(list, number)].prev = newpos;

    (list->data)[newpos].prev = number;
    (list->data)[number].next = newpos;

    (list->data)[newpos].value = value;

    ++(list->size);

    list->sorted = 0;

    ASSERT_OK(list);

    return newpos;
}

size_t List_insert_begin(struct List* list, element_t value)
{   
    Null_check(list);
    ASSERT_OK(list);

    if (list->size == list->capacity)
    {
        List_resize(list);
    }

    if (list->size == 0)
    {
        return List_insert_first(list, value);
    }

    size_t newpos = List_free_mem(list);
    
    list->first_free = (list->data)[newpos].next;

    (list->data)[newpos].prev = (list->data)[List_head_element(list)].prev;
    (list->data)[newpos].next = List_head_element(list);
    (list->data)[List_head_element(list)].prev = newpos;
    (list->data)[newpos].value = value;

    ++(list->size);
    
    list->sorted = 0;
    list->head   = newpos;

    ASSERT_OK(list);

    return newpos;
}

size_t List_insert_end(struct List* list, element_t value)
{
    Null_check(list);
    ASSERT_OK(list);

    if (list->size == list->capacity)
    {
        List_resize(list);
    }

    if (list->size == 0)
    {
        return List_insert_first(list, value);
    }

    size_t newpos = List_free_mem(list);
    
    list->first_free = (list->data)[newpos].next;

    (list->data)[newpos].prev = List_tail_element(list);
    (list->data)[newpos].next = 0;
    (list->data)[List_tail_element(list)].next = newpos;
    (list->data)[newpos].value = value;

    ++(list->size);
    
    list->tail = newpos;

    ASSERT_OK(list);

    return newpos;
}

void List_delete_element(struct List* list, size_t number)
{   
    Null_check(list);
    ASSERT_OK(list);

    if (number != list->tail)
    {
        list->sorted = 0;
    }

    if (list->size == 1)
    {
        list->head = 0;
        list->tail = 0;
    }

    else if (number == list->head)
    {
        list->head = List_next_element(list, number);
        (list->data)[List_next_element(list, number)].prev = 0;
    }

    else if (number == list->tail)
    {
        list->tail = List_prev_element(list, number);
        (list->data)[List_prev_element(list, number)].next = 0;
    } 

    else
    {
        (list->data)[List_prev_element(list, number)].next = List_next_element(list, number);
        (list->data)[List_next_element(list, number)].prev = List_prev_element(list, number);
    }
    
    (list->data)[number].next = list->first_free;
    (list->data)[number].prev = -1;
    (list->data)[number].value = Poison;

    list->first_free = number;

    --(list->size);

    ASSERT_OK(list);
}

element_t List_find_value_by_logical_index(struct List* list, size_t number)
{
    Null_check(list);
    ASSERT_OK(list);

    if (list->sorted)
    {
        return (list->data)[number].value;
    }

    else
    {
        size_t current_element = List_head_element(list);

        for (size_t index = 1; index < number; ++index)
        {
            current_element = List_next_element(list, current_element);
        }

        return (list->data)[current_element].value;
    }
}

void List_clear(struct List* list)
{   
    Null_check(list);

    list->error      = 0;
    list->head       = 0;
    list->tail       = 0;
    list->size       = 0;
    list->first_free = 1;
    list->sorted     = 1;

    (list->data)[0].value = Poison;
    (list->data)[0].next  = 0;
    (list->data)[0].prev  = 0;

    List_free_filling(list->data, 1, list->capacity);

    ASSERT_OK(list);
}

void List_resize(struct List* list)
{
    Null_check(list);
    ASSERT_OK(list);

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

            List_free_filling(list->data, list->capacity + 1, 20);

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

                    List_free_filling(list->data, list->capacity + 1, list->capacity + 1);

                    list->first_free = list->capacity + 1;
                    list->capacity   = list->capacity + 1;
                }
            }

            else
            {
                list->data = new_pointer;

                List_free_filling(list->data, (list->capacity) + 1, 1.5 * (list->capacity));

                list->first_free = list->capacity + 1;
                list->capacity   = 1.5 * list->capacity;
            }
        }

        else
        {
            list->data = new_pointer;

            List_free_filling(list->data, (list->capacity) + 1, 2 * (list->capacity));

            list->first_free = list->capacity + 1;
            list->capacity   = 2 * list->capacity;
        }
    }

    ASSERT_OK(list);
}

size_t List_insert_first(struct List* list, element_t value)
{
    Null_check(list);
    ASSERT_OK(list);

    if (list->size == list->capacity)
    {
        List_resize(list);
    }

    size_t newpos = List_free_mem(list);

    list->first_free = (list->data)[newpos].next;

    (list->data)[newpos].prev  = 0;
    (list->data)[newpos].next  = 0;
    (list->data)[newpos].value = value;

    ++(list->size);

    list->head = newpos;
    list->tail = newpos;

    ASSERT_OK(list);

    return newpos;
}

void List_sorted(struct List* list)
{   
    Null_check(list);
    ASSERT_OK(list);

    List_t* new_pointer = (List_t*) calloc (list->capacity + 1, sizeof(List_t));

    new_pointer[0].next  = 0;
    new_pointer[0].prev  = 0;
    new_pointer[0].value = Poison;

    for (size_t index = 1, current_element = List_head_element(list); index <= list->size; ++index, current_element = (list->data)[current_element].next)
    {
        new_pointer[index].value = (list->data)[current_element].value;
    }


    for (size_t index = 1; index <= list->size; ++index)
    {
        new_pointer[index].next = (index + 1) % (list->size + 1);
        new_pointer[index].prev = (index - 1);
    }

    list->head = 1;
    list->tail = list->size;

    List_free_filling(new_pointer, list->size + 1, list->capacity);

    list->first_free = list->size + 1;

    List_t* old_pointer = list->data;
    
    list->data = new_pointer;

    free(old_pointer);

    ASSERT_OK(list);
}

size_t List_find_first_value(struct List* list, element_t value)
{
    Null_check(list);
    ASSERT_OK(list);

    size_t current_element = List_head_element(list);

    for (size_t index = 1; index <= list->size; ++index)
    {
        if ((list->data)[index].value == value)
        {
            return current_element;
        }

        current_element = List_next_element(list, current_element);
    }

    ASSERT_OK(list);

    return -1;
}

size_t List_find_phys_number_by_logical_index(struct List* list, size_t number)
{
    Null_check(list);
    ASSERT_OK(list);

    if (list->sorted)
    {
        return number;
    }
    
    else
    {
        size_t current_element = List_head_element(list);

        for (size_t index = 1; index < number; ++index)
        {
            current_element = List_next_element(list, current_element);
        }

        return current_element;
    }
}

size_t List_find_logical_index_by_phys_number(struct List* list, size_t number)
{
    Null_check(list);
    ASSERT_OK(list);

    if (list->sorted)
    {
        return number;
    }
    
    else
    {
        size_t current_element = List_head_element(list);
        size_t index = 0;

        for (index = 1; current_element != number; ++index)
        {
            current_element = List_next_element(list, current_element);
        }

        return index;
    }
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
    case_of_switch(WRONG_SORTED)
    case_of_switch(WRONG_NUMBER_POISON_NEXT)
    case_of_switch(WRONG_NUMBER_POISON_PREV)
    case_of_switch(OUT_OF_MEMORY)
    default: return "Unknown ERROR";
    }
}

void List_free_filling(struct List_t* data, size_t begin, size_t end)
{
    for (size_t index = begin; index < end; ++index)
    {
        data[index].value = Poison;
        data[index].next  = index + 1;
        data[index].prev  = -1;
    }

    data[end].value = Poison;
    data[end].next  = 0;
    data[end].prev  = -1;
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

    // Full check error list

    return List_validator(list);
    // return 0;

}

int List_validator(struct List* list)
{
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

        for (size_t size_next = 1, current_element = list->head; size_next <= list->capacity; ++size_next)
        {   
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

        for (size_t size_prev = 1, current_element = list->tail; size_prev <= list->capacity; ++size_prev)
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
        if (((list->data)[(list->data)[current_element].next].prev != current_element) && (current_element != list->head) && (current_element != list->tail))
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

    if (list->sorted)
    {
        for (size_t index = 1, current_element = list->head; index <= list->size; ++index)
        {
            if (index != current_element)
            {
                list->error = WRONG_SORTED;
                return WRONG_SORTED;
            }

            current_element = (list->data)[current_element].next;
        }
    }
    
    return 0;
}