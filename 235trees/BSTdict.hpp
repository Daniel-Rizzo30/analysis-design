/*
Daniel Rizzo
CSCI 235
12/16/20
Project 6
BSTdict.hpp
Binary Search Tree Header file
*/

#ifndef BST_DICT_
#define BST_DICT_

#include "BinaryNode.hpp"
#include <string>
#include <vector>
#include <memory>
using namespace std;

template <typename ItemType>
class BSTdict
{
public:
    /** 
        Default Constructor 
    **/
    BSTdict();

    /** 
        Copy Constructor 
        @param tree : tree to copy from into 'this' tree, the caller.
        @post       : All contents, including dynamic memory, are copied into the calling tree.
    **/
    BSTdict(const BSTdict<ItemType>& tree);

    /**
       Destructor
       @post : deallocate all contents involec in the calling tree. 
    **/
	~BSTdict();
    
    /**
       Getter function
       @post : returns tree's root node. 
    **/
    auto getRootPtr();

    /**
        Checks if tree is empty
        @return true if tree is empty, false otherwise
    **/
    bool isEmpty() const;

    /**
        Inserts a string into the tree, doesn't allow duplicates. if(word == ptr) return false;
        @param word : is the string to be added to the tree, could be any data type though. 
        @return true if word is added, false otherwise
    **/
    bool insert(const ItemType& word);

    /**
        Removes a string from the tree
        @param word : is the string to be removed from the tree
        @return true if word is removed, false otherwise
    **/
    bool remove(const ItemType& word);

    /**
        Returns the length of the longest path in the tree
        @return the number of nodes on the longest path from root to leaf
    **/
    int getHeight();

    /**
        Inserts multiple strings at once into the tree
        @param vec : is the vector containing all the strings to be added
        @return true if all words are added, false otherwise
    **/
    bool insertVector(const vector<ItemType>& vec);

    /**
        Displays the tree. 
        @post prints words one per line using in-order traversal. 
    **/
    void display();

private:
    /**
        Helper function for copy constructor.
        @param old_tree_root_ptr is the root to the tree that is being copied
        @post creates new tree for caller. 
    **/
    auto copyTree(const shared_ptr<BinaryNode<ItemType>> old_tree_root_ptr) const;

    /**
        Helper function for destructor.
        @param sub_tree_ptr is the subtree being destroyed recursively until leaf is reached. 
        @post deallocates all memory associated with caller. 
    **/
    void destroyTree(std::shared_ptr<BinaryNode<ItemType>> sub_tree_ptr);


    /**
        Helper function for getHeight.
        @param sub_tree_ptr is the subtree whose paths lengths are being calculated recursively.  
        @return the length of the longest path in the tree. 
    **/
    int getHeightHelper(shared_ptr<BinaryNode<ItemType>> sub_tree_ptr) const;

    /**
        Helper function for insert.
        @param sub_tree_ptr is the subtree whose root node is to be compared to new_node_ptr
        @param new_node_ptr who is the new data being added to the tree  
        @param success is the bool passed by reference to signal if node is inserted successfully or not. 
        @post node is passed to either left or right subtree, or placed as left or right child.  
    **/
    auto placeNode(shared_ptr<BinaryNode<ItemType>> subtree_ptr, shared_ptr<BinaryNode<ItemType>> new_node_ptr, bool& success);

    /**
        Larger helper function for remove.
        @param sub_tree_ptr is the subtree who will be traverse for the target. 
        @param target is the node the function will try to remove
        @param success is the bool passed by reference to signal if node is removed successfully or not. 
        @post target node is removed after recursion, or it's not found and success is changed to false.   
    **/
    auto removeValue(std::shared_ptr<BinaryNode<ItemType>> subtree_ptr, const ItemType target, bool& success);

    /**
        Smaller helper function for removeValue.
        @param node_ptr is the node to be removed. 
        @post node is deleted and replaced.
    **/
    auto removeNode(std::shared_ptr<BinaryNode<ItemType>> node_ptr);

    /**
        Smallest helper function for removeNode.
        @param node_ptr is the root whose leftmost node will be removed. 
        @param inorderSuccessor is the value where this function will store what the value that will replace the old node is
        @post leftmost node is removed, and inorderSuccessor is updated. 
    **/
    auto removeLeftmostNode(shared_ptr<BinaryNode<ItemType>> nodePtr, ItemType& inorderSuccessor);

    /**
        Helper function for display.
        @param sub_tree_ptr is the root whose tree contents will be displayed in order traversal 
        @post the whole tree's contents are displayed in order. 
    **/
    void displayHelper(const std::shared_ptr<BinaryNode<ItemType>> sub_tree_ptr);

    shared_ptr<BinaryNode<ItemType>> root_ptr_; //Shared root pointer to beginning of tree

    //Add helper functions!

}; // end BSTdict
#include "BSTdict.cpp"
#endif