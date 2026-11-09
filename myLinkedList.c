/* This is a C Programming language project defining a linked list that lets the user add or get at the beginning (push/pop), remove items from the end, remove an item by value or index, and finally, print all the items from the list */
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
    struct node *prev;
} myNode;

// Print the linked list values
void printList(myNode *head)
{
    myNode *current = head;

    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
}

// Deletion function
int delete(myNode **head)
{
    int valueDel = -1;

    myNode *linkNode = NULL;

    if (*head == NULL) {
        return -1; // List is empty
    }

    linkNode = (*head)->next;
    valueDel = (*head)->value;

    free(*head);

    *head = linkNode;

    return valueDel;
}

// Remove by value
int removeByValue(myNode ** head, int value)
{
    myNode *previous, *current;

    if (*head == NULL) {
        return -1; // List is empty
    }

    if ((*head)->value == value) {
        return delete(head);
    }

    previous = current = (*head)->next;
    
    while (current)
    {
        if (current->value == value)
        {
            previous->next = current->next;
            free(current);

            return value;
        }

        previous = current;
        current = current->next;
    }

    return -1; // Value not found
}

int main(void)
{
    
}