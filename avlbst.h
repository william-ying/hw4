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
    AVLTree();
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    // Add helper functions here
    int rootbal;

};

template<class Key, class Value>
AVLTree<Key, Value>::AVLTree() : BinarySearchTree<Key, Value>::BinarySearchTree()
{
    this->root_ = NULL;
}


/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    AVLNode<Key, Value> *curr;
    curr = dynamic_cast<AVLNode<Key, Value>*>(this->root_);
    while (curr != NULL) {
        if (curr->getKey() < new_item.first) {
            // cout << "right " << curr->getKey() << new_item.first << endl;
            if (curr -> getRight() == NULL) {
                curr -> setRight(new AVLNode<Key, Value>(new_item.first, new_item.second, curr));
                curr = curr->getRight();
                break;
            }
            curr = curr -> getRight();
            
            
        } else if (curr->getKey() > new_item.first) {
            // cout << "left " << curr->getKey() << new_item.first << endl;
            if (curr -> getLeft() == NULL) {
                curr -> setLeft(new AVLNode<Key, Value>(new_item.first, new_item.second, curr));
                curr = curr->getLeft();
                break;
            }
            curr = curr -> getLeft();
        } else {
            curr->setValue(new_item.second);
            break;
        }
    }
    if (this->root_ == NULL) {
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        rootbal = 1;
        return;
    }
    curr->setBalance(1);
    cout << "insert" << curr->getKey() << " " << curr->getBalance() << endl;
    while (curr ->getParent() != NULL) {
        AVLNode<Key, Value>* currt;
        curr = curr->getParent();
        int left, right, left1, right1;
        if (curr->getLeft() == NULL) left = 0;
        else left = curr->getLeft()->getBalance();
        
        if (curr->getRight() == NULL) right = 0;
        else right = curr->getRight()->getBalance();

        
        cout << curr->getKey() << endl;
        cout << "l " << left;
        if (left != 0) cout << " " << curr->getLeft()->getKey();
        cout << endl << "r " << right;
        if (right != 0) cout << " " << curr->getRight()->getKey();
        cout << endl;
        
        if (left > right + 1) {
            cout << "spin right" << endl;
            currt = curr -> getLeft();
            if (currt->getLeft() == NULL) left1 = 0;
            else left1 = currt->getLeft()->getBalance();
            if (currt->getRight() == NULL) right1 = 0;
            else right1 = currt->getRight()->getBalance();

            
            if (right1 > left1) {
                cout << "bend" << endl;
                nodeSwap(currt, currt->getRight());
                currt = currt->getParent();
                AVLNode<Key, Value>* currt2 = currt -> getRight();
                
                // cout << currt->getLeft()->getKey() << endl;
                // cout << currt->getLeft()->getBalance() << endl;
                AVLNode<Key, Value>* temp = currt->getLeft();
                if (currt2->getRight() != NULL) currt2->getRight()->setParent(currt);
                currt->setLeft(currt2->getRight());
                currt2->setRight(currt2->getLeft());
                if (temp != NULL) temp->setParent(currt2);
                currt2->setLeft(temp);
                
                temp = currt->getLeft();
                currt->setLeft(currt->getRight());
                currt->setRight(temp);
            }
            
            currt = curr;
            curr = curr->getParent();
            
            AVLNode<Key, Value>* temp = currt->getRight();
            currt->setParent(curr->getParent());
            curr->setParent(currt);
            currt->setRight(curr);
            if (temp != NULL) temp->setParent(curr);
            curr->setLeft(temp);            
            

            if (curr->getLeft() == NULL) left = 0;
            else left = curr->getLeft()->getBalance();
            if (curr->getRight() == NULL) right = 0;
            else right = curr->getRight()->getBalance();
    
            curr -> setBalance(max(left, right) + 1);

            curr = currt;
            
        } else if (left + 1 < right) {
            cout << "spin left" << endl;
            currt = curr -> getRight();
            if (currt->getLeft() == NULL) left1 = 0;
            else left1 = currt->getLeft()->getBalance();
            if (currt->getRight() == NULL) right1 = 0;
            else right1 = currt->getRight()->getBalance();

            if (right1 < left1) {
                cout << "bend" << endl;
                nodeSwap(currt, currt->getLeft());
                currt = currt->getParent();
                AVLNode<Key, Value>* currt2 = currt -> getLeft();
                    
                AVLNode<Key, Value>* temp = currt->getRight();
                if (currt2->getLeft() != NULL) currt2->getLeft()->setParent(currt);
                currt->setRight(currt2->getLeft());
                currt2->setLeft(currt2->getRight());
                if (temp != NULL) temp->setParent(currt2);
                currt2->setRight(temp);

                temp = currt->getRight();
                currt->setRight(currt->getLeft());
                currt->setLeft(temp);


                
            }
            
            currt = curr;
            curr = curr->getParent();
            
            AVLNode<Key, Value>* temp = currt->getLeft();
            currt->setParent(curr->getParent());
            curr->setParent(currt);
            currt->setLeft(curr);
            if (temp != NULL) temp->setParent(curr);
            curr->setRight(temp);

            if (curr->getLeft() == NULL) left = 0;
            else left = curr->getLeft()->getBalance();
            if (curr->getRight() == NULL) right = 0;
            else right = curr->getRight()->getBalance();
    
            curr -> setBalance(max(left, right) + 1);

            curr = currt;
            
        }

        if (curr->getLeft() == NULL) left = 0;
        else left = curr->getLeft()->getBalance();
        if (curr->getRight() == NULL) right = 0;
        else right = curr->getRight()->getBalance();

        if (curr != this->root_) curr -> setBalance(max(left, right) + 1);
        else rootbal = max(left, right) + 1;
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    AVLNode<Key, Value> *curr;
    curr = dynamic_cast<AVLNode<Key, Value>*>(this->root_);
    AVLNode<Key, Value> *par = NULL;
    if (curr->getKey() == key) {
        if (curr->getLeft() == NULL && curr->getRight() == NULL) {
            delete curr;
        }
    }
    bool left = false;
    while (curr != NULL) {
        if (curr->getKey() > key) {
            curr = curr->getRight();
            left = false;
        } else if (curr->getKey() < key) {
            curr = curr->getLeft();
            left = true;
        } else {
            break;
        }
    }
    while (curr != NULL) {
        if (curr->getLeft() != NULL) {
            nodeSwap(curr, curr->getLeft());
            curr = curr->getLeft();
            left = true;
        } else if (curr->getRight() != NULL) {
            nodeSwap(curr, curr->getRight());
            curr = curr->getRight();
            left = false;
        } else {
            if (left) {
                curr->getParent()->setLeft(NULL);
            } else {
                curr->getParent()->setRight(NULL);
            }
            par = curr->getParent();
            delete curr;
        }
    }

    curr = par;
    while (curr != NULL) {
        AVLNode<Key, Value>* currt;
        int left, right, left1, right1;
        if (curr->getLeft() == NULL) left = 0;
        else left = curr->getLeft()->getBalance();
        if (curr->getRight() == NULL) right = 0;
        else right = curr->getRight()->getBalance();
        
        if (left > right + 1) {
            currt = curr -> getLeft();
            if (currt->getLeft() == NULL) left1 = 0;
            else left1 = currt->getLeft()->getBalance();
            if (currt->getRight() == NULL) right1 = 0;
            else right1 = currt->getRight()->getBalance();

            
            if (right1 > left1) {
                AVLNode<Key, Value>* currt2 = currt -> getRight();
                nodeSwap(currt2, currt->getLeft());
                nodeSwap(currt2->getLeft(), currt->getRight());
                nodeSwap(currt2->getRight(), currt->getRight());
            }
            
            nodeSwap(currt->getLeft(), curr->getRight());
            nodeSwap(curr->getLeft(), curr->getRight());
            nodeSwap(curr->getLeft()->getLeft(), currt->getLeft()->getRight());
            nodeSwap(curr->getRight()->getLeft(), currt->getRight()->getRight());
        } else if (left + 1 < right) {
            currt = curr -> getRight();
            if (currt->getLeft() == NULL) left1 = 0;
            else left1 = currt->getLeft()->getBalance();
            if (currt->getRight() == NULL) right1 = 0;
            else right1 = currt->getRight()->getBalance();

            if (right1 < left1) {
                AVLNode<Key, Value>* currt2 = currt -> getLeft();
                nodeSwap(currt2, currt->getRight());
                nodeSwap(currt2->getRight(), currt->getLeft());
                nodeSwap(currt2->getLeft(), currt->getLeft());
            }
            
            nodeSwap(currt->getRight(), curr->getLeft());
            nodeSwap(curr->getLeft(), curr->getRight());
            nodeSwap(curr->getLeft()->getLeft(), currt->getLeft()->getRight());
            nodeSwap(curr->getRight()->getLeft(), currt->getRight()->getRight());
        }

        if (curr->getLeft() == NULL) left = 0;
        else left = curr->getLeft()->getBalance();
        if (curr->getRight() == NULL) right = 0;
        else right = curr->getRight()->getBalance();

        curr -> setBalance(max(left, right) + 1);
        curr = curr->getParent();
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB;
    if (n1 == this->root_) tempB = rootbal;
    else tempB = n1->getBalance();
    if (n2 == this->root_) n1->setBalance(rootbal);
    else n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
