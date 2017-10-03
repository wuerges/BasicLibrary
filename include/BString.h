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

#if !defined(_BSTRING_H_)
#define _BSTRING_H_

/// \file BString.h
///
/// File where the BString Class is declared
///

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "BFunctions.h"

#if !defined (MAXTEXTLENGTH)
/// Maximum number of caracters on a string used in some functions where static vectors are required
#define MAXTEXTLENGTH 6144
#endif

/// Default Maximum number of caracters left empty for future use
#define DEFAULTMAXSTRINGLEGROOM 100
/// Default Percentage of caracters left empty for future use
#define DEFAULTSTRINGLEGROOMPERCENTAGE 0.5

///***********************************************************************
///
///	 Class BString : Class used to hold a string of undefined size
///                  The buffer grows as required
///
///***********************************************************************
class BString {
public:
	/// Default Constructor
	BString();					
	/// Constructor
	BString(const char * buf,	///< [in] Initialization buffer 
		double perc = DEFAULTSTRINGLEGROOMPERCENTAGE, ///< [in] (optional) Percentage of caracters left empty for future use
		int max = DEFAULTMAXSTRINGLEGROOM	///< [in] (optional) Maximum number of caracters left empty for future use
		);					
	/// Destructor
	~BString();					
	/// Returns the current buffer (content) of the object
	char * getBuffer() {return buffer;};			
	/// Returns the current length of the object's buffer (content)
	int getLength() { return length;};			
	/// Returns the maximum length of the object's buffer (content)
	int getSize() { return size;};
	/// Operator that assigns a copy of a vector of characters to the object's buffer
	void operator=(const char * buf ///< [in] Pointer to the vector of characters
		);	
	/// Operator that assigns a copy of the buffer of the input object to the current object
	void operator=(BString &		///< [in] BString Object
		);	
	/// Tests if the object's buffer is empty
	bool empty() { return (length == 0);};
	/// Tests if the object's  buffer is equal a vector of characters
	bool operator== (const char * str	///< [in] BVector of characters
		);
	/// Tests if the object's  buffer is equal to the buffer of the input object
	bool operator== (BString &			///< [in] BString object
		);
	/// Tests if the object's  buffer is different from a vector of characters
	bool operator != (const char * str);
	/// Tests if the object's  buffer is different from the buffer of the input object
	bool operator != (BString &			///< [in] BString object
		);
	/// Clips (removes) the final n characters
	void clipEnd(int n = 1				///< [in] Number of characters to remove
		);
	/// Reserves space (characters) in the buffer for future use
	void reserveSpace(int sz,	///< [in] Initial number of characters of the buffer
		double perc = DEFAULTSTRINGLEGROOMPERCENTAGE, ///< [in] (optional) Percentage of caracters left empty for future use
		int max = DEFAULTMAXSTRINGLEGROOM	///< [in] (optional) Maximum number of caracters left empty for future use
		);
	/// Assigns a formatted string to the object's buffer
	char * sprintf(char * format,	///< [in] Format of the string
		...);
	/// Concats a vector of characters to the object's buffer
	char * operator+=(const char *	///< [in] BVector of characters
		);
	/// Concats the buffer of an input object to the object's buffer
	char * operator+=(BString &		///< BString object
		);
	/// Returns a vector of characters that is the concatenation of the object's buffer with a vector of characters
	char * operator|(const char *	///< [in] BVector of characters
		);
	/// Returns a vector of characters that is the concatenation of the object's buffer with the buffer of another object
	char * operator|(BString &		///< BString object
		);

private:
	char * buffer;	///< Object's buffer
	int length;		///< Current buffer length
	int size;		///< Maximum buffer length
	double plr;		///< Percentage of characters left empty for future use
	int mlr;		///< Maximum number of characters left empty for future use
};


#endif // !defined(_BSTRING_H_)
			