/* Name and surname: David Tsofin

INSTRUCTIONS:
(1) Implement functions to meet the description provided at their declarations.
(2) All implementation must be in this single source file.
(3) Submit only this source file (with completed solutions).
(4) The program must be compilable.
(5) Global and static variables are forbidden.
(6) Do NOT change the function declarations (names, return types, or parameter
types/count). Do NOT change the provided data types or existing helper functions
(unless stated otherwise). (7) You may add helper functions or data types if
needed. (8) Test your solution (in the 'main' function and with any added
helpers or types). However, test code is not graded. (9) The 'main' function
must be at the end of the source code.
*/

#include <cstring>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATA TYPES
//-------------------------------------------------------------------------------------------------

// Node of a linked list
struct Node
{
  int data;   // value of the node
  Node *next; // pointer to the next node in the list
};

// Linked list
struct List
{
  Node *first; // pointer to the first node in the list
};

//-------------------------------------------------------------------------------------------------
// TASK 1 (0.8 points)
//-------------------------------------------------------------------------------------------------

/*
Function sorts array 'data' in descending order using the insertion sort
algorithm. PARAMETERS: [in, out] data - array to be sorted [in] length - number
of elements in the array INPUT CONDITIONS:
- 'length' can have any value
- 'data' points to a valid array
EXAMPLES:
(1, 3, 2) -> (3, 2, 1)
(1, 2, 2, 1) -> (2, 2, 1, 1)
(5) -> (5)
() -> ()
*/
void insertionSort(int *data, const size_t length)
{
  for (size_t i = 1; i < length; ++i)
  {
    int val = data[i];
    int j = i - 1;

    while (j >= 0 && data[j] < val)
    {
      data[j + 1] = data[j];
      j = j - 1;
    }

    data[j + 1] = val;
  }
}

//-------------------------------------------------------------------------------------------------
// TASK 2 (0.8 points)
//-------------------------------------------------------------------------------------------------

/*
Function sorts text strings in array 'data' in descending lexicographical order.
Rearrange the pointers in the array. Use insertion sort.
PARAMETERS:
[in, out] data - array to sort. It contains pointers to null-terminated strings.
                 The last pointer is 'nullptr', indicating the end.
INPUT CONDITIONS:
- 'data' contains at least one pointer
- The last pointer is 'nullptr'
EXAMPLES:
("Juraj", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", nullptr)
("Juraj", "Anabela", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej",
"Anabela", nullptr)
("Andrej", "Juraj", "Andrej", nullptr) -> ("Juraj", "Andrej", "Andrej", nullptr)
("Andrej", nullptr) -> ("Andrej", nullptr)
(nullptr) -> (nullptr)
NOTE:
To test, you can declare: `const char *names[] = {"Juraj", "Peter", "Andrej",
nullptr};` Use appropriate standard library function to compare string contents.
*/
void insertionSort(const char *data[])
{
  if (data[0] == nullptr)
  {
    return;
  }

  for (size_t i = 1; data[i] != nullptr; ++i)
  {
    const char *val = data[i];
    int j = i - 1;

    while (j >= 0 && strcmp(data[j], val) < 0)
    {
      data[j + 1] = data[j];
      j = j - 1;
    }

    data[j + 1] = val;
  }
}

//-------------------------------------------------------------------------------------------------
// TASK 3 (0.8 points)
//-------------------------------------------------------------------------------------------------

/*
Function sorts linked list 'list' in descending order.
Rearrange nodes (do not copy data). Use insertion sort.
PARAMETERS:
[in, out] list - linked list to sort
INPUT CONDITIONS:
- 'list' contains any number of nodes (may be empty)
- 'list' is not nullptr
EXAMPLES:
input: 2->1->3   output: 3->2->1
input: 1->2->2->1  output: 2->2->1->1
input: empty list  output: empty list
*/
void insertionSort(List *list)
{
  if (!list->first)
  {
    return;
  }

  if (!list->first->next)
  {
    return;
  }

  Node *head = nullptr;

  while (list->first != nullptr)
  {
    Node *current = list->first;
    list->first = list->first->next;

    if (head == nullptr || current->data > head->data)
    {

      current->next = head;
      head = current;
    }
    else
    {
      Node *p = head;
      while (p != NULL)
      {
        if (p->next == nullptr ||
            current->data > p->next->data)
        {
          current->next = p->next;
          p->next = current;
          break;
        }
        p = p->next;
      }
    }
  }

  list->first = head;
}

//-------------------------------------------------------------------------------------------------
// TASK 4 (0.8 points)
//-------------------------------------------------------------------------------------------------

/*
Function performs merge step of merge sort algorithm.
It merges two neighboring sorted parts of array 'input' into 'output'.
Sorting is in descending order.
PARAMETERS:
[out] output - output array; section output[low]...output[high-1] will be sorted
[in] input - input array; sections input[low]...input[middle-1] and
input[middle]...input[high-1] are sorted in descending order [in] low - index of
first element of left part [in] middle - index of first element of right part
[in] high - index after last element of right part
OUTPUT CONDITIONS:
- 'input' remains unchanged
- output[low]...output[high-1] contains sorted elements from
input[low]...input[high-1]
- Elements before 'low' and from 'high' onward are unchanged
EXAMPLE:
low: 4   middle: 8   high: 12
input: (10, 10, 10, 10, 7, 5, 2, 0, 8, 4, 2, 1, 10, 10, 10, 10)
output before: (20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20)
output after : (20, 20, 20, 20, 8, 7, 5, 4, 2, 2, 1, 0, 20, 20, 20, 20)
*/
void mergeNeighbours(int *output, const int *input, const size_t low,
                     const size_t middle, const size_t high)
{
  size_t i = low;
  size_t j = middle;
  size_t k = low;

  while (i < middle && j < high)
  {
    if (input[i] >= input[j])
    {
      output[k++] = input[i++];
    }
    else
    {
      output[k++] = input[j++];
    }
  }

  while (i < middle)
  {
    output[k++] = input[i++];
  }

  while (j < high)
  {
    output[k++] = input[j++];
  }
}

//-------------------------------------------------------------------------------------------------
// TASK 5 (0.8 points)
//-------------------------------------------------------------------------------------------------

/*
Function sorts array 'data' in descending order using merge sort algorithm.
Create one auxiliary array using new[] and delete[].
PARAMETERS:
[in, out] data - array to sort
[in] length - number of elements in array
INPUT CONDITIONS:
- 'data' points to a valid array
EXAMPLES:
(1, 3, 2) -> (3, 2, 1)
(1, 2, 2, 1) -> (2, 2, 1, 1)
(5) -> (5)
() -> ()
NOTE:
If using top-down approach:
- Allocate and copy data in this function
- Implement recursive function to handle merge sort logic
*/
void mergeSortRecursive(int input[], int output[], int low, int high)
{
  if (high - low <= 1)
  {
    return;
  }

  size_t middle = (low + high) / 2;

  mergeSortRecursive(output, input, low, middle);
  mergeSortRecursive(output, input, middle, high);

  mergeNeighbours(output, input, low, middle, high);
}

void mergeSort(int *data, const size_t length)
{
  if (length <= 1)
  {
    return;
  }

  int *temp = new int[length];

  for (size_t i = 0; i < length; ++i)
  {
    temp[i] = data[i];
  }

  mergeSortRecursive(temp, data, 0, length);

  delete[] temp;
}

//-------------------------------------------------------------------------------------------------
// TESTING HELPERS
//-------------------------------------------------------------------------------------------------
void printArray(const int *data, size_t length)
{
  for (size_t i = 0; i < length; ++i)
  {
    cout << data[i];
    if (i != length - 1)
      cout << ", ";
  }
  cout << endl;
}

void printCStringArray(const char *data[])
{
  if (data[0] == nullptr)
  {
    cout << "nullptr" << endl;
    return;
  }

  for (size_t i = 0; data[i] != nullptr; ++i)
  {
    cout << data[i];
    if (data[i + 1] != nullptr)
      cout << ", ";
  }
  cout << endl;
}

void printList(const List &list)
{
  if (list.first == nullptr)
  {
    cout << "empty list" << endl;
  }

  Node *current = list.first;
  while (current != nullptr)
  {
    cout << current->data;
    if (current->next != nullptr)
      cout << " -> ";
    current = current->next;
  }
  cout << endl;
}

void deleteList(List &list)
{
  Node *current = list.first;
  while (current)
  {
    Node *next = current->next;
    delete current;
    current = next;
  }
  list.first = nullptr;
}

//-------------------------------------------------------------------------------------------------
// MAIN FUNCTION
//-------------------------------------------------------------------------------------------------

int main()
{
  //==============================================
  // TASK 1 - insertionSort (integers)
  //==============================================
  cout << "==================== Task 1 ====================" << endl;

  int t1_1[] = {3, 1, 2};
  cout << "Test 1\nfunc insertionSort\ninput: ";
  printArray(t1_1, 3);
  insertionSort(t1_1, 3);
  cout << "output (expected): 3, 2, 1\nresult: ";
  printArray(t1_1, 3);
  cout << endl;

  int t1_2[] = {1, 2, 2, 1};
  cout << "Test 2\nfunc insertionSort\ninput: ";
  printArray(t1_2, 4);
  insertionSort(t1_2, 4);
  cout << "output (expected): 2, 2, 1, 1\nresult: ";
  printArray(t1_2, 4);
  cout << endl;

  int t1_3[] = {5};
  cout << "Test 3\nfunc insertionSort\ninput: ";
  printArray(t1_3, 1);
  insertionSort(t1_3, 1);
  cout << "output (expected): 5\nresult: ";
  printArray(t1_3, 1);
  cout << "\n\n";

  //==============================================
  // TASK 2 - insertionSort (strings)
  //==============================================
  cout << "==================== Task 2 ====================" << endl;

  const char *t2_1[] = {"Juraj", "Peter", "Andrej", nullptr};
  cout << "Test 1\nfunc insertionSort\ninput: ";
  printCStringArray(t2_1);
  insertionSort(t2_1);
  cout << "output (expected): Peter, Juraj, Andrej\nresult: ";
  printCStringArray(t2_1);
  cout << endl;

  const char *t2_2[] = {"Juraj", "Anabela", "Peter", "Andrej", nullptr};
  cout << "Test 2\nfunc insertionSort\ninput: ";
  printCStringArray(t2_2);
  insertionSort(t2_2);
  cout << "output (expected): Peter, Juraj, Andrej, Anabela\nresult: ";
  printCStringArray(t2_2);
  cout << endl;

  const char *t2_3[] = {"Andrej", "Juraj", "Andrej", nullptr};
  cout << "Test 3\nfunc insertionSort\ninput: ";
  printCStringArray(t2_3);
  insertionSort(t2_3);
  cout << "output (expected): Juraj, Andrej, Andrej\nresult: ";
  printCStringArray(t2_3);
  cout << "\n\n";

  cout << "Test 4\nfunc insertionSort\ninput: nullptr only\n";
  const char *t2_4[] = {nullptr};
  insertionSort(t2_4);
  cout << "output (expected): nullptr only\nresult: ";
  printCStringArray(t2_4);
  cout << endl;

  //==============================================
  // TASK 3 - insertionSort (linked list)
  //==============================================
  cout << "==================== Task 3 ====================" << endl;

  // Test 1
  List l3_1{nullptr};
  Node *n11 = new Node{2, nullptr};
  Node *n12 = new Node{1, nullptr};
  Node *n13 = new Node{3, nullptr};
  n11->next = n12;
  n12->next = n13;
  l3_1.first = n11;
  cout << "Test 1\nfunc insertionSort\ninput: ";
  printList(l3_1);
  insertionSort(&l3_1);
  cout << "output (expected): 3 -> 2 -> 1\nresult: ";
  printList(l3_1);
  deleteList(l3_1);
  cout << endl;

  // Test 2
  List l3_2{nullptr};
  Node *n21 = new Node{1, nullptr};
  Node *n22 = new Node{2, nullptr};
  Node *n23 = new Node{2, nullptr};
  Node *n24 = new Node{1, nullptr};
  n21->next = n22;
  n22->next = n23;
  n23->next = n24;
  l3_2.first = n21;
  cout << "Test 2\nfunc insertionSort\ninput: ";
  printList(l3_2);
  insertionSort(&l3_2);
  cout << "output (expected): 2 -> 2 -> 1 -> 1\nresult: ";
  printList(l3_2);
  deleteList(l3_2);
  cout << endl;

  // Test 3 - empty list
  List l3_3{nullptr};
  cout << "Test 3\nfunc insertionSort\ninput: empty list\n";
  insertionSort(&l3_3);
  cout << "output (expected): empty list\nresult: ";
  printList(l3_3);
  cout << "\n\n";

  //==============================================
  // TASK 4 - mergeNeighbours
  //==============================================
  cout << "==================== Task 4 ====================" << endl;

  // Test 1
  const int in4_1[] = {7, 5, 2, 0, 8, 4, 2, 1};
  int out4_1[] = {9, 9, 9, 9, 9, 9, 9, 9};
  cout << "Test 1\nfunc mergeNeighbours\ninput: ";
  printArray(in4_1, 8);
  mergeNeighbours(out4_1, in4_1, 0, 4, 8);
  cout << "output (expected): 8,7,5,4,2,2,1,0\nresult: ";
  printArray(out4_1, 8);
  cout << endl;

  // Test 2
  const int in4_2[] = {3, 1, 4, 2};
  int out4_2[] = {0, 0, 0, 0};
  cout << "Test 2\nfunc mergeNeighbours\ninput: ";
  printArray(in4_2, 4);
  mergeNeighbours(out4_2, in4_2, 0, 2, 4);
  cout << "output (expected): 4,3,2,1\nresult: ";
  printArray(out4_2, 4);
  cout << endl;

  // Test 3
  const int in4_3[] = {5, 5, 5, 1, 1, 1};
  int out4_3[] = {0, 0, 0, 0, 0, 0};
  cout << "Test 3\nfunc mergeNeighbours\ninput: ";
  printArray(in4_3, 6);
  mergeNeighbours(out4_3, in4_3, 0, 3, 6);
  cout << "output (expected): 5,5,5,1,1,1\nresult: ";
  printArray(out4_3, 6);
  cout << "\n\n";

  //==============================================
  // TASK 5 - mergeSort
  //==============================================
  cout << "==================== Task 5 ====================" << endl;

  int t5_1[] = {1, 3, 2};
  cout << "Test 1\nfunc mergeSort\ninput: ";
  printArray(t5_1, 3);
  mergeSort(t5_1, 3);
  cout << "output (expected): 3,2,1\nresult: ";
  printArray(t5_1, 3);
  cout << endl;

  int t5_2[] = {1, 2, 2, 1};
  cout << "Test 2\nfunc mergeSort\ninput: ";
  printArray(t5_2, 4);
  mergeSort(t5_2, 4);
  cout << "output (expected): 2,2,1,1\nresult: ";
  printArray(t5_2, 4);
  cout << endl;

  int t5_3[] = {5};
  cout << "Test 3\nfunc mergeSort\ninput: ";
  printArray(t5_3, 1);
  mergeSort(t5_3, 1);
  cout << "output (expected): 5\nresult: ";
  printArray(t5_3, 1);
  cout << endl;

  return 0;
}