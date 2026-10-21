#ifndef __AVL_NODE_H__
#define __AVL_NODE_H__


#include <cstddef>
/**
     * @brief Class to store a node of an AVL Tree
     */
template<class T>
class AVLNode{
    
    public:
        /**
         * @brief Constructor of an AVL tree node, which consists of the data value, pointer to left child, pointer to right child and its height
         *
         * @param value The data object
         * @return An AVL node with data value equals to the parameter and children as null pointers
         */
        AVLNode(const T& value) : data(value) , left(NULL) , right(NULL) , height(1) {}
        ~AVLNode() {}
        /**
         * @brief A function to get the height of the AVL tree node
         * @return The height of the AVL tree node
         */
        int getHeight();
        /**
         * @brief A function to get the balancing factor of an AVL Tree node
         * @return The balancing factor og the AVL Tree node
         */
        int getBF();
        //data value
        T data;
        //pointer to left child
        AVLNode* left;
        //pointer to right child
        AVLNode* right;
        //height of the node
        int height;
};

template<class T>
int AVLNode<T>::getHeight(){
    if(this == NULL)
        return 0;
    return this -> height;
}

template<class T>
int AVLNode<T>::getBF(){
    if(this == NULL)
        return 0;
    return this -> left -> getHeight() - this -> right -> getHeight();
}

#endif // __AVL_NODE_H__