#include "AVLTree.h"
#include <iostream>

template<class T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* y){

    AVLNode<T>* x = y -> left;
    AVLNode<T>* T2 = x -> right;

    x -> right = y;
    y -> left = T2;

    y -> height = std::max((y -> left)->getHeight() , (y -> right)->getHeight()) + 1;
    x -> height = std::max((x -> left)->getHeight() , (x -> right)->getHeight()) + 1;

    return x;
}

template<class T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* x){


    AVLNode<T>* y = x -> right;
    AVLNode<T>* T2 = y -> left;


    y -> left = x;
    x -> right = T2;

    x -> height = std::max(x -> left -> getHeight() , x -> right -> getHeight()) + 1;
    y -> height = std::max(y -> left -> getHeight() , y -> right -> getHeight()) + 1;

    return y;
}

template<class T>
AVLNode<T>* AVLTree<T>::balance(AVLNode<T>* node , T key){

    node -> height = 1 + std::max(node -> left -> getHeight() , node -> right -> getHeight());
    int bf = node -> getBF();
    // Left Left Case
    if(bf > 1 && node->left && (cmp(key , node -> left -> data)<0))
        return rightRotate(node);
    // Left Right Case
    if(bf > 1 && node->left && (cmp(node -> left -> data , key)<0)){
        node -> left = leftRotate(node -> left);
        return rightRotate(node);
    }
    // Right Left Case
    if(bf < -1 && node->right && (cmp(key , node -> right -> data)<0)){
        node -> right = rightRotate(node -> right);
        return leftRotate(node);
    }
    // Right Right Case
    if(bf < -1 && node->right && (cmp(node -> right -> data , key)<0))
        return leftRotate(node);
    return node;

}

template<class T>
AVLNode<T>* AVLTree<T>::findMin(AVLNode<T>* node){
    if(node == NULL)
        return node;
    if(node -> left == NULL)
        return node;
    return findMin(node -> left);
}

template<class T>
AVLNode<T>* AVLTree<T>::successor(AVLNode<T>* ro,AVLNode<T>* node){
    //std::cout<<"\n______HERE______\n";
    //printf("\n______%lf,%lf and %lf,%lf______\n",node->data->pl.first,node->data->pl.second,node->data->pu.first,node->data->pu.second);
    if(root==NULL){
        return NULL;
    }

    AVLNode<T>* succ=NULL;
    while (true)
    {
        // if the given key is less than the root node, visit the left subtree
        if(cmp(node->data,ro->data)<0)
        {
            // update successor to the current node before visiting left subtree
            succ = ro;
            ro = ro->left;
        }
 
        // if the given key is more than the root node, visit the right subtree
        else if (cmp(node->data,ro->data)>0) {
            ro = ro->right;
        }
 
        // if a node with the desired value is found, the successor is the minimum
        // value node in its right subtree (if any)
        else {
            if (ro->right) {
                succ = findMin(ro->right);
            }
            break;
        }
 
        // if the key doesn't exist in the binary tree, return next greater node
        if (!ro) {
            return succ;
        }
    }
 
    return succ;
}

template<class T>
AVLNode<T>* AVLTree<T>::findMax(AVLNode<T>* node){
    if(node == NULL)
        return node;
    if(node -> right == NULL)
        return node;
    return findMax(node -> right);
}

template<class T>
AVLNode<T>* AVLTree<T>::predecessor(AVLNode<T>* ro,AVLNode<T>* node){
    if(node -> left !=NULL)
        return findMax(node -> left);

    AVLNode<T>* pred=NULL;
    while (ro != NULL)
    {
        if (cmp(node->data,ro->data)>0)
        {
            pred = ro;
            ro = ro->right;
        }
        else if (cmp(node->data,root->data)<0)
            root = ro->left;
        else
            break;
    }
 
    return pred;
}

template<class T>
void AVLTree<T>::insert(T key){
    if(_search(root , key)!=NULL)
        return;
    root =  _insert(root , key);
    return;
}

template<class T>
void AVLTree<T>::remove(T key){
    root = _remove(root , key);
    return;
}

template<class T>
AVLNode<T>* AVLTree<T>::search(T key){
    return _search(root , key);
}
template<class T>
AVLNode<T>* AVLTree<T>::find_right(AVLNode<T>* node, T key){
    if (node == NULL)
        return NULL;
    if (cmp(node->data,key)==0)
        return node;

    else if (cmp(node->data,key)>0) {
        auto k = find_right(node->left,key);
        if (k == NULL)
            return node;
        else
            return k;
    }

    else
        return find_right(node->right,key);
}

template<class T>
AVLNode<T>* AVLTree<T>:: find_left(AVLNode<T>* node, T key){

    if (node == NULL)
        return NULL;
    if (cmp(node->data,key)==0)
        return node;

    else if (cmp(node->data,key)<0) {
        auto k = find_left(node->right,key);
        if (k == NULL)
            return node;
        else
            return k;
    }

    else
        return find_left(node->left,key);
}

template<class T>
void  inorder(AVLNode<T>* node){
    if(node == NULL)
        return;
    inorder(node -> left);
    printf("\ninorder______%lf,%lf and %lf,%lf______\n",node->data->pl.first,node->data->pl.second,node->data->pu.first,node->data->pu.second);
    inorder(node -> right);
    return;
}

template<class T>
void preorder(AVLNode<T>* node){
    if(node == NULL)
        return;
    std::cout << node -> data << " ";
    preorder(node -> left);
    preorder(node -> right);
    return;
}