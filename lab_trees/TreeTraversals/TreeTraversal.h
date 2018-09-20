#ifndef TREETRAVERSAL_H
#define TREETRAVERSAL_H

#include <iterator>
#include "../binarytree.h"

/**
 * Pure virtual class for traversal algorithms on trees.
 * 
 * Each derived class must not modify the tree itself
 * 
 * A derived class provides a traversal by returning instances of
 * TreeTraversal::Iterator.
 */
template <typename T>
class TreeTraversal {
    public:
    /**
     * A forward iterator class through an TreeTravesal,
     *  derived from the std iterator class.
     */
    class Iterator : std::iterator<std::forward_iterator_tag, typename BinaryTree<T>::Node*> {
	public:
    
	/**
	 * Default constructor for Iterator class
	 * Sets the traversal pointer to NULL
	 */
	Iterator() : traversal(NULL) 
	{
	    /*Nothing*/
	}
  	
	/**
	 * Two parameters constructor for Iterator class
	 *
	 * @param traversal, the traversal reference passed in
	 * @param root, the root of the tree to be traversed
	 */
	Iterator(TreeTraversal<T> & traversal, typename BinaryTree<T>::Node* root) 
	    :traversal(&traversal), root(root)
	{
	    /** initialize the current iterator to top Node of the stack*/
	    current = traversal.peek();
	}
	
	/**
	 * operator++ for Iterator class
	 *
	 * @return the current Node in the traversal
	 */
	Iterator & operator++() 
	{
	    if (!traversal->empty()) {
	    	current = traversal->pop();			
	    	traversal->add(current);
	    	current = traversal->peek();
	    }	
	    return *this;
    	}

    	/**
     	 * Iterator access opreator.
     	 * 
     	 * @return the current Node in the TreeTraversal.
     	 */	
    	typename BinaryTree<T>::Node* operator*() 
    	{
	    return current;
    	}

    	/**
     	 * Iterator inequality operator.
     	 * 
     	 * @return if two iterators are not equal.
     	 */
    	bool operator!=(const Iterator &other) 
    	{
	    bool thisEmpty = false; 
	    bool otherEmpty = false;

	    if (traversal == NULL) { thisEmpty = true; }
	    if (other.traversal == NULL) { otherEmpty = true; }
				
	    if (!thisEmpty)  { thisEmpty = traversal->empty(); }
	    if (!otherEmpty) { otherEmpty = other.traversal->empty(); }
			
	    if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
	    else if ((!thisEmpty)&&(!otherEmpty)) return (traversal != other.traversal); //both not empty then compare the traversals
	    else return true; // one is empty while the other is not, return true
    	}

    	private:
    	TreeTraversal * traversal;
    	typename BinaryTree<T>::Node* root;
    	typename BinaryTree<T>::Node* current;
    };  


    /**
     * Public pure virtual begin() function
     *
     * @return an Iterator points to the first element in the Traversal
     */
    virtual Iterator begin() = 0; 

    /**
     * Public pure virtual end() function 
     *
     * @return an Iterator PASS the last element in the Traversal
     */
    virtual Iterator end() = 0;

    /**
     * Public pure virtual add() function
     *
     * @param treeNode, the current Node to be processed
     */
    virtual void add(typename BinaryTree<T>::Node*& treeNode) = 0;

    /**
     * Public pure virtual pop() function
     *  remove the current Node to be processed
     * 
     * @return a pointer to the removed Node
     */
    virtual typename BinaryTree<T>::Node* pop() = 0;

    /**
     * Public pure virtual peek() function
     * 
     * @return a pointer to the Node on top of the stack
     */
    virtual typename BinaryTree<T>::Node* peek() const = 0;

    /**
     * Public pure virtual empty() function
     * 
     * @return if the stack is empty or not
     */
    virtual bool empty() const = 0;
};
#endif
