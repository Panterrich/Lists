#include "Lists.h"

//================================================================================================================

int main()
{
    struct List list = {};
    LIST_CONSTRUCT(&list, 20);
    List_graph(&list);

    // FILE* test = fopen("Unit_test.txt", "r");

    // for (int i = 1; i <= 20; ++i)
    // {
    //     fscanf(test, "%lg %lu %lu", &(list.data)[i].value, &(list.data)[i].next, &(list.data)[i].prev);
    // }
    
    // list.head = 1;
    // list.tail = 20;
    // list.size = 20;
    // list.first_free = 0;

    // fclose(test);

    List_insert_before(&list, 10, 10);
    List_graph(&list);

    // List_insert_after(&list, 1, 20);
    // List_graph(&list);

    // List_insert_before(&list, 1, 0);
    // List_graph(&list);

    // List_delete_element(&list, 2);
    // List_graph(&list); 
    // List_insert_before(&list, 1, 10);
    // List_graph(&list);

    // List_insert_after(&list, 1, 20);
    // List_graph(&list);

    // List_insert_before(&list, 1, 0);
    // List_graph(&list);

    // List_delete_element(&list, 2);
    // List_graph(&list);
    // List_sorted(&list);
    // List_graph(&list);
    // List_insert_before(&list, 1, 20);

    // List_graph(&list);
    // List_insert_after(&list, 3, 15);
    // List_insert_end(&list, 100);

    // // // //printf("value: %lg \n ", List_find_element(&list, 8));

    // // // //Hack(&list);

    // List_graph(&list);

    // List_clear(&list);
    // List_graph(&list);

    List_destruct(&list);
}