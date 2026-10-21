#ifndef __AVL_Tree_H__
#define __AVL_Tree_H__

#include "AVLNode.h"
#include <algorithm>
#include <stdlib.h>
#include <iostream>
/**
* @brief Class to store an AVL Tree
*/
template<class T>
class AVLTree{

    public:
        //root of the AVL tree
        AVLNode<T>* root;
        
        /**
        * @brief Constructor of an AVL tree, which consists of the data type of the data values in the tree, a comparator function and creates an empty AVL tree consisting of a NULL root node
        *
        * @param cmp comparator function for the tree
        */
        AVLTree(int (*_cmp)(T , T)) : cmp(_cmp) , root(NULL) {}
        ~AVLTree() {}
        
        /**
        * @brief Function to left rotate at a node
        *
        * @param y The AVL tree node at which left rotation has to be done
        */
        AVLNode<T>* leftRotate(AVLNode<T>* y);
        
        /**
        * @brief Function to right rotate at a node
        *
        * @param x The AVL tree node at which right rotation has to be done
        */
        AVLNode<T>* rightRotate(AVLNode<T>* x);
        
        /**
        * @brief Function to balance height at a node
        *
        * @param node Current AVL node
        * @param key The Newly inserted key
        * @return An AVL node pointer after balancing at the node
        */
        AVLNode<T>* balance(AVLNode<T>* node , T key);
        
        /**
        * @brief Function to find the minimum element of the AVL Tree
        *
        * @param node The root of the subtree whose minimum element has to be found
        * @return A pointer to the AVL node having the minimum data value in the subtree
        */
        AVLNode<T>* findMin(AVLNode<T>* node);
        
        /**
        * @brief Function to find the maximum element of the AVL Tree
        *
        * @param node The root of the subtree whose maximum element has to be found
        * @return A pointer to the AVL node having the maximum data value in the subtree
        */
        AVLNode<T>* findMax(AVLNode<T>* node);

        /**
        * @brief Function to find the successor to the given node of the AVL tree
        *
        * @param ro The pointer to the root of the AVL tree
        * @param node The pointer to the node whose successsor has to be found
        * @return A pointer to the successor the AVL tree node
        */
        AVLNode<T>* successor(AVLNode<T>* ro,AVLNode<T>* node);

        /**
        * @brief Function to find the predecessor to the given node of the AVL tree
        *
        * @param ro The pointer to the root of the AVL tree
        * @param node The pointer to the node whose predecessor has to be found
        * @return A pointer to the predecessor the AVL tree node
        */
        AVLNode<T>* predecessor(AVLNode<T>* ro,AVLNode<T>* node);

        /**
        * @brief Function to find the node having least data value greater than or equal to key
        *
        * @param node The pointer to the root of the tree
        * @param key The key value
        * @return A pointer to the node having least data value greater than or equal to key
        */
        AVLNode<T>* find_right(AVLNode<T>* node, T key);

        /**
        * @brief Function to find the node having greatest data value less than or equal to key
        *
        * @param node The pointer to the root of the tree
        * @param key The key value
        * @return A pointer to the node having greatest data value less than or equal to key
        */
        AVLNode<T>* find_left(AVLNode<T>* node, T key);

        /**
        * @brief Function to insert a node into the AVL tree
        *
        * @param key The data value of the node to be inserted
        */
        void insert(T key);

        /**
        * @brief Function to delete a node from an AVL tree
        *
        * @param key The data value of the node to be deleted
        */
        void remove(T key);

        /**
        * @brief Function to find the node having data value equal to the key
        *
        * @param key The key value which has to be searched in the tree
        * @return A pointer to the node having data value equal to key
        */
        AVLNode<T>* search(T key);

    private:
        /**
        * @brief Comparator function of the AVL Tree
        *
        * @param T1 The first parameter of comparision
        * @param T2 The second parameter of comparision
        * @return -1 if T1<T2
        * @return 0 if T1==T2
        * @return 1 if T1>T2
        */
        int (*cmp)(T , T); // returns -1 if arg1 < arg2, 0 if arg1=arg2, 1 if arg1>arg2

        /**
        * @brief Insert to AVL Tree and balance at the point of insertion
        *
        * @param node Pointer to root
        * @param key Key to be inserted
        * @return pointer to node at the point of insertion after balancing
        */
        AVLNode<T>* _insert(AVLNode<T>* node , T key);

        /**
        * @brief Delete from AVL Tree and balance at the point of deletion
        *
        * @param node Pointer to root
        * @param key Key to be deleted
        * @return pointer to node at the point of deletion after balancing
        */
        AVLNode<T>* _remove(AVLNode<T>* node , T key);

        /**
        * @brief Search in AVL Tree
        *
        * @param node Pointer to root
        * @param key Key to be searched
        * @return pointer to node whose data value equals key
        */
        AVLNode<T>* _search(AVLNode<T>* node , T key);

};

/**
* @brief Preorder traversal of the AVL Tree
*
* @param node Pointer to root of the subtree to be traversed
*/
template<class T>
void preorder(AVLNode<T>* node);

/**
* @brief Inorder traversal of the AVL Tree
*
* @param node Pointer to root of the subtree to be traversed
*/
template<class T>
void inorder(AVLNode<T>* node);

template<class T>
AVLNode<T>* AVLTree<T>::_insert(AVLNode<T>* node , T key){
    if(node == NULL)
        return new AVLNode<T>(key);
    
    if(cmp(key , node -> data)<0)
        node -> left = _insert(node -> left , key);
    else if(cmp(key, node -> data)>0)
            node -> right = _insert(node -> right , key);

    return balance(node , key);
}

template<class T>
AVLNode<T>* AVLTree<T>::_remove(AVLNode<T>* node , T key){

    if(node == NULL)
        return node;
    else if(cmp(key,node -> data)<0)
        node -> left = _remove(node -> left , key);
    else if(cmp(key,node -> data)>0)
        node -> right = _remove(node -> right , key);
    else if(node -> left && node -> right){
        AVLNode<T>* temp = findMin(node -> right);
        node -> data = temp -> data;
        node -> right = _remove(node -> right , temp -> data);
    }
    else{
        AVLNode<T>* temp = node;
        if(node -> left == NULL)
            node = node -> right;
        else if(node -> right == NULL)
            node = node -> left;
        delete temp;
    }
    if(node == NULL)
        return node;
    
    node->height = std::max(node -> left -> getHeight() , node -> right -> getHeight()) + 1;
    int bf = node -> getBF();
    if (bf > 1 && node->left->getBF() >= 0)
        return rightRotate(node);
 
    // Left Right Case
    if (bf > 1 && node->left->getBF() < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Right Case
    if (bf < -1 && node->right->getBF() <= 0)
        return leftRotate(node);
 
    // Right Left Case
    if (bf < -1 && node->right->getBF() > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

template<class T>
AVLNode<T>* AVLTree<T>::_search(AVLNode<T>* node , T key){
    if(node == NULL)
        return node;
    if(cmp(node->data,key)==0)
        return node;
    if(cmp(key,node->data)<0)
        return _search(node->left , key);
    return _search(node->right , key);
}

#include "AVLTree.cpp"

#endif // __AVL_Tree_H__