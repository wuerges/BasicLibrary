#pragma warning( once : 4996 )
#pragma warning( once : 4244 )

/// \file BSet.cpp
///
/// File where the BSet Class is defined
///

#include "BSet.h"

BSet :: BSet(char *str): sz(0), set(NULL)
#if defined(_STATEERROR_)
  , stat(STATEOK)
#endif
{

	if (str == NULL) {
#if defined(_STATEERROR_)
		stat = STATENULL;
#endif
		return;
	}
	set = removeDoubles(str); 
	sz = strlen(set);
}
BSet :: ~BSet() {
  if (set != NULL)
      delete [] set;
}
char * BSet :: toString(int t) {

	if (t < 0) t = 0;
	int l = 1 + t + 5 * sz + 2;
	char * str = new char [l]; 
	for (int i=0; i < t; i++) 
		str[i] = '\t';
	str[t] = '{';
	int x = t+1;
	for (int i = 0; i < sz; i++) {
		if (i != 0) {
			str[x++] = ',';
			str[x++] = ' ';
		}
		str[x++] = '\'';
		if (isprint(set[i]))
			str[x++] = set[i];
		else switch (set[i]) {
				case '\n': str[x++] = '\\';
					  str[x++] = 'n';
					  break;
				case '\t': str[x++] = '\\';
					  str[x++] = 't';
					  break;
				case '\f': str[x++] = '\\';
					  str[x++] = 'f';
					  break;
				case '\v': str[x++] = '\\';
					  str[x++] = 'v';
					  break;
				case '\r': str[x++] = '\\';
					  str[x++] = 'r';
					  break;
				default: str[x++] = 'n'; // Not printable
						 str[x++] = 'p'; 
			}
		str[x++] = '\'';
	}
	str[x++] = '}';
	str[x] = '\0';

	return str;
}

bool BSet :: operator==(BSet & set1) {
	return operator==(set1.getSet());
}
bool BSet :: operator==(BString & set1) {
	return operator==(set1.getBuffer());
}
bool  BSet :: operator==(char * str) {
#if defined(_STATEERROR_)
	stat = STATEOK;
#endif

	if (set == NULL)
		if (str == NULL)
			return true;
		else
			return false;
	else
		if (str == NULL)
			return false;
		else {
			int n = strlen(str);
			for (int i = 0; i < n; i++)
				if (!in(str[i]))
					return false;
			for (int i = 0; i < sz; i++)
				if (strchr(str,set[i]) == NULL)
					return false;
			return true;
		}
}
void BSet :: operator=(BSet & set1) {
	operator=(set1.getSet());
}
void BSet :: operator=(BString & set1) {
	operator=(set1.getBuffer());
}
void  BSet :: operator=(char * str) {
#if defined(_STATEERROR_)
	stat = STATEOK;
#endif

	if (set != NULL)
       delete [] set;
#if defined(_STATEERROR_)
  else
       stat += STATENULL;
#endif

	set = NULL;
	sz = 0;
	if (str == NULL)
       return;
	set = removeDoubles(str);
	sz = strlen(set);
}

void BSet :: operator+=(BSet & set1) {
	operator+=(set1.getSet());
}
void BSet :: operator+=(BString & set1) {
	operator+=(set1.getBuffer());
}
void BSet :: operator+=(char * str) {
#if defined(_STATEERROR_)
	stat = STATEOK;
#endif

	if (str == NULL)
       return;

	int s = strlen(str);
	char * str1 = new char [sz+s+1];
	char * str2 = NULL;
	if (set != NULL) {
		strcpy(str1,set);
		str2 = set;
	} else
		str1[0] = '\0';
	strcat(str1,str);
	set = removeDoubles(str1);
	sz = strlen(set);
	delete [] str1;
	if (str2 != NULL)
		delete [] str2;
}

void BSet :: operator+=(char c) {
#if defined(_STATEERROR_)
	stat = STATEOK;
#endif

	if (in(c))
		return;

	char * str1 = new char [sz+2];
	char * str2 = set;
	if (set != NULL) {
		strcpy(str1,set);
	} else
		str1[0] = '\0';
	str1[sz++] = c;
	str1[sz] = '\0'; 
	set = str1;
	if (str2 != NULL)
		delete [] str2;
}
void BSet :: operator-=(BSet & set1) {
	operator-=(set1.getSet());
}
void BSet :: operator-=(BString & set1) {
	operator-=(set1.getBuffer());
}
void BSet :: operator-=(char * str) {

#if defined(_STATEERROR_)
	stat = STATEOK;
#endif

	if (str == NULL)
       return;

	char * set1 = set;
	set = removeSubset(set1, str);
	sz = strlen(set);
	delete [] set1;
}
void BSet :: operator-=(char c) {
#if defined(_STATEERROR_)
	stat = STATEOK;
#endif

	if (!in(c))
		return;

	int i = 0;
	while (set[i] != c) i++;
	int n = i+1;
	while (n < sz) set[i++] = set[n++];
	sz--;
}
bool BSet :: in(char c) {
 int x;

 for(x = 0; x < sz; x++)
    if (c == set[x])
       return true;

return false;
}
char * BSet::removeDoubles(char *str) {
	int n = strlen(str);
	char * nstr = new char[n+1];

	int x, y, z = 0;
	bool found;
	nstr[0] = '\0';
	for (x=0; x < n; x++) {
		found = false;
        for (y=0; y < z && ! found; y++)
			if (str[x] == nstr[y])
				found = true;
        if (!found)
			nstr[z++] = str[x];
	};
  nstr[z] = '\0';
  return nstr;
}
char * BSet::removeSubset(char * str1, char *str2) {
	int n1 = strlen(str1);
	int n2 = strlen(str2);
	char * nstr = new char[n1+1];


	int x, y, z = 0;
	bool found;
	nstr[0] = '\0';
	for (x=0; x < n1; x++) {
		found = false;
        for (y=0; y < n2 && ! found; y++)
			if (str1[x] == str2[y])
				found = true;
        if (!found)
			nstr[z++] = str1[x];
	};
  nstr[z] = '\0';
  return nstr;
}
