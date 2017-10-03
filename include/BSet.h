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

#if !defined(_BSET_H_)
#define _BSET_H_

/// \file BSet.h
///
/// File where the BSet Class is declared
///

#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "BString.h"

///***********************************************************************
///
///	 Class BSet : Class used to hold a set 
///
///***********************************************************************
class BSet {
 public:
	/// Constructor
	BSet(char * = NULL);
	/// Destructor
	~BSet();
	/// Operator that compares this set object with another one
	bool operator==(BSet & set	///< [in] Source BSet Object
		);
	/// Operator that compares this set object with a string
	bool operator==(char * set	///< [in] Source string (set)
		);
	/// Operator that compares this set object with a string
	bool operator==(BString & set ///< [in] Source String (set)
		);
	/// Operator that assigns a copy of the set to the object
	void operator=(BSet & set	///< [in] Source BSet Object
		);
	/// Operator that assigns a copy of the set to the object
	void operator=(char * set	///< [in] Source string (set)
		);
	/// Operator that assigns a copy of the set to the object
	void operator=(BString & set ///< [in] Source String (set)
		);
	/// Operator that increments the object with new elements
	void operator+=(BSet &		///< [in] Source of elements
		);
	/// Operator that increments the object with new elements
	void operator+=(char *		///< [in] Source of elements
		);
	/// Operator that decrements the object with new elements
	void operator+=(BString &		///< [in] Source of elements
		);
	/// Operator that increments the object with one new element
	void operator+=(char		///< [in] Element
		);
	/// Operator that decrements the object of some elements
	void operator-=(BSet &		///< [in] Source of elements
		);
	/// Operator that decrements the object of some elements
	void operator-=(char *		///< [in] Source of elements
		);
	/// Operator that decrements the object of some elements
	void operator-=(BString &		///< [in] Source of elements
		);
	/// Operator that decrements the object with of some element
	void operator-=(char		///< [in] Element
		);
	/// Returns the number of elements of the set
	int getCount() { return sz;};
	/// Returns the elements of the set on a string
	char * getSet() { return set;};
	/// Returns true if the element belongs to the set
	bool in (char		///< [in] Element
		);
	/// Functions that convert the set content in a string to be printed.
	char * toString(int t = 0	///< [in] (optional) Number of tabs to use
		);

 private:
    /// Function that returns a string with all characters of the input but without duplicates
	char * removeDoubles(char * str		///< [in] Input String
		);
	char * removeSubset(char * str1,	///< [in] String with set
					    char * str2		///< [in] String with elements to remove
		);

	char * set;
	int sz;

#if defined(_STATEERROR_)
	BState stat;
#endif
};


#endif
