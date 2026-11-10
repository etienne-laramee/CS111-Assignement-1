/* This is a C Programming language project defining a linked list that lets the user add or get at the beginning (push/pop), remove items from the end, remove an item by value or index, and finally, print all the items from the list */
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int value;
    struct node *next;
} myNode;

// Print the linked list values
void printList(myNode *head)
{
    myNode *current = head;

    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }

    printf("\n");
}

/* Search by value, return index
    Return the index if found, otherwise return -1
*/
int searchByValue(const myNode *head, int value)
{
    const myNode *current = head;
    int index = 0;

    // Cycle through the list and check each value.
    // If the value matches the queried value, return the index.
    while (current != NULL)
    {
        if (current->value == value)
        {
            return index;
        }

        index++;
        current = current->next;
    }

    // Otherwise after we reach the end of the list, return -1.
    return -1;
}

/* Remove from the beginning of the list
    Return the value if found and removed, otherwise return -1
*/
int pop(myNode **head)
{
    // List is empty
    if (*head == NULL)
    {
        return -1;
    }

    int value = -1;
    myNode *tempNode = NULL;

    tempNode = (*head)->next;
    value = (*head)->value;

    free(*head);

    *head = tempNode;

    return value;
}

/* Push at head
    Return the value of the newly inserted node
*/
int push(myNode **head, int value)
{
    myNode *newNode = malloc(sizeof(myNode));

    // malloc failed
    if (newNode == NULL)
    {
        return -1;
    }

    // Set the value
    newNode->value = value;

    // Set current head to be the second node instead
    newNode->next = *head;

    // New head is the newly created node
    *head = newNode;

    return newNode->value;
}

/* Remove from the end of the list
    Returns the removed node value, or -1 if list is empty
*/
int removeFromEnd(myNode **head)
{
    // List is empty
    if (*head == NULL)
    {
        return -1;
    }

    // List contains only one element
    if ((*head)->next == NULL)
    {
        return pop(head);
    }

    myNode *current, *previous;
    current = previous = *head;

    // Cycle through the list.
    // When the current node's next pointer is NULL, remove current node.
    while (current != NULL)
    {
        if (current->next != NULL)
        {
            previous = current;
            current = current->next;
        } else {
            int value = current->value;

            // Remove last node
            free(current);

            // Remove the previous reference to the last node
            previous->next = NULL;

            return value;
        }
    }

    // Just in case. Should not happen.
    return -1;
}

/* Remove by index (zero based)
    Returns the value if found and removed, otherwise returns -1 
*/
int removeByIndex(myNode **head, int index)
{
    myNode *previous, *current;
    int counter = 0;

    // List is empty
    if (*head == NULL)
    {
        return -1;
    }

    // Case where the head is to be removed
    if (index == 0)
    {
        return pop(head);
    }

    previous = current = *head;

    while (counter <= index && current)
    {
        if (counter == index)
        {
            int value = current->value;
            previous->next = current->next;
            free(current);
            return value;
        }

        previous = current;
        current = current->next;
        counter++;
    }

    return -1; // Node not found, or index out of bounds
}

/* Remove by value
   Returns the value if found and removed, otherwise returns -1 
*/
int removeByValue(myNode ** head, int value)
{
    myNode *previous, *current;

    // List is empty
    if (*head == NULL) {
        return -1;
    }

    // Case where the head is to be removed
    if ((*head)->value == value) {
        return pop(head); // Remove head node
    }

    previous = current = *head;
    
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

    return -1; // Node not found
}

/* Input by file
    Return 0 if successful, -1 otherwise
*/
int inputFromFile(myNode **head, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return -1; // Failed to open file
    }

    // Read each line. Each line should contain one value.
    // For each integer value, create a new node and push it into the list.
    int value;
    while (fscanf(file, "%d", &value) == 1)
    {
        // Skip negative values
        if (value < 0)
        {
            continue;
        }

        // Push value to the list. on failure, close the file and return -1.
        if (push(head, value) == -1)
        {
            fclose(file);
            return -1; // Failed to push value into the list
        }
    }

    fclose(file);
    return 0; // Success. All file values added to the list
}

/* Output to file
    Return 0 if successful, -1 otherwise
*/
int outputToFile(const myNode *head, const char *filename)
{
    FILE *file = fopen(filename, "w");

    // Failed to open file
    if (file == NULL)
    {
        return -1;
    }

    // Go trough list and write each value to the file, one per line.
    const myNode *current = head;
    while (current != NULL)
    {
        fprintf(file, "%d\n", current->value);
        current = current->next;
    }

    fclose(file);
    return 0; // Success
}

int main(void)
{
    myNode *myNodeList = NULL;
    int choice, value, result;
    char filename[256];

    while (1)
    {
        printf("\n===== Linked List Manager =====\n");
        printf("1. Push value\n");
        printf("2. Pop value\n");
        printf("3. Remove last value\n");
        printf("4. Remove by index\n");
        printf("5. Remove by value\n");
        printf("6. Search by value\n");
        printf("7. Print list\n");
        printf("8. Import from file\n");
        printf("9. Export to file\n");
        printf("0. Exit\n");
        printf("Choice: ");

        // Read menu choice
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");

            // Clear invalid input
            while (getchar() != '\n')
            {
            }
            continue;
        }

        if (choice == 0)
        {
            break;
        }

        // Ask for an integer when required
        if (choice == 1 || choice == 4 ||
            choice == 5 || choice == 6)
        {
            printf(choice == 4 ? "Enter index: " : "Enter value: ");

            if (scanf("%d", &value) != 1 || value < 0)
            {
                printf("Invalid input. Enter a non-negative integer.\n");
                while (getchar() != '\n')
                {
                }
                continue;
            }
        }

        switch (choice)
        {
        case 1:
            result = push(&myNodeList, value);
            printf(result == -1 ? "Failed to add value.\n"
                                : "Value added.\n");
            break;

        case 2:
            result = pop(&myNodeList);
            if (result == -1)
                printf("List is empty.\n");
            else
                printf("Removed: %d\n", result);
            break;

        case 3:
            result = removeFromEnd(&myNodeList);
            if (result == -1)
                printf("List is empty.\n");
            else
                printf("Removed: %d\n", result);
            break;

        case 4:
            result = removeByIndex(&myNodeList, value);
            if (result == -1)
                printf("Index not found.\n");
            else
                printf("Removed: %d\n", result);
            break;

        case 5:
            result = removeByValue(&myNodeList, value);
            if (result == -1)
                printf("Value not found.\n");
            else
                printf("Removed: %d\n", result);
            break;

        case 6:
            result = searchByValue(myNodeList, value);
            if (result == -1)
                printf("Value not found.\n");
            else
                printf("Found at index: %d\n", result);
            break;

        case 7:
            printf("List: ");
            printList(myNodeList);
            break;

        case 8:
        case 9:
            printf("Enter filename: ");
            if (scanf("%255s", filename) != 1)
            {
                printf("Invalid filename.\n");
                break;
            }

            if (choice == 8)
                result = inputFromFile(&myNodeList, filename);
            else
                result = outputToFile(myNodeList, filename);

            printf(result == 0 ? "File operation successful.\n"
                                : "File operation failed.\n");
            break;

        default:
            printf("Invalid choice.\n");
            break;
        }
    }

    // Free all remaining nodes before exiting
    while (myNodeList != NULL)
    {
        pop(&myNodeList);
    }

    printf("Goodbye.\n");
    return 0;
}