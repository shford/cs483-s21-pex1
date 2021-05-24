/*
* Hampton Ford
* Purpose: Implement a doubly linked list library supporting operations:
* init(), append(), prepend(), remNode(), insertAfter(), traverseList(), list_delete()
* Last Updated 02/23/2020
*/

#pragma once

#define MAX_NODE_DATA_LEN 60

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node_type{
    char data[MAX_NODE_DATA_LEN];
    struct Node_type* next;
    struct Node_type* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int list_size;
} List;

/*
 * Purpose: Allocate the first node in a list
 * @Params: char* to assign to .data element
 * @Return: Return a pointer to new Node (error check in main)
*/
Node* init_list(char* data);

/*
 * Purpose: Add another node to the 'end' of the list
* @Params: Node*, char*
* @Return: Address to new node
*/
Node* append(Node* last_Node, char* newData);

/*
 * Purpose: Remove a node from the given list
 * @Params: tail or head element of List to remove
 * @Return: void
*/
void remNode(Node* end_Node);

/*
 * Purpose: Print all values in list in order
 * @Params: Node* list_head
 * @Return: Return 0 on success and -1 on failure
*/
int list_traverse(Node* list_head);

/*
 * Purpose: Print all values in list in reverse order
 * @Params: Node* list_tail
 * @Return: Return 0 on success and -1 on failure
*/
int list_rev_traverse(Node* list_tail);

/*
 * Purpose: Delete a list
 * @Params: Node* list_head
 * @Return: void
*/
void list_delete(Node* list_head);