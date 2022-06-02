/*
Daniel Rizzo
CSCI 235
12/16/20
Project 6
BSTdict.cpp
Binary Search Tree Implementation file
*/

#include "BSTdict.hpp"
#include <string>
#include <vector>
#include <cstddef>
#include <memory>
#include <iostream>
using namespace std;

template <typename ItemType>
BSTdict<ItemType>::BSTdict()
{root_ptr_ = nullptr;} // end default constructor

template <typename ItemType>
BSTdict<ItemType>::BSTdict(const BSTdict<ItemType>& tree) {
    root_ptr_ = copyTree(tree.root_ptr_); // Call helper function 
} // end copy constructor

template <typename ItemType>
BSTdict<ItemType>::~BSTdict() { 
	destroyTree(root_ptr_); // Call helper function 
} // end destructor 

/******************* Public Functions ***********************/

template <typename ItemType>
auto BSTdict<ItemType>::getRootPtr() {return root_ptr_;}

template <typename ItemType>
bool BSTdict<ItemType>::isEmpty() const {
    return (root_ptr_ == nullptr); //If root ptr is empty, the tree is empty. 
}

template <typename ItemType>
bool BSTdict<ItemType>::insert(const ItemType& word) {
    bool is_successful = false;
    //call may change this variable
    auto new_node_ptr = make_shared<BinaryNode<ItemType>>(word); 
	placeNode(root_ptr_, new_node_ptr, is_successful); 
    return is_successful;
} // end insert

template <typename ItemType>
bool BSTdict<ItemType>::remove(const ItemType& word) {
    bool is_successful = false; 
	// call may change is_successful 
	root_ptr_ = removeValue(root_ptr_, word, is_successful); //Update root_ptr_ - whole tree gets rewritten
	return is_successful; 

}

template <typename ItemType>
int BSTdict<ItemType>::getHeight() {
    return getHeightHelper(root_ptr_); // Call helper function
}

template <typename ItemType>
bool BSTdict<ItemType>::insertVector(const vector<ItemType>& vec) {
    bool success = true;
    for (int j = 0; j < vec.size(); j++) { //for each string in vector
        success = insert(vec.at(j)); //try to insert, and set success = that boolean
        if (success == false) //if success was changed to false due to a string not being inserted
            break; //break the loop
    }
    return success; //return success
}

template <typename ItemType>
void BSTdict<ItemType>::display() {
   displayHelper(root_ptr_); //Call helper function so that main() doesn't have to deal with smart pointers in this recursive funct. 
}

/******************** Private Helper Functions ******************/

template <typename ItemType>
auto BSTdict<ItemType>::copyTree(const shared_ptr<BinaryNode<ItemType>> old_tree_root_ptr) const 
{ 
	shared_ptr<BinaryNode<ItemType>> new_tree_ptr; // Copy tree nodes during a preorder traversal 
	if (old_tree_root_ptr != nullptr) //Recursive
	{ 
		// Copy node 
		new_tree_ptr = make_shared<BinaryNode<ItemType>> (old_tree_root_ptr->getItem(), nullptr, nullptr); //make_share is like "new" keyword
		new_tree_ptr->setLeftChildPtr(copyTree(old_tree_root_ptr ->getLeftChildPtr())); //Set left/right child and copy the rest of the tree
		new_tree_ptr->setRightChildPtr(copyTree(old_tree_root_ptr ->getRightChildPtr())); //using the pointer to the old tree's children
	} // end if 
	return new_tree_ptr; 
} // end copyTree 

template <typename ItemType>
void BSTdict<ItemType>::destroyTree(std::shared_ptr<BinaryNode<ItemType>> sub_tree_ptr) 
{ 
	if (sub_tree_ptr != nullptr) //Post order traversal
	{ 
		destroyTree(sub_tree_ptr->getLeftChildPtr()); //Must destroy children before root, so that we don't lose 
		destroyTree(sub_tree_ptr->getRightChildPtr()); //access to the rest of the tree
		sub_tree_ptr.reset(); // same as sub_tree_ptr = nullptr for smart pointers 
	} // end if 
} // end destroyTree

template <typename ItemType>
int BSTdict<ItemType>::getHeightHelper(shared_ptr<BinaryNode<ItemType>> sub_tree_ptr) const 
{ 
	if (sub_tree_ptr == nullptr) //Post Order Traversal used here
		return 0; //base case - node
	else 
		return 1 + std::max(getHeightHelper(sub_tree_ptr->getLeftChildPtr()), //recursive call - left then right
            getHeightHelper(sub_tree_ptr->getRightChildPtr())); //get the biggest path between the right or left subtrees.
} // end getHeightHelper

template <typename ItemType>
auto BSTdict<ItemType>::placeNode(shared_ptr<BinaryNode<ItemType>> subtree_ptr, 
        shared_ptr<BinaryNode<ItemType>> new_node_ptr, bool& success) 
{ 
	if (subtree_ptr == nullptr) {
        return new_node_ptr; //base case 
        success = true; //
    }
    else {
		if (subtree_ptr->getItem() > new_node_ptr->getItem()) //if node on tree > new node
			subtree_ptr->setLeftChildPtr(placeNode(subtree_ptr ->getLeftChildPtr(), new_node_ptr, success)); //place on left subtree, recursively
		else 
			subtree_ptr->setRightChildPtr(placeNode(subtree_ptr ->getRightChildPtr(), new_node_ptr, success)); //place on right subtree
		return subtree_ptr; 
	} // end if 
} // end placeNode

template <typename ItemType>
auto BSTdict<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>> subtree_ptr, const ItemType target, bool& success) 
{ 
	if (subtree_ptr == nullptr) { // Base case 1
		// Not found here 
		success = false; //Passed by reference, so it will get updated for original remove funct as well
		return subtree_ptr; 
	} 
	if (subtree_ptr->getItem() == target) { // Base case 2
		// Item is in the root of this subtree 
		subtree_ptr = removeNode(subtree_ptr); 
		success = true; 
		return subtree_ptr; 
	}
	else { //Recursion
		if (subtree_ptr->getItem() > target) { //if target is less than the current node, go to left
			// Search the left subtree 
			subtree_ptr->setLeftChildPtr(removeValue(subtree_ptr ->getLeftChildPtr(), target, success)); 
		} 
		else { //if target is greater than current node, go to right
			// Search the right subtree 
			subtree_ptr->setRightChildPtr(removeValue(subtree_ptr ->getRightChildPtr(), target, success)); //Have to reset right/left childptr
		} 
		return subtree_ptr; 
	} // end if 
} // end removeValue

template <typename ItemType>
auto BSTdict<ItemType>::removeNode(std::shared_ptr<BinaryNode<ItemType>> node_ptr) { 
	//Case 1) Node is a leaf - it is deleted: 
	if (node_ptr->isLeaf()) { 
		node_ptr.reset(); 
		return node_ptr; // delete and return nullptr 
	}
	//Case 2) Node has one child - parent adopts child: 
	else if (node_ptr->getLeftChildPtr() == nullptr) // Has rightChild only 
    { 
		return node_ptr->getRightChildPtr(); 
	} 
	else if (node_ptr->getRightChildPtr() == nullptr) // Has left child only 
    { 
		return node_ptr->getLeftChildPtr(); 
	}
	//Case 3) Node has two children: 
	else { 
		ItemType new_node_value; 
		node_ptr->setRightChildPtr(removeLeftmostNode(node_ptr->getRightChildPtr(), new_node_value)); //Replace with in order successor
		node_ptr->setItem(new_node_value); //Place in order successor, now found in new_node_value, where the node to be removed is
		return node_ptr; 
	} // end if 
} // end removeNode

template <typename ItemType>
auto BSTdict<ItemType>::removeLeftmostNode(shared_ptr<BinaryNode<ItemType>> nodePtr, ItemType& inorderSuccessor) { 
	if (nodePtr->getLeftChildPtr() == nullptr) { // base case, node has no left children, so it is the leftmost node
		inorderSuccessor = nodePtr->getItem(); //update inorderSuccessor
		return removeNode(nodePtr); //remove this node using removeNode funct, it must only have 1 or 0 kids. 
	} 
	else { //recursive case
		nodePtr->setLeftChildPtr(removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor)); //get next left child
		return nodePtr; 
	} // end if 
} // end removeLeftmostNode

template <typename ItemType>
void BSTdict<ItemType>::displayHelper(const std::shared_ptr<BinaryNode<ItemType>> sub_tree_ptr) {
    if (sub_tree_ptr != nullptr) { //Let's do in order traversal, so root node is in the middle
        displayHelper(sub_tree_ptr->getLeftChildPtr());
        cout << " " << sub_tree_ptr->getItem() << endl;
        displayHelper(sub_tree_ptr->getRightChildPtr());
    }
}