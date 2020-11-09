#include "Lists_pointer.h"

int main()
{
    struct List_pointer list = {};
    LIST_POINTER_CONSTRUCT(&list);

    List_pointer_insert_before(&list, 5, 20);
    List_pointer_insert_after(&list, 1, 30);

    List_pointer_graph(&list);

    List_pointer_insert_before(&list, 2, 15);

    List_pointer_insert_begin(&list, 0);

    List_pointer_insert_end(&list, 100);
    List_pointer_graph(&list);
    
    List_pointer_insert_after(&list, 4, 30);
    List_pointer_graph(&list);

    List_pointer_insert_after(&list, 3, 30);
    List_pointer_graph(&list);

    List_pointer_delete_element(&list, 5);
    
    List_pointer_graph(&list);

    List_pointer_destruct(&list);
}
