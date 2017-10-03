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

#if !defined(_STATEERROR_)
#define _STATEERROR_

/// \file BState.h
///
/// File where the BState class are declared 
///

#include <string.h>
#include <limits.h>
#include <stdio.h>

#define BSTATENUMBEROFDEFAULTSTATES	       6
#define BSTATENUMBEROFDIGITSFORERRORS     10  	    
#define BSTATEDEFAULTOBJECT				   0
#define BSTATEOK					       0
#define BSTATEUNKOWNERROR     		       1
#define BSTATEUNEXPECTEDERROR              2
#define BSTATEERRORINVALIDINPUT            3
#define BSTATEERRORMAXOBJECTS              4
#define BSTATEERRORMAXSTATES               5
#define BSTATEDEFAULTOBJECTDESCRIPTION     "Default object"
#define BSTATEOKDESCRIPTION                "State ok"
#define BSTATEUNKOWNERRORDESCRIPTION       "Unknown error"
#define BSTATEUNEXPECTEDERRORDESCRIPTION   "Unexpected error"
#define BSTATEERRORINVALIDINPUTDESCRIPTION "Invalid input"
#define BSTATEERRORMAXOBJECTSDESCRIPTION   "Maximum number of objects achieved"
#define BSTATEERRORMAXSTATESDESCRIPTION    "Maximum number of states achieved"


///***********************************************************************
///
///	 Class BState : Class used to hold a state for an object or procedure
///
///***********************************************************************
class BState {
public:
	/// Constructor
	BState();
	/// Destructor
	~BState();
	/// Defines a new object and returns its id
	int defineObject(char * text = NULL		///< [in] (optional) Name or descriptiob of the object
		);
	/// Defines a new state and returns its number
	int defineState(char * text = NULL		///< [in] (optional) Name or description of the state
		);
	/// Sets the current state of the object
	bool setState(int objid,				///< [in] Object id
		          int stateno				///< [in] Number of the state
		);
	/// Sets the current state of the current object
	bool setState(int stateno				///< [in] Number of the state
		);
	/// Returns the state for the current Object
	int  getState() { return objcurstate[curobj];};
	/// Returns the state for the Object
	int  getState(int objid					///< [in] Object id
		);
	/// Returns the id of the current object
	int  getObject() { return curobj;};
	/// Returns the name or description of the state
	char *  getStateDescription(int stateno	///< [in] State number
		);
	/// Returns the name or description of the object
	char *  getObjectDescription(int objid	///< [in] Object id
		);
	/// Functio that prints the list of states and object definitions on the standard output.
	void printDefinitions(char* str,	///< [in] Title/name of the list
		int tab = 0			///< [in] (optional) Number of tabs at the beginning of the list. Default is 0
		);
	/// Functio that prints the list of states and object definitions on the provided file.
	void printDefinitions(FILE * f = NULL,		///< [in] File descriptor
		char* str = NULL,	///< [in] (optional) Title/name of the list. Default is NULL.
		int tab = 0			///< [in] (optional) Number of tabs at the beginning of the list. Default is 0
		);
	/// Functio that prints the list of current states of objects on the standard output.
	void printObjectStates(char* str,	///< [in] Title/name of the list
		int tab = 0			///< [in] (optional) Number of tabs at the beginning of the list. Default is 0
		);
	/// Functio that prints the list of current states of objects on the provided file.
	void printObjectStates(FILE * f = NULL,		///< [in] File descriptor
		char* str = NULL,	///< [in] (optional) Title/name of the list. Default is NULL.
		int tab = 0			///< [in] (optional) Number of tabs at the beginning of the list. Default is 0
		);


private:
	unsigned int maxstates;			///< Maximum number of states
	unsigned int maxobjs;			///< Maximum number of objects
	unsigned int statedefno;		///< Number of states currently defined
	unsigned int objdefno;			///< Number of objects currently defined
	unsigned int curobj;			///< Current Object
	unsigned int * objcurstate;		///< Vector of object states
	char ** objdesc;				///< Vector of objects descriptions
	char ** statedesc;				///< Vector of states descriptions
};




#endif