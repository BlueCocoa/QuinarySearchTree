//
//  QuinarySearchTree.hpp
//  Quinary Search Tree
//
//  Copyright (c) 2016 BlueCocoa
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifndef QUINARYSEARCHTREE_HPP
#define QUINARYSEARCHTREE_HPP

#include <cmath>
#include <stdlib.h>
#include <string.h>

class QuinarySearchTree {
private:
    typedef struct quinary_node_t {
        unsigned long long c;
        struct quinary_node_t * le[2], * eq, * gt[2];
        const char * data;
    } quinary_node_t, * quinary_tree;
public:
    ~QuinarySearchTree() {
        clean(tree);
    }
    
    QuinarySearchTree& put(const char * key, const char * value) {
        size_t size_to_fit = ceill((strlen(key) + sizeof(unsigned long long))>>3) + 1;
        unsigned long long * data = (unsigned long long *)malloc(sizeof(unsigned long long) * size_to_fit);
        memset(data, 0, sizeof(unsigned long long) * size_to_fit);
        memcpy(data, key, strlen(key));
        this->tree = insert(this->tree, data, key, value);
        free(data);
        return  *this;
    }
    
    const char * get(const char * key) {
        size_t size_to_fit = ceill((strlen(key) + sizeof(unsigned long long))>>3) + 1;
        unsigned long long * data = (unsigned long long *)malloc(sizeof(unsigned long long) * size_to_fit);
        memset(data, 0, sizeof(unsigned long long) * size_to_fit);
        memcpy(data, key, strlen(key));
        quinary_tree result = search(this->tree, data);
        free(data);
        if (!result) {
            return NULL;
        }
        return result->data;
    }
private:
    quinary_tree tree = NULL;
    quinary_tree insert(quinary_tree tree, unsigned long long * key, const char * original_key, const char * value) {
        if (tree == NULL) {
            tree = (quinary_tree)malloc(sizeof(quinary_node_t));
            bzero(tree, sizeof(quinary_node_t));
            tree->c = *key;
        }
        
        if (*key < tree->c) {
            tree->le[(*key & 0x1)] = insert(tree->le[(*key & 0x1)], key, original_key, value);
        } else if (*key > tree->c) {
            tree->gt[(*key & 0x1)] = insert(tree->gt[(*key & 0x1)], key, original_key, value);
        } else {
            if (*key != 0) {
                tree->eq = insert(tree->eq, ++key, original_key, value);
            } else {
                if (tree->data != NULL) {
                    free((void *)tree->data);
                }
                tree->data = strdup(value);
                if (tree->eq == NULL) {
                    tree->eq = (quinary_tree)strdup(original_key);
                }
            }
        }
        return tree;
    }
    
    quinary_tree search(const quinary_tree tree, unsigned long long * key) {
        quinary_tree root;
        root = tree;
        while (root) {
            if (*key < root->c) {
                root = root->le[(*key & 0x1)];
            } else if (*key > root->c) {
                root = root->gt[(*key & 0x1)];
            } else {
                if (*key == 0) {
                    return root;
                }
                key++;
                root = root->eq;
            }
        }
        return NULL;
    }
    
    void clean(quinary_tree p) {
        if (p) {
            clean(p->le[0]);
            clean(p->le[1]);
            if (p->c) clean(p->eq);
            if (p->data) free((void *)p->data);
            clean(p->gt[0]);
            clean(p->gt[1]);
            free(p);
        }
    }
};

#endif /* QUINARYSEARCHTREE_HPP */
