#include "BFunctions.h"

void strcatcar (char * str, char car) {

    if (str == NULL)
        return;

    int sz = strlen(str);

    str[sz] = car;
    str[sz+1] = '\0';

}
void remove(char * dt) {
	if (dt != NULL)
		delete [] dt;
}
char * clone(char * dt) {
	if (dt == NULL)
		return NULL;
	char * ret = new char [strlen(dt)+1];
	strcpy(ret,dt);
	return ret;
}
bool isEqual(char * s1, char * s2) {
	if (s1 == NULL && s2 == NULL)
		return true;
	if (s1 == NULL || s2 == NULL)
		return false;
	return strcmp(s1,s2) == 0;
}
bool ordered(char * s1, char * s2, bool asc) {
	int resp = strcmp(s1,s2);
	if (asc && resp < 0)
		return true;
	if (!asc && resp > 0)
		return true;
	return false;
}
char * toString(char * dt) { return clone(dt);};
int getTrueCount(bool * vec, int sz) {
	if (vec == NULL)
		return 0;

	int i, n;
	for (i = 0, n = 0; i < sz; i++)
		if (vec[i])
			n++;
	return n;
}
int getIndexOfNthTrue(bool * vec, int sz, int n) {
	if (vec == NULL || sz == 0 || n >= sz)
		return 0;

	int i;
	for (i = 0; i < sz; i++)
		if (vec[i]) {
			n--;
			if (n == 0)
				return i;
		}

	return INVALIDINDEX;
}

int getfalseCount(bool * vec, int sz) {
	if (vec == NULL)
		return 0;

	int i, n;
	for (i = 0, n = 0; i < sz; i++)
		if (!vec[i])
			n++;
	return n;
}

