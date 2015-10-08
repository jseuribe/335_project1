/********************************************************************************************************************************************************
 Title: BSTDNA
 Author: Jose Antonio Uribe(With modifications on the code by Mark Allen Weiss)
 Created: October 15, 2014
 Purpose:A BST tree specifically designed to handle the sequenceMap data type
 Build with: g++ -o programname "Your_Main_Function_Holding_File_Here".cpp
 Given that this is simply a header with implementations inside, just include in your main function file.
********************************************************************************************************************************************************/


#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void find( x )
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

class BinarySearchTree
{
  public:
    BinarySearchTree( ) :root{ nullptr } , totalInsertionCalls{0} , totalContainsCalls{0} , totalRemoveCalls{0}, successfulRemoves{0} {}

    /**
     * Copy constructor
     */
    BinarySearchTree( BinarySearchTree & rhs ) : root{ nullptr }
    {
	totalInsertionCalls = rhs.totalInsertionCalls;
	totalContainsCalls = rhs.totalContainsCalls;
	totalRemoveCalls = rhs.totalRemoveCalls;
	successfulRemoves = rhs.successfulRemoves;
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const sequenceMap & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const sequenceMap & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    //finds the item, specified by x.
    void find(sequenceMap x)
    {
	find(x, root);
    }
    /**
     * Returns true if x is found in the tree.
     */
    bool contains( sequenceMap  x ) 
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
    void insert( sequenceMap & x )
    {
	//cout << "We are going to insert: " << x << endl;
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( sequenceMap && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( sequenceMap & x )
    {
        remove( x, root );
    }

    /*
	MODIFICATIONS BELOW
	These new functions are specific to the assignment; they are all new.
    */

    int returnInsertionCalls()
    {
	return totalInsertionCalls;
    }

    int returnContainsCalls()
    {
	return totalContainsCalls;
    }

    int returnRemoveCalls()
    {
	return totalRemoveCalls;
    }

    int returnSuccessfulRemoves()
    {
	return successfulRemoves;
    }

    float numberOfNodes()
    {
	float value = 0;
	return numberOfNodes(root, value);
    }

    float depth()
    {
	float depthsoFar = 0;
	return depth(root, depthsoFar);

    }

    void resetInsertCalls()
    {
	totalInsertionCalls = 0;
    }

    void resetContainsCalls()
    {
	totalContainsCalls = 0;
    }

    void resetRemoveCalls()
    {
	totalRemoveCalls = 0;
    }

    void resetSuccessfulRemoves()
    {
	successfulRemoves = 0;
    }

    /*
	END OF MODIFICATIONS
    */

  private:
    int totalInsertionCalls;
    int totalContainsCalls;
    int totalRemoveCalls;
    int successfulRemoves;
    struct BinaryNode
    {
        sequenceMap element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( sequenceMap & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( sequenceMap && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;

    // If the node is found, we use printAcronyms to print it; else, we state its absence
    void find( sequenceMap x, BinaryNode *t )
    {

        if( t == nullptr ) cout << "not found" << endl;
        else if( x < t->element )
            find( x, t->left );
        else if( t->element < x )
            find( x, t->right );
        else (t->element).printAcronyms();

    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( sequenceMap & x, BinaryNode * & t )
    {

	totalInsertionCalls++;
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( (x < t->element) )
            insert( x, t->left );
        else if( (t->element < x) )
            insert( x, t->right );
        else (t->element).mergeObjects(x);  // If the sequence exists already, we append the acronym of our new object to this existing obj.
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * NOTE: This function is never used. Disregard; it is kept in out of fear of breaking the tree datatype
     */
    void insert( sequenceMap && x, BinaryNode * & t )
    {
	totalInsertionCalls++;
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( (x < t->element) ){
            insert( std::move( x ), t->left );
	}
        else if( (t->element < x) ){
            insert( std::move( x ), t->right );
	}
        else
            (t->element).mergeObjects(x);  // if the obj exists, append the acronyms of the new obj to it.
    }
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( sequenceMap & x, BinaryNode * & t )
    {
        totalRemoveCalls++;
	if(t == nullptr) return; // Item not found; do nothing
        else if( (x < t->element) ){
            remove( x, t->left );
	}
        else if( (t->element < x) ){
            remove( x, t->right );
	}
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
	    successfulRemoves++;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
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
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( sequenceMap  x, BinaryNode *t ) 
    {
	
	totalContainsCalls++;
        
        if( t == nullptr ){
		return false;
	}
        else if( x < t->element ){
            return contains( x, t->left );
	}
        else if( t->element < x ){
            return contains( x, t->right );
	}
	else return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
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
    void makeEmpty( BinaryNode * & t )
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
    void printTree( BinaryNode *t ) const
    {
        if( t != nullptr )
        {
	    printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }

    float numberOfNodes(BinaryNode *root, float value)
    //Recursive function to compute the # of nodes.
    {
	if(root == nullptr) return 0;
	else return numberOfNodes(root->left, value) + numberOfNodes(root->right, value) + 1;
    }

    float depth(BinaryNode *root, float depthsoFar)
    {
	if(root == nullptr) return 0;
	else return depth(root->left, depthsoFar+1) + depth(root->right, depthsoFar+1) + depthsoFar;

    }

};

#endif
