// ITP 365 Fall 2018
// HW6 - Doubly Linked List and Movie Player
// Name: Mara Pleasure
// Email: mpleasur@usc.edu
// Platform: Mac
//
// ITPDoubleList.hpp
// Defines and implements the ITPDoubleList collection
//

#pragma once
#include "error.h"
#include <ostream>
#include <sstream>
#include "leaker.h"

template <typename T>
class ITPDoubleList
{
private:
    
    // Node only used internally to list
    struct Node
    {
        // Data in this node
        T mData;
        // Link to previous node
        Node* mPrev;
        // Link to next node
        Node* mNext;
    };
    
    // Pointer to the head node
    Node* mHead;
    // Pointer to the tail node
    Node* mTail;
    // Number of nodes currently in the list
    unsigned mSize;
    
public:
    // Iterator helper class...
    class Iterator
    {
    private:
        Node* mCurr;
    public:
        // Needed for List access
        friend class ITPDoubleList;
        // Constructors
        Iterator()
        {
            //sets mCurr to null pointer
            mCurr = nullptr;
        }
        
        Iterator(Node* inCurr)
        {
            //sets mCurr to inCurr
            mCurr = inCurr;
        }
        
        Iterator(const Iterator& src)
        {
            //sets mCurr to the mCurr of SRC
            mCurr = src.mCurr;
        }
        
        // Assignment
        Iterator& operator=(const Iterator& src)
        {
            //like above but assignment
            mCurr = src.mCurr;
            return *this;
        }
        
        // Incrementors / Decrementors
        // ++i
        Iterator& operator++()
        {
            //goes to next iterator
            mCurr = mCurr->mNext;
            return *this;
        }
        
        // i++
        Iterator operator++(int)
        {
            Iterator retval(*this);
            mCurr = mCurr->mNext;
            return retval;
        }
        
        // --i
        Iterator& operator--()
        {
            //goes to previous iterator
            mCurr = mCurr->mPrev;
            return *this;
        }
        
        // i--
        Iterator operator--(int)
        {
            
            Iterator retval(*this);
            mCurr = mCurr->mPrev;
            return retval;
        }
        
        // Dereference
        T& operator*() const
        {
            //dereference to data
            return mCurr->mData; // CONFUSED
        }
        
        Node* operator->() const
        {
            //dereference pointer
            return mCurr;;
        }
        
        // Comparison
        bool operator==(const Iterator& rhs) const
        {
            //checks if they are equal
            return(mCurr == rhs.mCurr);
        }
        
        bool operator!=(const Iterator& rhs) const
        {
            //checks if they are not equal
            return(mCurr != rhs.mCurr);
        }
    };
    
    // List functions...
    
    // Function: Default Constructor
    // Purpose: Initializes size to 0 and head/tail to null
    // Input: None
    // Returns: Nothing
    ITPDoubleList()
    {
        //sets size to 0 and everything to null
        mSize = 0;
        mHead = nullptr;
        mTail = nullptr;
    }
    
    // Function: Copy Constructor
    // Purpose: Initializes this list as a deep copy of other
    // Input: Other list to copy (const reference)
    // Returns: Nothing
    ITPDoubleList(const ITPDoubleList& other)
    {
        //resets
        mSize = 0;
        mHead = nullptr;
        mTail = nullptr;
        
        //gets mHead from other
        Node* tempNode = other.mHead;
        
        //as long as it is not a nullptr copies it to the mData
        while (tempNode != nullptr){
            push_back(tempNode->mData);
            tempNode = tempNode->mNext;
        }
        
    }
    
    // Function: Destructor
    // Purpose: Calls the clear function to delete the list
    // Input: None
    // Returns: Nothing
    ~ITPDoubleList()
    {
        clear();
    }
    
    // Function: clear
    // Purpose: Deletes every node in this list, sets size to 0, and head/tail to null
    // Input: None
    // Returns: Nothing
    void clear()
    {
        //as long as the size is greater than 0 will delete the first item in the double list
        while(mSize > 0){
            pop_front();
        }
    }
    
    // Assignment Operator
    // Function: Assignment Operator
    // Purpose: Clear this list, and then make a deep copy of other
    // Input: Other list to copy (const reference)
    // Returns: *this
    ITPDoubleList& operator=(const ITPDoubleList& other)
    {
        //clears first
        clear();
        //makes a temp node
        Node* tempNode = other.mHead;
        //while temp node is not null
        while (tempNode != nullptr){
            push_back(tempNode->mData);
            tempNode = tempNode->mNext;
        }
        
        return *this; // FIX RETURN VALUE
    }
    
    // Function: size
    // Purpose: Gets the current size of the linked list
    // Input: None
    // Returns: size of the list
    unsigned size() const
    {
        return mSize;
    
    }
    
    // Function: push_front
    // Purpose: Inserts a node at the front of the linked list
    // Input: Value to store in the new node
    // Returns: Nothing
    void push_front(const T& value)
    {
        //makes a dynamically allocated new node
        Node* newNode = new Node;
        //sets it data to the value, its previous to null and its next to the current head
        newNode->mData = value;
        newNode->mPrev = nullptr;
        newNode->mNext = mHead;
        //rearranges the head and tail depending on list size
        if (mSize == 0){
            mTail = newNode;
        }
        else{
            mHead->mPrev = newNode;
        }
        mHead = newNode;
        //increments size
        mSize = mSize + 1;
        
    }
    
    // Function: front
    // Purpose: Gets the value of the node at the front of the list
    // Input: None
    // Returns: Value of the node at the front of the list
    T& front()
    {
    
        if (mSize == 0){
            error("Size is 0");
        }
        //front item of list
        return mHead->mData;
      
    }
    
    // Function: pop_front
    // Purpose: Removes the node at the front of the list
    // Input: None
    // Returns: None
    void pop_front()
    {
        //don't delete then
        if (mSize == 0){
            error("Size is 0");
        }
        //if the size is 1, then only one item and delete than then set all to null
        else if (mSize == 1){
            delete mHead;
            mHead = nullptr;
            mTail = nullptr;
            mSize = 0;
            
        }
        else{
            //make a temp node and save pointer to mHead
            Node* tempNode = mHead->mNext;
            //delete mHead
            delete mHead;
            //make temp the new head
            mHead = tempNode;
            //reset mPrev
            mHead->mPrev = nullptr;
            //decrement size
            mSize = mSize - 1;
        }
        
    }
    
    // Function: push_back
    // Purpose: Inserts a node at the end of the linked list
    // Input: Value to store in the new node
    // Returns: Nothing
    void push_back(const T& value)
    {
        //make a dynamically allocated new node
        Node* newNode = new Node;
        //set data to value
        newNode->mData = value;
        //set prev to tail
        newNode->mPrev = mTail;
        //set next to null
        newNode->mNext = nullptr;
        
        //if 0, then simply the first item
        if (mSize == 0){
            mHead = newNode;
        }
        //if there is more than one, than set the tail to point to the new node
        else{
            mTail->mNext = newNode;
        }
        mTail = newNode;
        //increment size
        mSize = mSize + 1;
    }
    
    // Function: back
    // Purpose: Gets the value of the node at the back of the list
    // Input: None
    // Returns: Value of the node at the back of the list
    T& back()
    {   if (mSize == 0){
        
            error("Size is 0");
        }

        //return data from tail
        return mTail->mData;
    
    }
    
    // Function: pop_back
    // Purpose: Removes the node at the end of the list
    // Input: None
    // Returns: None
    void pop_back()
    {
        //error is size is 0
        if (mSize == 0){
            error("Size is 0");
        }
        //if size is 1, than delete and change to null
        else if (mSize == 1){
            delete mTail;
            mHead = nullptr;
            mTail = nullptr;
            mSize = 0;
        }
        else{
            //make a temp node and save the node before the tail
            Node* tempNode = mTail->mPrev;
            //delete tail
            delete mTail;
            //change tail to temp node
            mTail = tempNode;
            //set the next to null
            mTail->mNext = nullptr;
            //decrement size
            mSize = mSize - 1;
            
        }
    }
    
    // Function: begin
    // Purpose: Gets an iterator for the start of the list
    // Input: None
    // Returns: Iterator pointing to beginning of list
    Iterator begin() const
    {
    
        return Iterator(mHead);
        //return *(new Iterator); // CONFUSED
    }
    
    // Function: end
    // Purpose: Gets an iterator for the end of the list
    // Input: None
    // Returns: Iterator pointing to end of list
    Iterator end() const
    {
        return Iterator(mTail->mNext);
       //return *(new Iterator); // CONFUSED
    }

	// Function: erase
	// Purpose: Removes the item at the node pointed to by i
	// Input: Iterator pointing to a valid node to remove before
	// Returns: A new iterator pointing to the node after the removed item
    Iterator erase(Iterator& i)
    {
        //if the iterator is invalid, error
        if (i.mCurr == nullptr){
            error("Iterator is invalid");
        }
        //if the iterator is at begin
        else if(i.mCurr == mHead){
            //pop_front
            pop_front();
            return begin();
        }
        //if the iterator is at the tail
        else if(i.mCurr == mTail){
            //popback
            pop_back();
            return end();
        }
       
        Node* before = i->mPrev;
        Node* after = i->mNext;
        Node* toDel = i.mCurr;
        // make before, after and to del pointers
        delete toDel;
        before->mNext = after;
        //sets after's previous to before
        after->mPrev = before;
        //decrement size
        mSize = mSize - 1;
        //return an iterator to after
        return Iterator(after);
        
        
        
    }

	// Function: insert
	// Purpose: Inserts a list item before node pointed to by i
	// Input: Iterator pointing to a valid node to insert before
	// Returns: A new iterator pointing to the inserted value
    Iterator insert(Iterator& i, const T& val)
    {
       // Node* newNode;
        //newNode = i.mCurr;
        if (i.mCurr == nullptr){
            error("Iterator is invalid");
        }
        else if(i.mCurr == mHead){
            push_front(val);
            return begin();
        }
        else if(i->mPrev == mTail){
            push_back(val);
            //return iterator to last element (not end!)
            return Iterator(mTail);
        }
        
        //make before and after pointers
        Node* before = i->mPrev;
        Node* after = i.mCurr;
        //dynamically allocate a new node
        Node* newNode = new Node;
        //change new node to match val, before and after pointers
        newNode->mData = val;
        newNode->mPrev = before;
        newNode->mNext = after;
            
           
        //sets before next to the new node
        before->mNext = newNode;
        //sets afters previous to the new node
        after->mPrev = newNode;
        mSize = mSize + 1;
        //return an iterator pointing to the inserted node
        return Iterator(newNode);
        
        
    }
    
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!! DO NOT EDIT BELOW THIS LINE !!!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
public:
    // Function: Output Stream Operator
    // Purpose: Prints the contents of the list to the provided stream
    // Written in the format of {x, y, ..., z}
    // Input: Stream to write to, list to write
    // Output: Stream after values are written
    friend std::ostream& operator<<(std::ostream& os, const ITPDoubleList<T>& list)
    {
        os << "{";
        
        Node* temp = list.mHead;
        while (temp != nullptr)
        {
            os << temp->mData;
            if (temp != list.mTail)
            {
                os << ",";
            }
            
            temp = temp->mNext;
        }
        
        os << "}";
        return os;
    }
    
    // Function: toString
    // Purpose: Converts list to a string
    // Input: None
    // Output: String (in the format as the ostream)
    std::string toString() const
    {
        std::stringstream str;
        str << *this;
        return str.str();
    }
    
    // Function: toReverseString
    // Purpose: Outputs the list in reverse
    // Input: None
    // Output: String in reverse
    std::string toReverseString() const
    {
        std::stringstream str;
        
        str << "{";
        
        Node* temp = mTail;
        while (temp != nullptr)
        {
            str << temp->mData;
            if (temp != mHead)
            {
                str << ",";
            }
            
            temp = temp->mPrev;
        }
        
        str << "}";
        
        return str.str();
    }
};
