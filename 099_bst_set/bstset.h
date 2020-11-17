#ifndef _BSTMAP_H_
#define _BSTMAP_H_
#include <iostream>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <string>

#include "set.h"

template <typename T>
class BstSet : public Set<T> {
private:
    class Node {
    public:
        T key;
        Node * left;
        Node * right;
        Node (const T & key) : key(key), left(NULL), right(NULL) { }
    };
    Node * root;
public:
    void destroy (Node * curr) {
        if (curr != NULL) {
            destroy(curr->left);
            destroy(curr->right);
            delete curr;
        }
        return;
    }
    Node * copyPreOrder (Node * rhs_curr) {
        if (rhs_curr == NULL) {
            return NULL;
        }
        Node * helper = NULL;
        helper = new Node (rhs_curr->key);
        helper->left = copyPreOrder(rhs_curr->left);
        helper->right = copyPreOrder(rhs_curr->right);
        return helper;
    }

    BstSet () : root(NULL) { }
    BstSet (const BstSet & rhs) : root (NULL) {
        root = copyPreOrder(rhs.root);
    }
    BstSet & operator=(const BstSet & rhs) {
        if (this != &rhs) {
            destroy(root);
            root = copyPreOrder(rhs.root);
        }
        return *this;
    }
    virtual void add (const T & key) {
        Node ** curr = &root;
        while (* curr != NULL) {
            if (key == (*curr)->key) {
                return;
            }
            if (key < (*curr)->key) {
                curr = &(*curr)->left;
            }
            else {
                curr = &(*curr)->right;
            }
        }
        *curr = new Node (key);
    }
    virtual bool contains(const T & key) const {
        Node * curr = root;
        while (curr != NULL) {
            if (curr->key == key) {
                return true;
            }
            else if (curr->key > key) {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
        }
        return false;
    }
    virtual void remove(const T & key) {
        Node ** curr = &root;
        while (* curr != NULL) {
            if ((*curr)->key > key) {
                curr = &(*curr)->left;
            }
            else if ((*curr)->key < key) {
                curr = &(*curr)->right;
            }
            else {
                if ((*curr)->left == NULL) {
                    Node * temp = (*curr)->right;
                    delete (*curr);
                    *curr = temp;
                }
                else if ((*curr)->right == NULL) {
                    Node * temp = (*curr)->left;
                    delete (*curr);
                    *curr = temp;
                }
                else {
                    Node ** temp_curr = curr;
                    curr = &(*curr)->left;
                    while ((*curr)->right != NULL) {
                        curr = &(*curr)->right;
                    }
                    (*temp_curr)->key = (*curr)->key;
                    Node * curr_left = (*curr)->left;
                    delete (*curr);
                    *curr = curr_left;
                }
            }
        }
        return;
    }
    ~BstSet<T>() {
        destroy(root);
    }
};

#endif
