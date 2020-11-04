#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// data structures representing DLList

// data type for nodes
typedef struct DLListNode {
	int  value;  // value (int) of this list item 
	struct DLListNode *prev;
	// pointer previous node in list
	struct DLListNode *next;
	// pointer to next node in list
} DLListNode;

//data type for doubly linked lists
typedef struct DLList{
	int  size;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *last;  // last node in list
} DLList;

// create a new DLListNode
DLListNode *newDLListNode(int it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = it;
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLList
DLList *newDLList()
{
	DLList *L;

	L = malloc(sizeof (struct DLList));
	assert (L != NULL);
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

// create a DLList from a text file
DLList *CreateDLListFromFileDlist(const char *filename)
{ 
 int nodes_size;
 int nodes[100];
 const size_t line_size = 300;
 char* line = malloc(line_size);
 int i = 0;
 if(filename=="stdin"){ 
	 char line2[100];
	 while(fgets(line2,100,stdin) != NULL){
		 if( line2[0] == '\n'){
            break;
        }
        sscanf(line2,"%d",&nodes[i]); //store in the nodes array
        i++;
        
	 }

 }else {
    FILE *fp;
    
    fp = fopen(filename,"r");
	if(fp == NULL){
		printf("Cannot open file");
		exit(-1);
	}
    
    while(fgets(line,line_size,fp) != NULL){
        char *token;
        token = strtok(line," ");
        while(token != NULL){
            char *stopstring;
            long l;
            // printf("%d %d\n",atoi(token),i);
            l = strtol(token,&stopstring,10);
            if(stopstring == token){
                token = strtok(NULL," ");
                continue;
            }
            // printf("%lu\n",l);
            nodes[i] = (int) l;
            i++;
            token = strtok(NULL," "); //increment token
        }
    }
	fclose(fp);
 }
    nodes_size = i;
	i = 1;
    free(line);
    
 
	// create linked list
	DLList *l_ptr;
	l_ptr = newDLList();
	// Get first node
	DLListNode *start_node,*curr_node,*next_node;
	start_node = newDLListNode(nodes[0]);
	curr_node = start_node;
	//loop over rest of the elements
	for ( i = 1; i < nodes_size; i++){
		next_node = newDLListNode(nodes[i]);
		next_node -> prev = curr_node;
		curr_node -> next = next_node;
		curr_node = next_node; //Uodate current node
	}
	l_ptr->first = start_node;
	l_ptr->last = curr_node;
	// free(start_node); check later
	// free(next_node);
	return l_ptr;
}

// clone a DLList
// put your time complexity analysis for cloneList() here
DLList *cloneList(DLList *u)
{
 DLList *cl;
 cl = newDLList();
 DLListNode *current = u->first,*curr_node = NULL,*next_node = NULL;
 while(current != NULL){
     if(curr_node == NULL){ //just for the first node
        curr_node = newDLListNode(current->value);
        next_node = curr_node;
        cl->first = curr_node;
     }
     else {
         next_node->next = newDLListNode(current->value); //create next node for new list
         next_node = next_node->next;
         next_node->prev = curr_node; //for the new node
         curr_node->next = next_node; //for node in previous   
         curr_node = curr_node->next;
     }
     current = current->next;
 }
 cl->last = next_node;
 return cl;
}

// compute the union of two DLLists u and v
//O(mn)
DLList *setUnion(DLList *u, DLList *v)
{
 	DLList *l;
    l = newDLList();
    l = cloneList(u);
    int insert = 1; 
    DLListNode *current,*prev_node = l->last,*next_node = v->first,*new_node;
    while(next_node != NULL){
    	current = u->first;
        while(current != NULL){ //loop over the first list
            if ( next_node-> value == current->value){ //If element is present in both 
                insert = 0;
        	    break;
            }
            current = current->next;
        }
        if (insert == 0){ //if element is already there in the first list
            insert = 1; //reset
            next_node = next_node->next;
            continue;
        }
        else {
            new_node = newDLListNode(next_node->value);
            new_node->next = NULL;
            new_node->prev = l->last;
            l->last->next = new_node;
            l->last = new_node;
            next_node = next_node->next;
        }
    }
    l->last = new_node;
    return l;
}

// compute the insection of two DLLists u and v
//O(mn)
DLList *setIntersection(DLList *u, DLList *v)
{
  DLList *l;
  l = newDLList();
  DLListNode *current_u = u->first,*start = NULL,*next;
  //Loop over both elements ,if an element is present in both, it is inserted in the new list.
  while(current_u != NULL){ 
	  DLListNode *current_v = v->first;
	  while(current_v != NULL){
		  if(current_u->value == current_v->value){ //insert element
			  if(start == NULL){
				next = newDLListNode(current_u->value);
				l->first = next;
				start = next;
			  }
			  else{
				  next = newDLListNode(current_u->value);
				  start->next = next;
				  next->prev = start;
				  start = next;
			  }
		  }
		  current_v = current_v->next;//go to the next element
	  }
	  current_u = current_u->next;
  }
  l->last = next;
  return l;
}

// free up all space associated with list
// put your time complexity analysis for freeDLList() here
void freeDLList(DLList *L)
{
	DLListNode *node,*temp;
	node = L->first;
	while(node != NULL){
		temp = node;
		free(temp);
		node = node->next;
	}
}


// display items of a DLList
// put your time complexity analysis for printDDList() here
void printDLList(DLList *u)
{
 DLListNode *node;
 node = u->first;
//  Loop terminates when last node is accessed
 while(node->next != NULL){
	printf("%d\n",node->value);
	node = node->next;
 }
 printf("%d\n\n",u->last->value);
}

int main()
{
 DLList *list1, *list2, *list3, *list4,*list5;

 list1=CreateDLListFromFileDlist("File1.txt");
 printDLList(list1);

 list2=CreateDLListFromFileDlist("File2.txt");
 printDLList(list2);

 list3=setUnion(list1, list2);
 printDLList(list3);

 list4=setIntersection(list1, list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 printf("please type all the integers of list1\n");
 list1=CreateDLListFromFileDlist("stdin");
 
 printf("please type all the integers of list2\n");
 list2=CreateDLListFromFileDlist("stdin");

 list3=cloneList(list1);
 printDLList(list3);
 list4=cloneList(list2);
 printDLList(list4);

list5=setIntersection(list3,list4);
printDLList(list5);
 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 return 0; 
}
