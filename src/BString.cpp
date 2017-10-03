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

#include "BString.h"

/// \file BString.cpp
///
/// File where the BString Class is defined
///

BString::BString() : buffer(NULL), length(0), size(0), plr(DEFAULTSTRINGLEGROOMPERCENTAGE), mlr(DEFAULTMAXSTRINGLEGROOM) {
}
BString::BString(const char * bf, double pc, int m) : buffer(NULL), length(0), size(0), plr(pc), mlr(m) {
	if (bf == NULL)
		return;

	length = strlen(bf);
	int lr = length * plr;
	if (lr > mlr)
		lr = mlr;
	size = length + lr + 1;
	buffer = new char [size];
	strcpy(buffer, bf);

}
BString::~BString() {
	if (buffer != NULL)
		delete [] buffer;
}

void BString::operator=(BString &str) {
	operator=(str.getBuffer());
}
void BString::operator=(const char * bf) {
	if (bf == NULL) {
		length = 0;
		if (buffer != NULL)
			delete [] buffer;
		buffer = NULL;
		return;
	}

	int len = strlen(bf);

	if (len >= size) {
		if (buffer != NULL)
			delete [] buffer;
		length = len;
		int lr = len * plr;
		if (lr > mlr)
			lr = mlr;
		size = length + lr + 1;
		buffer = new char [size];
		strcpy(buffer, bf);
		return;
	}

	strcpy(buffer, bf);
}
char * BString::operator+=(BString &str) {
	return operator+=(str.getBuffer());
}
char * BString::operator+=(const char * bf) {
	if (bf == NULL || strlen(bf) == 0)
		return NULL;

	int len = length + strlen(bf);

	if (len <  size) {
		strcat(buffer, bf);
		return buffer;
	}

	int lr = len * plr;
	if (lr > mlr)
		lr = mlr;
	length = len;
	size = len + lr + 1;
	char * aux = new char [size];
	if (buffer != NULL) {
		strcpy(aux, buffer);
		delete [] buffer;
	}
	strcat(aux,bf);
	buffer = aux;

	return buffer;

}
char * BString::operator|(BString &str) {
	return operator|(str.getBuffer());
}
char * BString::operator|(const char * bf) {
	if (bf == NULL || strlen(bf) == 0)
		return buffer;

	int len = length + strlen(bf);

	char str[MAXTEXTLENGTH];

	if (length >= MAXTEXTLENGTH) {
		strncpy(str, buffer,MAXTEXTLENGTH-1);
		str[MAXTEXTLENGTH] = '\0';
	} else {
		strcpy(str, buffer);
		if (len >= MAXTEXTLENGTH) {
			int nc = MAXTEXTLENGTH - length;
			if (nc > 1) {
				strncat(str,bf, nc-1);
				str[MAXTEXTLENGTH+nc] = '\0';
			} 
		} else 
			strcat(str,bf);
	}
	return str;

}
void BString::reserveSpace(int len, double p, int m) {
	if (p != 0)
		plr = p;
	if (m != 0)
		mlr = m;
	if (len >= size) {
		int lr = len * plr;
		if (lr > mlr)
			lr = mlr;
		size = len + lr + 1;
		char * aux = new char [size];
		if (buffer != NULL) {
			strcpy(aux, buffer);
			delete [] buffer;
		}
		buffer = aux;
		return;
	}
}

char * BString::sprintf(char * formatstring, ...) {
	
	va_list args;
    va_start(args, formatstring);

	char str[MAXTEXTLENGTH];

	vsprintf(str, formatstring, args);

	operator=(str);

	va_end (args);

	return buffer;
}



bool BString::operator!=(const char * bf) {
	return !operator==(bf);
}
bool BString::operator!=(BString &str) {
	return !operator==(str.getBuffer());
}

bool BString::operator==(BString &str) {
	return operator==(str.getBuffer());
}
bool BString::operator==(const char * bf) {
	if (bf == NULL)
		if (buffer == NULL)
			return true;
		else
			return false;

	if (buffer == NULL)
		return false;

	if (strcmp(buffer, bf) == 0)
		return true;

	return false;
}

void BString::clipEnd(int pad) {
	if (pad <= 0)
		return;

	length = max(0, length - pad);
	buffer[length] = '\0';

}


