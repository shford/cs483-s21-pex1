/*
 * Hampton Ford
 * Purpose: Implement a stack based on the linked list library supporting operations:
 *          init_queue(), enqueue(), dequeue(), isEmptyQ(), qpeek(), q_display(),
 *          remDuplicates(), nth_history(), nth_recall()
 *
 * Last Updated 02/28/2020
 */

#include "Queue.h"

/*
Usage:
    List list;
    init_queue(&list,'h');
    enqueue('t', &list);
    printf("%c", dequeue(&list));
    printf("%c", dequeue(&list));
*/

/*
 * Purpose: Make a queue based ADT
 * @Params: List* , char*
 * @Return: void
 */
void init_queue(List* list, char* data) {
    list->head = init_list(data);
    //List elements head and tail are the same for list with only 1 Node (size 1)
    list->tail = list->head;
    list->list_size = 1;
}

/*
 * Purpose: Push a char to the queue
 * @Params: List* tail, char*
 * @Return: void
 */
void enqueue(List* list, char* data) {
    if (list->head == NULL) {
        printf("Queue does not exist.");
        exit(1);
    }
    list->tail = append(list->tail, data);
    list->list_size++;
}

/*
 * Purpose: Pop a char off the queue
 * @Params: List*
 * @Return: void
 */
void dequeue(List* list) {
    if (list->list_size == 0) { //nothing left in list
        printf("\nQueue is empty\n");
        exit(1);
    }
    char data;
    Node* newHead;

    //Special case when one node left
    if (list->head == list->tail) {
        newHead = NULL;
    } else {
        newHead = list->head->next;
    }

    remNode(list->head); //see CS220 PEX3 for original version

    list->head = newHead;
    list->list_size--;
}

/*
 * Purpose: Reports if queue is empty
 * @Params: List*
 * @Return: Return 0 if queue is empty
 */
int isEmptyQ(List* list) {
    if (list->list_size == 0) { //nothing left in list
        return 0;
    }
    else {
        return 1;
    }
}

/*
 * Purpose: Print queue
 * @Params: List*
 * @Return: void
 */
void q_display(List* queue) {
    list_traverse(queue->head);
}

/*
 * Purpose: Let's you see the 'top' value of the queue
 * @Params: List*
 * @Return: Return char from top of list
 */
char qpeek(List* list) {
    if (list->list_size != 0) { //list not empty
        return list->head->data;
    }
    else {
        printf("Can't peek into empty queue.");
        exit(1);
    }
}

/*
 * Purpose: Remove duplicate nodes
 * @Params: List*, char*
 * @Return: void
*/
void remDuplicates(List* list, char* word) {
    Node* tmpNode = list->head;
    while (tmpNode != NULL) {
        //if duplicate then delete original node
        if (strstr(tmpNode->data, word) != NULL) { //command was used
            //delete duplicate node (automatically reassigns next and prev)
            if (tmpNode->next == NULL) { //reassign tail b/c we're gonna delete that node
                list->tail = tmpNode->prev;
            }
            remNode(tmpNode);
            list->list_size--;
            break;
        }
        if (tmpNode->next != NULL) {
            tmpNode = tmpNode->next;
        }
        else {
            tmpNode = NULL;
        }

    }
}

/*
 * Purpose: Get the nth through the last data
 * @Params: List*, int
 * @Return: void
*/
void nth_history(List* list, int n) {
    Node* tmpNode = list->head;
    //just go through first list-size-n 'th nodes w/out printing
    for (int i = 0; i < (list->list_size - n); ++i) {
        tmpNode = tmpNode->next;
    }
    for (int i = 0; i < n; ++i) {
        printf("%d '%s'\n", n-i, tmpNode->data);
        tmpNode = tmpNode->next;
    }
}

/*
 * Purpose: Get the n datum
 * @Params: List*, int
 * @Return: void
*/
void nth_recall(List* list, int n) {
    Node* tmpNode = list->head;
    //just go through first list-size-n 'th nodes w/out printing
    for (int i = 0; i < (list->list_size - n); ++i) {
        tmpNode = tmpNode->next;
    }
    printf("%d '%s'\n", list->list_size - n - 1, tmpNode->prev->data); //compensate for itself
}