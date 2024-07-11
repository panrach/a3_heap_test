#include "minheap.h"
#include "minheap.c"
#include <stdbool.h>
#include <assert.h>

#define CAP 11

void print(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
}

bool compareArray(int a1[], int a2[], int size) {
    for (int i = 0; i < size; i++) {
        if (a1[i] != a2[i]) {
            return false;
        }
    }
    return true;
}

bool compare(MinHeap* heap, int expected[], int size) {
    int actual[CAP];

    for (int i = 0; i < size; i++) {
        actual[i] = heap->arr[i + 1].priority;
    }

    bool same = compareArray(actual, expected, size);

    if (!same) {
        printf("Expected: ");
        print(expected, size);
        printf("Actual:   ");
        print(actual, size);
    }

    return same;
}

void initialize(MinHeap* heap) {
    // Initialize the heap nodes with unique values
    int id = 0;
    heap->arr[1].priority = 2;
    heap->arr[1].id = id;
    id++;
    heap->size++;

    heap->arr[2].priority = 2;
    heap->arr[2].id = id;
    id++;
    heap->size++;

    heap->arr[3].priority = 4;
    heap->arr[3].id = id;
    id++;
    heap->size++;

    heap->arr[4].priority = 3;
    heap->arr[4].id = id;
    id++;
    heap->size++;

    heap->arr[5].priority = 7;
    heap->arr[5].id = id;
    id++;
    heap->size++;

    heap->arr[6].priority = 8;
    heap->arr[6].id = id;
    id++;
    heap->size++;

    heap->arr[7].priority = 5;
    heap->arr[7].id = id;
    id++;
    heap->size++;

    heap->arr[8].priority = 9;
    heap->arr[8].id = id;
    id++;
    heap->size++;

    heap->arr[9].priority = 6;
    heap->arr[9].id = id;
    id++;
    heap->size++;
}

/*
1.1: Max is the root
1.2: priority already in the heap
1.3: already a valid heap
1.4: heapify from middle 
*/
void test_heapify() {
    // initialize heap
    MinHeap* heap = newHeap(CAP);
    initialize(heap);

    // 1.1
    heap->arr[1].priority = 11;
    int expected[CAP] = {2, 3, 4, 6, 7, 8, 5, 9, 11}; 
    heapify(heap, 1);
    printf("1.1:%s\n", compare(heap, expected, CAP) ? " PASSED": " FAILED");

    // 1.2
    heap->arr[1].priority = 6;
    int expected2[CAP] = {3, 6, 4, 6, 7, 8, 5, 9, 11}; 
    heapify(heap, 1);
    printf("1.2:%s\n", compare(heap, expected2, CAP) ? " PASSED": " FAILED");

    // 1.3
    heapify(heap, 2);
    printf("1.3:%s\n", compare(heap, expected2, CAP) ? " PASSED": " FAILED");

    // 1.4
    heap->arr[3].priority = 12;
    int expected4[CAP] = {3, 6, 5, 6, 7, 8, 12, 9, 11}; 
    heapify(heap, 3);
    printf("1.4:%s\n", compare(heap, expected4, CAP) ? " PASSED": " FAILED");

    deleteHeap(heap);
}

/*
2.1: First extract
2.2: Second extract
2.3: Third extract
2.4: Empty extract
*/
void test_extractMin() {
    MinHeap* heap = newHeap(CAP);
    initialize(heap);
    int offset = 3;

    // first extract
    int expected[CAP - 1] = {2, 3, 4, 6, 7, 8, 5, 9}; 
    extractMin(heap);
    printf("2.1:%s\n", compare(heap, expected, CAP - offset) ? " PASSED": " FAILED");
    offset++;

    // second
    int expected2[CAP - 2] = {3, 6, 4, 9, 7, 8, 5}; 
    extractMin(heap);
    printf("2.2:%s\n", compare(heap, expected2, CAP - offset) ? " PASSED": " FAILED");
    offset++;

    // third
    int expected3[CAP - 3] = {4, 6, 5, 9, 7, 8}; 
    extractMin(heap);
    printf("2.3:%s\n", compare(heap, expected3, CAP - offset) ? " PASSED": " FAILED");
    offset++;

    // empty heap
    MinHeap* empty = newHeap(CAP);
    int expected4[CAP] = {}; 
    extractMin(heap);
    printf("2.4:%s\n", compare(empty, expected4, CAP) ? " PASSED": " FAILED");

    deleteHeap(heap);
    deleteHeap(empty);
}

/*
3.1: decreasing order
3.2: duplicate insertion (insert 1)
3.3: insert 0
3.4: insert another 1
3.5: insert past capacity
*/

void test_insert() {
    MinHeap* heap = newHeap(CAP);
    int size = 8;
    
    // 3.1
    assert(insert(heap, 8, 1) == true);
    assert(insert(heap, 7, 2) == true);
    assert(insert(heap, 6, 3) == true);
    assert(insert(heap, 5, 4) == true);
    assert(insert(heap, 4, 5) == true);
    assert(insert(heap, 3, 6) == true);
    assert(insert(heap, 2, 7) == true);
    assert(insert(heap, 1, 8) == true);
    int expected[9] = {1, 2, 3, 5, 6, 7, 4, 8}; 
    printf("3.1:%s\n", compare(heap, expected, size) ? " PASSED": " FAILED");

    // 3.2
    assert(insert(heap, 1, 10) == true);
    size++;
    int expected2[10] = {1, 1, 3, 2, 6, 7, 4, 8, 5}; 
    printf("3.2:%s\n", compare(heap, expected2, size) ? " PASSED": " FAILED");

    // 3.3
    assert(insert(heap, 0, 11) == true);
    size++;
    int expected3[10] = {0, 1, 3, 2, 1, 7, 4, 8, 5, 6}; 
    printf("3.3:%s\n", compare(heap, expected3, size) ? " PASSED": " FAILED");

    // 3.4
    assert(insert(heap, 1, 12) == true);
    size++;
    int expected4[11] = {0, 1, 3, 2, 1, 7, 4, 8, 5, 6, 1}; 
    printf("3.4:%s\n", compare(heap, expected4, size) ? " PASSED": " FAILED");

    // 3.5
    assert(insert(heap, 10, 13) == false);
    printf("3.5:%s\n", compare(heap, expected4, size) ? " PASSED": " FAILED");

    deleteHeap(heap);
}

// 4.1: id 0, priority 2
// 4.2: id 1, priority 2
// 4.3: id 4, priority 7
void test_getPriority() {
    MinHeap* heap = newHeap(CAP);
    initialize(heap);

    printf("4.1: %s\n", getPriority(heap, 0) == 2 ? "PASSED" : "FAILED");
    printf("4.2: %s\n", getPriority(heap, 1) == 2 ? "PASSED" : "FAILED");
    printf("4.3: %s\n", getPriority(heap, 4) == 7 ? "PASSED" : "FAILED");
}

/*
5.1: change smallest
5.2: with an id that doesn't exist
5.3: with an id that exists but the new priority is bigger
5.4: with an id that exists but new priority is the same
5.5: with an id that exists and new priority is smaller
*/
void test_decreasePriority() {
    MinHeap* heap = newHeap(CAP);
    initialize(heap);
    int size = 11;

    // 5.1
    int expected[11] = {1, 2, 4, 3, 7, 8, 5, 9, 6}; 
    printf("5.1: %s\n", decreasePriority(heap, 0, 1) && compare(heap, expected, size) ? "PASSED" : "FAILED");

    // 5.2
    printf("5.2: %s\n", !decreasePriority(heap, 0, 1) ? "PASSED" : "FAILED");

    // 5.3
    printf("5.3: %s\n", !decreasePriority(heap, 4, 8) ? "PASSED" : "FAILED");

    // 5.4
    printf("5.4: %s\n", !decreasePriority(heap, 4, 7) ? "PASSED" : "FAILED");

    int expected2[11] = {0, 1, 4, 3, 2, 8, 5, 9, 6}; 
    // 5.5
    printf("5.5: %s\n", decreasePriority(heap, 4, 0) && compare(heap, expected2, size) ? "PASSED" : "FAILED");

}

int main() {
    // test_heapify();
    // test_extractMin();
    // test_insert();
    test_getPriority();
    test_decreasePriority();
}
