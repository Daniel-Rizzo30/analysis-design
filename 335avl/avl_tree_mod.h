/* 
    Daniel Rizzo
    CSCI 335
    Homework 3 2.3
    Professor Sven Dietrich
    March 12th, 2021
    avl_tree_mod.h
    Header file for modded tree data structure. 
*/

#ifndef AVL_TREE_MOD_H
#define AVL_TREE_MOD_H

#include "dsexceptions.h"
#include "sequence_map.h"
#include <algorithm>
#include <iostream> 
#include <string>
#include <cmath>
using namespace std;

// AvlTree Modded class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTreeMod
{
  public:
    AvlTreeMod( ) : root{ nullptr }
      { }
    
    AvlTreeMod( const AvlTreeMod & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    AvlTreeMod( AvlTreeMod && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    ~AvlTreeMod( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTreeMod & operator=( const AvlTreeMod & rhs )
    {
        AvlTreeMod copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    AvlTreeMod & operator=( AvlTreeMod && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }
    /** Functions to manipulate recursive call data members*/
    float getRemoveRecursiveCalls() {
        return remove_recursive_calls_;
    }
    void resetRemoveRecursiveCalls() {
        remove_recursive_calls_ = 0;
    }
    float getFindRecursiveCalls() {
        return find_recursive_calls_;
    }
    void resetFindRecursiveCalls() {
        find_recursive_calls_ = 0;
    }

    /**
     * Removes a node from the tree based on a recognition sequence
     * @param x is the recognition sequence / SequenceMap / Comparable to be searched for and removed
     * @return false if no node with the reco seq is found, true if a node is found and removed
     */
    bool removeSequence(Comparable &x) {
        if( isEmpty( ) ) {
            cout << "Empty tree" << endl;
            return false;
        }
        else if ( !(find(x.getRecognitionSequence())) ) { // If reco seq already doesn't exist in tree,
            return false; // Can't remove it, return false.
        }
        else {
            remove(x, root);
            return !(find(x.getRecognitionSequence())); // Return the opposite of what find would - not found = success.
        }
    }

    /**
     * Searches tree for a recognition sequence
     * @param a_rec_seq is the sequence being searched for
     * @return true if recognition sequence is found, false otherwise
     */
    bool find(string a_reco_seq) {
        if( isEmpty( ) ) {
            cout << "Empty tree" << endl;
            return false;
        }
        else {
            bool found; // Keep track of if found
            find(a_reco_seq, found, root);
            return found;
        }
    }

    /** 
     * Print the tree's average depth
     */
    float AverageDepth( ) const {
        if( isEmpty( ) ) {
            cout << "Empty tree" << endl;
            return -1; // Sentinal value
        }
        else {
            fixDepths(0, root); // Set all depths of every node using inner function.
            float TotalDepths = 0;
            AverageDepth(TotalDepths, root); // Call inner function
            int n = NumberofNodes(); // Get number of nodes
            float AvgDepth = TotalDepths / n;
            return AvgDepth; 
        }
    }

    /**
     * Print the tree's ratio of average depth.
     */
    float Ratio( ) const
    {
        if( isEmpty( ) ) {
            cout << "Empty tree" << endl;
            return -1; // Sentinal value
        }
        else {
            float Average = AverageDepth(); // Get average
            int n = NumberofNodes(); // Get number of nodes
            return (Average / log2(n)); // Compute and return the ratio
        }
    }


    /**
     * Print the number of nodes in the tree.
     */
    int NumberofNodes( ) const
    {
        size_t N = 0;
        if( isEmpty( ) )
            return N; // return 0. 
        else {
            NumberofNodes( N, root ); // Call inner function to recursively count nodes
            return N; // return N. 
        }
    }

    /**
     * Prints all enzyme acronyms for the given recognition sequence.
     */
    void printEnzymeAcronyms(string a_reco_seq) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl; // Can't work with an empty tree
        else {
            bool found = false; // Use boolean to keep track of if a matching recognition sequence was found
            printEnzymeAcronyms(a_reco_seq, found, root); // Call inner function
            if (found == false) // Will be updated to true if found
                cout << "Not Found" << endl; // Otherwise nothing has printed so print Not Found.
        } 
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;
        int       depth; // Add to keep track of all depths

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    AvlNode *root;
    float remove_recursive_calls_ = 0; // Keep track of remove's calls
    float find_recursive_calls_ = 0; // Keep track of find's calls


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if (t != nullptr) { // Can't compare if the node is empty
            if(t->element.getRecognitionSequence() == x.getRecognitionSequence()){ // If recognition sequences match,
                t->element.Merge(x); // Then merge
                return; // No new Node added, so then there's no need to call balance(). 
            }
        }

        // Continue searching tree for other nodes that may match Recognition Sequence
        if( t == nullptr ) // If empty, add new Node
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if (t != nullptr) { // Can't compare if the node is empty
            if(t->element.getRecognitionSequence() == x.getRecognitionSequence()){ // If recognition sequences match,
                t->element.Merge(x); // Then merge
                return; // No new Node added, so then there's no need to call balance(). 
            }
        }

        // Continue searching tree for node that may match Recognition Sequence
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        
        balance( t );
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        remove_recursive_calls_++; // Add 1 to remove's calls since it's searching a new node
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            oldNode = nullptr;
        }
        
        balance( t );
    }
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        } else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
	}
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal function for finding a node based on recognition sequence
     * @param a_reco_seq is the recognition sequence being looked for
     * @param found is the boolean keeping track of if the node is ever found in any call. 
     * @param t is the node currently at. 
     */
    void find(string a_reco_seq, bool &found, AvlNode *t) {
        if( t != nullptr ) {
            find_recursive_calls_++; // Update find's calls
            if (t->element.getRecognitionSequence() == a_reco_seq) { // Match
                found = true; // It's found
                return; // Need to return so no more functions are called recursively
            }
            if( a_reco_seq < t->element.getRecognitionSequence() ) // Check one side of the tree depending on comparison
                return find( a_reco_seq, found, t->left );
            else if( t->element.getRecognitionSequence() < a_reco_seq ) // Cuts down on calls exponentially. 
                return find( a_reco_seq, found, t->right );
        }
    }

    /**
     * Internal method to obtain average depth of the tree
     * @param TotalDepths is the Total depth that is added to on each recursive pass
     * @param t is the current node whose height is being calculated.
     */
    void AverageDepth(float &TotalDepths, AvlNode *t ) const {
        if( t != nullptr ) { // Search height if not empty
            AverageDepth(TotalDepths, t->left); // Search depth of the children.
            TotalDepths += t->depth; // Add the depth of the current node to Total, use root height to get max depth
            AverageDepth(TotalDepths, t->right);
        }
    }

    /**
     * Internal function to print number of nodes in the tree
     * @param count is the number of nodes counted so far
     * @param t is the Node currently being checked
     */
    void NumberofNodes( size_t &count, AvlNode *t ) const { 

        if( t != nullptr ) { // Count node if not empty
            count++; // Increment the count
            NumberofNodes(count, t->left); // Count the children.
            NumberofNodes(count, t->right);
        }
    }


    /**
     * Internal method to print out all associated enzyme acronyms
     * @param a_reco_seq is the recognition sequence to check with
     * @param found keeps track of if a node has been found yet.
     * @param t is the Node currently being checked
     */
    void printEnzymeAcronyms(string a_reco_seq, bool &found, AvlNode *t) const {

        if( t != nullptr ) { // Search node if not empty
            if (t->element.getRecognitionSequence() == a_reco_seq) { // First check if at the matching node
                cout << t->element; // Use overloaded << to print all enzyme acronyms
                found = true; // Set found to true, it's passed by reference so it will update
                return; // Matching node found, so the function's purpose is complete, it can return.
            }
            printEnzymeAcronyms(a_reco_seq, found, t->left); // If not found, check the children.
            printEnzymeAcronyms(a_reco_seq, found, t->right);
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Function to be called before calculating Average Depth that sets all nodes' depths
     * @param t is the node currently at
     * @param depth is the depth of the current node, calculated from knowing root depth == 0.
     */
    void fixDepths(int depth, AvlNode *t) const {
        if (t != nullptr) {
            t->depth = depth;
            fixDepths(depth + 1, t->left); // left sub-tree
            fixDepths(depth + 1, t->right); // right sub-tree
        }
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 ) {
        AvlNode *k2 = k3->left->right; // k2 is k3's grandchild
        AvlNode *k1 = k3->left; // k1 is k3's left child. 
        k3->left = k2->right; // Give k2's right side (C) to k3's left side
        k1->right = k2->left; // Give k2's left (B) to k1's right
        k2->left = k1; // Make k1 and k3 children of k2
        k2->right = k3;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1; // Reset all heights
        k3->height = max( height( k3->left ), height( k3->right ) ) + 1;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1; // Reset the new subroot last
        k3 = k2; // Set old subroot equal to new subroot so that the parent of this subroot points to the right node

    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 ) {
        AvlNode *k2 = k1->right->left; // k2 is k1's grandchild. 
        AvlNode *k3 = k1->right; // k3 is k1's right child. 
        k1->right = k2->left; // Give k2's left side (B) to k1
        k3->left = k2->right; // Give k2's right side (C) to k3.
        k2->left = k1; // Make k1 and k3 children of k2
        k2->right = k3;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1; // Reset all heights
        k3->height = max( height( k3->left ), height( k3->right ) ) + 1;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1; // Reset the new subroot last
        k1 = k2; // Set old subroot equal to new subroot so that the parent of this subroot points to the right node
    }
};

#endif