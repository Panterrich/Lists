#include "Lists_pointer.h"

void List_pointer_construct(struct List_pointer* list)
{
    assert(list != nullptr);

    list->head = 0;
    list->tail = 0;
    list->size = 0;
}

void List_pointer_clear(struct List_pointer* list)
{
    assert(list != nullptr);

    List_pointer_t* current_element = List_pointer_tail_element(list);
    List_pointer_t* next_element    = nullptr;

    for (size_t index = 0; index < list->size; ++index)
    {
        next_element = current_element->prev;

        current_element->prev = nullptr;
        current_element->next = nullptr;
        current_element->value = Poison;

        free(current_element);

        current_element = next_element;
    }

    list->size = -1;
    list->head = nullptr;
    list->tail = nullptr;
}

void List_pointer_destruct(struct List_pointer* list)
{
    assert(list != nullptr);

    List_pointer_clear(list);

    list->size = -1;
}

List_pointer_t* List_pointer_find_element(struct List_pointer* list, size_t number)
{   
    assert(list != nullptr);

    List_pointer_t* current_element = List_pointer_head_element(list);

    for (size_t index = 1; index < number; ++index)
    {
        current_element = List_pointer_next_element(list, current_element);
    }

    return current_element;
}

List_pointer_t* List_pointer_insert_first(struct List_pointer* list, element_t value)
{   
    assert(list != nullptr);

    List_pointer_t* new_element = (List_pointer_t*) calloc(1, sizeof(List_pointer_t));

    new_element->value = value;
    new_element->prev  = nullptr;
    new_element->next  = nullptr;

    list->size = 1;
    list->head = new_element;
    list->tail = new_element; 

    return new_element;
}

List_pointer_t* List_pointer_insert_before(struct List_pointer* list, size_t number, element_t value)
{
    assert(list != nullptr);

    if (list->size == 0)
    {
        return List_pointer_insert_first(list, value);
    }

    if (number == 1)
    {
        return List_pointer_insert_begin(list, value);
    }

    List_pointer_t* current_element = List_pointer_find_element(list, number);
    List_pointer_t* new_element = (List_pointer_t*) calloc (1, sizeof(List_pointer_t));

    new_element->prev  = current_element->prev;
    new_element->next  = current_element;
    new_element->value = value;

    List_pointer_prev_element(list, current_element)->next = new_element;
    current_element->prev = new_element;

    ++(list->size);
    
    return new_element;
}

List_pointer_t* List_pointer_insert_after(struct List_pointer* list, size_t number, element_t value)
{
    assert(list != nullptr);

    if (list->size == 0)
    {
        return List_pointer_insert_first(list, value);
    }

    if (number == list->size)
    {
        return List_pointer_insert_end(list, value);
    }

    List_pointer_t* current_element = List_pointer_find_element(list, number);
    List_pointer_t* new_element = (List_pointer_t*) calloc (1, sizeof(List_pointer_t));

    new_element->next  = current_element->next;
    new_element->prev  = current_element;
    new_element->value = value;

    List_pointer_next_element(list, current_element)->prev = new_element;
    current_element->next = new_element;

    ++(list->size);
    
    return new_element;
}

List_pointer_t* List_pointer_insert_begin(struct List_pointer* list, element_t value)
{
    assert(list != nullptr);
    
    if (list->size == 0)
    {
        return List_pointer_insert_first(list, value);
    }

    List_pointer_t* current_element = List_pointer_head_element(list);

    List_pointer_t* new_element = (List_pointer_t*) calloc (1, sizeof(List_pointer_t));

    new_element->prev  = nullptr;
    new_element->next  = current_element;
    new_element->value = value;

    current_element->prev = new_element;

    list->head = new_element;

    ++(list->size);
    
    return new_element;
}

List_pointer_t* List_pointer_insert_end(struct List_pointer* list, element_t value)
{
    assert(list != nullptr);

    if (list->size == 0)
    {
        return List_pointer_insert_first(list, value);
    }

    List_pointer_t* current_element = List_pointer_tail_element(list);

    List_pointer_t* new_element = (List_pointer_t*) calloc (1, sizeof(List_pointer_t));

    new_element->prev  = current_element;
    new_element->next  = nullptr;
    new_element->value = value;

    current_element->next = new_element;

    list->tail = new_element;

    ++(list->size);
    
    return new_element;
}

void List_pointer_delete_element(struct List_pointer* list, size_t number)
{
    assert(list != nullptr);

    List_pointer_t* current_element = List_pointer_find_element(list, number);

    if (list->size == 1)
    {
        list->head = nullptr;
        list->tail = nullptr;
    }

    else if (current_element == list->head)
    {
        list->head = List_pointer_next_element(list, current_element);
        List_pointer_next_element(list, current_element)->prev = nullptr;
    }

    else if (current_element == list->tail)
    {
        list->tail = List_pointer_prev_element(list, current_element);
        List_pointer_prev_element(list, current_element)->next = nullptr;
    } 

    else
    {
        List_pointer_prev_element(list, current_element)->next = List_pointer_next_element(list, current_element);
        List_pointer_next_element(list, current_element)->prev = List_pointer_prev_element(list, current_element);
    }
    

   current_element->next = nullptr;
   current_element->prev = nullptr;
   current_element->value = Poison;

   free(current_element);

    --(list->size);
}

List_pointer_t* List_pointer_head_element(struct List_pointer* list)
{
    assert(list != nullptr);

    return list->head;
}

List_pointer_t* List_pointer_tail_element(struct List_pointer* list)
{
    assert(list != nullptr);

    return list->tail; 
}

List_pointer_t* List_pointer_next_element(struct List_pointer* list, List_pointer_t* current_element)
{
    assert(list            != nullptr);
    assert(current_element != nullptr);

    return current_element->next;
}

List_pointer_t* List_pointer_prev_element(struct List_pointer* list, List_pointer_t* current_element)
{
    assert(list            != nullptr);
    assert(current_element != nullptr);

    return current_element->prev;
}

List_pointer_t* List_pointer_find_value(struct List_pointer* list, element_t value)
{
    assert(list != nullptr);

    List_pointer_t* current_element = List_pointer_head_element(list);

    for (size_t index = 1; index <= list->size; ++index)
    {
        if (current_element->value == value)
        {
            return current_element;
        }

        current_element = List_pointer_next_element(list, current_element);
    }

    return nullptr;
}

void List_pointer_graph(struct List_pointer* list)
{
    assert(list != nullptr);

    FILE* text = fopen("graph_pointer.dot", "w");

    fprintf(text, "digraph G {\n"            
                  "graph [bgcolor = Snow2]\n" 
                  "rankdir = LR;\n");

    List_pointer_t* current_element = List_pointer_head_element(list);
   
    for (size_t index = 1; index <= list->size; ++index)
    {   
        if (!isnan(current_element->value))
        {
           fprintf(text, "\t%lu [shape = plaintext, label =<\n"
                          "\t<table>\n"
                          "\t<tr>\n" 
                          "\t\t<td colspan=\"3\"> %lg </td>\n"
                          "\t </tr>\n"
                          "\t <tr>\n"
                          "\t\t <td> %p </td>\n"
                          "\t\t <td> %p </td>\n"
                          "\t\t <td> %p </td>\n"
                          "\t </tr>\n"
                          "\t</table>>, style = filled, color = deepskyblue2, fillcolor = lightskyblue]\n", 
                    index, current_element->value, current_element->prev, current_element, current_element->next);
        }

        else
        {
            fprintf(text, "\t%lu [shape = plaintext, label =<\n"
                          "\t<table>\n"
                          "\t<tr>\n" 
                          "\t\t<td colspan=\"3\"> %lg </td>\n"
                          "\t </tr>\n"
                          "\t <tr>\n"
                          "\t\t <td> %p </td>\n"
                          "\t\t <td> %p </td>\n"
                          "\t\t <td> %p </td>\n"
                          "\t </tr>\n"
                          "\t</table>>, style = filled, color = red,  fillcolor = lightcoral]\n", 
                    index, current_element->value, current_element->prev, current_element, current_element->next);
        }

        current_element = List_pointer_next_element(list, current_element);
    }
    
    current_element = List_pointer_head_element(list);

    for (size_t index = 1; index < list->size; ++index)
    {   
        if (!isnan(current_element->value))
        {
            if ((!isnan((List_pointer_next_element(list, current_element)->value))) && (List_pointer_next_element(list, current_element)->prev == current_element))
            {
                fprintf(text, "\t%ld -> %ld [color = deepskyblue2]; \n", index, index + 1);
                fprintf(text, "\t%ld -> %ld [color = deepskyblue2]; \n", index + 1, index);
            }

            else if  ((List_pointer_next_element(list, current_element) == nullptr) && (current_element == list->tail))
            {
                ;
            }

            else 
            {
                fprintf(text, "\t%ld -> %ld [color = darkred]; \n", index, index + 1);
                fprintf(text, "\t%ld -> %ld [color = darkred]; \n", index + 1, index);
            }
        }

        else 
        {
            fprintf(text, "\t%ld -> %ld [color = darkred]; \n", index, index + 1);
            fprintf(text, "\t%ld -> %ld [color = darkred]; \n", index + 1, index);
        }

        current_element = List_pointer_next_element(list, current_element);
    }

    fprintf(text, "\tHEAD [style = filled, color = black, fillcolor = salmon1]; \n");
    fprintf(text, "\tTAIL [style = filled, color = black, fillcolor = salmon1]; \n");
    
    fprintf(text, "\tHEAD -> %ld [color = deeppink]; \n", (list->size != 0));
    fprintf(text, "\tTAIL -> %ld [color = deeppink]; \n", list->size);

    fprintf(text, "}\n");

    fclose(text);

    system("dot -Tjpeg -ograph_pointer.jpeg graph_pointer.dot");
    system("gwenview graph_pointer.jpeg");
}
