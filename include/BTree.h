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

#ifndef _BTREE_H_
#define _BTREE_H_

#include <stdio.h>
#include "BFunctions.h"
#include "BList.h"



//******************** BTreeNode ***************
template <class T>
class BTreeNode {
public:
	BTreeNode();
	BTreeNode(T);
	~BTreeNode();
	T getData();
	bool hasChildren();
	BTreeNode<T> * addChild(T);
	BTreeNode<T> * addChildOrdered(T, bool asc = true, bool samekey = false);
	bool sortChildren(bool asc = true);
	bool removeChildren();
	bool removeFirstChild();
	BTreeNode<T> * getParent();
	BTreeNode<T> * getNextChild();
	BTreeNode<T> * getFirstChild();
	BTreeNode<T> * getLastChild();
	BTreeNode<T> * getNextDepthFirst();
	void resetState();
	static BTreeNode<T> * getNextBreadthFirst(BList<BTreeNode<T> *>*);
	static void remove(BTreeNode<T>  * node) { node->removeChildren(); delete node; node = NULL;};
	BTreeNode<T> * clone();
	static BTreeNode<T> * clone(BTreeNode<T> *);
	int getChildCount();
	char * toString(int p = 0, int t = 0);
	void printSubTree(FILE * f = NULL, char* str = NULL, int tab = 0);
	bool isRoot();
	bool isLeaf();
	int getHeight();

protected:
	void printChildren(FILE *, int&, int);
	BTreeNode<T> * addChildNode(BTreeNode<T> *);

	T data;
	int state;
	BTreeNode<T> * parent;
	// children
	BTreeNode<T> * firstchild;
	BTreeNode<T> * lastchild;
	BTreeNode<T> * currentchild;
	int nc;
	// Siblings
	BTreeNode<T> * nextsibling;
	BTreeNode<T> * previoussibling;

};


template <class T> BTreeNode<T>::BTreeNode() {
	data = invalid(data);
	parent = firstchild = lastchild = currentchild = previoussibling = nextsibling = NULL;
	nc = 0;
	state = INVALIDVALUE;
}
template <class T> BTreeNode<T>::BTreeNode(T dt) {
	data = ::clone(dt);
	parent = firstchild = lastchild = currentchild = previoussibling = nextsibling = NULL;
	nc = 0;
	state = INVALIDVALUE;
}
template <class T> BTreeNode<T>::~BTreeNode() {
	BTreeNode<T> * node = NULL;
	currentchild = firstchild;
	while (currentchild != NULL) {
		node = currentchild->nextsibling;
		delete currentchild;
		currentchild = node;
	}
	::remove(data);

}
template <class T> int BTreeNode<T>::getHeight() {
	int mh = 0,
		h;
	currentchild = firstchild;
	while (currentchild != NULL) {
		h = currentchild->getHeight();
		if (mh < h + 1)
			mh = h + 1;
		currentchild = currentchild->nextsibling;
	}
	return mh;
}
template <class T> void BTreeNode<T>::resetState() {
	currentchild = firstchild;
	while (currentchild != NULL) {
		currentchild->resetState();
		currentchild = currentchild->nextsibling;
	}
	state = INVALIDVALUE;
}
template <class T> bool BTreeNode<T>::hasChildren() {

	if (firstchild == NULL)
		return false;

	return true;
}
template <class T> bool BTreeNode<T>::removeFirstChild() {

	if (firstchild == NULL)
		return false;

	BTreeNode<T> * node = NULL;

	node = firstchild->nextsibling;
	if (lastchild == firstchild)
		lastchild = NULL;
	if (currentchild == firstchild)
		currentchild = node;
	delete firstchild;
	firstchild = node;
	if (firstchild != NULL)
		firstchild->previoussibling = NULL;
	nc--;

	return true;
}
template <class T> BTreeNode<T> * BTreeNode<T>::clone() {
	BTreeNode<T> * node1 = new BTreeNode<T>(data);

	BTreeNode<T> * node2 = NULL;
	BTreeNode<T> * node3 = getFirstChild();
	while (node3 != NULL) {
		node2 = clone(node3);
		node1->addChildNode(node2);
		node3 = getNextChild();
	}
	return node1;
}
template <class T> BTreeNode<T> * BTreeNode<T>::clone(BTreeNode<T> * node) {

	if(node == NULL)
		return NULL;
	return node->clone();

}
template <class T> bool BTreeNode<T>::removeChildren() {

	if (firstchild == NULL)
		return false;

	BTreeNode<T> * node = NULL;
	currentchild = firstchild;
	while (currentchild != NULL) {
		node = currentchild->nextsibling;
		currentchild->removeChildren();
		currentchild = node;
	}
	nc = 0;
	firstchild = currentchild = lastchild = NULL;

	return true;
}
template <class T> BTreeNode<T> * BTreeNode<T>::addChild(T dt) {

	if (isInvalid(dt))
		return NULL;

	BTreeNode<T>  * node = new BTreeNode<T>(dt);

	node->parent = this;
	if (firstchild == NULL) {
		firstchild = node;
		lastchild = node;
	} else {
		lastchild->nextsibling = node;
		node->previoussibling = lastchild;
		lastchild = node;
	}

	nc++;

	return node;
}
template <class T> BTreeNode<T> * BTreeNode<T>::addChildNode(BTreeNode<T> * node) {

	if (node == NULL)
		return NULL;

	node->parent = this;
	if (firstchild == NULL) {
		firstchild = node;
		lastchild = node;
	} else {
		lastchild->nextsibling = node;
		node->previoussibling = lastchild;
		lastchild = node;
	}

	nc++;

	return node;
}
template <class T> BTreeNode<T> * BTreeNode<T>::addChildOrdered(T dt, bool asc, bool samekey) {
	if (isInvalid(dt))
		return NULL;


	BTreeNode<T>  * cur = NULL,
		*node = NULL;
	bool found = false; 

	cur = firstchild;
	while (cur != NULL && !found) {
		if (!samekey && isEqual(dt,cur->data))
			return false;
		else if (ordered(dt, cur->data, asc)) {
			found = true;
			node = new BTreeNode<T>(dt);
			node->parent = this;
			node->nextsibling = cur;
			node->previoussibling = cur->previoussibling;
			if (cur->previoussibling != NULL)
				cur->previoussibling->nextsibling = node;
			cur->previoussibling = node;
			if (firstchild == cur)
				firstchild = node;
			nc++;
		}
		cur = cur->nextsibling;
	}
	if (!found) 
		node = this->addChild(dt);

	return node;
}
template <class T> bool BTreeNode<T>::sortChildren(bool asc) {
	if (firstchild == NULL)
		return false;

	bool t = true;
	BTreeNode<T>  * node = NULL,
		* nextnode = NULL;

	while (t) {
		t = false;
		node = firstchild;
		while (node != NULL && node->nextsibling != NULL) {
			nextnode = node->nextsibling;
			if (!ordered(node->data,nextnode->data,asc)) {
					node->nextsibling = nextnode->nextsibling;
					nextnode->previoussibling = node->previoussibling;
					node->previoussibling = nextnode;
					nextnode->nextsibling = node;
					if (node == firstchild)
						firstchild = nextnode;
					else 
						nextnode->previoussibling->nextsibling = nextnode;
					if (nextnode == lastchild)
						lastchild = node;
					else 
						node->nextsibling->previoussibling = node;
					t = true;
			} else
				node = node->nextsibling;
		}
	}

	return true;
}
template <class T> T BTreeNode<T>::getData() {
	return data;
}
template <class T> bool BTreeNode<T>::isRoot() {
	if (parent == NULL)
		return true;
	return false;
}
template <class T> bool BTreeNode<T>::isLeaf() {
	if (firstchild == NULL)
		return true;
	return false;
}
template <class T> BTreeNode<T> * BTreeNode<T>::getParent() {
	return parent;
}
template <class T> int BTreeNode<T>::getChildCount() {
	return nc;
}
template <class T> BTreeNode<T> * BTreeNode<T>::getFirstChild() {
	currentchild = firstchild;
	return firstchild;
}
template <class T> BTreeNode<T> * BTreeNode<T>::getLastChild() {
	currentchild = lastchild;
	return lastchild;
}
template <class T> BTreeNode<T> * BTreeNode<T>::getNextChild() {
	if (currentchild == NULL) 
		return NULL;

	currentchild = currentchild->nextsibling;
	return currentchild;
 }
template <class T> char * BTreeNode<T>::toString(int p, int t) {

	if (t < 0) t = 0;
	char *strtab = new char [t+1];

	strtab[0] = '\0';
	for (int i=0; i < t; i++) 
		strtab[i] = '\t';
	strtab[t] = '\0';

	char * strdata = ::toString(data);

	int l = 1;
	l+= p > INVALIDINDEX ? 15+t : 0;

	char * strnum = NULL;
	
	if (p > INVALIDINDEX) {
		strnum = new char [l];
		sprintf(strnum, "%sNode:    %3d\n", strtab, p);
	}

	l+= 18+t;
	l+= strdata == NULL ? 15+t : 10+t+strlen(strdata);
	l+= 18+t;
	l+= 11+t;

	char * str = new char [l]; 
		
	if (strnum == NULL)
		sprintf(str, "%sPointer: %p\n%sData:    %s\n%sParent:  %p\n%sChildren:", 
			strtab, this, strtab, strdata, strtab, parent, strtab);
	else
		sprintf(str, "%s%sPointer: %p\n%sData:    %s\n%sParent:  %p\n%sChildren:", 
			strnum, strtab, this,  strtab, strdata, strtab, parent, strtab);

	delete [] strnum;
	delete [] strdata;
	delete [] strtab;

	return str;
}
template <class T> void BTreeNode<T>::printSubTree(FILE * f, char * name, int t) {

	FILE * file = f == NULL ? stderr : f;

	fprintf(file,"\nSubTree: "); 
	if (name != NULL)
		fprintf(file,"%s", name);
	fprintf(file,"\n\n");
	int p = 0;
	printChildren(file,p, t);
	fprintf(file,"\n");
}
template <class T> void BTreeNode<T>::printChildren(FILE * file, int &p, int t) {

	if (t < 0) t = 0;
	char *strtab = new char [t+1];

	strtab[0] = '\0';
	for (int i=0; i < t; i++) strtab[i] = '\t';
	strtab[t] = '\0';
	
	fprintf(file,"%s",toString(p,t));
	
	BTreeNode * node;
	node = firstchild;
	if (nc > 0)
		fprintf(file,"\t{\n\n");
	while (node != NULL) {
		p++;
		node->printChildren(file,p,t+1);
		node = node->nextsibling;
	}
	if (nc > 0)
		fprintf(file,"%s}\n\n", strtab);
	else
		fprintf(file,"\n\n");
	delete [] strtab;

}
template <class T> BTreeNode<T> * BTreeNode<T>::getNextDepthFirst() {

	if (state == 0) {
		if (currentchild->nextsibling == NULL) {
			currentchild = NULL;
			state = 1;
			return this;
		} else {
			currentchild = currentchild->nextsibling;
			return currentchild->getNextDepthFirst();
		}
	} else if (state == 1) {
		state = INVALIDVALUE;
		if (parent == NULL)
			return NULL;
		return parent->getNextDepthFirst();
	} else if (firstchild == NULL) {
		state = 1;
		return this;
	} else {
		state = 0;
		currentchild = firstchild;
		return currentchild->getNextDepthFirst();
	}
}
template <class T> BTreeNode<T> * BTreeNode<T>::getNextBreadthFirst(BList< BTreeNode<T>* > * list) {

	BListNode<BTreeNode<T>*> * node1 = list->getFirst();
	if (node1 == NULL)
		return NULL;
	BTreeNode<T> * node2 = node1->getData();
	list->removeFirst();
	BTreeNode<T> * node3 = node2->firstchild;

	while (node3 != NULL) {
		list->add(node3,true);
		node3 = node3->nextsibling;
	}

	return node2;
}



#endif // _BTREE_H_
