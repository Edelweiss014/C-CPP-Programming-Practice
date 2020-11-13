#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>
#include <exception>

class WrongIndexErr : public std::exception {
public:
    virtual const char * what() const throw() {
        return "Index out of range";
    }
};

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        T data;
        Node * next;
        Node * prev;
        Node() : data(0), next(NULL), prev(NULL) { }
        Node(const T & d) : data(d), next(NULL), prev(NULL) { }
    };
    Node * head;
    Node * tail;
    int size;
public:
    LinkedList() : head(NULL), tail(NULL), size(0) { }
    LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(rhs.size) {
        Node * temp = rhs.head;
        while (temp != NULL) {
            addBack(temp->data);
            temp = temp->next;
        }
    }
    LinkedList & operator=(const LinkedList & rhs) {
        if (this != &rhs) {
            LinkedList tempList(rhs);
            for (int i = 0; i < this->size; i++) {
                Node * temp = this->head;
                this->head = this->head->next;
                delete temp;
            }
            this->size = rhs.size;
            this->head = tempList.head;
            this->tail = tempList.tail;
            tempList.head = NULL;
            tempList.tail = NULL;
        }
        return *this;
    }
    ~LinkedList() {
        for (int i = 0; i < size; i++) {
            Node * temp = this->head;
            this->head = this->head->next;
            delete(temp);
        }
    }
    void addFront(const T & item) {
        Node * newNode = new Node(item);
        newNode->prev = NULL;
        newNode->next = this->head;
        this->size++;
        if (this->size == 1) {
            this->tail = newNode;
        }
        else {
            this->head->prev = newNode;
        }
        this->head = newNode;
        return;
    }
    void addBack(const T & item) {
        Node * newNode = new Node(item);
        newNode->next = NULL;
        newNode->prev = this->tail;
        this->size++;
        if (this->size == 1) {
            this->head = newNode;
        }
        else {
            this->tail->next = newNode;
        }
        this->tail = newNode;
        return;
    }
    bool remove(const T & item) {
        if (this->head == NULL) return false;
        if (head->data == item) {
            Node * temp = head;
            if (this->size == 1) {
                head = NULL;
                tail = NULL;
            }
            else {
                head = head->next;
            }
            delete temp;
            this->size--;
            return true;
        }
        Node * this_curr = head;
        while (this_curr->next != NULL) {
            if (this_curr->next->data == item) {
                Node * toDelete = this_curr->next;
                if (this_curr->next->next == NULL) {
                    this_curr->next = NULL;
                    tail = this_curr;
                }
                else {
                    this_curr->next = this_curr->next->next;
                    this_curr->next->prev = this_curr;
                }
                delete toDelete;
                this->size--;
                return true;
            }
            this_curr = this_curr->next;
        }
        return false;
    }
    T & operator[](int index) {
        if (index < 0 || index >= size) {
            throw WrongIndexErr();
        }
        Node * curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return (curr->data);
    }
    const T & operator[](int index) const {
        if (index < 0 || index >= size) {
            throw WrongIndexErr();
        }
        Node * curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return (curr->data);
    }
    int find(const T & item) {
        Node * curr = head;
        for (int i = 0; i < size; i++) {
            if (curr->data == item) {
                return i;
            }
            curr = curr->next;
        }
        return -1;
    }
    int getSize() const {
        return size;
    }
};


#endif
