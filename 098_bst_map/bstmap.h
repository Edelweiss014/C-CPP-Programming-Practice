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
    Node * findReplace (Node * curr) const {
        Node * ans = curr->right;
        while (ans->left != NULL) {
            ans = ans->left;
        }
        return ans;
    }
    Node * add_helper (Node * curr, const K & key, const V & value) {
        if (curr == NULL) {
            Node * ans = new Node (key, value);
            return ans;
        }
        else {
            if (key < curr->key) {
                Node * newLeft = add_helper(curr->left, key, value);
                curr->left = newLeft;
            }
            else if (key > curr->key) {
                 Node * newRight = add_helper(curr->right, key, value);
                 curr->right = newRight;
            }
            else {
                // same value again
                curr->value = value;
            }
        }
        return curr;
    }
    Node * remove_helper (Node * curr, const K & key) {
        if (curr->key == key) {
            Node * temp = NULL;
            if (curr->left == NULL) {
                temp = curr->right; 
                delete curr;
                return temp;
            }
            else if (curr->right == NULL) {
                temp = curr->left;
                delete curr; 
                return temp;
            }
            else {
                temp = findReplace(curr);
                curr->key = temp->key;
                curr->value = temp->value;
                delete temp;
                return curr;
            }
        }
        else if (curr->key < key) {
            curr->right = remove_helper(curr->right, key);
            return curr;
        }
        else {
            curr->left = remove_helper(curr->left, key);
            return curr;
        }
    }
    void destroy (Node * curr) {
        if (curr != NULL) {
            destroy(curr->left);
            destroy(curr->right);
            delete curr;
        }
        return;
    }
    void addPreOrder (Node * curr) {
        if (curr != NULL) {
            add(curr->key, curr->value);
        }
        addPreOrder(curr->left);
        addPreOrder(curr->right);
    }
public:
    BstMap () : root(NULL) { }
    BstMap (const BstMap & rhs) {
        addPreOrder(rhs.root);
    }
    BstMap & operator=(const BstMap & rhs) {
        if (this != &rhs) {
            destroy(root);
            addPreOrder(rhs.root);
        }
        return *this;
    }
    virtual void add (const K & key, const V & value) {
        root = add_helper(root, key, value);
        return;
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
        root = remove_helper(root, key);
        return;
    }
    ~BstMap() {
        destroy(root);
    }
};

#endif