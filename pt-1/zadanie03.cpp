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

    if (head == nullptr || current->data < head->data)
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
            current->data < p->next->data)
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

  size_t n1 = middle - low + 1;
  size_t n2 = high - middle;

  int L[n1];
  int R[n2];

  for (size_t i = 0; i < n1; i++)
    L[i] = input[low + i];

  for (size_t j = 0; j < n2; j++)
    R[j] = input[middle + 1 + j];

  size_t i = 0, j = 0;
  size_t k = low;

  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
    {
      output[k] = L[i];
      i++;
    }
    else
    {
      output[k] = R[j];
      j++;
    }
    k++;
  }

  // Copy the remaining elements of L[],
  // if there are any
  while (i < n1)
  {
    output[k] = L[i];
    i++;
    k++;
  }

  // Copy the remaining elements of R[],
  // if there are any
  while (j < n2)
  {
    output[k] = R[j];
    j++;
    k++;
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
void mergeSort(int *data, const size_t length)
{
  // TODO
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
  // Task 1: insertionSort - integers
  int nums1[] = {1, 3, 4, 6, 7, 12, 9, 0, 2};
  size_t len1 = 9;

  cout << "Task 1 - To sort integers: " << endl;
  printArray(nums1, len1);

  insertionSort(nums1, len1);

  cout << "Task 1 - Sorted integers: " << endl;
  printArray(nums1, len1);
  cout << "\n"
       << endl;

  // Task 2: insertionSort - strings
  const char *names[] = {"Juraj", "Peter", "Andrej", nullptr};
  cout << "Task 2 - To sort strings: " << endl;
  printCStringArray(names);

  insertionSort(names);

  cout << "Task 2 - Sorted strings: " << endl;
  printCStringArray(names);
  cout << "\n"
       << endl;

  // Task 3: insertionSort - linked list
  List list{nullptr};

  Node *a = new Node{2, nullptr};
  Node *b = new Node{1, nullptr};
  Node *c = new Node{3, nullptr};

  a->next = b;
  b->next = c;

  list.first = a;

  cout << "Task 3 - To sort linked list: " << endl;
  printList(list);
  insertionSort(&list);
  cout << "Task 3 - Sorted linked list: " << endl;
  printList(list);
  deleteList(list);
  cout << "\n"
       << endl;

  // Task 4: mergeNeighbours
  // Тест 0: исходный пример
  const int input0[] = {10, 10, 10, 10, 7, 5, 2, 0, 8, 4, 2, 1, 10, 10, 10, 10};
  int output0[] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
  cout << "Test 0 - Original example:" << endl;
  mergeNeighbours(output0, input0, 4, 8, 12);
  printArray(output0, 16);

  // Тест 1
  const int input1[] = {5, 3, 1, 4, 2, 0};
  int output1[] = {9, 9, 9, 9, 9, 9};
  cout << "Test 1:" << endl;
  mergeNeighbours(output1, input1, 0, 3, 6);
  printArray(output1, 6); // Expected: 5 4 3 2 1 0

  // Тест 2 - одинаковые элементы
  const int input2[] = {7, 7, 7, 7, 7, 7};
  int output2[] = {0, 0, 0, 0, 0, 0};
  cout << "Test 2:" << endl;
  mergeNeighbours(output2, input2, 0, 3, 6);
  printArray(output2, 6); // Expected: 7 7 7 7 7 7

  // Тест 3 - левая часть пустая
  const int input3[] = {8, 6, 4};
  int output3[] = {0, 0, 0};
  cout << "Test 3:" << endl;
  mergeNeighbours(output3, input3, 0, 0, 3);
  printArray(output3, 3); // Expected: 8 6 4

  // Тест 4 - правая часть пустая
  const int input4[] = {9, 5, 1};
  int output4[] = {0, 0, 0};
  cout << "Test 4:" << endl;
  mergeNeighbours(output4, input4, 0, 3, 3);
  printArray(output4, 3); // Expected: 9 5 1

  // Тест 5 - по одному элементу
  const int input5[] = {10, 5};
  int output5[] = {0, 0};
  cout << "Test 5:" << endl;
  mergeNeighbours(output5, input5, 0, 1, 2);
  printArray(output5, 2); // Expected: 10 5

  // Тест 6 - перемешанные элементы
  const int input6[] = {3, 1, 4, 2};
  int output6[] = {0, 0, 0, 0};
  cout << "Test 6:" << endl;
  mergeNeighbours(output6, input6, 0, 2, 4);
  printArray(output6, 4); // Expected: 4 3 2 1

  // Task 5: mergeSort
  int nums2[] = {1, 2, 2, 1};
  mergeSort(nums2, 4);
  cout << "Task 5 - Merge sorted: ";
  printArray(nums2, 4);

  return 0;
}
