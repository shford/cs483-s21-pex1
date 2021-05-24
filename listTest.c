#include "Queue.h"
#include <stdio.h>

/*
 * NOTE: I wrote this after I completed the PEX.
 *       Also I used a double-linked list modified off a queue data structure.
 *       so... I guess I'll just show that every function needed for this pex worked b/c
 *       i'm not sure what else to do here and it seems overkill to rewrite an entire library for tests.
 */

int main(void) {
    List list;

    char* zero = "zero";
    char* one = "one";
    char* two = "two";
    char* three = "three";

    //Init Test
    init_queue(&list, one);
    printf("init_queue test:\n");
    q_display(&list);

    /* expected output:
    one
    */

    //Enqueue test
    printf("\n");
    enqueue(&list, two);
    enqueue(&list, three);
    printf("enqueue test:\n");
    q_display(&list);

    /* expected output:
    one
    two
    three
    */

    //Dequeue test
    printf("\n");
    dequeue(&list);
    printf("dequeue test:\n");
    q_display(&list);

    /* expected output:
    two
    three
    */


    //You listed a prepend functionlity
    //I didn't need but here it is anyways I guess
    printf("\n");
    Node* newHead = init_list(zero);
    newHead->next = list.head;
    list.head->prev = newHead;
    list.head = newHead;
    list.list_size++; //added a new node
    printf("\nPrepend and q_display test:\n");
    q_display(&list);
    /* expected output:
    zero
    two
    three
     */

    //Node removal based on data
    printf("\n");
    remDuplicates(&list, "three");
    printf("\nremDuplicates test case1 - (found):\n");
    q_display(&list);
    /* expected output:
    zero
    two
    */

    //Node removal based on data when target node data not found
    printf("\n");
    remDuplicates(&list, "one\n");
    printf("\nremDuplicates test case2 - (not found):\n");
    q_display(&list);
    /* expected output:
    zero
    two
    */


    printf("\n");
    printf("history test:\n");
    nth_history(&list,2);
    /* expected output:
    2 'zero'
    1 'two'
    */

    //list deletion test
    list_delete(list.head);
    printf("List deleted successfully.\n");
}