/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include <algorithm>
#include <vector>

using namespace std;

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node *tOrig = t;
    Node *rightOrig = t->right;
    Node *rightLeft = rightOrig->left;

    t = rightOrig;
    rightOrig->left = tOrig;
    tOrig->right = rightLeft;

    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    tOrig->height = 1 + max(heightOrNeg1(tOrig->left), heightOrNeg1(tOrig->right));    
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node *tOrig = t;
    Node *leftOrig = t->left;
    Node *leftRight = leftOrig->right;

    t = leftOrig;
    leftOrig->right = tOrig;
    tOrig->left = leftRight;

    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    tOrig->height = 1 + max(heightOrNeg1(tOrig->left), heightOrNeg1(tOrig->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) {
        return;
    }

    int bal = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);

    if (bal >= 2) {
        int bal_inner = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (bal_inner >= 1) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    } else if (bal <= -2) {
        int bal_inner = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (bal_inner <= -1) {
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        Node *newNode = new Node(key, value);
        subtree = newNode;
    }

    if (subtree->key > key) {
        insert(subtree->left, key, value);
        rebalance(subtree);
        subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));

    } else if (subtree->key < key) {
        insert(subtree->right, key, value);
        rebalance(subtree);
        subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));

    } 
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node *iop = subtree->left;
            while (iop->right != NULL) {
                iop = iop->right;
            }
            swap(iop, subtree);
            remove(subtree->left, key);
            subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
        } else {
            /* one-child remove */
            // your code here
            if (subtree->right != NULL && subtree->left == NULL) {
                Node *temp = subtree;
                Node *tempRight = subtree->right;
                subtree = tempRight;
                subtree->height = 1 + heightOrNeg1(tempRight);
                delete temp;
                temp = NULL;
            } else {
                Node *temp = subtree;
                Node *tempLeft = subtree->left;
                subtree = tempLeft;
                subtree->height = 1 + heightOrNeg1(tempLeft);
                delete temp;
                temp = NULL;
            }
        }
    }
    rebalance(subtree);
}
