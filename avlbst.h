#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

    // helper functions
    void rotateLeft(AVLNode<Key, Value>* node); // TODO
    void rotateRight(AVLNode<Key, Value>* node); // TODO

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}



// helper functions

template<class Key, class Value>
void AVLNode<Key, Value>::rotateLeft(AVLNode<Key, Value>* node) // mirror of rotateRight
{
    // TODO
    AVLNode<Key, Value>* parent = node->getParent();
    AVLNode<Key, Value>* y = node;
    AVLNode<Key, Value>* x = node->getRight();
    AVLNode<Key, Value>* b = x->getLeft();

    parent->setRight(x);
    x->setparent(parent);
    x->setLeft(y);
    y->setParent(x);
    y->setright(b);
    b->setparent(y);

}

template<class Key, class Value>
void AVLNode<Key, Value>::rotateRight(AVLNode<Key, Value>* node)
{
    // TODO

    AVLNode<Key, Value>* parent = node->getParent();
    AVLNode<Key, Value>* y = node;
    AVLNode<Key, Value>* x = node->getLeft();
    AVLNode<Key, Value>* b = x->getRight();

    parent->setLeft(x);
    x->setParent(parent);
    x->setRight(y);
    y->setParent(x);
    y->setLeft(b);
    b->setParent(y);
    
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key, Value>* node, int8_t diff); // TODO, balances tree after insertion
    void removeFix(AVLNode<Key, Value>* node, int8_t diff); // TODO, balances tree after removal
    
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO

    BinarySearchTree<Key, Value>::insert(key); // do same insert as BST

    if(!BinarySearchTree<Key, Value>::isBalanced()) // check tree balance
    {
        insertFix(); // balance in helper function
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO

    // traverse to node (and swap if necessary)
    // should be same as BST remove
    if(root_ == nullptr) // tree is empty
    {
        return;
    }

    Node<Key, Value>* node = root_;
    Node<Key, Value>* parent = nullptr;

    //traverse to node
    while(node != nullptr && node->getKey() != key) 
    {
        parent = node;
        if(key < node->getKey()) 
        {
            node = node->getLeft();
        } 
        else 
        {
            node = node->getRight();
        }
    }

    // check if node has 2 children
    if (node->getLeft() && node->getRight()) 
    {
        Node<Key, Value>* pred = predecessor(node);
        nodeSwap(node, pred);
        parent = node->getParent(); 
        node = pred;
    }



    // check balance
    if(BinarySearchTree<Key, Value>::isBalanced()) // checks if tree is balanced
    {
        return; // we can skip balancing process
    }

    AVLNode<Key, Value>* parent = node->Node<Key, Value>::getParent();

    if(parent != nullptr)
    {
        if(parent->BinarySearchTree<Key, Value>::getLeft() == node) // node is a left child
        {
            node->updateBalance(1);
        }
        if(parent->BinarySearchTree<Key, Value>::getRight() == node) // node is a right child
        {
            node->updateBalance(-1);
        }
    }

    // remove node


    // patch tree



}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* node, int8_t diff)
{

    AVLNode<Key, Value>* parent = node->getParent();
    AVLNode<Key, Value>* grandp = parent->getParent();

    if(parent == nullptr || grandp == nullptr) // base case
    {
        return;
    }

    if(parent == grandp->getLeft()) // p is left child of g
    {

        grandp.balance_ += -1 // update balance, correct???
        if(grandp->getBalance() == 0)
        {
            return;
        }
        if(grandp->getBalance() == -1)
        {
            //insertFix(grandp, parent); // this is not correct but is how its written in slides
        }
        if(grandp->getBalance() == -2)
        {
            if(node == parent->getLeft()) // zig-zig case
            {
                rotateRight(grandp);
                setBalance(parent);
                grandp->setBalance(0);
            }
            if(node == parent->getRight()) // zig-zag case
            {
                rotateLeft(parent);
                rotateRight(grandp);
                if(node->getBalance() == -1)
                {
                    parent->setBalance(0);
                    grandp->setBalance(1);
                    node->setBalance(0);
                }
                if(node->getBalance() == 0)
                {
                    parent->setBalance(0);
                    grandp->setBalance(0);
                    node->setBalance(0);
                    
                }
                if(node->getBalance() == 1)
                {
                    parent->setBalance(1);
                    grandp->setBalance(0);
                    node->setBalance(0);
                }

            }
        }


    }
    if(parent == grandp->getLeft()) // p is right child of g, mirror of above
    {



    }

}


template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node, int8_t diff) 
{

    if(node == nullptr)
    {
        return;
    }

    // compute recursive calls args
    AVLNode<Key, Value>* parent = node->getParent();
    int8_t ndiff = 0;
    if(parent != nullptr)
    {
        if(parent->BinarySearchTree<Key, Value>::getLeft() == node) // node is a left child
        {
            ndiff = 1;
        }
        else // node is a right child
        {
            ndiff = -1;
        }
    }
    
    AVLNode<Key, Value>* child = node; // fix, need to find out which child we are operating on, will we have to write more mirror cases??
    AVLNode<Key, Value>* grandp = parent->getparent();



    // balance cases
    if(diff == -1) // operating on left child
    {

        if(node->getBalance() + diff == -2) // heavy on left
        {
            // do we need another mirror for child?????

            
            if(child->getBalance() == -1) // zig-zig case
            {
                rotateRight(node);
                node.setBalance(0);
                child.setBalance(0);
                removeFix(parent, ndiff); // recursive call
            }
            if(child->getBalance() == 0) // zig-zig case, although doesnt rly matter
            {
                rotateRight(node);
                node.setBalance(-1);
                child.setBalance(1);
            }
            if(child->getBalance() == 1) // zig-zag case
            {
                int8_t grandpBalance = grandp->getBalance();
                grandp = child->getRight();
                rotateLeft(child);
                rotateRight(node);
                if(grandpBalance == 1)
                {
                    node.setBalance(0);
                    child.setBalance(-1);
                    grandp->setBalance(0);
                }
                if(grandpBalance == 0)
                {
                    node.setBalance(0);
                    child.setBalance(0);
                    grandp->setBalance(0);
                }
                if(grandpBalance == -1)
                {
                    node.setBalance(1);
                    child.setBalance(0);
                    grandp->setBalance(0);
                }
            }
            removeFix(parent, ndiff); // recursive call
        }
        if(node->getBalance() + diff == -1)
        {
            node->setBalance = -1;
        }
        if(node->getBalance() + diff == 0)
        {
            node->setBalance(0);
            removeFix(parent, ndiff); // recursive call
        }


    }
    if(diff == 1) // mirrored
    {



    }
    // else // dont know if this is necessary, might be balanced anyways if triggered
    // {
    //     removeFix(parent, ndiff);
    // }


}


#endif
