#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
  // base case 
  if (head == NULL)
  {
    smaller = NULL;
    larger = NULL;
    return;  
  }

  Node*current = head;
  Node* rest = head -> next; 
  head = NULL;
  current->next = NULL; 

  llpivot(rest, smaller, larger, pivot);

  if (current->val <= pivot){
    current -> next = smaller;
    smaller = current; 
  }

  else {
    current -> next = larger;
    larger = current; 
  }
}