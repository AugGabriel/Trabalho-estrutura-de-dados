#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Define an enumeration for different node types (e.g., Student or Professor).
typedef enum
{
    TYPE_TIME,
    TYPE_PARTIDA,
} NodeType;

// Define the LinkedList and ListNode data structures
typedef struct list LinkedList;    // Represents a linked list
typedef struct list_node ListNode; // Represents a node in the linked list

// Operations on the linked list

/**
 * Create an empty linked list and return a pointer to it.
 *
 * @return - A pointer to the newly created linked list.
 */
LinkedList *ll_create();

/**
 * Insert an element at the beginning of the linked list.
 *
 * @param l    - A pointer to the linked list.
 * @param info - A pointer to the data to be inserted.
 * @param type - The type of the data node (Partida or Time).
 */
void ll_insert(LinkedList *l, void *data, NodeType type);


/**
 * Append an element to the end of the linked list.
 *
 * @param l    - A pointer to the linked list.
 * @param info - A pointer to the data to be inserted.
 * @param type - The type of the data node (Partida or Time).
 */
void ll_append(LinkedList *l, void *info, NodeType type);

/**
 * Remove the first occurrence of a specific element from the linked list.
 *
 * @param l    - A pointer to the linked list.
 * @param info - A pointer to the element to be removed.
 * @return     - The position of the removed element in the list.
 */
int ll_remove(LinkedList *l, void *info);

/**
 * Remove all elements that match a specific value from the linked list.
 *
 * @param l   - A pointer to the linked list.
 * @param cpf - The CPF to match and remove.
 */
//void ll_remove_all(LinkedList *l, const char *cpf);

/**
 * Remove all elements from the linked list.
 *
 * @param l - A pointer to the linked list to be cleared.
 */
//void ll_clear(LinkedList *l);

/**
 * Get the size (number of elements) of the linked list.
 *
 * @param l - A pointer to the linked list.
 * @return  - The number of elements in the linked list.
 */
int ll_size(LinkedList *l);

/**
 * Check whether a specific element is in the linked list.
 *
 * @param l   - A pointer to the linked list.
 * @param cpf - The CPF to check for.
 * @return    - 1 if the element is in the linked list, 0 otherwise.
 */
//int ll_is_in(LinkedList *l, const char *cpf);

/**
 * Check whether the linked list is empty.
 *
 * @param l - A pointer to the linked list.
 * @return  - 1 if the linked list is empty, 0 otherwise.
 */
int ll_is_empty(LinkedList *l);

/**
 * Get the data at a specific position in the linked list.
 *
 * @param l   - A pointer to the linked list.
 * @param pos - The position of the element to retrieve.
 * @return    - A pointer to the data at the specified position.
 */
void *ll_get(LinkedList *l, int pos);

/**
 * Display all elements of the linked list.
 *
 * @param l - A pointer to the linked list to be printed.
 */
void ll_print(LinkedList *l);

/**
 * Free the memory used by the linked list.
 *
 * @param l - A pointer to the linked list to be freed.
 */
void ll_free(LinkedList *l, int apagar_informacoes);

#endif
