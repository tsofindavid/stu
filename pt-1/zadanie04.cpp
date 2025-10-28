/*
Name and Surname: David Tsofin

INSTRUCTIONS:
(1) Implement functions so that they fulfill the description in their
declarations. (2) The entire implementation must be in this single file. (3)
Submit only this source file (with completed solutions). (4) The program must be
compilable. (5) Global and static variables are prohibited. (6) Do not change
the declarations of functions you are tasked to implement (do not change names,
return values, or the type and number of parameters in the given functions). Do
not change implementations of given data types, nor implementations of
ready-made helper functions (unless stated otherwise in the task description).
(7) If necessary, you can add additional helper functions or data types.
(8) Test your solution (in the 'main' function and using added helper functions
or data types). Test code will not be graded. (9) The 'main' function must be
the last in the source code.
*/

#include <iostream>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATA TYPES
//-------------------------------------------------------------------------------------------------

// Weight of product and packaging. Weight of packaged product is the sum of
// both components
struct Weight {
  int product; // product weight
  int packing; // packaging weight
};

//-------------------------------------------------------------------------------------------------
// TASK 1 (0.8 points)
//-------------------------------------------------------------------------------------------------
/*
    Function sorts the 'data' array from largest element to smallest.
    Use the bubble sort algorithm.

    PARAMETERS:
        [in, out] data - array that the function will sort
        [in] length    - number of array elements

    INPUT CONDITION:
        if 'length' > 0, then 'data' points to a valid array

    EXAMPLES:
        (1, 4, 2) -> (4, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (5) -> (5)
        () -> ()
*/
void bubbleSort(int *data, const size_t length) {
  if (length < 2) {
    return;
  }

  for (size_t i = 0; i < length - 1; i++) {
    for (size_t j = 0; j < length - i - 1; j++) {
      if (data[j] < data[j + 1]) {
        swap(data[j], data[j + 1]);
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------
// TASK 2 (0.8 points)
//-------------------------------------------------------------------------------------------------
/*
    Function sorts the 'data' array according to the total weight of packaged
   goods, i.e., based on the sum of components ('product' and 'packing'). The
   sorting order is from heaviest packaged goods to lightest packaged goods. Use
   the bubble sort algorithm.

    Structure comparison condition:
    When comparing elements, the function sums the 'product' and 'packing'
   values of both compared structures. Structures with a larger sum of
   components will be placed before structures with a smaller sum of components
   after sorting.

    Mutual ordering of structures with equal sum of components:
    For point evaluation, the mutual ordering of structures with equal sum of
   components does not matter (even though the component values may be
   different). In practice, however, there may be a requirement to implement
   stable sorting (structures with equal sum of components do not change their
   mutual order).

    PARAMETERS:
        [in, out] data - array that the function will sort
        [in] length    - number of array elements

    INPUT CONDITION:
        if 'length' > 0, then 'data' points to a valid array

    EXAMPLES:
        ((10, 1), (20, 2), (5, 2)) -> ((20, 2), (10, 1), (5, 2)) because
   20+2=22, 10+1=11, 5+2=7 and 22 > 11 > 7
        ((11, 1), (2, 1), (10, 2), (15, 7)) -> ((15, 7), (11, 1), (10, 2), (2,
   1))
        () -> ()

    NOTE:
        Examples of simple array creation in test code:
        Weight packages[] = {{10, 1}, {20, 2}, {5,2}};
        Weight packages[] = {{.product = 10, .packing = 1}, {.product = 20,
   .packing = 2}, {.product = 5, .packing = 2}};
*/
void bubbleSort(Weight *data, const size_t length) {
  if (length < 2) {
    return;
  }

  for (size_t i = 0; i < length - 1; i++) {
    for (size_t j = 0; j < length - i - 1; j++) {
      if (data[j].product + data[j].packing <
          data[j + 1].product + data[j + 1].packing) {
        swap(data[j], data[j + 1]);
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------
// TASK 3 (0.8 points)
//-------------------------------------------------------------------------------------------------
/*
    Function selects a pivot and returns its index.
    The pivot is selected as the median of the elements:
      - data[low]
      - data[(high+low)/2]
      - data[high-1]

    PARAMETERS:
        [in] data - array in which the function selects a pivot in the part with
   indices 'low' ... 'high'-1 [in] low  - index of the first element of the
   array part where the function looks for a pivot [in] high - index after the
   last element of the array part where the function looks for a pivot

    RETURN VALUE:
        pivot index

    INPUT CONDITIONS:
        'data' points to a valid array
        'low' < 'high'

    EXAMPLES:
    data: (10, 20, 2000, 30, 1000, 40, 5000, 50, 60, 70), low: 2, high: 7 ->
    return 2

    data: (10, 20, 1000, 30, 2000, 40, 5000, 50, 60, 70), low: 2, high:7 ->
    return 4

    data: (10, 20, 5000, 30, 1000, 40, 2000, 50, 60, 70), low: 2, high: 7 ->
    return 6

    data: (10, 20, 1000, 30, 40, 2000, 50, 5000, 60, 70), low: 2, high: 8 ->
    return 5

    data: (10, 20, 1000, 2000, 30, 40, 50), low: 2, high: 4 ->
    return 3

    data: (10, 20, 2000, 1000, 30, 40, 50), low: 2, high:4 ->
    return 3

    data: (10, 20, 1000, 30, 40), low: 2, high: 3 ->
    return 2
*/
size_t getPivotIndex(const int *data, const size_t low, const size_t high) {
  size_t l_index = low;
  size_t m_index = (high + low) / 2;
  size_t h_index = high - 1;

  if ((data[l_index] >= data[m_index] && data[l_index] <= data[h_index]) ||
      (data[l_index] <= data[m_index] && data[l_index] >= data[h_index])) {
    return l_index;
  }

  if ((data[m_index] >= data[l_index] && data[m_index] <= data[h_index]) ||
      (data[m_index] <= data[l_index] && data[m_index] >= data[h_index])) {
    return m_index;
  }

  return h_index;
}

//-------------------------------------------------------------------------------------------------
// TASK 4 (0.8 points)
//-------------------------------------------------------------------------------------------------
/*
    Function performs partition (part of the quick sort algorithm) and returns
   the new pivot index. Use the Lomuto style algorithm. Sorting order: First (on
   the left) will be elements greater than or equal to the pivot, then the
   pivot, then (on the right) elements less than the pivot.

    PARAMETERS:
        [in, out] data - array in which partition will be performed in the part
   'low' ... 'high'-1 [in] pivot     - pivot index (before performing partition)
        [in] low       - index of the first element of the array part where
   partition will be performed [in] high      - index after the last element of
   the array part where partition will be performed

    RETURN VALUE:
        Pivot index after performing partition.

    INPUT CONDITIONS:
        'low' <= 'pivot' < 'high' (pivot index can be any in the range
   'low'...'high'-1, for example in case of random pivot selection) 'data'
   points to a valid array

    EXAMPLES:
    1st example:
    input: data: (10, 20, 30, 40, 50, 60, 70, 80, 90),
    pivot: 5,
    low: 2,
    high: 7
    output: data: (10, 20, 70, 60, 50, 30, 40, 80, 90),
    return 3

    2nd example:
    input:  data: (10, 20, 30, 40, 50, 60, 70, 50, 80, 90),
    pivot: 4,
    low: 2,
    high: 8
    output: data: (10, 20, 50, 60, 70, 50, 30, 40, 80, 90),
    return 5
*/
size_t partition(int *data, const size_t pivot, const size_t low,
                 const size_t high) {

  size_t h_index = high - 1;

  swap(data[pivot], data[h_index]);

  size_t i = low;
  for (size_t j = low; j < h_index; j++) {
    if (data[j] >= data[h_index]) {
      swap(data[i], data[j]);
      i++;
    }
  }

  swap(data[i], data[h_index]);

  return i;
}

//-------------------------------------------------------------------------------------------------
// TASK 5 (0.8 points)
//-------------------------------------------------------------------------------------------------
/*
    Function sorts part of the 'data' array (with indices 'low' ... 'high'-1).
    Use the quick sort algorithm, Lomuto style.
    The sorting order is from largest element to smallest.

    PARAMETERS:
        [in, out] data - array whose part the function will sort
        [in] low       - index of the first element of the array part to be
   sorted [in] high      - index after the last element of the array part to be
   sorted

    INPUT CONDITION:
        if 'low' < 'high', then 'data' points to a valid array

    EXAMPLE:
        data: (1, 2, 3, 4, 5, 6, 7, 8, 9), low: 2, high: 7 -> data: (1, 2, 7, 6,
   5, 4, 3, 8, 9)
*/
void quickSort(int *data, const size_t low, const size_t high) {
  if (low >= high) {
    return;
  }

  size_t p_index = getPivotIndex(data, low, high);
  size_t np_index = partition(data, p_index, low, high);

  quickSort(data, low, np_index);
  quickSort(data, np_index + 1, high);
}

//-------------------------------------------------------------------------------------------------
// TESTING
//-------------------------------------------------------------------------------------------------

// here you can add helper functions and structures

int main() {
  // Test 1: bubbleSort for integers
  {
    cout << "Test 1: bubbleSort for integers" << endl;
    int data1[] = {1, 4, 2};
    size_t length1 = sizeof(data1) / sizeof(data1[0]);
    bubbleSort(data1, length1);
    cout << "Expected: 4 2 1" << endl;
    cout << "Got: ";
    for (size_t i = 0; i < length1; i++) {
      cout << data1[i] << " ";
    }
    cout << endl << endl;
  }

  // Test 2: bubbleSort for integers with duplicates
  {
    cout << "Test 2: bubbleSort for integers with duplicates" << endl;
    int data2[] = {1, 2, 2, 1};
    size_t length2 = sizeof(data2) / sizeof(data2[0]);

    bubbleSort(data2, length2);
    cout << "Expected: 2 2 1 1" << endl;
    cout << "Got: ";

    for (size_t i = 0; i < length2; i++) {
      cout << data2[i] << " ";
    }
    cout << endl << endl;
  }

  // Test 3: bubbleSort for single element
  {
    cout << "Test 3: bubbleSort for single element" << endl;
    int data3[] = {5};
    size_t length3 = sizeof(data3) / sizeof(data3[0]);
    bubbleSort(data3, length3);
    cout << "Expected: 5" << endl;
    cout << "Got: ";
    for (size_t i = 0; i < length3; i++) {
      cout << data3[i] << " ";
    }
    cout << endl << endl;
  }

  // Test 4: bubbleSort for empty array
  {
    cout << "Test 4: bubbleSort for empty array" << endl;
    int data4[] = {};
    size_t length4 = 0;
    bubbleSort(data4, length4);
    cout << "Expected: (empty)" << endl;
    cout << "Got: (empty)" << endl << endl;
  }

  // Test 5: bubbleSort for Weight structures
  {
    cout << "Test 5: bubbleSort for Weight structures" << endl;
    Weight data5[] = {{10, 1}, {20, 2}, {5, 2}};
    size_t length5 = sizeof(data5) / sizeof(data5[0]);
    bubbleSort(data5, length5);
    cout << "Expected: (20,2) (10,1) (5,2)" << endl;
    cout << "Got: ";
    for (size_t i = 0; i < length5; i++) {
      cout << "(" << data5[i].product << "," << data5[i].packing << ") ";
    }
    cout << endl << endl;
  }

  // Test 6: bubbleSort for Weight structures complex case
  {
    cout << "Test 6: bubbleSort for Weight structures complex case" << endl;
    Weight data6[] = {{11, 1}, {2, 1}, {10, 2}, {15, 7}};
    size_t length6 = sizeof(data6) / sizeof(data6[0]);
    bubbleSort(data6, length6);
    cout << "Expected: (15,7) (11,1) (10,2) (2,1)" << endl;
    cout << "Got: ";
    for (size_t i = 0; i < length6; i++) {
      cout << "(" << data6[i].product << "," << data6[i].packing << ") ";
    }
    cout << endl << endl;
  }

  // Test 7: getPivotIndex
  {
    cout << "Test 7: getPivotIndex" << endl;
    int data7[] = {10, 20, 2000, 30, 1000, 40, 5000, 50, 60, 70};
    size_t low = 2, high = 7;
    size_t pivotIndex = getPivotIndex(data7, low, high);
    cout << "Array: ";
    for (size_t i = low; i < high; i++) {
      cout << data7[i] << " ";
    }
    cout << endl;
    cout << "Pivot index: " << pivotIndex << " (value: " << data7[pivotIndex]
         << ")" << endl;

    // Test median calculation
    int a = data7[low];              // 2000
    int b = data7[(high + low) / 2]; // data7[4] = 1000
    int c = data7[high - 1];         // data7[6] = 5000
    cout << "Candidates: " << a << ", " << b << ", " << c << endl;
    cout << "Median should be: 2000" << endl << endl;
  }

  // Test 8: getPivotIndex another case
  {
    cout << "Test 8: getPivotIndex another case" << endl;
    int data8[] = {10, 20, 1000, 30, 2000, 40, 5000, 50, 60, 70};
    size_t low = 2, high = 7;
    size_t pivotIndex = getPivotIndex(data8, low, high);
    cout << "Array: ";
    for (size_t i = low; i < high; i++) {
      cout << data8[i] << " ";
    }
    cout << endl;
    cout << "Pivot index: " << pivotIndex << " (value: " << data8[pivotIndex]
         << ")" << endl;

    int a = data8[low];              // 1000
    int b = data8[(high + low) / 2]; // data8[4] = 2000
    int c = data8[high - 1];         // data8[6] = 5000
    cout << "Candidates: " << a << ", " << b << ", " << c << endl;
    cout << "Median should be: 2000" << endl << endl;
  }

  // Test 9: partition function
  {
    cout << "Test 9: partition function" << endl;
    int data9[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    size_t pivot = 5; // value 60
    size_t low = 2, high = 7;

    cout << "Before partition: ";
    for (size_t i = 0; i < 9; i++) {
      cout << data9[i] << " ";
    }
    cout << endl;

    size_t newPivot = partition(data9, pivot, low, high);

    cout << "After partition: ";
    for (size_t i = 0; i < 9; i++) {
      cout << data9[i] << " ";
    }
    cout << endl;
    cout << "New pivot index: " << newPivot << " (value: " << data9[newPivot]
         << ")" << endl;
    cout << "Expected new pivot: 3" << endl << endl;
  }

  // Test 10: quickSort function
  {
    cout << "Test 10: quickSort function" << endl;
    int data10[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t low = 2, high = 7;

    cout << "Before quickSort: ";
    for (size_t i = 0; i < 9; i++) {
      cout << data10[i] << " ";
    }
    cout << endl;

    quickSort(data10, low, high);

    cout << "After quickSort: ";
    for (size_t i = 0; i < 9; i++) {
      cout << data10[i] << " ";
    }
    cout << endl;
    cout << "Expected: 1 2 7 6 5 4 3 8 9" << endl << endl;
  }

  // Test 11: comprehensive quickSort test
  {
    cout << "Test 11: comprehensive quickSort test" << endl;
    int data11[] = {3, 7, 2, 8, 1, 9, 4, 6, 5};
    size_t low = 0, high = 9;

    cout << "Before quickSort: ";
    for (size_t i = 0; i < 9; i++) {
      cout << data11[i] << " ";
    }
    cout << endl;

    quickSort(data11, low, high);

    cout << "After quickSort: ";
    for (size_t i = 0; i < 9; i++) {
      cout << data11[i] << " ";
    }
    cout << endl;
    cout << "Expected: 9 8 7 6 5 4 3 2 1" << endl;
  }

  return 0;
}
