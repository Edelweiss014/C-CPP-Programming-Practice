
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <assert.h>

#include "il.h"


void testList() {
    IntList list1;
    assert(list1.head == NULL && list1.tail == NULL 
                    && list1.getSize() == 0 && list1.find(1) == -1 && list1.size == 0);
    list1.addFront(1);
    assert(list1.head != NULL && list1.tail != NULL
                    && list1.getSize() == 1 && list1.find(0) == -1 && list1.find(1) == 0
                    && list1[0] == 1);
    list1.addBack(2);
    assert(list1.getSize() == 2 && list1.find(0) == -1 && list1.find(2) == 1 && list1[1] == 2);
    IntList list2(list1);
    assert(list2.getSize() == 2 && list2.find(0) == -1 && list2.find(2) == 1 && list2[1] == 2);
    assert(list1.remove(1) == true);
    list2 = list1;
    assert(list2.getSize() == 1 && list2.find(0) == -1 && list2.find(2) == 0 && list2[0] == 2);
    list2.addFront(3);
    assert(list2.getSize() == 2 && list2.find(0) == -1 && list2.find(3) == 0 && list2[0] == 3
                    && list2[1] == 2);
    assert(list2.remove(6) == false);
    assert(list1.remove(2) == true);
    assert(list1.head == NULL && list1.tail == NULL 
                    && list1.getSize() == 0 && list1.find(1) == -1 && list1.size == 0);
    list1.addBack(12);
    assert(list1.head != NULL && list1.tail != NULL
                    && list1.getSize() == 1 && list1.find(5) == -1 && list1.find(1) == -1
                    && list1[0] == 12);
    assert(list1.head->next == NULL && list1.head->prev == NULL && list1.head->data == 12
                    && list1.tail->data == 12);
    assert(list2.head->next->data == 2 && list2.head->next->prev->data == 3
                    && list2.tail->prev->data == 3 && list2.tail->prev->next->data == 2);
    list2.addBack(-1);
    assert(list2.head->next->next->data == -1 && list2.tail->prev->prev->data == 3 
                    && list2.head->next->prev->data == 3 && list2.tail->prev->next->data == -1);
    assert(list2.head->next->next->next == NULL && list2.tail->prev->prev->prev == NULL);
    assert(list2.head->next == list2.tail->prev);
    list1.addBack(0);
    list1.addFront(-100);
    list1.addBack(13);
    list1.addFront(31);
    list1.addBack(29);
    assert(list1.getSize() == 6 && list1.size == 6 && list1[4] == 13);
    list1.addBack(0);
    assert(list1.remove(0) == true);
    assert(list1.getSize() == 6 && list1[5] == 0);
    assert(list2.head == list2.head->next->prev && list2.tail == list2.tail->prev->next);
    list2[2] = 31;
    assert(list2.getSize() == 3 && list2.head->next->next->data == 31);
    assert(list2[0] == 3 && list2[1] == 2 && list2[2] == 31);
    IntList list3;
    list3.addFront(1);
    list3.addBack(4);
    list3.addBack(10);
    assert(list3.remove(4) == true);
    assert(list3.find(4) == -1 && list3.find(1) == 0 && list3.find(10) == 1);
    assert(list3.remove(233) == false);
    assert(list3.head->next == list3.tail);
    assert(list3.tail->prev == list3.head);
    return; 
}

int main() {
    testList();
    return EXIT_SUCCESS;
}
