#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
    clear();
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
    Node *insert = new Node(ndata);
    insert->prev = tail_->prev;
    insert->next = tail_;
    tail_->prev->next = insert;
    tail_->prev = insert;
    length_++;
}

/**
 * Swaps the two nodes at the indexes "node1" and "node2".
 * The indexes of the nodes are 1 based.
 * assumes i and j are valid (in {1, length_} inclusive)
 * 
 */
void Chain::swap(int i, int j)
{
    Node *iNode = walk(head_, i);
    Node *jNode = walk(head_, j);
    Node *temp = NULL;

    temp = iNode->next;
    iNode->next = jNode->next;
    jNode->next = temp;
    iNode->next->prev = iNode;
    jNode->next->prev = jNode;

    temp = iNode->prev;
    iNode->prev = jNode->prev;
    jNode->prev = temp;
    iNode->prev->next = iNode;
    jNode->prev->next = jNode;
}

/**
 * Reverses the chain
 */
void Chain::reverse()
{
    int mid = length_ / 2;
    for (int i = 1; i <= mid; i++)
    {
        swap(i, length_ + 1 - i);
    }
}

/*
* Modifies the current chain by "rotating" every k nodes by one position.
* In every k node sub-chain, remove the first node, and place it in the last 
* position of the sub-chain. If the last sub-chain has length less than k,
* then don't change it at all. 
* Some examples with the chain a b c d e:
*   k = 1: a b c d e
*   k = 2: b a d c e
*   k = 3: b c a d e
*   k = 4: b c d a e
*/
void Chain::rotate(int k)
{
    for (int i = 1; i <= length_; i += k)
    {
        if (i + k - 1 <= length_)
        {
            for (int j = i; j < i + k - 1; j++)
            {
                swap(j, j + 1);
            }
        }
    }
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{
    Node *curr = head_;
    while (curr != NULL)
    {
        Node *delNode = curr;
        curr = curr->next;
        delete delNode;
    }
    head_ = NULL;
    tail_ = NULL;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other)
{
    head_ = new Node();
    tail_ = new Node();
    head_->next = tail_;
    tail_->prev = head_;
    length_ = 0;
    numRows_ = other.numRows_;
    numCols_ = other.numCols_;
    height_ = other.height_;
    width_ = other.width_;

    int len = other.length_;
    Node *currOther = other.head_->next;

    while (len--)
    {
        insertBack(currOther->data);
        currOther = currOther->next;
    }
}

/***********************************
 * swapColumns
 * parameters: 1 <= i <= numCols_
 *             1 <= j <= numCols_
 *
 * Swaps the positions of columns i and j
 * in the original grid of blocks by
 * moving nodes in the chain.
 *
 ***********************************/
void Chain::swapColumns(int i, int j)
{
    for (int r = 1; r <= numRows_; r++)
    {
        int iIndex = numCols_ * (r - 1) + i;
        int jIndex = numCols_ * (r - 1) + j;
        swap(iIndex, jIndex);
    }
}

/***********************************
 * swapRows
 * parameters: 1 <= i <= numRows_
 *             1 <= j <= numRows_
 *
 * Swaps the positions of rows i and j
 * in the original grid of blocks by
 * moving nodes in the chain.
 *
 ***********************************/
void Chain::swapRows(int i, int j)
{
    for (int c = 1; c <= numCols_; c++)
    {
        int iIndex = numCols_ * (i - 1) + c;
        int jIndex = numCols_ * (j - 1) + c;
        swap(iIndex, jIndex);
    }
}
