#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here


bool equalPaths(Node * root)
{
    if(root == nullptr) // base case
    {
        return true;
    }

    if(root->left == nullptr && root->right == nullptr) // base case, node is a leaf node
    {
        return true;
    }

    // if((root->left == nullptr && root->right != nullptr) 
    // || (root->left != nullptr && root->right == nullptr)) // root node has only 1 subtree
    // {
    //     return false; // paths cannot be equal
    // } 

    Node* leftChild = root->left;
    Node* rightChild = root->right;

    // if((leftChild->left == nullptr && leftChild->right == nullptr) 
    // && (rightChild->left == nullptr && rightChild->right == nullptr)) // both children leaf nodes
    // {
    //     return true; // does this count as base case? is it also redundant?
    // }


    /* 
        check to see if subtrees have same length, 
        as we recurse down, this will see if there is a difference
    */
    bool subtreesEqual = getLength(leftChild) == getLength(rightChild);  

    return equalPaths(leftChild) && equalPaths(rightChild) && subtreesEqual;

}

int getLength(Node* root)
{
    if(root == nullptr) // base case, root is null
    {
        return 0;
    }

    if(root->left == nullptr && root->right == nullptr) // base case, root is leaf node
    {
        return 1;
    }

    int leftDepth = getLength(root->left);
    int rightDepth = getLength(root->right);

    if(leftDepth > 0 && rightDepth > 0) // left and right have subtrees
    {
        if(leftDepth < rightDepth) // gets smaller height between left and right (right case also accounts for equal)
        {
            return leftDepth + 1;
        }
        else
        {
            return rightDepth + 1;
        }
    }

    if(leftDepth > 0) // subtree only in left
    {
        return leftDepth + 1;
    }
    else // subtree only in right
    {
        return rightDepth + 1;
    }

}

