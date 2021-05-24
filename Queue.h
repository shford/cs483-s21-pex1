/*
 * Hampton Ford
 * Purpose: Implement a stack based on the linked list library supporting operations:
 *          init_queue(), enqueue(), dequeue(), isEmptyQ(), qpeek(), q_display(),
 *          remDuplicates(), nth_history(), nth_recall()
 *
 * Last Updated 02/28/2020
 */

#pragma once

#include <stdio.h>
#include <string.h>
#include "linked_list.h"

/*
 * Purpose: Make a queue based ADT
 * @Params: List* list, char*
 * @Return: void
 */
void init_queue(List* list, char* data);

/*
 * Purpose: Push a char to the queue
 * @Params: List* tail, char*
 * @Return: void
 */
void enqueue(List* list, char* data);

/*
 * Purpose: Pop a char off the queue
 * @Params: List*
 * @Return: void
 */
void dequeue(List* list);

/*
 * Purpose: Reports if queue is empty
 * @Params: List*
 * @Return: Return 0 if queue is empty
 */
int isEmptyQ(List* list);

/*
 * Purpose: Print queue
 * @Params: List*
 * @Return: void
 */
void q_display(List* queue);

/*
 * Purpose: Let's you see the 'top' value of the queue
 * @Params: List*
 * @Return: Return char from top of list
 */
char qpeek(List* list);

/*remDuplicates
 * Purpose: Remove duplicate nodes
 * @Params: List*, char*
 * @Return: void
*/
void remDuplicates(List* list, char* word);

/*
 * Purpose: Get the nth through the last data
 * @Params: List*, int
 * @Return: void
*/
void nth_history(List* list, int n);

/*
 * Purpose: Get the n datum
 * @Params: List*, int
 * @Return: void
*/
void nth_recall(List* list, int n);