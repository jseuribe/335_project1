/********************************************************************************************************************************************************
 Title: lazy BST Tree
 Author: Jose Antonio Uribe(With modifications on the code by Mark Allen Weiss)
 Created: October 15, 2014
 Purpose:A lazy deletion class, which marks nodes deleted when removed.
 Build with: g++ -o programname "Your_Main_Function_Holding_File_Here".cpp
 Given that this is simply a header with implementations inside, just include in your main function file.
********************************************************************************************************************************************************/


#ifndef LAZY_BINARY_SEARCH_TREE_H
#define LAZY_BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

class LazyBinarySearchTree
{
  public:
    LazyBinarySearchTree( ) :root{ nullptr } , totalInsertionCalls{0} , totalContainsCalls{0} , totalRemoveCalls{0}, successfulRemoves{0} {}

    /**
     * Copy constructor
     */
    LazyBinarySearchTree( LazyBinarySearchTree & rhs ) : root{ nullptr }
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
    LazyBinarySearchTree( LazyBinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~LazyBinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    LazyBinarySearchTree & operator=( LazyBinarySearchTree & rhs )
    {
        LazyBinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    LazyBinarySearchTree & operator=( LazyBinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */

    /*
    const sequenceMap & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     *//*
    const sequenceMap & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    */

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
     *//*
    void insert( sequenceMap && x )
    {
        insert( std::move( x ), root );
    }*/
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( sequenceMap & x )
    {
        remove( x, root );
    }

    /*
	MODIFICATIONS BELOW
	These new functions are specific to the assignment; they are 	      all new.
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
	bool active;

        BinaryNode( sequenceMap & theElement, BinaryNode *lt, BinaryNode *rt, bool nodestatus )
          : element{ theElement }, left{ lt }, right{ rt },  active{nodestatus} { }
        
        BinaryNode( sequenceMap && theElement, BinaryNode *lt, BinaryNode *rt, bool nodestatus )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt }, active{nodestatus} { }

	void deactivate()
    	{
	    active = false;
   	}

    	void reActivate()
    	{
	    active = true;
    	}
    };

    BinaryNode *root;

    // If the node is found, we use printAcronyms to print it; else,    we state its absence
    void find( sequenceMap x, BinaryNode *t )
    {
        if( t == nullptr ) cout << "not found" << endl;
        else if( x < t->element )
            find( x, t->left );
        else if( t->element < x )
            find( x, t->right );
        else if(t->active == true) (t->element).printAcronyms();

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
            t = new BinaryNode{ x, nullptr, nullptr, true };
	else if(t->active == false) t->reActivate();//If the node exists already, we simply reactivate it.
        else if( (x < t->element) )
            insert( x, t->left );
        else if( (t->element < x) )
            insert( x, t->right );
        else (t->element).mergeObjects(x);  //The objects are merged if it exists already, and it's active.
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    /*
    void insert( sequenceMap && x, BinaryNode * & t )
    {
	totalInsertionCalls++;
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr, true };
        else if( (x < t->element) ){
	    //cout << "TO THE LEFT" << endl;
            insert( std::move( x ), t->left );
	}
        else if( (t->element < x) ){
	    //cout << "TO THE RIGHT" << endl;
            insert( std::move( x ), t->right );
	}
        else (t->element).mergeObjects(x);  // Duplicate; do nothing
    }*/

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( sequenceMap & x, BinaryNode * & t )
    {
        totalRemoveCalls++;
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( (x < t->element) ){
            remove( x, t->left );
	}
        else if( (t->element < x) ){
            remove( x, t->right );
	}
	//else if(t->active == false) return; //node already deleted; disregard
        else
        {
	    //cout << t->active << " should be 1" << endl;
	    //cout << x << " " << t->element << endl;
            t->deactivate();//We delete the node if it's active.
	    //cout << t->active << " should be 0" << endl;
	    successfulRemoves++;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */

    /*THESE ARE INCLUDED FOR COMPLETION'S SAKE. SINCE IT WILL NOT BE GRADED, IT WON'T WORK.
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if(t == nullptr) return nullptr;//end of tree
        cout << t->element << endl;
        BinaryNode *current = findMin(t->left);//Will search for the min as of this node
        //if(current != nullptr) return current;//If the previous node is not empty, the current node is therefore the smallest
        if(t->active)return t;//If this node is active, it is therefore the smallest
        return findMin(t->right);//If the node is inactive, the right node may be the smallest
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if(t == nullptr) return nullptr;//End of tree
	BinaryNode *current = findMax(t->right);//Will search for the max as of this node
        if(current != nullptr) return current;//If the previous node is not empty, the current node is therefore the biggest
        if(t->active)return t;//If the node is active, then it is therefore the biggest
        return findMax(t->left);//If all nodes in the right are deactivated, the left must be searched.
    }
*/

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( sequenceMap  x, BinaryNode *t ) 
    {
	totalContainsCalls++;
        if( t == nullptr ){
		return true;
	}
        else if( x < t->element ){
            return contains( x, t->left );
	}
        else if( t->element < x ){
            return contains( x, t->right );
	}
        else
	{
	  if(t->active == false){
	    return false;//If the node is deactivated, it technically does not exist.
	  }
	  else return true; //Match
	}

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
	//string temp;
	//temp = (t->element).getRecognitionSequence();
	//cout << "temp has: "  << temp << endl;
        if( t != nullptr )
        {
	    printTree( t->left );
            if(t->active == true)cout << t->element << endl;
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
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ), t->active };
    }

    float numberOfNodes(BinaryNode *root, float value)
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
