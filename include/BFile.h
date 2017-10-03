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

#if !defined(_BFILE_H_)
#define _BFILE_H_

#ifdef _WIN32
#include <direct.h>
#endif // _WIN32
#ifdef __GNUC__
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif // __GNUC__

#include <string.h>
#include <stdio.h>
#include "BFunctions.h"
#include "BState.h"

/// \file BFile.h
///
/// File where the BFile class and other auxiliary funcytions are declared
///

#if defined (WIN32)
/// Flag that defines the separator for directory names
	#define USEBACKSLASH true
#else
	#define USEBACKSLASH false
#endif


///  Function that returns a new token from a string. The string is updated to point to the next token
char * getNextToken(char *& iostring,			///< [in] String to extract a token
					char delimiter = '\\'		///< [in] (optional) Directory separator character
					);
///  Function that returns the full path from a string (removes the file name if it exists).
char * getFullPath(char * filename,				///< [in] File name string
				   bool keepslash = false,		///< [in] (optional) Flag that defines when to keep the directory separator or to remove it
				   bool backslash = USEBACKSLASH ///< [in] (optional) Directory separator
				   );
///  Function that skips the path and returns a pointer to the file name
char * skipPath(char * filename,	///< [in] File name
				bool backslash = USEBACKSLASH	///< [in] (optional) Directory separator
				);
///  Function that returns true if the file name has an absolute path or false otherwise
bool hasAbsolutePath(char * filename, ///< [in] File name
					 bool backslash = USEBACKSLASH	///< [in] (optional) Directory separator
					 );
///  Function that returns true if the path exists or false otherwise
bool existPath(char * pathname, ///< [in] File name
			   bool backslash = USEBACKSLASH	///< [in] (optional) Directory separator
			   );
///  Function that creates a path if it does not exist
void createPath(char * pathname, ///< [in] Path name
				bool backslash = USEBACKSLASH	///< [in] (optional) Directory separator
				);
///  Function that returns the concatenatation of the path and the file name
char * putPath(char * path,		///< [in] Path name
			   char * file,		///< [in] File name
			   bool backslash = USEBACKSLASH	///< [in] (optional) Directory separator
			   );
///  Function that returns the concatenatation of the path and the file name and the file extension
char * putPath(char * path,		///< [in] Path name
			   char * file,		///< [in] File name
			   char * ext,		///< [in] File extension
			   bool backslash = USEBACKSLASH	///< [in] (optional) Directory separator
			   );
///  Function that returns a new string with the file name but without the extension
char * removeFileExtension(char * filename	///< [in] File name
						   );
///  Function that returns a pointer to the file extension
char * getFileExtension(char * filename	///< [in] File name
						   );
///  Function that returns the working directory
char * getWorkingDirectory();
///  Function that creates a directory
bool createDirectory(char * dir	///< [in] Directory name
					 );


///***********************************************************************
///
///	 Class BFile : Class used to keep information about a file
///
///***********************************************************************
class BFile {
public:
	/// Default Constructor
	BFile();
	/// Constructor
	BFile(char * filename	///< [in] File name with path (absolute or relative)
		);
	/// Destructor
	~BFile();
	/// Function that opens a file even if the directory does not exists
	bool forceOpen(char * mode	///< [in] File mode (r/w)
		);
	/// Function that opens a file if the directory exists
	bool open(char * mode		///< [in] File mode (r/w)
		);
	/// Function that opens a file if the directory exists
	bool open(char * filename,	///< [in] File name (that will overwrite the current file name)
		char * mode				///< [in] File mode (r/w)
		);
	/// Function that replaces the current file name
	bool setFileName(char *	filename	///< [in] File name
		);
	/// Function that closes the file
	bool close();
	/// Function that returns the file descriptor
	FILE * getDescriptor() {return filedescriptor;};
	/// Function that returns the path of the file
	char * getPath() {return pathname;};
	/// Function that returns the name of the file
	char * getName() {return filename;};
	/// Function that returns the extension of the file
	char * getExtension() {return fileextension;};
	/// Function that returns the full name of the file (path\file.ext)
	char * getFullName() {return fullname;};

private:
	char * pathname;		///< Path name (absolute or relative path)
	char * filename;		///< Just the file name
	char * fileextension;	///< File extension
	char * fullname;		///< The full name
	FILE * filedescriptor;	///< File descriptor
};



#endif
