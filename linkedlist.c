#include "linkedlist.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>

// Define a structure for the linked list.
struct list
{
    int count;       // Number of elements in the linked list.
    ListNode *first; // A pointer to the first node in the linked list.
};

// Define a structure for a node in the linked list.
struct list_node
{
    NodeType type;
    void *info;     // Data associated with the node (generic pointer).
    ListNode *next; // A pointer to the next node in the linked list.
};

// Create an empty linked list and return a pointer to it.
LinkedList *ll_create()
{
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
    l->first = NULL;
    l->count = 0;
    return l;
}

// Get the number of elements in the linked list.
int ll_size(LinkedList *l)
{
    return l->count;
}

// Check whether the linked list is empty.
int ll_is_empty(LinkedList *l)
{
    return ll_size(l) == 0;
}

// Insert an element at the beginning of the linked list.
void ll_insert(LinkedList *l, void *info, NodeType type)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->type = type;
    node->info = info;
    node->next = l->first;

    l->first = node;
    l->count++;
}

void *ll_get(LinkedList *l, int pos) {
    int i = 0;    
    ListNode *node = l->first;
    while (node != NULL) {
        if (i == pos)
            return node->info;
        node = node->next;
        i++;
    }
    perror("Posição fora dos limites da LinkedList.");
    exit(EXIT_FAILURE);
}

// Display all elements of the linked list.
void ll_print(LinkedList *l) {
    int cabecalho = 1;
    for (ListNode *p = l->first; p != NULL; p = p->next) {
        if (p->type == TYPE_TIME) {
            if (cabecalho) {
                printf("%s\t%9s\t\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
                cabecalho = 0;
            }
            time_print(p->info); // Print the information of each Student structure.
        }
    }
    printf("\n"); // Print a newline character to separate the output.
}

// Function to free the memory used by the linked list.
void ll_free(LinkedList *l)
{
    ListNode *p = l->first;
    while (p != NULL)
    {
        ListNode *t = p->next; // Store a reference to the next node.
        free(p);               // Free the memory allocated for the current node.
        p = t;                 // Move to the next node.
    }
    free(l); // Free the memory allocated for the list structure itself.
}
