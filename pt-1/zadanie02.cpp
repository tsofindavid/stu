/*
Name and surname: David Tsofin

INSTRUCTIONS:
(1)  Implement functions so they fulfill the description at their declarations.
(2)  The entire implementation must be in this one file.
(3)  Submit only this source file (with completed solutions).
(4)  The program must be compilable.
(5)  Global and static variables are forbidden.
(6)  Under no circumstances change the declarations of functions you are supposed to program
     (don't change names, return values, or type and number of parameters in given functions).
     Don't change implementations of given data types or implementations of finished helper functions
     (unless stated otherwise in the task assignment).
(7)  If needed, you can add additional helper functions or data types to the code.
(8)  Test your solution (in the 'main' function and using added helper functions or data types).
     However, testing code will not be graded.
(9)  The 'main' function must be last in the source code.
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATA TYPES
//-------------------------------------------------------------------------------------------------

// Representation of a linked list node
struct Node
{
    int data;   // node value
    Node *next; // address of the next list node
};

// Representation of a linked list
struct List
{
    Node *first; // address of the first list node
};

// Helper structure for task 2
struct ListData
{
    int *data;  // array of node values
    size_t len; // length of 'data' array
};

//-------------------------------------------------------------------------------------------------
// HELPERS
//-------------------------------------------------------------------------------------------------

vector<int> listToVector(const List *list)
{
    vector<int> data = {};
    Node *ptr = list->first;

    if (ptr != nullptr)
    {
        data.push_back(ptr->data);

        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
            data.push_back(ptr->data);
        }
    }

    return data;
}

set<int> listToSet(const List *list)
{
    set<int> data = {};
    Node *ptr = list->first;

    if (ptr != nullptr)
    {
        data.insert(ptr->data);

        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
            data.insert(ptr->data);
        }
    }

    return data;
}

List *vectorToList(const vector<int> data)
{
    List *list = new List{nullptr};

    if (data.empty())
    {
        return list;
    }

    list->first = new Node{data[0], nullptr};

    Node *ptr = list->first;

    for (size_t i = 1; i < data.size(); i++)
    {
        ptr->next = new Node{data[i], nullptr};
        ptr = ptr->next;
    }

    return list;
}

//-------------------------------------------------------------------------------------------------
// TASK 1 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function adds a new node with value 'val' at the end of the linked list 'list'.

    INPUT CONDITIONS:
        1) It holds that 'list' always exists (i.e. 'list' is different from 'nullptr') and can
           have any number of nodes (0 or more).

    PARAMETERS:
        [in, out] list - address of the linked list to which we are adding a node
        [in] val       - value of the node to be added at the end of list 'list'

    RETURN VALUE:
        None.

    EXAMPLES:
        empty list, 5 ---> (5)
        (1), 1 ---> (1, 1)
        (8, 2, 6, 6), 14 ---> (8, 2, 6, 6, 14)
        (6, 100, 33), -85 ---> (6, 100, 33, -85)
        (1, 2, 3, 4, 5), 3 ---> (1, 2, 3, 4, 5, 3)
*/

void appendNode(List *list, const int val)
{
    Node *ptr = list->first;
    if (ptr != nullptr)
    {
        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
        }

        ptr->next = new Node{val, nullptr};
    }
    else
    {
        list->first = new Node{val, nullptr};
    }
}

//-------------------------------------------------------------------------------------------------
// TASK 2 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function creates a new linked list that will be constructed using data in the input
    structure 'listData'. Structure 'listData' contains field 'data', which represents an array
    of values for individual list nodes. Structure 'listData' also contains field 'len', which
    tells the length of array 'data'. The created list must contain nodes that correspond
    by their values and order to elements stored in array 'data' (list length will be 'len').
    The function finally returns the address of the created list.

    INPUT CONDITIONS:
        1) It holds that 'listData' always exists (i.e. 'listData' is different from 'nullptr').
        2) For field 'len' it holds that it will never have a greater value than the real number of elements in array 'data'.

    OUTPUT CONDITION:
        1) If field 'len' equals 0, then an empty linked list is created and returned
           (i.e. a valid list that has 0 nodes).

    PARAMETERS:
        [in] listData - structure using which the list is created

    RETURN VALUE:
        Address of the linked list that was created using structure 'listData'.
        See instructions above.

    EXAMPLES:
        field 'data' = (1,2,3)
        field 'len' = 0
        output list will have 0 nodes, i.e. ()

        field 'data' = (1,2,3)
        field 'len' = 2
        output list will be (1,2)

        field 'data' = (1,2,3)
        field 'len' = 3
        output list will be (1,2,3)

        field 'data' = (-9,412,64,72,100,100,6)
        field 'len' = 4
        output list will be (-9,412,64,72)
*/

List *createList(const ListData *listData)
{
    List *list = new List{nullptr};

    for (size_t i = 0; i < listData->len; i++)
    {
        appendNode(list, listData->data[i]);
    }

    return list;
}

//-------------------------------------------------------------------------------------------------
// TASK 3 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function adds a new node with value 'val' into the ascending sorted list 'sortedList'.
    The addition must happen in such a way that list 'sortedList' remains ascending sorted
    after adding the new node.

    NOTE: The order of duplicates in list 'sortedList' doesn't matter.

    INPUT CONDITIONS:
        1) It holds that 'sortedList' always exists (i.e. 'sortedList' is different from 'nullptr').
        2) Input list 'sortedList' can have any number of nodes (0 or more).
        3) Input list 'sortedList' is sorted in ascending order.

    PARAMETERS:
        [in, out] sortedList   - address of input linked list that is sorted
                                 in ascending order
        [in] val               - value of the node to be added to list 'sortedList'

    RETURN VALUE:
        None.

    EXAMPLES:
        (), 0 ---> (0)
        (), 156 ---> (156)
        (8), 4 ---> (4, 8)
        (7), 10 ---> (7, 10)
        (55), 55 ---> (55, 55) ... note: order of duplicates doesn't matter
        (1, 8, 236, 888), 70 ---> (1, 8, 70, 236, 888)
        (5, 5, 14, 82, 82, 100), 5 ---> (5, 5, 5, 14, 82, 82, 100)
*/

void insertNode(List *sortedList, const int val)
{
    Node *node = new Node{val, nullptr};

    if (sortedList->first == nullptr)
    {
        sortedList->first = node;
        return;
    }

    if (val <= sortedList->first->data)
    {
        node->next = sortedList->first;
        sortedList->first = node;
        return;
    }

    Node *ptr = sortedList->first;
    while (ptr->next != nullptr && ptr->next->data < val)
    {
        ptr = ptr->next;
    }

    node->next = ptr->next;
    ptr->next = node;
}

//-------------------------------------------------------------------------------------------------
// TASK 4 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function creates a new list by joining lists 'list1' and 'list2'. The function returns the address
    of the newly created list. In the joined list, first come nodes of list 'list1' (in unchanged order)
    and then follow nodes of list 'list2' (in unchanged order). When creating the new list, you can
    use deep or shallow copy of existing nodes (both solutions will be accepted).

    NOTE:
        An empty list is a list that is valid but contains 0 nodes
        (i.e. field 'first' is set to 'nullptr').

    INPUT CONDITIONS:
        1) Lists 'list1' and 'list2' can be arbitrarily long (0 or more nodes).

    PARAMETERS:
        [in, out] list1 - address of the first list
        [in, out] list2 - address of the second list

    RETURN VALUE:
        Address of the list created by joining lists 'list1' and 'list2'.

    EXAMPLES:
        () + () ---> ()
        (5, 9) + () ---> (5, 9)
        () + (2, 2, 2) ---> (2, 2, 2)
        (1) + (2) ---> (1, 2)
        (7) + (3, 9, 16) ---> (7, 3, 9, 16)
        (50, -47, 23, 1) + (0, 0, 9, -8) ---> (50, -47, 23, 1, 0, 0, 9, -8)
*/

List *joinLists(List *list1, List *list2)
{
    List *list = new List{nullptr};
    Node *tail = nullptr;

    Node *ptr = list1->first;
    while (ptr != nullptr)
    {
        Node *node = new Node{ptr->data, nullptr};

        if (list->first == nullptr)
        {
            list->first = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }

        ptr = ptr->next;
    }

    ptr = list2->first;
    while (ptr != nullptr)
    {
        Node *node = new Node{ptr->data, nullptr};

        if (list->first == nullptr)
        {
            list->first = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }

        ptr = ptr->next;
    }

    return list;
}

//-------------------------------------------------------------------------------------------------
// TASK 5 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function removes the last node from list 'list'. If list 'list' is empty, the function does
    nothing. Memory of the node that the function removes must be correctly deallocated.

    INPUT CONDITIONS:
        1) It holds that 'list' always exists (i.e. 'list' is different from 'nullptr').
        2) List 'list' can be arbitrarily long (0 or more nodes).

    PARAMETERS:
        [in, out] list - address of the input list

    RETURN VALUE:
        None.

    EXAMPLES:
        () ---> ()
        (1) ---> ()
        (1, 2) ---> (1)
        (1, 2, 3) ---> (1, 2)
*/

void removeLastNode(List *list)
{
    if (list->first == nullptr)
    {
        return;
    }

    if (list->first->next == nullptr)
    {
        delete list->first;
        list->first = nullptr;
        return;
    }

    Node *ptr = list->first;
    while (ptr->next->next != nullptr)
    {
        ptr = ptr->next;
    }

    delete ptr->next;
    ptr->next = nullptr;
}

//-------------------------------------------------------------------------------------------------
// TASK 6 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function verifies whether the input list 'list' is a palindrome. We will consider an empty list
    as a palindrome.

    Note: A palindrome represents a sequence of values that reads the same in both directions.
    URL: https://sk.wikipedia.org/wiki/Palindr%C3%B3m
    Example of palindrome: 1212121 or 4953594

    INPUT CONDITIONS:
        1) It holds that 'list' always exists (i.e. 'list' is different from 'nullptr').
        2) List 'list' can be arbitrarily long (0 or more nodes).

    PARAMETERS:
        [in] list - address of the input list

    RETURN VALUE:
        Boolean value 'true'/'false' according to whether the input list is/isn't a palindrome.

    EXAMPLES:
        () ---> true
        (1) ---> true
        (2, 2, 2, 2) ---> true
        (1, 2, 3, 4, 5) ---> false
        (1, 2, 2, 1) ---> true
        (8, 4, 8, 4, 8) ---> true
        (9, 842, 613, 2, 613, 842, 9) ---> true
        (7, 9, 1, 2) ---> false
        (0, 0, 0, 7, 0, 0) ---> false
*/

bool isPalindrome(const List *list)
{
    vector<int> data = listToVector(list);

    vector<int> dataReverse = data;
    std::reverse(dataReverse.begin(), dataReverse.end());

    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i] != dataReverse[i])
        {
            return false;
        }
    }

    return true;
}

//-------------------------------------------------------------------------------------------------
// TASK 7 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function returns the sum of values of the first 'n' nodes in list 'list'.

    INPUT CONDITIONS:
        1) It holds that 'list' always exists (i.e. 'list' is different from 'nullptr').
        2) List 'list' can be arbitrarily long (0 or more nodes).
        3) Parameter 'n' will never have a higher value than the real number of nodes in the list.

    PARAMETERS:
        [in] list - input linked list
        [in] n - number of nodes from the beginning of list 'list' whose sum will be returned

    RETURN VALUE:
        Sum of values of the first 'n' nodes of list 'list'. If 'n'=0, then the function returns value 0.

    EXAMPLES:
        (), 0 ---> 0
        (1,2,3), 0 ---> 0
        (6), 1 ---> 6
        (5,6,7), 2 ---> 11
        (4,4,4,4,4,4), 6 ---> 24
        (-8,41,-314,21), 3 ---> -281
*/

int sumNodes(const List *list, const size_t n)
{
    int sum = 0;

    if (list->first == nullptr || n == 0)
    {
        return sum;
    }

    Node *ptr = list->first;
    for (size_t i = 0; i < n; i++)
    {
        sum += ptr->data;
        ptr = ptr->next;
    }

    return sum;
}

//-------------------------------------------------------------------------------------------------
// TASK 8 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function verifies whether list 'list1' contains all values of nodes from list 'list2'.
    Order doesn't matter.

    INPUT CONDITIONS:
        1) It holds that 'list1' and 'list2' always exist (i.e. are different from 'nullptr').
        2) Lists 'list1' and 'list2' can be arbitrarily long (0 or more nodes).
        3) List 'list2' will not contain duplicate nodes.

    PARAMETERS:
        [in] list1 - first list
        [in] list2 - second list

    RETURN VALUE:
        Boolean value 'true'/'false' according to whether list 'list1' contains/doesn't contain
        all values of nodes from list 'list2'.

    EXAMPLES:
        (), () ---> true
        (), (1, 2, 3) ---> false
        (1, 2, 3), () ---> true
        (5, 6, 7), (5, 6, 8) ---> false
        (8, 4, 3), (3, 8, 4) ---> true
        (7, 6, 1, 9, 8), (1, 6, 8) ---> true
        (3, 3, 3, 3, 3), (2, 3) ---> false
        (8, 6, 1, 2, 5, 0, 7, 7), (7) ---> true
        (9, 5, 10), (41, 10, 5) ---> false
*/

bool contains(const List *list1, const List *list2)
{

    if (list1->first == nullptr)
    {
        if (list2->first == nullptr)
        {
            return true;
        }

        return false;
    }

    if (list2->first == nullptr)
    {
        return true;
    }

    set<int> set1 = listToSet(list1);
    set<int> set2 = listToSet(list2);

    for (int value : set2)
    {
        if (!set1.count(value))
        {
            return false;
        }
    }

    return true;
}

//-------------------------------------------------------------------------------------------------
// TASK 9 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function creates and returns a DEEP copy of list 'list'. In the created copy, values
    and order of nodes from the original list must be preserved.

    INPUT CONDITIONS:
        1) It holds that 'list' always exists (i.e. is different from 'nullptr').
        2) List 'list' can be arbitrarily long (0 or more nodes).

    OUTPUT CONDITION
        Addresses of nodes at the same positions in both lists must differ (because it's a deep copy)

    PARAMETERS:
        [in] list - address of the list whose deep copy should be created

    RETURN VALUE:
        Address of the list that was created as a deep copy of input list 'list'.
        A copy of an empty list is an empty list.

    EXAMPLES:
        Input = ()
        Output = ()

        Input = (1, 2, 3)
        Output = (1, 2, 3)
*/

List *deepCopyList(const List *list)
{
    List *copy = new List{nullptr};

    Node *ptr = list->first;
    if (ptr != nullptr)
    {
        Node *copyPtr = new Node{ptr->data};
        copy->first = copyPtr;

        while (ptr->next != nullptr)
        {
            ptr = ptr->next;

            copyPtr->next = new Node{ptr->data};
            copyPtr = copyPtr->next;
        }
    }

    return copy;
}

//-------------------------------------------------------------------------------------------------
// TASK 10 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function finds the last occurrence of a node with value 'val' in list 'list' and returns its address.
    If such a node is not found in list 'list', the function returns 'nullptr'.

    INPUT CONDITIONS:
        1) It holds that 'list' always exists (i.e. is different from 'nullptr').
        2) List 'list' can be arbitrarily long (0 or more nodes).

    PARAMETERS:
        [in] list - input linked list
        [in] val - searched node value

    RETURN VALUE:
        Address of the last occurrence of a node with value 'val' in list 'list'.

    EXAMPLES (must be tested using debugger):
        (), 2 ---> nullptr
        (5, 4, 3, 2), 1 ---> nullptr
        (-5, 4, -9, 66), 4 ---> address of 2nd node
        (1, 1, 1, 5, 6, 41), 1 ---> address of 3rd node
        (8, 6, 7, 3, 2, 6), 6 ---> address of 6th node
*/

Node *findLastNodeOccurrence(const List *list, const int val)
{
    Node *last = nullptr;

    if (list->first == nullptr)
    {
        return last;
    }

    Node *ptr = list->first;

    if (ptr->data == val)
    {
        last = ptr;
    }

    while (ptr->next != nullptr)
    {
        ptr = ptr->next;

        if (ptr->data == val)
        {
            last = ptr;
        }
    }

    return last; // change this line according to the task, it's here only for compilation
}

//-------------------------------------------------------------------------------------------------
// TESTING
//-------------------------------------------------------------------------------------------------

// here you can add helper testing functions and structures

// Helper function to print list
void printList(const List *list)
{
    cout << "(";
    Node *current = list->first;
    while (current != nullptr)
    {
        cout << current->data;
        if (current->next != nullptr)
        {
            cout << ", ";
        }
        current = current->next;
    }
    cout << ")";
}

// Helper function to delete entire list
void deleteList(List *list)
{
    Node *current = list->first;
    while (current != nullptr)
    {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
    delete list;
}

// Helper function to count nodes
int countNodes(const List *list)
{
    int count = 0;
    Node *current = list->first;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
}

int main()
{

    cout << "=== TASK 1: appendNode ===" << endl;
    {
        List *list = new List{nullptr};
        cout << "Empty list + 5: ";
        appendNode(list, 5);
        printList(list);
        cout << " (expected: (5))" << endl;

        cout << "Add 1: ";
        appendNode(list, 1);
        printList(list);
        cout << " (expected: (5, 1))" << endl;

        deleteList(list);
    }
    cout << endl;

    cout << "=== TASK 2: createList ===" << endl;
    {
        int data1[] = {1, 2, 3};
        ListData ld1 = {data1, 0};
        List *list1 = createList(&ld1);
        cout << "data={1,2,3}, len=0: ";
        printList(list1);
        cout << " (expected: ())" << endl;
        deleteList(list1);

        ListData ld2 = {data1, 2};
        List *list2 = createList(&ld2);
        cout << "data={1,2,3}, len=2: ";
        printList(list2);
        cout << " (expected: (1, 2))" << endl;
        deleteList(list2);

        ListData ld3 = {data1, 3};
        List *list3 = createList(&ld3);
        cout << "data={1,2,3}, len=3: ";
        printList(list3);
        cout << " (expected: (1, 2, 3))" << endl;
        deleteList(list3);
    }
    cout << endl;

    cout << "=== TASK 3: insertNode ===" << endl;
    {
        List *list = new List{nullptr};
        cout << "Empty list + 0: ";
        insertNode(list, 0);
        printList(list);
        cout << " (expected: (0))" << endl;
        deleteList(list);

        int data[] = {1, 8, 236, 888};
        ListData ld = {data, 4};
        list = createList(&ld);
        cout << "List (1,8,236,888) + 70: ";
        insertNode(list, 70);
        printList(list);
        cout << " (expected: (1, 8, 70, 236, 888))" << endl;
        deleteList(list);
    }
    cout << endl;

    cout << "=== TASK 4: joinLists ===" << endl;
    {
        List *list1 = new List{nullptr};
        List *list2 = new List{nullptr};
        List *joined = joinLists(list1, list2);
        cout << "() + (): ";
        printList(joined);
        cout << " (expected: ())" << endl;
        deleteList(joined);

        int data1[] = {1};
        int data2[] = {2};
        ListData ld1 = {data1, 1};
        ListData ld2 = {data2, 1};
        list1 = createList(&ld1);
        list2 = createList(&ld2);
        joined = joinLists(list1, list2);
        cout << "(1) + (2): ";
        printList(joined);
        cout << " (expected: (1, 2))" << endl;
        deleteList(list1);
        deleteList(list2);
        deleteList(joined);
    }
    cout << endl;

    cout << "=== TASK 5: removeLastNode ===" << endl;
    {
        List *list = new List{nullptr};
        cout << "Empty list: ";
        removeLastNode(list);
        printList(list);
        cout << " (expected: ())" << endl;
        deleteList(list);

        int data[] = {1, 2, 3};
        ListData ld = {data, 3};
        list = createList(&ld);
        cout << "Remove last from (1,2,3): ";
        removeLastNode(list);
        printList(list);
        cout << " (expected: (1, 2))" << endl;
        deleteList(list);
    }
    cout << endl;

    cout << "=== TASK 6: isPalindrome ===" << endl;
    {
        List *list = new List{nullptr};
        cout << "Empty list: " << (isPalindrome(list) ? "true" : "false") << " (expected: true)" << endl;
        deleteList(list);

        int data1[] = {1};
        ListData ld1 = {data1, 1};
        list = createList(&ld1);
        cout << "(1): " << (isPalindrome(list) ? "true" : "false") << " (expected: true)" << endl;
        deleteList(list);

        int data2[] = {1, 2, 2, 1};
        ListData ld2 = {data2, 4};
        list = createList(&ld2);
        cout << "(1,2,2,1): " << (isPalindrome(list) ? "true" : "false") << " (expected: true)" << endl;
        deleteList(list);

        int data3[] = {1, 2, 3, 4, 5};
        ListData ld3 = {data3, 5};
        list = createList(&ld3);
        cout << "(1,2,3,4,5): " << (isPalindrome(list) ? "true" : "false") << " (expected: false)" << endl;
        deleteList(list);
    }
    cout << endl;

    cout << "=== TASK 7: sumNodes ===" << endl;
    {
        List *list = new List{nullptr};
        cout << "Empty list, n=0: " << sumNodes(list, 0) << " (expected: 0)" << endl;
        deleteList(list);

        int data[] = {5, 6, 7};
        ListData ld = {data, 3};
        list = createList(&ld);
        cout << "(5,6,7), n=2: " << sumNodes(list, 2) << " (expected: 11)" << endl;
        cout << "(5,6,7), n=3: " << sumNodes(list, 3) << " (expected: 18)" << endl;
        deleteList(list);
    }
    cout << endl;

    cout << "=== TASK 8: contains ===" << endl;
    {
        List *list1 = new List{nullptr};
        List *list2 = new List{nullptr};
        cout << "(), (): " << (contains(list1, list2) ? "true" : "false") << " (expected: true)" << endl;
        deleteList(list1);
        deleteList(list2);

        int data1[] = {8, 4, 3};
        int data2[] = {3, 8, 4};
        ListData ld1 = {data1, 3};
        ListData ld2 = {data2, 3};
        list1 = createList(&ld1);
        list2 = createList(&ld2);
        cout << "(8,4,3), (3,8,4): " << (contains(list1, list2) ? "true" : "false") << " (expected: true)" << endl;
        deleteList(list1);
        deleteList(list2);

        int data3[] = {5, 6, 7};
        int data4[] = {5, 6, 8};
        ListData ld3 = {data3, 3};
        ListData ld4 = {data4, 3};
        list1 = createList(&ld3);
        list2 = createList(&ld4);
        cout << "(5,6,7), (5,6,8): " << (contains(list1, list2) ? "true" : "false") << " (expected: false)" << endl;
        deleteList(list1);
        deleteList(list2);
    }
    cout << endl;

    cout << "=== TASK 9: deepCopyList ===" << endl;
    {
        List *list = new List{nullptr};
        List *copy = deepCopyList(list);
        cout << "Copy of empty list: ";
        printList(copy);
        cout << " (expected: ())" << endl;
        deleteList(list);
        deleteList(copy);

        int data[] = {1, 2, 3};
        ListData ld = {data, 3};
        list = createList(&ld);
        copy = deepCopyList(list);
        cout << "Copy of (1,2,3): ";
        printList(copy);
        cout << " (expected: (1, 2, 3))" << endl;
        cout << "Addresses differ: " << (list->first != copy->first ? "true" : "false") << " (expected: true)" << endl;
        deleteList(list);
        deleteList(copy);
    }
    cout << endl;

    cout << "=== TASK 10: findLastNodeOccurrence ===" << endl;
    {
        List *list = new List{nullptr};
        Node *found = findLastNodeOccurrence(list, 2);
        cout << "Empty list, val=2: " << (found == nullptr ? "nullptr" : "found") << " (expected: nullptr)" << endl;
        deleteList(list);

        int data1[] = {1, 1, 1, 5, 6, 41};
        ListData ld1 = {data1, 6};
        list = createList(&ld1);
        found = findLastNodeOccurrence(list, 1);
        if (found != nullptr)
        {
            Node *temp = list->first;
            int pos = 1;
            while (temp != found && temp != nullptr)
            {
                temp = temp->next;
                pos++;
            }
            cout << "(1,1,1,5,6,41), val=1: found at position " << pos << " (expected: 3)" << endl;
        }
        deleteList(list);

        int data2[] = {8, 6, 7, 3, 2, 6};
        ListData ld2 = {data2, 6};
        list = createList(&ld2);
        found = findLastNodeOccurrence(list, 6);
        if (found != nullptr)
        {
            Node *temp = list->first;
            int pos = 1;
            while (temp != found && temp != nullptr)
            {
                temp = temp->next;
                pos++;
            }
            cout << "(8,6,7,3,2,6), val=6: found at position " << pos << " (expected: 6)" << endl;
        }
        deleteList(list);
    }
    cout << endl;

    cout << "All tests completed!" << endl;
    return 0;
}