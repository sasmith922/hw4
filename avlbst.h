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

    // if(this->root_ == nullptr) // empty tree
    // {
    //     this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
    //     return;
    // }

    // //insert

    // // BinarySearchTree<Key, Value>::insert(new_item); // insert same as bst

    // if (this->root_ == nullptr) 
    // {
    //     this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
    //     return;
    // }

    // AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);
    // AVLNode<Key, Value>* parent = nullptr;

    // while(current != nullptr) // walking to node
    // {
    //     parent = current;
    //     if(new_item.first < current->getKey()) 
    //     {
    //         current = current->getLeft();
    //     } 
    //     else if(new_item.first > current->getKey()) 
    //     {
    //         current = current->getRight();
    //     } 
    //     else 
    //     {
    //         current->setValue(new_item.second);
    //         return;
    //     }
    // }

    // AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
    // if(new_item.first < parent->getKey()) 
    // {
    //     parent->setLeft(newNode);
    // } 
    // else 
    // {
    //     parent->setRight(newNode);
    // }


    // // balancing
    // // AVLNode<Key, Value>* node = static_cast<AVLNode<Key, Value>*>(this->internalFind(new_item.first)); // node we inserted
    // // AVLNode<Key, Value>* parent = node->getParent();


    // if(parent == nullptr) // no parent, no need for balancing
    // {
    //     return;
    // }
    
    // // update balances
    // newNode->setBalance(0);
    // if(parent->getBalance() == -1 || parent->getBalance() == 1)
    // {
    //     parent->setBalance(0);
    // }
    // else if(parent->getBalance() == 0)
    // {
    //     if(parent->getLeft() == newNode) // node is left of parent
    //     {
    //         parent->setBalance(-1);
    //     }
    //     if(parent->getRight() == newNode) // node is right of parent
    //     {
    //         parent->setBalance(1);
    //     }
    //     insertFix(parent, newNode); // call insertFix!!!
    // }

    // If tree is empty, create root
    if(this->root_ == nullptr)
    {
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        return;
    }

    // Start from root and walk to insertion point
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
            // Key already exists, update value
            current->setValue(new_item.second);
            return;
        }
    }

    // Create and attach new node
    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
    if(new_item.first < parent->getKey())
    {
        parent->setLeft(newNode);
    }
    else
    {
        parent->setRight(newNode);
    }

    newNode->setBalance(0);

    // Rebalancing
    if(parent->getBalance() == -1 || parent->getBalance() == 1)
    {
        parent->setBalance(0); // was imbalanced, now balanced
    }
    else if(parent->getBalance() == 0)
    {
        // update balance and start fixing
        if(parent->getLeft() == newNode)
        {
            parent->setBalance(-1);
        }
        else
        {
            parent->setBalance(1);
        }
        insertFix(parent, newNode);
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

    //std::cout << "called remove" << key << std::endl;
    std::cout << "[remove] Removing key: " << key << std::endl;


    AVLNode<Key, Value>* node = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    if (node == nullptr) return;

    // Case 1: node has two children → swap with predecessor, reduce to 0/1-child case
    if (node->getLeft() != nullptr && node->getRight() != nullptr)
    {
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(node));
        nodeSwap(pred, node);
        //node = pred; // pred is now in the position to be deleted
    }

    // Now node has at most one child
    AVLNode<Key, Value>* child = nullptr;
    if (node->getLeft() != nullptr)
    {
        child = static_cast<AVLNode<Key, Value>*>(node->getLeft());
    }
    else if (node->getRight() != nullptr)
    {
        child = static_cast<AVLNode<Key, Value>*>(node->getRight());
    }

    AVLNode<Key, Value>* parent = static_cast<AVLNode<Key, Value>*>(node->getParent());
    int diff = 0;

    // IMPORTANT: compute diff BEFORE cutting the node from its parent
    if (parent != nullptr)
    {
        if (parent->getLeft() == node)
        {
            diff = 1;
        }
        else
        {
            diff = -1;
        }
    }

    // Reconnect child to parent
    if (parent != nullptr)
    {
        // Compute diff FIRST
        if (parent->getLeft() == node)
            diff = 1;
        else
            diff = -1;

        // THEN unlink the node
        if (diff == 1)
            parent->setLeft(child);
        else
            parent->setRight(child);
    }
    else
    {
        this->root_ = child;
    }

    if (child != nullptr)
    {
        child->setParent(parent);
    }

    delete node;

    if (parent != nullptr)
    {
        std::cout << "[remove] Calling removeFix on parent: " 
          << parent->getKey() << " with diff: " << static_cast<int>(diff) << std::endl;
        removeFix(parent, diff);
    }
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

    if(parent == nullptr) return;
    //std::cout << "insertfix called" << std::endl;

    AVLNode<Key, Value>* grandparent = parent->getParent();
    if(grandparent == nullptr)
    {
        return;
    }


    if(grandparent == nullptr) return;

    // Determine if parent is left or right child of grandparent
    if (grandparent->getLeft() == parent)
    {
        grandparent->updateBalance(-1);

        if (grandparent->getBalance() == 0)
        {
            //std::cout << "insertFix stopped (balanced)\n";
            return;
        }
        else if (grandparent->getBalance() == -1)
        {
            //std::cout << "insertFix recursing up (still unbalanced)\n";
            insertFix(grandparent, parent);
        }
        else if (grandparent->getBalance() == -2)
        {
            //std::cout << "rebalance\n";
            // Zig-Zig Left (left-left)
            if (parent->getLeft() == node)
            {
                //std::cout << "zig zig left\n";
                rotateRight(grandparent);
                parent->setBalance(0);
                grandparent->setBalance(0);
            }
            // Zig-Zag Left-Right
            else if (parent->getRight() == node)
            {
                //std::cout << "zig zag left-right\n";
                rotateLeft(parent);
                rotateRight(grandparent);

                int b = node->getBalance();
                if (b == 1)
                {
                    parent->setBalance(0);
                    grandparent->setBalance(-1);
                }
                else if (b == -1)
                {
                    parent->setBalance(1);
                    grandparent->setBalance(0);
                }
                else // b == 0
                {
                    parent->setBalance(0);
                    grandparent->setBalance(0);
                }
                node->setBalance(0);
            }
        }
    }
    // Case 2: parent is the right child of grandparent
    else
    {
        grandparent->updateBalance(1);

        if (grandparent->getBalance() == 0)
        {
            //std::cout << "insertFix stopped (balanced)\n";
            return;
        }
        else if (grandparent->getBalance() == 1)
        {
            //std::cout << "insertFix recursing up (still unbalanced)\n";
            insertFix(grandparent, parent);
        }
        else if (grandparent->getBalance() == 2)
        {
            //std::cout << "rebalance\n";
            // Zig-Zig Right (right-right)
            if (parent->getRight() == node)
            {
                //std::cout << "zig zig right\n";
                rotateLeft(grandparent);
                parent->setBalance(0);
                grandparent->setBalance(0);
            }
            // Zig-Zag Right-Left
            else if (parent->getLeft() == node)
            {
                //std::cout << "zig zag right-left\n";
                rotateRight(parent);
                rotateLeft(grandparent);

                int b = node->getBalance();
                if (b == 1)
                {
                    parent->setBalance(0);
                    grandparent->setBalance(-1);
                }
                else if (b == -1)
                {
                    parent->setBalance(1);
                    grandparent->setBalance(0);
                }
                else // b == 0
                {
                    parent->setBalance(0);
                    grandparent->setBalance(0);
                }
                node->setBalance(0);
            }
        }
    }

}


template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node, int8_t diff) 
{

    if(node == nullptr)
    {
        return;
    }

    std::cout << "[removeFix] node: " << node->getKey() << ", diff: " << diff
          << ", balance: " << (int)node->getBalance()
          << ", newBalance: " << (int)(node->getBalance() + diff) << std::endl;

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
    // DO NOT OPERATE ON/WITH PARENT, SHOULD ONLY BE FOR RECURSIVE CALL
    

    // balance cases
    if(diff == -1) // operating on left child
    {
       
        if(node->getBalance() + diff == -2) // heavy on left
        {
            std::cout << "[removeFix] Rotating at node " << node->getKey() << std::endl;
            AVLNode<Key, Value>* child = node->getLeft();
            if(child->getBalance() == -1) // zig-zig case
            {
                std::cout << "  >> Rotating at node " << node->getKey()
          << ", child: " << child->getKey()
          << ", child balance: " << (int)child->getBalance() << std::endl;

                rotateRight(node);
                node->setBalance(0);
                child->setBalance(0);
                removeFix(parent, ndiff); // recursive call
            }
            else if(child->getBalance() == 0) // zig-zig case, although doesnt rly matter
            {
                std::cout << "  >> Rotating at node " << node->getKey()
          << ", child: " << child->getKey()
          << ", child balance: " << (int)child->getBalance() << std::endl;

                rotateRight(node);
                node->setBalance(0);
                child->setBalance(0);
                return; // done early
                //removeFix(parent, ndiff);//temp
            }
            else if(child->getBalance() == 1) // zig-zag case
            {
                AVLNode<Key, Value>* grandch = child->getRight(); // declare grandchild node here, only used in zig-zag case
                int8_t grandchBalance = grandch->getBalance();
                std::cout << "  >> Rotating at node " << node->getKey()
          << ", child: " << child->getKey()
          << ", child balance: " << (int)child->getBalance() << std::endl;

                rotateLeft(child);
                std::cout << "  >> Rotating at node " << node->getKey()
          << ", child: " << child->getKey()
          << ", child balance: " << (int)child->getBalance() << std::endl;

                rotateRight(node);
                if(grandchBalance == 1)
                {
                    node->setBalance(0);
                    child->setBalance(-1);
                    grandch->setBalance(0);
                }
                else if(grandchBalance == 0)
                {
                    node->setBalance(0);
                    child->setBalance(0);
                    grandch->setBalance(0);
                }
                else if(grandchBalance == -1)
                {
                    node->setBalance(1);
                    child->setBalance(0);
                    grandch->setBalance(0);
                }
                removeFix(parent, ndiff); // recursive call
                return; // ??
            }
            
        }
        else if(node->getBalance() + diff == -1)
        {
            node->setBalance(-1);
            return; // done early
        }
        else if(node->getBalance() + diff == 0)
        {
            node->setBalance(0);
            removeFix(parent, ndiff); // recursive call
            return; // ??
        }


    }
    else if(diff == 1) // mirrored, operating on right child
    {

        if(node->getBalance() + diff == 2) // heavy on right
        {
            std::cout << "[removeFix] Rotating at node " << node->getKey() << std::endl;
            AVLNode<Key, Value>* child = node->getRight();   
            if(child->getBalance() == 1) // zig-zig case
            {
                std::cout << "  >> Rotating at node " << node->getKey()
          << ", child: " << child->getKey()
          << ", child balance: " << (int)child->getBalance() << std::endl;

                rotateLeft(node);
                node->setBalance(0);
                child->setBalance(0);
                removeFix(parent, ndiff); // recursive call
            }
            else if(child->getBalance() == 0) // zig-zig case, although doesnt rly matter
            {
                std::cout << "  >> Rotating at node " << node->getKey()
          << ", child: " << child->getKey()
          << ", child balance: " << (int)child->getBalance() << std::endl;

                rotateLeft(node);
                node->setBalance(0);
                child->setBalance(0);
                return; // done early
                //removeFix(parent, ndiff); // temp
            }
            else if(child->getBalance() == -1) // zig-zag case
            {
                AVLNode<Key, Value>* grandch = child->getLeft(); // declare grandchild node here, only used in zig-zag case
                int8_t grandchBalance = grandch->getBalance();
                std::cout << "  >> Rotating at node " << node->getKey()
          << ", child: " << child->getKey()
          << ", child balance: " << (int)child->getBalance() << std::endl;

                rotateRight(child);
                std::cout << "  >> Rotating at node " << node->getKey()
          << ", child: " << child->getKey()
          << ", child balance: " << (int)child->getBalance() << std::endl;

                rotateLeft(node);
                if(grandchBalance == -1)
                {
                    node->setBalance(0);
                    child->setBalance(1);
                    grandch->setBalance(0);
                }
                else if(grandchBalance == 0)
                {
                    node->setBalance(0);
                    child->setBalance(0);
                    grandch->setBalance(0);
                }
                else if(grandchBalance == 1)
                {
                    node->setBalance(-1);
                    child->setBalance(0);
                    grandch->setBalance(0);
                }
                removeFix(parent, ndiff); // recursive call
                return; // ??
            }
            
        }
        else if(node->getBalance() + diff == 1)
        {
            node->setBalance(1);
            return; // done early
        }
        else if(node->getBalance() + diff == 0)
        {
            node->setBalance(0);
            removeFix(parent, ndiff); // recursive call
            return; // ??
        }


    }
    // else // dont know if this is necessary, might be balanced anyways if triggered
    // {
    //     removeFix(parent, ndiff);
    // }


}


#endif
