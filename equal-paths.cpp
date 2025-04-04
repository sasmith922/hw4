#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
# include <algorithm>

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

    // Node* leftChild = root->left;
    // Node* rightChild = root->right;

    // bool subtreesEqual = getLength(leftChild) == getLength(rightChild);  

    // return equalPaths(leftChild) && equalPaths(rightChild) && subtreesEqual;

    int leafDepth = -1;
    return equalPathsHelper(root, 0, leafDepth);

}

int getLength(Node* root)
{
    if(root == nullptr) // base case, root is null
    {
        return 0;
    }


    int leftDepth = getLength(root->left);
    int rightDepth = getLength(root->right);

    return 1 + max(leftDepth, rightDepth);

}

bool equalPathsHelper(Node* root, int depth, int& leafDepth)
{
    if (root == nullptr) return true;

    // If it's a leaf
    if (root->left == nullptr && root->right == nullptr)
    {
        if (leafDepth == -1) leafDepth = depth;
        return depth == leafDepth;
    }

    // Check subtrees
    return equalPathsHelper(root->left, depth + 1, leafDepth) &&
           equalPathsHelper(root->right, depth + 1, leafDepth);
}

