# CS 111 - C Programming language - User-Defined Linked List

This is the assignment for the CS 111 course from Study.com. This assignment implements a singly linked list data structure.

The program provides functions to insert, remove, search, traverse, and display list elements, as well as import and export values using text files.

Each node contains a positive integer value and a pointer to the next node, if any, or a pointer to NULL.

## Included in this project

- `README.md` the current file
- `main.c` program file
- `example.txt` text file used for testing the inputFromFile() function.

## Features

- **Push / Pop:** Add or remove nodes at the beginning of the list.
- **Remove:** Delete nodes by index, value, or from the end of the list.
- **Search:** Find a value and return its index.
- **Print:** Display all values in the list.
- **File I/O:** Import and export list values using text files.

## Instructions (Windows)

Using GCC, compile the program from the project's root directory:

```bash
gcc main.c -o main.exe
```

Run the program in Windows PowerShell:

```powershell
.\main.exe
```

### The program provides an interactive menu to perform the various linked-list operations.

```powershell
===== Linked List Manager =====
1. Push value
2. Pop value
3. Remove last value
4. Remove by index
5. Remove by value
6. Search by value
7. Print list
8. Import from file
9. Export to file
0. Exit
Choice: 
```

## Example Usage

Here are some lines I used for testing:

```c
myNode *myNodeList = NULL;

// Build the linked list
push(&myNodeList, 10);
push(&myNodeList, 15);
push(&myNodeList, 25);
push(&myNodeList, 1);
push(&myNodeList, 5);

printList(myNodeList);

// Remove values
printf("Popped: %d\n", pop(&myNodeList));
printf("Removed by value: %d\n", removeByValue(&myNodeList, 25));
printf("Removed from end: %d\n", removeFromEnd(&myNodeList));
printf("Removed by index: %d\n", removeByIndex(&myNodeList, 1));

// Search for a value
printf("Index of 15: %d\n", searchByValue(myNodeList, 15));

// Import and export values
inputFromFile(&myNodeList, "example.txt");
outputToFile(myNodeList, "output.txt");
```

## AI use disclosure

- ChatGPT has been used for bouncing ideas during the building of the solution.
- It has also been used to provide feedback and suggestions on things to improve in the code.
- Finally it has been used to help write some of the readme documentation as well as some boilerplate for the main function's menu.