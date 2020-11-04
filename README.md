# Doubly-linked-list
### Data Structures and Algorithms. 
## Implemented doubly linked list and set of functions based on doubly linked list.

## A short description of implemented functions
1. DLList *CreateDLListFromFileDlist(const char *filename). This function creates a doubly linked list of integers by reading all integers from a text file named filename, and returns a pointer to the doubly linked list created.
2. void printDLList(DLList *u ). This function prints all the elements (integers) of a doubly linked list pointed by u in the order they appear in the list on the standard output, one element per line.
3. DLList *cloneList(DLList *u). This function creates an identical copy of a doubly linked list u and returns a pointer to the list cloned.
4. DLList *setUnion(DLList *u, DLList *v). This function computes the union of the two sets of integers that are stored in the doubly linked lists pointed by u and v, respectively, and returns a pointer to the doubly linked list that stores the union.
5. DLList *setIntersection(DLList *u, DLList *v). This function computes the intersection of the two sets of integers that are stored in the doubly linked lists pointed by u and v, respectively, and returns a pointer to the doubly linked list that stores the intersection.
6. void freeDLList(DLList *u). This function frees the space occupied by all the nodes of the doubly linked list pointed by u.
