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
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node); // TODO, balances tree after insertion
    void removeFix(AVLNode<Key, Value>* node, int8_t diff); // TODO, balances tree after removal
    void rotateLeft(AVLNode<Key, Value>* node); // TODO
    void rotateRight(AVLNode<Key, Value>* node); // TODO
    
};


template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node) // mirror of rotateRight
{
    // TODO
    AVLNode<Key, Value>* parent = node->getParent();
    AVLNode<Key, Value>* y = node;
    AVLNode<Key, Value>* x = node->getRight();
    AVLNode<Key, Value>* b = x->getLeft();

    x->setLeft(y);
    y->setParent(x);
    y->setRight(b);
    if(b != nullptr)
    {
        b->setParent(y);
    }
    x->setParent(parent);

    if(parent == nullptr) 
    {
        this->root_ = x;
    } 
    else 
    {
        if(parent->getLeft() == y) 
        {
            parent->setLeft(x);
        } 
        else 
        {
            parent->setRight(x);
        }
    }
    

}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node)
{
    // TODO

    AVLNode<Key, Value>* parent = node->getParent();
    AVLNode<Key, Value>* y = node;
    AVLNode<Key, Value>* x = node->getLeft();
    AVLNode<Key, Value>* b = x->getRight();

    x->setRight(y);
    y->setParent(x);
    y->setLeft(b);
    if(b != nullptr)
    {
        b->setParent(y);
    }
    x->setParent(parent);

    if(parent == nullptr) 
    {
        this->root_ = x;
    } 
    else 
    {
        if(parent->getRight() == y) 
        {
            parent->setRight(x);
        } 
        else 
        {
            parent->setLeft(x);
        }
    }
    
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO

    if(this->root_ == nullptr) // empty tree
    {
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        return;
    }

    //insert

    // BinarySearchTree<Key, Value>::insert(new_item); // insert same as bst

    if (this->root_ == nullptr) 
    {
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        return;
    }

    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);
    AVLNode<Key, Value>* parent = nullptr;

    while(current != nullptr) 
    {
        parent = current;
        if(new_item.first < current->getKey()) 
        {
            current = current->getLeft();
        } 
        else if(new_item.first > current->getKey()) 
        {
            current = current->getRight();
        } 
        else 
        {
            current->setValue(new_item.second);
            return;
        }
    }

    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
    if(new_item.first < parent->getKey()) 
    {
        parent->setLeft(newNode);
    } 
    else 
    {
        parent->setRight(newNode);
    }


    // balancing
    // AVLNode<Key, Value>* node = static_cast<AVLNode<Key, Value>*>(this->internalFind(new_item.first)); // node we inserted
    // AVLNode<Key, Value>* parent = node->getParent();


    if(parent == nullptr) // no parent, no need for balancing
    {
        return;
    }
    
    // update balances
    newNode->setBalance(0);
    if(parent->getBalance() == -1 || parent->getBalance() == 1)
    {
        parent->setBalance(0);
    }
    else if(parent->getBalance() == 0)
    {
        if(parent->getLeft() == newNode) // node is left of parent
        {
            parent->setBalance(-1);
        }
        if(parent->getRight() == newNode) // node is right of parent
        {
            parent->setBalance(1);
        }
        insertFix(parent, newNode); // call insertFix!!!
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
    if(this->root_ == nullptr) // tree is empty
    {
        return;
    }

    //traverse to node
    AVLNode<Key, Value>* node = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::internalFind(key));
    if(node == nullptr) // node not found
    {
        return;
    }
    AVLNode<Key, Value>* parent = nullptr;

    

    

    // check if node has 2 children
    if (node->getLeft() && node->getRight()) 
    {
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(node));
        BinarySearchTree<Key, Value>::nodeSwap(node, pred);
        parent = node->getParent(); 
        node = pred;
    }

    // check balance
    if(BinarySearchTree<Key, Value>::isBalanced()) // checks if tree is balanced
    {
        return; // we can skip balancing process
    }

   
    parent = static_cast<AVLNode<Key, Value>*>(node->Node<Key, Value>::getParent());
    int8_t diff = 0;
    if(parent != nullptr)
    {
        if(parent->getLeft() == node) // node is a left child
        {
            diff = 1;
        }
        if(parent->getRight() == node) // node is a right child
        {
            diff = -1;
        }
    }


    // remove node
    // already found node
    if (node == nullptr)
    {
        return; // no key is found
    }

    // Case 1: Node has two children
    if (node->getLeft() && node->getRight()) 
    {
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(node));
        if (pred == nullptr)
        {
            return;
        }

        nodeSwap(node, pred);
        node = pred;

        // relinking pointers after nodeswap
        AVLNode<Key, Value>* child = node->getLeft(); // pred never has a right child
        AVLNode<Key, Value>* parent = node->getParent();

        // relink child parent pointer
        if(child != nullptr) 
        {
            child->setParent(parent);
        }

        // relink parent pointer to child
        if (parent != nullptr)
        {
            if (parent->getLeft() == node)
            {
                parent->setLeft(child);
            } 
            else if (parent->getRight() == node)
            {
                parent->setRight(child);
            }
        } 
        else
        {
            this->root_ = child; // when we delete the root
        }

        // patch tree
        removeFix(parent, diff);
        delete node;
        return;
    }

    // Case 2 & 3: Node has at most one child
    //std::cout << "one child or leaf!" << std::endl;
    AVLNode<Key, Value>* child = nullptr;
    if(node->getLeft()) 
    {
        child = node->getLeft();
    } 
    else if(node->getRight()) 
    {
        child = node->getRight();
    }

    if (child != nullptr) {
        child->setParent(node->getParent());
    }


    AVLNode<Key, Value>* parent = node->getParent();

    if(node == this->root_)
    {
        this->root_ = child;
    }
    else if(parent != nullptr && parent->getLeft() == node)
    {
        parent->setLeft(child);
    }
    else if(parent != nullptr && parent->getRight() == node)
    {
        parent->setRight(child);
    }

    //std::cout << "Ready to delete node with key: " << node->getKey() << std::endl;
    // patch tree
    removeFix(parent, diff);
    delete node;
    

    //done?

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
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node)
{

    if(node == nullptr)
    {
        return;
    }

    AVLNode<Key, Value>* grandp = parent->getParent();

    if(parent == nullptr || grandp == nullptr) // base case
    {
        return;
    }

    if(parent == grandp->getLeft()) // p is left child of g
    {

        grandp->updateBalance(-1); // update balance, correct???
        if(grandp->getBalance() == 0)
        {
            return;
        }
        if(grandp->getBalance() == -1)
        {
            insertFix(grandp, parent); // recursive call
        }
        if(grandp->getBalance() == -2)
        {
            if(node == parent->getLeft()) // zig-zig case
            {
                rotateRight(grandp);
                parent->setBalance(0); // edit
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
    if(parent == grandp->getRight()) // p is right child of g, mirror of above
    {
        grandp->updateBalance(1); 
        if(grandp->getBalance() == 0)
        {
            return;
        }
        if(grandp->getBalance() == 1)
        {
            insertFix(grandp, parent); // recursive call
        }
        if(grandp->getBalance() == 2)
        {
            if(node == parent->getRight()) // zig-zig case
            {
                rotateLeft(grandp);
                parent->setBalance(0); 
                grandp->setBalance(0);
            }
            if(node == parent->getLeft()) // zig-zag case
            {
                rotateRight(parent);
                rotateLeft(grandp);
                if(node->getBalance() == 1)
                {
                    parent->setBalance(0);
                    grandp->setBalance(-1);
                    node->setBalance(0);
                }
                if(node->getBalance() == 0)
                {
                    parent->setBalance(0);
                    grandp->setBalance(0);
                    node->setBalance(0);
                    
                }
                if(node->getBalance() == -1)
                {
                    parent->setBalance(-1);
                    grandp->setBalance(0);
                    node->setBalance(0);
                }

            }
        }

    // done?

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
        if(parent->getLeft() == node) // node is a left child
        {
            ndiff = 1;
        }
        else // node is a right child
        {
            ndiff = -1;
        }
    }
    
    //AVLNode<Key, Value>* child = node; // fix, need to find out which child we are operating on, will we have to write more mirror cases??
    AVLNode<Key, Value>* grandch = parent->getParent();

    // balance cases
    if(diff == -1) // operating on left child
    {
        AVLNode<Key, Value>* child = node->getLeft();
        if(node->getBalance() + diff == -2) // heavy on left
        {
            
            if(child->getBalance() == -1) // zig-zig case
            {
                rotateRight(node);
                node->setBalance(0);
                child->setBalance(0);
                removeFix(parent, ndiff); // recursive call
            }
            if(child->getBalance() == 0) // zig-zig case, although doesnt rly matter
            {
                rotateRight(node);
                node->setBalance(-1);
                child->setBalance(1);
            }
            if(child->getBalance() == 1) // zig-zag case
            {
                int8_t grandchBalance = grandch->getBalance();
                grandch = child->getRight();
                rotateLeft(child);
                rotateRight(node);
                if(grandchBalance == 1)
                {
                    node->setBalance(0);
                    child->setBalance(-1);
                    grandch->setBalance(0);
                }
                if(grandchBalance == 0)
                {
                    node->setBalance(0);
                    child->setBalance(0);
                    grandch->setBalance(0);
                }
                if(grandchBalance == -1)
                {
                    node->setBalance(1);
                    child->setBalance(0);
                    grandch->setBalance(0);
                }
            }
            removeFix(parent, ndiff); // recursive call
        }
        if(node->getBalance() + diff == -1)
        {
            node->setBalance(-1);
        }
        if(node->getBalance() + diff == 0)
        {
            node->setBalance(0);
            removeFix(parent, ndiff); // recursive call
        }


    }
    if(diff == 1) // mirrored, operating on right child
    {
        AVLNode<Key, Value>* child = node->getRight();
        if(node->getBalance() + diff == 2) // heavy on right
        {
            
            if(child->getBalance() == 1) // zig-zig case
            {
                rotateLeft(node);
                node->setBalance(0);
                child->setBalance(0);
                removeFix(parent, ndiff); // recursive call
            }
            if(child->getBalance() == 0) // zig-zig case, although doesnt rly matter
            {
                rotateRight(node);
                node->setBalance(1);
                child->setBalance(-1);
            }
            if(child->getBalance() == -1) // zig-zag case
            {
                int8_t grandchBalance = grandch->getBalance();
                grandch = child->getLeft();
                rotateRight(child);
                rotateLeft(node);
                if(grandchBalance == -1)
                {
                    node->setBalance(0);
                    child->setBalance(1);
                    grandch->setBalance(0);
                }
                if(grandchBalance == 0)
                {
                    node->setBalance(0);
                    child->setBalance(0);
                    grandch->setBalance(0);
                }
                if(grandchBalance == 1)
                {
                    node->setBalance(-1);
                    child->setBalance(0);
                    grandch->setBalance(0);
                }
            }
            removeFix(parent, ndiff); // recursive call
        }
        if(node->getBalance() + diff == 1)
        {
            node->setBalance(1);
        }
        if(node->getBalance() + diff == 0)
        {
            node->setBalance(0);
            removeFix(parent, ndiff); // recursive call
        }


    }
    // else // dont know if this is necessary, might be balanced anyways if triggered
    // {
    //     removeFix(parent, ndiff);
    // }


}


#endif
