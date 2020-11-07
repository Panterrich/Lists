#include "Lists.h"

//================================================================================================================

int main()
{
    struct List list = {};
    LIST_CONSTUCT(&list, 20);
    // List_graph(&list);

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

    List_insert_begin(&list, 10);
    List_graph(&list);

    List_insert_before(&list, 1, 20);

    List_graph(&list);
    //List_insert_after(&list, 3, 15);
    //List_insert_end(&list, 100);

    //printf("value: %lg \n ", List_find_element(&list, 8));

    //Hack(&list);

    // List_graph(&list);

    List_clear(&list);
    List_graph(&list);

    List_destruct(&list);
}