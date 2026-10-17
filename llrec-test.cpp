#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------

struct is_odd {
  bool operator()(int v) const {return v %2 != 0;}
};


struct is_even {
  bool operator()(int v) const {return v %2 == 0;}
};

struct is_neg {
  bool operator()(int v) const {return v < 0;}
};

struct removeall {
  bool operator()(int) const {return true;}
};

struct removenone {
  bool operator()(int) const {return false;} 
};

struct divby {
  int d;
  divby(int divisor) : d (divisor) {}
  bool operator()(int v) const {return v % d == 0;} 
};

template <typename Comp>
void runTest(const char* filename, const char* label, Comp pred)
{
  Node* h = readList(filename);
  h = llfilter(h, pred);
  cout << label << ": ";
  print(h);
  dealloc(h);
}


int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    // Test out your linked list code
    dealloc(head);

    runTest(argv[1], "remove odds", is_odd()); 
    runTest(argv[1], "remove evens", is_even()); 
    runTest(argv[1], "remove neg", is_neg()); 
    runTest(argv[1], "remove multiples of 3", divby(3)); 
    runTest(argv[1], "remove none", removenone()); 
    runTest(argv[1], "remove all", removeall()); 

    Node* empty = llfilter(NULL, is_odd());
    cout << "filtered empty list"; 
    print (empty);

    Node* single = new Node(5, NULL);
    single = llfilter(single, is_even());
    cout << "single node (5), remove events: ";
    print (single);
    single = llfilter(single, is_odd());
    cout << "single node (5), remove odds: ";
    print (single); 
    dealloc (single);


    
    return 0;

}
