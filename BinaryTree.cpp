// FILE: binaryTree.cpp
// TEMPLATE CLASS BINARY SEARCH
// TREE


#ifndef BIN_TREE_H
#define BIN_TREE_H
#include "BinaryTree.h"
// Specification of the class

template <class keyType, class dataType>

BST(): root(nullptr){}

~BST(){
    destroyTree(root);
}