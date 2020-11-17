#ifndef _BSTMAP_H_
#define _BSTMAP_H_
#include <iostream>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <string>

#include "map.h"

template <typename K, typename V>
class BstMap : public Map<K, V> {
private:
    class Node {
    public:
        K key;
        V value;
        Node * left;
        Node * right;
        Node (const K & key, const V & value) : key(key), value(value), left(NULL), right(NULL) { }
    };
    Node * root;

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
        helper = new Node (rhs_curr->key, rhs_curr->value);
        helper->left = copyPreOrder(rhs_curr->left);
        helper->right = copyPreOrder(rhs_curr->right);
        return helper;
    }
public:
    BstMap () : root(NULL) { }
    BstMap (const BstMap & rhs) : root (NULL) {
        root = copyPreOrder(rhs.root);
    }
    BstMap & operator=(const BstMap & rhs) {
        if (this != &rhs) {
            destroy(root);
            root = copyPreOrder(rhs.root);
        }
        return *this;
    }
    virtual void add (const K & key, const V & value) {
        Node ** curr = &root;
        while (* curr != NULL) {
            if (key == (*curr)->key) {
                (*curr)->value = value;
            }
            if (key < (*curr)->key) {
                curr = &(*curr)->left;
            }
            else {
                curr = &(*curr)->right;
            }
        }
        *curr = new Node (key, value);
    }
    virtual const V & lookup(const K & key) const throw (std::invalid_argument) {
        Node * curr = root;
        while (curr != NULL) {
            if (curr->key == key) {
                return curr->value;
            }
            else if (curr->key > key) {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
        }
        throw std::invalid_argument("Invalid!");
    }
    virtual void remove(const K & key) {
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
                    Node ** temp = curr;
                    temp = &(*temp)->left;
                    while ((*temp)->right != NULL) {
                        temp = &(*temp)->right;
                    }
                    (*curr)->key = (*temp)->key;
                    (*curr)->value = (*temp)->value;
                    delete (*temp);
                }
            }
        }
        return;
    }
    ~BstMap<K, V>() {
        destroy(root);
    }
};

#endif
