#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    //std::cout << "calling getleft" << std::endl;
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2);

    // Add helper functions here
    static Node<Key, Value>* successor(Node<Key, Value>* current); // TODO, should be like predecessor
    int getHeight(); // gets height of a tree, useful for finding balance

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr) : current_(ptr)
{
    // TODO
    // done?
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() : current_(nullptr) 
{
    // TODO
    // done?
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    //return (current_->getKey() == rhs.current_->getKey()) && (current_->getValue() == rhs.current_->getValue());
    return current_ == rhs.current_;
    // done?
     
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    //return (current_->getKey() != rhs.current_->getKey()) || (current_->getValue() != rhs.current_->getValue());
    return current_ != rhs.current_;
    // done?

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    current_ = BinarySearchTree<Key, Value>::successor(current_);
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    // if(root_ == nullptr) // base case, empty tree, set root to pair
    // {
    //     root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
    //     return;
    // }
    

    // if(root_->getKey() == keyValuePair.first) // key of root and inserted nodes are same
    // {
    //     root_->setValue(keyValuePair.second);
    // }

    // if(root_->getKey() > keyValuePair.first) // inserted node is less than root, operating on left subtree
    // {
    //     if(root_->getLeft() == nullptr) // check if left subtree is empty
    //     {
    //         Node<Key, Value>* temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, root_);
    //         root_->setLeft(temp);
    //     }
    //     BinarySearchTree<Key, Value> leftSubtree;
    //     leftSubtree.root_ = root_->getLeft();
    //     leftSubtree.insert(keyValuePair);
    //     root_->setLeft(leftSubtree.root_); // connecting subtree to root when subtree is updated
    //     if(leftSubtree.root_ != nullptr)
    //     {
    //         leftSubtree.root_->setParent(root_);
    //     }
    // }

    // if(root_->getKey() < keyValuePair.first) // inserted node is more than root, operating on right subtree
    // {
    //     if(root_->getRight() == nullptr) // check if right subtree empty
    //     {
    //         Node<Key, Value>* temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, root_);
    //         root_->setRight(temp);
    //     }
    //     BinarySearchTree<Key, Value> rightSubtree;
    //     rightSubtree.root_ = root_->getRight();
    //     rightSubtree.insert(keyValuePair);
    //     root_->setRight(rightSubtree.root_); 
    //     if(rightSubtree.root_ != nullptr)
    //     {
    //         rightSubtree.root_->setParent(root_);
    //     }       
    // }
    // // done? do we have to update all member variables for the node?

    if (root_ == nullptr) {
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
        return;
    }

    Node<Key, Value>* current = root_;
    Node<Key, Value>* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (keyValuePair.first < current->getKey()) {
            current = current->getLeft();
        } else if (keyValuePair.first > current->getKey()) {
            current = current->getRight();
        } else {
            current->setValue(keyValuePair.second);
            return;
        }
    }

    Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
    if (keyValuePair.first < parent->getKey()) {
        parent->setLeft(newNode);
    } else {
        parent->setRight(newNode);
    }

    // Sanity check: verify bidirectional connection
    if (newNode->getParent() != nullptr) {
        if (newNode->getParent()->getLeft() != newNode &&
            newNode->getParent()->getRight() != newNode) {
            std::cout << "[BUG] Parent pointer is set, but parent doesn't point to this node!\n";
        }
    }

}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    //std::cout << "remove called!" << std::endl;
    // TODO
    // if(root_ == nullptr) // base case, empty tree
    // {
    //     return;
    // }

    // BinarySearchTree<Key, Value> subtree;

    // if(root_->getKey() == key) // found the node to be removed
    // {
    //     if(root_->getLeft() == nullptr && root_->getRight() == nullptr) // leaf node, no children
    //     {
    //         delete root_;
    //         root_ = nullptr; // reset root node
    //         return;
    //     }
    //     if(root_->getLeft() != nullptr && root_->getRight() == nullptr) // only a left child
    //     {
    //         Node<Key, Value>* leftChild = root_->getLeft();
    //         leftChild->setParent(root_->getParent()); // update childs parent pointer to be roots parent
    //         delete root_;
    //         root_ = leftChild;
    //         return;

    //     }
    //     if(root_->getLeft() == nullptr && root_->getRight() != nullptr) // only a right child
    //     {
    //         Node<Key, Value>* rightChild = root_->getRight();
    //         rightChild->setParent(root_->getParent()); // update childs parent pointer to be roots parent
    //         delete root_;
    //         root_ = rightChild;
    //         return;
    //     }
    //     // root has 2 children
    //     Node<Key, Value>* pred = predecessor(root_);
    //     nodeSwap(root_, pred); // swap root w predeccessor 
    //     subtree.root_ = root_->getLeft(); // node we want to remove is now child in left subtree
    //     subtree.remove(key); // recursively remove node from left subtree
    //     root_->setLeft(subtree.root_);
    //     return;
    // }

    // if(root_->getKey() > key) // recurse down left subtree
    // {
    //     subtree.root_ = root_->getLeft();
    //     subtree.remove(key);
    //     root_->setLeft(subtree.root_);
    // }
    // if(root_->getKey() < key) // recurse down right subtree
    // {
    //     subtree.root_ = root_->getRight();
    //     subtree.remove(key);
    //     root_->setRight(subtree.root_);
    // }
    // // done?

    //std::cout << "remove called!" << std::endl;

    if (root_ == nullptr) {
        //std::cout << "Tree is empty" << std::endl;
        return;
    }

    Node<Key, Value>* node = root_;
    Node<Key, Value>* parent = nullptr;

    //std::cout << "nodes init" << std::endl;

    // Search for the node to remove
    while (node != nullptr && node->getKey() != key) {
        parent = node;
        if (key < node->getKey()) {
            node = node->getLeft();
        } else {
            node = node->getRight();
        }
    }
    //std::cout << "while finishes!" << std::endl;

    if (node == nullptr) return; // Key not found

    // Case 1: Node has two children
    if (node->getLeft() != nullptr && node->getRight() != nullptr) {
        Node<Key, Value>* pred = predecessor(node);
        if (pred == nullptr) return;

        nodeSwap(node, pred);

        // Now node holds the predecessor’s old position and is ready for deletion
    }

    // Case 2 & 3: Node has at most one child
    Node<Key, Value>* child = nullptr;
    if (node->getLeft() != nullptr) {
        child = node->getLeft();
    } else {
        child = node->getRight();
    }

    if (child != nullptr) {
        child->setParent(node->getParent());
    }

    Node<Key, Value>* nodeParent = node->getParent();
    if (node == root_) {
        root_ = child;
    } else if (nodeParent != nullptr && nodeParent->getLeft() == node) {
        nodeParent->setLeft(child);
    } else if (nodeParent != nullptr) {
        nodeParent->setRight(child);
    }

    delete node;

}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current) 
{
    // TODO
    //std::cout << "predecessor called" << std::endl;
    if(current == nullptr) // base case
    {
        return nullptr; // is this right?
    }

    if(current->getLeft() != nullptr) // predecessor is rightmost node in left subtree
    {
        Node<Key, Value>* node = current->getLeft();
        while(node->getRight() != nullptr) // iteratively move to rightmost node
        {
            node = node->getRight();
        }
        return node;
    }

    // if(current->getLeft() == nullptr) // no left subtree, work up the tree through parent pointers
    // {
    //     Node<Key, Value>* parent = current->getParent();
    //     if(current == parent->getRight())
    //     {
    //         return parent; // predecessor is the parent of current, current is right child of parent
    //     }
    //     return parent; // recurse up the tree
    // }

    Node<Key, Value>* parent = current->getParent();
    while (parent != nullptr && current == parent->getLeft()) {
        current = parent;
        parent = parent->getParent();
    }
    //std::cout << "predecessor works!" << std::endl;
    return parent;
    
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current) // mirrors predecessor
{
    //std::cout << "successor called" << std::endl;
    if(current == nullptr)
    {
        //std::cout << "current is null" << std::endl;
        return nullptr;
    }

    if(current->getRight() != nullptr)
    {
        Node<Key, Value>* node = current->getRight();
        
        while(node->getLeft() != nullptr)
        {
            //std::cout << "left" << std::endl;
            node = node->getLeft();
            
        }
        return node;
    }

    // if(current->getRight() == nullptr)
    // {
    //     std::cout << "parent" << std::endl;
    //     Node<Key, Value>* parent = current->getParent();
    //     if(current == parent->getLeft())
    //     {
    //         return parent;
    //     }
    //     return parent;
    // }
    Node<Key, Value>* parent = current->getParent();
    while (parent != nullptr && current == parent->getRight()) {
        current = parent;
        parent = parent->getParent();
    }
    return parent;

   
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    if (root_ == nullptr) return;

    // Recursive post-order delete written directly
    if (root_->getLeft() != nullptr) {
        Node<Key, Value>* leftChild = root_->getLeft();
        root_->setLeft(nullptr);
        BinarySearchTree<Key, Value> leftTree;
        leftTree.root_ = leftChild;
        leftTree.clear();
    }

    if (root_->getRight() != nullptr) {
        Node<Key, Value>* rightChild = root_->getRight();
        root_->setRight(nullptr);
        BinarySearchTree<Key, Value> rightTree;
        rightTree.root_ = rightChild;
        rightTree.clear();
    }

    delete root_;
    root_ = nullptr;

    // done?

}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    if(root_ == nullptr) // empty (sub)tree
    {
        return nullptr;
    }

    if(root_->getLeft() == nullptr) // no left subtree
    {
        return root_;
    }

    // left subtree
    BinarySearchTree<Key, Value> leftSubtree;
    leftSubtree.root_ = root_->getLeft();
    return leftSubtree.getSmallestNode(); // recursive call
    //done?
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    if(root_ == nullptr) // base case, empty tree
    {
        return nullptr;
    }

    if(root_->getKey() == key) // base case, found key
    {
        return root_;
    }

    BinarySearchTree<Key, Value> subtree;

    if(root_->getKey() > key) // key is less than root, go down left subtree
    {
        subtree.root_ = root_->getLeft();
        return subtree.internalFind(key);
    }
    else // key is greater than root, go down right subtree
    {
        subtree.root_ = root_->getRight();
        return subtree.internalFind(key);
    }
    //done?
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    if(root_ == nullptr) // base case, empty tree will always be balanced
    {
        return true;
    }

    BinarySearchTree<Key, Value> leftSubtree;
    leftSubtree.root_ = root_->getLeft();
    BinarySearchTree<Key, Value> rightSubtree;
    rightSubtree.root_ = root_->getRight();

    int leftHeight = leftSubtree.getHeight();
    int rightHeight = rightSubtree.getHeight();

    bool differenceCheck = abs(leftHeight - rightHeight) <= 1; // difference between subtrees is not greater than 1
    bool subtreeCheck =  leftSubtree.isBalanced() && rightSubtree.isBalanced(); // recursive call, sees if subtrees are balanced
    return differenceCheck && subtreeCheck;
    
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::getHeight()
{

    if(root_ == nullptr) // base case, empty tree has height of 0
    {
        return 0;
    }

    BinarySearchTree<Key, Value> leftSubtree;
    leftSubtree.root_ = root_->getLeft();
    BinarySearchTree<Key, Value> rightSubtree;
    rightSubtree.root_ = root_->getRight();

    int leftHeight = leftSubtree.getHeight();
    int rightHeight = rightSubtree.getHeight();

    return 1 + std::max(leftHeight, rightHeight); // returns greatest height of subtrees

}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
