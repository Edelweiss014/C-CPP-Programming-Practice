#ifndef _BSTMAP_H_
#define _BSTMAP_H_
#include <iostream>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <string>

template <typename K, typename V>
class BstMap : public Map {
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
    Node * findReplace (Node * curr) {
        Node * ans = curr->right;
        while (ans->left != NULL) {
            ans = ans->left;
        }
        return ans;
    }
    Node * add_helper (Node * curr, const K & key, const V & value) {
        if (curr == NULL) {
            Node * ans = new Node (key, value, NULL, NULL);
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
        if (curr->left == NULL) {
            Node * temp = curr->right;
            delete curr;
            return temp;
        }
        else if (curr->right == NULL) {
            Node * temp = curr->left;
            delete curr;
            return temp;
        }
        else {
            Node * replacement = findReplace(curr);
            curr->key = replacement->key;
            curr->value = replacement->value;
            delete replacement;
            return curr;
        }
    }
    void destroy (Node * curr) {
        if (curr != NULL) {
            destroy(curr->left);
            destroy(curr->right);
            destroy(curr);
        }
        return;
    }
public:
    virtual void add (const K & key, const V & value) {
        add_helper(root, key, value);
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
        throw std::invalid_argument();
    }
    virtual void remove(const K & key) {
        Node * curr = root;
        while (curr != NULL) {
            if (curr->key == key) {
                curr
            }
            else if (curr->key > key) {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
        }
        if (curr == NULL) return;
        remove_helper(curr, key);
        return;
    }
    virtual ~Map() {
        destroy(root);
    }
};

#endif