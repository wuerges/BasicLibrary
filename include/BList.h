/***************************** License **********************************

 Copyright (C) 2011 by Jose Carlos Bins Filho josebins@gmail.com

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

************************************************************************/


#if !defined(_BLIST_H_)
#define _BLIST_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "BFunctions.h"

/// \file BFile.h
///
/// File where the BFile class and other auxiliary funcytions are declared
///


/// Default base index. Initial value used to count indexes.
#define BLISTBASEINDEX 0

template <class Td, class Tk> class BList;


//
//--------------------------------------------------------------------------------------------
///
/// Class BListNode : class that holds a node used in the BList class
///
///	Depending of your data and of the functions you use you  may need to
///	create one or more of the functions below for your data.
///
///	bool isInvalid(T dt)       : that tests if the dt is invalid or NULL\n
///	T invalid(T dt)            : that returns an invalid dt or NULL\n
///	bool isEqual(T dt1, T dt2) : that tests it the two are equal\n
///	T copy(T dt)               : that copies the value of dt (does not allocate space)\n
///	T clone(T dt)              : that makes a new copy of dt (allocates space)\n
///	bool ordered(T dt1, T dt2, bool asc) : that returns true if dt1 is smaller or equal dt2
///	                             when asc is true; or returns true if dt2  is smaller or equal
///						         dt2 when asc is false; or returns false otherwise\n
/// void remove(T dt)          : remove your data; if you data is a class or string
///	                             that is not necessary\n
/// char * toSring(T dt)	   : Converts the content of the data in a string to be printed\n
///
///	Functions for the most common data types are provided (see Bfunctions.h)
///	You can redefine them or create new ones for your data
///
//--------------------------------------------------------------------------------------------
//
template <class Td, class Tk = int> class BListNode  {
public:
	/// Constructor for keyless node. If the reference is not set a new copy of the data is created.
	BListNode(Td dt,		///< [in] Node data
		bool ref = false	///< [in] (optional) Reference. If not set a new copy of the data is created.
		);
	/// Constructor. If the reference is not set a new copies of the data and key are created.
	BListNode(Td dt,		///< [in] Node data
		Tk k,				///< [in] Node key
		bool ref = false	///< [in] (optional) Reference. If not set a new copy of the data is created.
		);
	/// Destructor. If the node is a reference the data and key will not be deleted.
	~BListNode();
	/// Function that returns the previous node
	BListNode<Td,Tk>* getPrevious();
	/// Function that returns the previous node
	BListNode<Td,Tk>* getNext();
	/// Function that returns the node's data
	Td getData();
	/// Function that returns the node's key
	Tk getKey();
	/// Function that set the node's data. If the node is not a reference the old data is deleted.
	void setData(Td);
	/// Function that set the node's key. If the node is not a reference the old key is deleted.
	void setKey(Tk);
	/// Functions that convert the node content in a string to be printed.
	char * toString(int i, int t = 0);
	friend class BList<Td,Tk>;

protected:
	bool reference;   // if a BListNode is set as a reference that means that its content only points
	                  // for some data. So it will not be deleted when the BListNode is deleted.
	Tk key;
	Td data;
	BListNode<Td,Tk>
		*previous,
		*next;
};

template <class Td, class Tk> BListNode<Td, Tk>::BListNode(Td dt, bool ref) {

	if (ref)
		data = copy(dt);
	else
		data = clone(dt);
	key = invalid(key);
	previous = next = NULL;
	reference = ref;

}
template <class Td, class Tk> BListNode<Td, Tk>::BListNode(Td dt, Tk k,  bool ref) {

	if (ref) {
		data = copy(dt);
		key = copy(k);
	} else {
		data = clone(dt);
		key = clone(k);
	}

	previous = next = NULL;
	reference = ref;

}
template <class Td, class Tk> BListNode<Td, Tk>::~BListNode() {

	if (reference)
		return;
	remove(data);
	remove(key);

}
template <class Td, class Tk> BListNode<Td, Tk> * BListNode<Td, Tk>::getPrevious() {
	return previous;
}
template <class Td, class Tk> BListNode<Td, Tk> * BListNode<Td, Tk>::getNext() {
	return next;
}
template <class Td, class Tk> Td BListNode<Td, Tk>::getData() {
	return data;
}
template <class Td, class Tk> Tk BListNode<Td, Tk>::getKey() {
	return key;
}
template <class Td, class Tk> void BListNode<Td, Tk>::setData(Td dt) {
	if (!reference)
		remove(data);
	data = clone(dt);
}
template <class Td, class Tk> void BListNode<Td, Tk>::setKey(Tk k) {
	if (!reference)
		remove(key);
	key = clone(k);
}
template <class Td, class Tk> char * BListNode<Td, Tk>::toString(int p, int t) {

	if (t < 0) t = 0;
	char *strtab = new char [t+1];

	strtab[0] = '\0';
	for (int i=0; i < t; i++)
		strtab[i] = '\t';
	strtab[t] = '\0';

	char * strkey = ::toString(key),
		 * strpkey = NULL,
		 * strnkey = NULL,
		 * strdata = ::toString(data);

	if (previous != NULL && previous->key != NULL)
		strpkey = ::toString(previous->key);
	if (next != NULL && next->key != NULL)
		strnkey = ::toString(next->key);

	int l = 1;
	l+= p > INVALIDINDEX ? 15+t : 0;

	char * strnum = NULL;

	if (p > INVALIDINDEX) {
		strnum = new char [l];
		sprintf(strnum, "%sNode:    %3d\n", strtab, p);
	}

	l+= 18+t;
	l+= strkey == NULL ? 15+t : 10+t+strlen(strkey);
	l+= strdata == NULL ? 15+t : 10+t+strlen(strdata);
	l+= strpkey == NULL ? 15+t : 10+t+strlen(strpkey);
	l+= strnkey == NULL ? 15+t : 10+t+strlen(strnkey);

	char * str = new char [l];

	if (strnum == NULL)
		sprintf(str, "%sPointer: %p\n%sKey:     %s\n%sData:    %s\n%sPrev:    %s\n%sNext:    %s\n",
			strtab, this, strtab, strkey, strtab, strdata, strtab, strpkey, strtab, strnkey);
	else
		sprintf(str, "%s%sPointer: %p\n%sKey:     %s\n%sData:    %s\n%sPrev:    %s\n%sNext:    %s\n",
			strnum, strtab, this, strtab, strkey, strtab, strdata, strtab, strpkey, strtab, strnkey);

	delete [] strnum;
	delete [] strkey;
	delete [] strpkey;
	delete [] strnkey;
	delete [] strdata;
	delete [] strtab;

	return str;
}

//
//--------------------------------------------------------------------------------------------
///
/// Class BList : class that holds a double linked list
///
///	Depending of your data and of the functions you use you  may need to
///	create one or more of the functions below for your data.
///
///	bool isInvalid(T dt)       : that tests if the dt is invalid or NULL\n
///	T invalid(T dt)            : that returns an invalid dt or NULL\n
///	bool isEqual(T dt1, T dt2) : that tests it the two are equal\n
///	T copy(T dt)               : that copies the value of dt (does not allocate space)\n
///	T clone(T dt)              : that makes a new copy of dt (allocates space)\n
///	bool ordered(T dt1, T dt2, bool asc) : that returns true if dt1 is smaller or equal dt2
///	                             when asc is true; or returns true if dt2  is smaller or equal
///						         dt2 when asc is false; or returns false otherwise\n
/// void remove(T dt)          : remove your data; if you data is a class or string
///	                             that is not necessary\n
/// char * toSring(T dt)	   : Converts the content of the data in a string to be printed\n
///
///	Functions for the most common data types are provided (see Bfunctions.h)
///	You can redefine them or create new ones for your data
///
//--------------------------------------------------------------------------------------------
//
template <class Td, class Tk = int> class BList {
public:
	/// Constructor
	BList(int = BLISTBASEINDEX	///< [in] (optional) Initial value for the index; Default is BLISTBASEINDEX
		);
	/// Destructor
	~BList();
	/// Function that returns the number of itens on the list
	int getCount() { return n;};
	/// Function that returns the index base set at the creation of the list
	int getIndexBase() { return indbase;};
	/// Function that returns a pointer to the node selected by the index used
	BListNode<Td,Tk> * getNodeByIndex(int ind	///< [in] Index of the node
		);
	/// Function that returns a pointer to the node selected by the key used
	BListNode<Td,Tk> * getNodeByKey(Tk k		///< [in] Key of the node
		);
	/// Function that returns a pointer to the node selected by the data used
	BListNode<Td,Tk> * getNodeByData(Td dt		///< [in] Data of the node
		);
	/// Function that returns a pointer to the current node. If there are no nodes or the current node is not set it returns NULL.
	BListNode<Td,Tk> * getCurrent() { return current;};
	/// Function that returns a pointer to the first node. If there are no nodes it returns NULL.
	BListNode<Td,Tk> * getFirst();
	/// Function that returns a pointer to the previous node. . If there are no nodes or the current node is the first one it returns NULL.
	BListNode<Td,Tk> * getPrevious();
	/// Function that returns a pointer to the next node. If there are no nodes or the current node is the last one it returns NULL.
	BListNode<Td,Tk> * getNext();
	/// Function that returns a pointer to the last node. If there are no nodes it returns NULL.
	BListNode<Td,Tk> * getLast();
	/// Function that returns true is the current node is the first node or false otherwise
	bool isFirst() {current == first;};
	/// Function that returns true is the current node is the last node or false otherwise
	bool isLast() {current == last;};
	/// Function that returns the index for the current node.
	int getCurrentIndex();
	/// Function that returns the key for the current node.
	Tk getCurrentKey();
	/// Function that returns the data of the current node.
	Td getCurrentData();
	/// Function that sets the data of the current node. A new copy of data is done.
	bool setCurrentData(Td dt	///< [in] Data to copy
		);
	/// Function that sets the key of the current node. A new copyof the key is done.
	bool setCurrentKey(Tk k		///< [in] Key to copy
		);
	/// Function that adds a node to the list. A copy of the data is done if the node is not used as a reference.
	BListNode<Td,Tk> *  add(Td dt,	///< [in] Data for the node
		bool ref=false				///< [in] (optional) Flag to consider the node as a reference. The data will not be deleted at destruction of the node. Default is false.
		);
	/// Function that adds a node to the list. Copies of the data and key are done if the node is not used as a reference.
	BListNode<Td,Tk> *  add(Td dt,	///< [in] Data for the node
		Tk k,						///< [in] Key for the node
		bool ref=false				///< [in] (optional) Flag to consider the node as a reference. The data will not be deleted at destruction of the node. Default is false.
		);
	/// Function that adds a node at the first position of the list. A copy of the data is done if the node is not used as a reference.
	BListNode<Td,Tk> *  addFirst(Td dt,	///< [in] Data for the node
		bool ref=false				///< [in] (optional) Flag to consider the node as a reference. The data will not be deleted at destruction of the node. Default is false.
		);
	/// Function that adds a node at the first position of the list. Copies of the data and key are done if the node is not used as a reference.
	BListNode<Td,Tk> *  addFirst(Td dt,	///< [in] Data for the node
		Tk k,						///< [in] Key for the node
		bool ref=false				///< [in] (optional) Flag to consider the node as a reference. The data will not be deleted at destruction of the node. Default is false.
		);
	/// Function that adds a node at the last position of the list. A copy of the data is done if the node is not used as a reference.
	BListNode<Td,Tk> *  addLast(Td dt,	///< [in] Data for the node
		bool ref=false				///< [in] (optional) Flag to consider the node as a reference. The data will not be deleted at destruction of the node. Default is false.
		) {return add(dt,ref);};
	/// Function that adds a node at the last position of the list. Copies of the data and key are done if the node is not used as a reference.
	BListNode<Td,Tk> *  addLast(Td dt,	///< [in] Data for the node
		Tk k,						///< [in] Key for the node
		bool ref=false				///< [in] (optional) Flag to consider the node as a reference. The data will not be deleted at destruction of the node. Default is false.
		) {return add(dt,k,ref);};
	/// Function that adds a node to the list before the current node's position. A copy of the data is done if the node is not used as a reference.
	BListNode<Td,Tk> *  addBefore(Td dt,	///< [in] Data for the node
		bool ref=false				///< [in] (optional) Flag to consider the node as a reference. The data will not be deleted at destruction of the node. Default is false.
		);
	/// Function that adds a node to the list before the current node's position. Copies of the data and key are done if the node is not used as a reference.
	BListNode<Td,Tk> *  addBefore(Td dt,	///< [in] Data for the node
		Tk k,						///< [in] Key for the node
		bool ref=false				///< [in] (optional) Flag to consider the node as a reference. The data will not be deleted at destruction of the node. Default is false.
		);
	/// Function that adds a node to the list after the current node's position. A copy of the data is done if the node is not used as a reference.
	BListNode<Td,Tk> *  addAfter(Td dt,	///< [in] Data for the node
		bool ref=false				///< [in] (optional) Flag to consider the node as a reference. The data will not be deleted at destruction of the node. Default is false.
		);
	/// Function that adds a node to the list after the current node's position. Copies of the data and key are done if the node is not used as a reference.
	BListNode<Td,Tk> *  addAfter(Td dt,	///< [in] Data for the node
		Tk k,						///< [in] Key for the node
		bool ref=false				///< [in] (optional) Flag to consider the node as a reference. The data will not be deleted at destruction of the node. Default is false.
		);
	/// Function that adds a node to the list in the ordered position of its key. Copies of the data and key are done if the node is not used as a reference.
	BListNode<Td,Tk> *  insert(Td dt,	///< [in] Data for the node
		Tk k,						///< [in] Key for the node
		bool ref=false,				///< [in] (optional) Flag to consider the node as a reference. The data will not be deleted at destruction of the node. Default is false.
		bool ascending = true		///< [in] (optional) Direction of the ordering. Default is ascending
		);
	/// Function that removes the first node of the list. If the reference flag is not set the data and key are deleted.
	bool removeFirst();
	/// Function that removes the last node of the list. If the reference flag is not set the data and key are deleted.
	bool removeLast();
	/// Function that removes the current list node. If the reference flag is not set the data and key are deleted.
	bool removeCurrent();
	/// Function that removes all list nodes. For each node, if the reference flag is not set the data and key are deleted.
	bool clean();
	/// Function that checks if a series of nodes fit the list (begining at the first node). A list of data and keys must be provided to the test. The order is: node 1 data, node 1 key, node 2 data, node 2 key, ...
	bool check(int n,		///< number of itens to check
		...);
	/// Function that checks if a series of node's data fit the list (begining at the first node). A list of data itens must be provided to the test.
	bool checkData(int n,		///< number of itens to check
		...);
	/// Function that checks if a series of node's key fit the list (begining at the first node). A list of keys must be provided to the test.
	bool checkKey(int n,		///< number of itens to check
		...);
	/// Function that clones a list.
	BList<Td, Tk> * clone();
	/// Function that clones a list. If the object is invalid returns NULL.
	static BList<Td, Tk> * clone(BList<Td, Tk> *	///< [in] List to clone
		);
	/// Function that removes a list. If the object is invalid returns false.  After removing the object sets its pointer to NULL.
	static bool remove(BList<Td, Tk> *&);
	/// Function that creates a list if the pointer is NULL, otherwise returns false.
	static bool create(BList<Td, Tk> *&,	///< [in,out] Pointer to the BList object
		int = BLISTBASEINDEX				///< [in] (optional) Initial value for the index; Default is BLISTBASEINDEX
		);
	/// Function that returns a copy of the list. The data and key of each node are not new objects but references. When the list is removed the data and key of each node are not deleted.
	BList<Td, Tk> * getReference();
	/// Function that returns a copy of the list. If the pointer is NULL returns NULL. The data e key of each node are not new objects but references. When the list is removed the data and key of each node are not deleted.
	static BList<Td, Tk> * getReference(BList<Td, Tk> *		///< [in,out] Pointer to the BList object
		);
	/// Function that sorts the list using the key of each node
	void bubbleSort(bool = true);
	/// Functio that prints the list on the standard output.
	void print(char* str,	///< [in] Title/name of the list
		int tab = 0			///< [in] (optional) Number of tabs at the beginning of the list. Default is 0
		);
	/// Functio that prints the list on the provided file.
	void print(FILE * f = NULL,		///< [in] File descriptor
		char* str = NULL,	///< [in] (optional) Title/name of the list. Default is NULL.
		int tab = 0			///< [in] (optional) Number of tabs at the beginning of the list. Default is 0
		);
	/// Functio that converts the list to an vector of the data type.
	Td * toVector();
	bool isMember(Td);

protected:
	BListNode<Td, Tk>
		* first,	///< Pointer to the first node
		* last,		///< Pointer to the last node
		* current;	///< Pointer to the current node
	int
		n;			///< Number of nodes
	int indbase;	///< Initial value for the index
	Td invdt;		///< An invalid data item
	Tk invkey;		///< An invalid key item
};


template <class Td, class Tk> BList<Td, Tk>::BList(int ind) {
	first = last = current = NULL;
	n = 0;
	indbase = ind;
	invdt = invalid(invdt);
	invkey = invalid(invkey);
}
template <class Td, class Tk> BList<Td, Tk>::~BList() {
	BListNode<Td, Tk>  *nxt;
	current = first;
	while (current != NULL) {
		nxt = current->next;
		delete current;
		current = nxt;
	}


}
template <class Td, class Tk> BListNode<Td,Tk> * BList<Td, Tk>::getNodeByIndex(int p) {

	if (p-indbase >= n)
		return NULL;

	BListNode<Td, Tk> * node = NULL;

	node = first;

	while (node != NULL && p > indbase) {
		node = node->next;
		p--;
	}

	current = node;

    return current;
}
template <class Td, class Tk> BListNode<Td,Tk> * BList<Td, Tk>::getNodeByKey(Tk k) {

	BListNode<Td, Tk> * node = NULL;

	node = first;

	if (isInvalid(k))
		return NULL;

	while (node != NULL && !isEqual(k,node->key)) {
		node = node->next;
	}

	current = node;

    return current;
}
template <class Td, class Tk> BListNode<Td,Tk> * BList<Td, Tk>::getNodeByData(Td dt) {

	BListNode<Td, Tk> * node = NULL;

	node = first;

	if (isInvalid(dt))
		return NULL;

	while (node != NULL && !isEqual(dt,node->data)) {
		node = node->next;
	}

	current = node;

    return current;
}
template <class Td, class Tk> BListNode<Td, Tk> * BList<Td, Tk>::getFirst() {

	if (first == NULL)
		return NULL;
	current = first;

	return current;
}
template <class Td, class Tk> BListNode<Td, Tk> * BList<Td, Tk>::getPrevious() {

	if (current == NULL)
		return NULL;
	current = current->previous;

	return current;
}
template <class Td, class Tk> BListNode<Td, Tk> * BList<Td, Tk>::getNext() {

	if (current == NULL)
		return NULL;
	current = current->next;

	return current;
}
template <class Td, class Tk> BListNode<Td, Tk> * BList<Td, Tk>::getLast() {

	if (last == NULL)
		return NULL;
	current = last;

	return current;
}
template <class Td, class Tk> int BList<Td, Tk>::getCurrentIndex() {

	if (current == NULL)
		return INVALIDINDEX;

	BListNode<Td, Tk> * node = first;

	int p = indbase;

	while (node != current) {
		node = node->next;
		p++;
	}

	return p;
}
template <class Td, class Tk> Tk BList<Td, Tk>::getCurrentKey() {

	if (current == NULL)
		return invkey;

	return current->key;
}
template <class Td, class Tk> Td BList<Td, Tk>::getCurrentData() {

	if (current == NULL)
		return invdt;

	return current->data;
}
template <class Td, class Tk> bool BList<Td, Tk>::setCurrentKey(Tk k) {

	if (current == NULL || isInvalid(k))
		return false;

	current->setKey(k);

	return true;

}
template <class Td, class Tk> bool BList<Td, Tk>::setCurrentData(Td dt) {

	if (current == NULL || isInvalid(dt))
		return false;

	current->setData(dt);

	return true;
}
template <class Td, class Tk> BListNode<Td, Tk>  * BList<Td, Tk>::add(Td dt, bool ref) {

	if (isInvalid(dt))
		return NULL;

	BListNode<Td, Tk>  * node = new BListNode<Td, Tk>(dt,ref);

	if (first == NULL) {
		first = node;
		last = node;
	} else {
		last->next = node;
		node->previous = last;
		last = node;
	}

	current = node;

	n++;

    return node;
}
template <class Td, class Tk> BListNode<Td, Tk>  * BList<Td, Tk>::add(Td dt, Tk k, bool ref) {

	if (isInvalid(dt))
		return NULL;

	BListNode<Td, Tk>  * node = new BListNode<Td, Tk>(dt,k,ref);

	if (first == NULL) {
		first = node;
		last = node;
	} else {
		last->next = node;
		node->previous = last;
		last = node;
	}

	current = node;

	n++;

    return node;
}
template <class Td, class Tk> BListNode<Td, Tk>  * BList<Td, Tk>::addFirst(Td dt, bool ref) {

	if (isInvalid(dt))
		return NULL;

	BListNode<Td, Tk>  * node = new BListNode<Td, Tk>(dt,ref);

	if (first == NULL) {
		first = node;
		last = node;
	} else {
		first->previous = node;
		node->next = first;
		first = node;
		}
	current = node;
	n++;

	return node;
}
template <class Td, class Tk> BListNode<Td, Tk>  * BList<Td, Tk>::addFirst(Td dt, Tk k, bool ref) {

	if (isInvalid(dt))
		return NULL;

	BListNode<Td, Tk>  * node = new BListNode<Td, Tk>(dt,k,ref);

	if (first == NULL) {
		first = node;
		last = node;
	} else {
		first->previous = node;
		node->next = first;
		first = node;
		}
	current = node;
	n++;

	return node;
}
template <class Td, class Tk> BListNode<Td, Tk>  * BList<Td, Tk>::addBefore(Td dt, bool ref ) {

	if (current == NULL || isInvalid(dt))
		return NULL;

	BListNode<Td, Tk> * node = new BListNode<Td, Tk>(dt,ref);

	if (current->previous != NULL)
		current->previous->next = node;
	else
		first = node;
	node->previous = current->previous;
	node->next = current;
	current->previous = node;

	current = node;
	n++;
	return node;
}
template <class Td, class Tk> BListNode<Td, Tk>  * BList<Td, Tk>::addBefore(Td dt, Tk k, bool ref ) {

	if (current == NULL || isInvalid(dt))
		return NULL;

	BListNode<Td, Tk> * node = new BListNode<Td, Tk>(dt,k,ref);

	if (current->previous != NULL)
		current->previous->next = node;
	else
		first = node;
	node->previous = current->previous;
	node->next = current;
	current->previous = node;

	current = node;
	n++;
	return node;
}
template <class Td, class Tk> BListNode<Td, Tk>  * BList<Td, Tk>::addAfter(Td dt, bool ref ) {

	if (current == NULL || isInvalid(dt))
		return NULL;

	BListNode<Td, Tk> * node = new BListNode<Td, Tk>(dt,ref);

	if (current->next != NULL)
		current->next->previous = node;
	else
		last = node;
	node->next = current->next;
	node->previous = current;
	current->next = node;
	current = node;
	n++;
	return node;
}
template <class Td, class Tk> BListNode<Td, Tk>  * BList<Td, Tk>::addAfter(Td dt, Tk k, bool ref ) {

	if (current == NULL || isInvalid(dt))
		return NULL;

	BListNode<Td, Tk> * node = new BListNode<Td, Tk>(dt,k,ref);

	if (current->next != NULL)
		current->next->previous = node;
	else
		last = node;
	node->next = current->next;
	node->previous = current;
	current->next = node;
	current = node;
	n++;
	return node;
}
template <class Td, class Tk> BListNode<Td, Tk>  * BList<Td, Tk>::insert(Td dt, Tk k, bool ref, bool asc ) {

	if (isInvalid(dt) || isInvalid(k))
		return NULL;

	current = first;

	bool done = false;

	while (current != NULL && !done) {
		if (!ordered(current->key, k, asc)) {
			addBefore(dt, k, ref);
			done = true;
		}
		current = current->next;
	}
	if (!done)
		return add(dt,k,ref);

	return NULL;
}
template <class Td, class Tk> bool BList<Td, Tk>::checkData(int n, ... ) {

	if (n <= 0)
		return false;

    va_list args;
    va_start(args, n);

	Td dt;
	BListNode<Td,Tk> * node = first;

	while (n > 0 && node != NULL) {
		dt = va_arg(args, Td);
		if (!isEqual(node->data, dt))
			return false;
		node = node->next;
		n--;
	}
	return true;
}
template <class Td, class Tk> bool BList<Td, Tk>::checkKey(int n, ... ) {

	if (n <= 0)
		return false;

    va_list args;
    va_start(args, n);

	Tk k;
	BListNode<Td,Tk> * node = first;

	while (n > 0 && node != NULL) {
		k = va_arg(args, Tk);
		if (!isEqual(node->key, k))
			return false;
		node = node->next;
		n--;
	}
	return true;
}
template <class Td, class Tk> bool BList<Td, Tk>::check(int n, ... ) {

	if (n <= 0)
		return false;

    va_list args;
    va_start(args, n);

	Td dt = invdt;
	Tk k = invkey;
	BListNode<Td,Tk> * node = first;

	while (n > 0 && node != NULL) {
		dt = va_arg(args, Td);
		if (!isEqual(node->data, dt))
			return false;
		n--;
		if (n > 0) {
			k = va_arg(args, Tk);
			if (!isEqual(node->key, k))
				return false;
			node = node->next;
			n--;
		}
	}
	return true;
}
template <class Td, class Tk> bool BList<Td, Tk>::removeFirst() {
	if (first == NULL)
		return false;

	BListNode<Td, Tk>  *node = first;
	if (node->next != NULL)
		node->next->previous = node->previous;
	first = node->next;
	if (node == last)
		last = node->previous;
	current = node->next;
	delete node;
	n--;

	return true;
}
template <class Td, class Tk> bool BList<Td, Tk>::removeLast() {

	if (last == NULL)
		return false;

	BListNode<Td, Tk>  *node = last;
	if (node->previous != NULL)
		node->previous->next = node->next;
	if (node == first)
		first = node->next;
	last = node->previous;
	current = NULL;
	delete node;
	n--;

	return true;
}
template <class Td, class Tk> bool BList<Td, Tk>::removeCurrent() {

	if (current == NULL)
		return false;

	BListNode<Td, Tk>  *node = current;
	if (node->next != NULL)
		node->next->previous = node->previous;
	if (node->previous != NULL)
		node->previous->next = node->next;
	if (node == first)
		first = node->next;
	if (node == last)
		last = node->previous;
	current = node->next;
	delete node;
	n--;

	return true;
}
template <class Td, class Tk> bool BList<Td, Tk>::clean() {

	BListNode<Td, Tk>  *node;

	node = first;

	while (node != NULL) {
		current = node->next;
		delete node;
		node = current;
	}

	first = NULL;
	last = NULL;
	current = NULL;
	n = 0;

	return true;
}
template <class Td, class Tk> BList<Td, Tk> * BList<Td, Tk>::clone() {

	BList<Td, Tk> * nlist = new BList<Td, Tk>;

	if (first == NULL)
		return nlist;

	current = first;

	while (current != NULL) {
		if (current->data != NULL)
			nlist->add(clone(current->data), clone(current->key));
		current = current->getNext();
	}

	return nlist;
}
template <class Td, class Tk> BList<Td, Tk> * BList<Td, Tk>::clone(BList<Td, Tk> * p) {
	if (p == NULL)
		return NULL;

	return p->clone();
}
template <class Td, class Tk> bool BList<Td, Tk>::remove(BList<Td, Tk> *& l) {

	if (l == NULL)
		return false;

	delete l;

	l = NULL;
	return true;
}
template <class Td, class Tk> bool BList<Td, Tk>::create(BList<Td, Tk> *& l, int ind) {
	if (l != NULL)
		return false;

	l = new BList<Td, Tk>(ind);

	return true;
}
template <class Td, class Tk> Td * BList<Td, Tk>::toVector() {

	Td * vec = NULL;

	if (first == NULL)
		return vec;

	vec = new Td [getCount()];

	current = first;
	int i = 0;
	while (current != NULL) {
		vec[i++] = ::clone(current->data);
		current = current->getNext();
	}

	return vec;
}
template <class Td, class Tk> BList<Td, Tk> * BList<Td, Tk>::getReference() {
	BList<Td, Tk> * nlist = new BList<Td, Tk>;

	if (first == NULL)
		return nlist;

	current = first;

	while (current != NULL) {
		nlist->add(current->data,current->key,true);
		current = current->getNext();
	}

	return nlist;
}
template <class Td, class Tk> BList<Td, Tk> * BList<Td, Tk>::getReference(BList<Td, Tk> * l) {

	if (l == NULL)
		return NULL;

	return l->getReference();
}
template <class Td, class Tk> void BList<Td, Tk>::bubbleSort(bool asc) {

	bool t = true;
	BListNode<Td, Tk>	* node1 = NULL,
				    * node2 = NULL,
				    * aux1 = NULL,
				    * aux2 = NULL;

	while (t) {
		t = false;
		node1 = first;
		while (node1 != NULL && node1->next != NULL) {
			node2 = node1->next;
			if (!ordered(node1->getKey(),node2->getKey(),asc)) {
				aux1 = node1->previous;
				aux2 = node2->next;
				node1->previous = node2;
				node2->next = node1;
				node1->next = aux2;
				node2->previous = aux1;
				if (aux1 != NULL)
					aux1->next = node2;
				if (aux2 != NULL)
					aux2->previous = node1;
				if (first == node1)
					first = node2;
				if (last == node2)
					last = node1;
				t = true;
			} else
				node1 = node1->next;
		}
	}
}
template <class Td, class Tk> void BList<Td, Tk>::print(char * name, int t) { print(NULL, name, t);};
template <class Td, class Tk> void BList<Td, Tk>::print(FILE * f, char * name, int t) {

	BListNode<Td, Tk>  *node;

	node = first;

	int p = indbase;

	if (t < 0) t = 0;
	char *strtab = new char [t+1];

	strtab[0] = '\0';
	for (int i=0; i < t; i++) strtab[i] = '\t';
	strtab[t] = '\0';


	FILE * file = f == NULL ? stderr : f;

	fprintf(file,"\n%sList: ",strtab);
	if (name != NULL)
		fprintf(file,"%s", name);
	fprintf(file,"\t{\n\n");

	char * str;

	while (node != NULL) {
		str = node->toString(p++,t+1);
		fprintf(file,"%s\n", str);
		delete [] str;
		node = node->next;
	}
	fprintf(file,"%s}\n", strtab);
	delete [] strtab;
}
template <class Td, class Tk> bool BList<Td, Tk>::isMember(Td dt) {

	BListNode<Td, Tk> * node = NULL;

	node = first;

	if (isInvalid(dt))
		return NULL;

	while (node != NULL && !isEqual(dt,node->data)) {
		node = node->next;
	}

	if (node)
        return true;

    return false;
}

template <class Td> class BStack {
public:
	BStack();
	~BStack();
	int getCount() { return list->getCount();};
	void push(Td);
	Td pop();
	void print(char*);
	void print(FILE * f = NULL, char* str = NULL, int t = 0);

protected:
	BList<Td> *list;
};

template <class Td> BStack<Td>::BStack(){

	list = new BList<Td>;
	BList<double>::create(list);
}
template <class Td> BStack<Td>::~BStack(){

	delete list;
}
template <class Td> void BStack<Td>::push(Td dt){

	list->add(dt);
}
template <class Td> Td BStack<Td>::pop(){

	BListNode<Td> * node = list->getLast();
	if (node == NULL)
		return NULL;

	Td dt = node->getData();

	list->removeCurrent();

	return dt;
}
template <class Td> void BStack<Td>::print(char * name){
	print(NULL,name);
}
template <class Td> void BStack<Td>::print(FILE * f, char * name, int t){

	FILE * file = f == NULL ? stderr : f;

	if (t < 0) t = 0;
	char *strtab = new char [t+1];

	strtab[0] = '\0';
	for (int i=0; i < t; i++) strtab[i] = '\t';
	strtab[t] = '\0';

	fprintf(file,"\n%sStack: ",strtab);
	if (name != NULL)
		fprintf(file,"%s", name);

	fprintf(file,"\t{\n");
	list->print(f, "Stack", t+1);
	fprintf(file,"%s}\n",strtab);

	delete [] strtab;
}


template <class T> class BCircularList {
public:
	BCircularList(int sz=10);
	~BCircularList();
	T getNext();
	T insert(T);
	int getIndex() { return index;};
	int getSize() { return size;};
	int getCurrentSize() { return (full)? size : index;};
	bool isFull() { return full;};
	BCircularList<T> * clone();
	static BCircularList<T> * clone(BCircularList<T> *);
	T * toVector();
	double mean();
	double std(double avg);
	double std();
	double mad();
	double mad(double med);
	double median();
	double stdmad(double med);
	double stdmad();


protected:
	T * list;
	int index;
	int size;
	bool full;
	T invdt;
};

template <class T> BCircularList<T>::BCircularList(int sz): list(NULL), index(0), size(sz), full(false) {
	list = new T[size];
	invdt = invalid(invdt);
}
template <class T> BCircularList<T>::~BCircularList() {
	delete [] list;
}
template <class T> BCircularList<T> * BCircularList<T>::clone(){
	BCircularList<T> * cl = new BCircularList<T>(size);
	cl->index = index;
	cl->full = full;
	int i;
	for (i=0; i < size; i++)
		cl->list[i] = ::clone(list[i]);
	return cl;
}
template <class T> BCircularList<T> * BCircularList<T>::clone(BCircularList<T> * cl){

	if (cl == NULL)
		return NULL;

	return cl->clone();

}
template <class T> T * BCircularList<T>::toVector(){

	T * vec = new T [size];
	int i;
	for (i=0; i < clone->size; i++)
		vec[i] = ::clone(list[i]);
	return vec;
}
template <class T> T BCircularList<T>::getNext() {
	T ret;
	if (full)
		ret = list[index];
	else
		ret = invdt;

	index++;
	if (index >= size) {
		index = 0;
		full = true;
	}
	return ret;
}
template <class T> T BCircularList<T>::insert(T val) {
	T ret;
	if (full)
		ret = list[index];
	else
		ret = invdt;

	list[index] = val;
	index++;
	if (index >= size) {
		index = 0;
		full = true;
	}
	return ret;
}
template <class T> double BCircularList<T>::mean() {

	double sum=0;

	int sz = (full) ? size : index;

	for (int i=0; i<sz; i++)
		sum += list[i];

	if (sz == 0)
		return 0;

	return sum/sz;

}
template <class T> double BCircularList<T>::std(double avg) {
	double
		val = 0,
		sum = 0;

	int sz = (full) ? size : index;

	for (int i=0; i<sz; i++) {
		val = list[i] - avg;
		sum += val * val;
	}

	if (sz == 0)
		return 0;

	return sqrt(sum/(sz-1));
}
template <class T> double BCircularList<T>::std() {

	double avg = mean();

	double
		val = 0,
		sum = 0;;

	int sz = (full) ? size : index;

	for (int i=0; i<sz; i++) {
		val = list[i] - avg;
		sum += val * val;
	}

	if (sz == 0)
		return 0;

	return sqrt(sum/(sz-1));
}

template <class T> double BCircularList<T>::median() {

	int sz = (full) ? size : index;

	if (sz == 0)
		return 0;

	T * l1 = copyVector(list, sz);

	quicksort(l1, 0, sz-1);

	double m1 = (sz % 2 != 0) ? l1[sz/2] : (l1[sz/2] + l1[sz/2-1]) / 2;

	delete [] l1;

	return m1;

}
template <class T> double BCircularList<T>::mad() {

	int sz = (full) ? size : index;

	if (sz == 0)
		return 0;

	T * l1 = copyVector(list, sz);

	quicksort(l1, 0, sz-1);

	double m1 = (sz % 2 != 0) ? l1[sz/2] : (l1[sz/2] + l1[sz/2-1]) / 2;

	T * l2 = new T[sz];

	int i;

	for(i=0; i < sz; i++)
		l2[i] = fabs(l1[i] - m1);


	quicksort(l2, 0, sz-1);

	double m2 = (sz % 2 != 0) ? l2[sz/2] : (l2[sz/2] + l2[sz/2-1]) / 2;

	delete [] l1;
	delete [] l2;

	return m2;

}
template <class T> double BCircularList<T>::mad(double med) {

	int sz = (full) ? size : index;

	T * l2 = new T[sz];

	int i;

	for(i=0; i < sz; i++)
		l2[i] = fabs(list[i] - med);


	quicksort(l2, 0, sz-1);

	double m2 = (sz % 2 != 0) ? l2[sz/2] : (l2[sz/2] + l2[sz/2-1]) / 2;

	delete [] l2;

	return m2;

}
template <class T> double BCircularList<T>::stdmad(double med) {
	return 1.48 * mad(med);
}
template <class T> double BCircularList<T>::stdmad() {

	return 1.48 * mad();
}

#endif




