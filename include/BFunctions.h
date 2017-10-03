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

#if !defined(_BFUNCTIONS_H_)
#define _BFUNCTIONS_H_

#include <string.h>
#include <math.h>
#include <stdio.h>

#define PI     3.14159265
#define SQRT2  1.41421356						///< Square root of 2
#define SQRTPI 1.77245385						///< Square root of PI
#define SMALLVALUEDIFFERENTFROMZERO 0.00000001	///< Small value used for avoid division by zero
#define INVALIDRETURN                      -1	///< Constant used as invalid return
#define INVALIDINDEX                       -1	///< Constant used as invalid index
#define INVALIDVALUE                       -1	///< Constant used as invalid value

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define SQR(a)				(((a) == 0) ? 0 : ((a) * (a)))
#define SIGN(a,b)			((b) >= 0.0 ? fabs(a) : -fabs(a))

inline int round(int v)					{ return v;}
#ifdef WIN32
inline int round(float v)				{ return ((v >= 0)? (int)(v + 0.5) : (int)(v - 0.5));}
//inline int round(double v)				{ return ((v >= 0)? (int)(v + 0.5) : (int)(v - 0.5));}
#endif


void strcatcar(char *, char);

inline const char * getTypeName(char * v)		{ return "char *";}
inline const char * getTypeName(int v)			{ return "int";}
inline const char * getTypeName(float v)		{ return "float";}
inline const char * getTypeName(double v)		{ return "double";}
inline const char * getTypeName(bool v)		    { return "bool";}
inline const char * getInputFormat(char * v)	{ return "%s";}
inline const char * getInputFormat(int v)		{ return "%d";}
inline const char * getInputFormat(float v)		{ return "%f";}
inline const char * getInputFormat(double v)	{ return "%f";}
inline const char * getInputFormat(bool v)		{ return "%d";}
inline const char * getOutputFormat(char * v)	{ return "%s";}
inline const char * getOutputFormat(int v)		{ return "%3d";}
inline const char * getOutputFormat(float v)	{ return "%7.3f";}
inline const char * getOutputFormat(double v)	{ return "%7.3f";}
inline const char * getOutputFormat(bool v)		{ return "%d";}
inline const char * boolToString(bool v)		{ return (v)? "True" : "False";}
inline const char * getFormatAndSize(int v, int &sz)	{ sz = 5; return "%5d";}
inline const char * getFormatAndSize(float v, int &sz)	{ sz = 10; return "%10.2f";}
inline const char * getFormatAndSize(double v, int &sz)	{ sz = 10; return "%10.2f";}

template <class T> void fillPrintFormat(char *form, T val) {
    int i,j, le = strlen(form);
    char * aux = new char [le+1];
    strcpy(aux,form);
    int k=0;
    form[k]='\0';
    for(i=0; i < le; i++) {
        if (i < le-1 && aux[i] == '%' && aux[i+1] == 'T') {
            strcat(form,getOutputFormat(val));
            k+=strlen(getOutputFormat(val));
            i++;
        } else
            form[k++] = aux[i];
        form[k]='\0';
    }
    delete [] aux;
}


template <class T> bool isPointer(T dt) { return false;};
template <class T> bool isPointer(T * dt) { return true;};

template <class T> void remove(T dt) {};
template <class T> void remove(T * dt) {
	if (dt == NULL)
		return;
	delete dt;
}
void remove(char * dt);

template <class T> T clone(T dt) {
	return dt;
}
template <class T> T * clone(T * dt) {
	if (dt == NULL)
		return NULL;
	return dt->clone();
}
char * clone(char * dt);

template <class T> T  copy(T dt) {
	return dt;
}
template <class T> T * copy(T * dt) {
	return dt;
}

template <class T> bool isEqual(T d1, T d2) { return d1 == d2;}
bool isEqual(char * s1, char * s2);

template <class T> T invalid(T d) {
	return INVALIDVALUE;
}
template <class T> T * invalid(T *d) {
	return NULL;
}

template <class T> T * zero(T d) {
	return 0;
}
template <class T> T * zero(T *d) {
	return NULL;
}

template <class Td, class Tk> Tk getKey(Td d, Tk k) {
	return k;
}

template <class T> bool isInvalid(T d) {
	return d == INVALIDVALUE;
}
template <class T> bool isInvalid(T *d) {
	return d == NULL;
}

template <class T> bool ordered(T d1, T d2, bool asc) {
	if (asc && d1 <= d2)
		return true;
	if (!asc && d2 <= d1)
		return true;
	return false;
}
bool ordered(char * s1, char * s2, bool asc);

template <class T> char * toString(T dt) {
	const char * format = getOutputFormat(dt);
	char * str = new char [20];
	sprintf(str, format, dt);
	return str;
}
char * toString(char * dt);

///
/// vector functions: Those are not geometric vectors but an one line (or column) array of elements
///

/// Create Vector
template <class T> T *		createVector(int);
/// Copies a vector to a new created vector and returns it
template <class T> T*		cloneVector(T *, int);
/// Copies a vector to another pre-existing vector
template <class T> bool		copyVector(T *, int, T *);
template <class T> T* 		copyVector(T *, int, T *);
/// Delete the vector
template <class T> bool		deleteVector(T *&);
/// Clear the vector
template <class T> bool		clearVector(T *, int);
/// Prints the vector
template <class T> void     printVector(char * title, char * format, T *vec, int r);
template <class T> void     printVector(FILE * f, char * title, char * format, T *vec, int r);
/// Adds two vectors and returns a new created vector as the result
template <class T> T *		addVectors(T *, T *, int);
/// Adds two vector and returns the result on a third pre-exiting vector
template <class T> bool		addVectors(T *, T *, int, T *);
/// Subtracts two vectors and returns a new created vector as the result
template <class T> T *		subtractVectors(T *, T *, int);
/// Subtracts two vector and returns the result on a third pre-exiting vector
template <class T> bool		subtractVectors(T *, T *, int, T *);
/// Multiplies all elements of a vector by a constant and returns a new created vector as the result
template <class T> T *		multiplyVectorByConstant(T *, T, int);
/// Multiplies all elements of a vector by a constant and returns the result on a second pre-exiting vector
template <class T> bool		multiplyVectorByConstant(T *, T, int, T *);
/// Computes the dot product of two vectors (sum(x0[i] * x1[i]) p/ i=0...n)
template <class T> T		dotProduct(T *, T *, int);
/// Computes product of a column vector times a line vector
template <class T> T**		vectorProduct(T *, T *, int);
/// Computes the product of a column vector times a line vector the result is returned on a pre-existing matrix
template <class T> bool		vectorProduct(T *, T *, T **, int);
/// Computes the variance of a vector
template <class T> double	variance(T*,int);
/// Computes the standard deviation of a vector
template <class T> double	standardDeviation(T*,int);
/// Computes the median of a vector
template <class T> T		median(T*,int, bool);
/// Computes the maximum value of a vector
template <class T> T		maximum(T*,int);
/// Computes the maximum value of a vector and returns its position
template <class T> T		maximum(T*,int, int&);
/// Computes the minimum value of a vector
template <class T> T		minimum(T*,int);
/// Computes the minimum value of a vector and returns its position
template <class T> T		minimum(T*,int, int&);
/// Returns the number of true values
int			getTrueCount(bool *, int);
/// Returns the index of the nth true values
int			getIndexOfNthTrue(bool *, int, int);
/// Returns the number of false values
int			getfalseCount(bool *, int);
/// Returns the vector with each element rounded
void round(double * vec, int sz, int rc);


template <class T> T *   createVector(int r) {

	if (r <= 0)
		return NULL;

	T * res = new T [r];

	return res;
}
template <class T> T *   cloneVector(T* vec, int r) {

	if (vec == NULL || r <= 0)
		return NULL;

	T * res = new T [r];

	int i;

	for(i=0; i < r; i++)
		res[i] = vec[i];


	return res;
}
template <class T> bool copyVector(T* vec, int r, T* res) {

	if (vec == NULL)
		return false;

	int i;

	for(i=0; i < r; i++)
		res[i] = vec[i];

	return true;
}
template <class T> T* copyVector(T* vec, int r, T* res) {

	if (vec == NULL || r <= 0)
		return NULL;

	int i;

	for(i=0; i < r; i++)
		res[i] = vec[i];

	return res;
}
template <class T> bool deleteVector(T*& vec) {

	if (vec == NULL)
		return false;

	delete [] vec;
	vec = NULL;
	return vec;
}
template <class T> bool clearVector(T* vec, int r) {

	if (vec == NULL || r <= 0)
		return false;

	T z = zero(z);

	int i;

	for(i=0; i < r; i++)
		vec[i] = z;

	return vec;
}
template <class T> void printVector(char * title, char * format, T *vec, int r) {
	printVector(NULL, title, format, vec, r);
}
template <class T> void printVector(FILE * f, char * title, char * format, T *vec, int r) {
	if (vec == NULL)
		return;

	int i;

    FILE * file = NULL;

	if (f == NULL)
		file = f;
	else
		file = stdout;

	fprintf(file,"\nVector:%s Elements: %d\n", title, r);

	for(i=0;i<r;i++)
		fprintf(file, format, vec[i]);

	fprintf(file,"\n");

}
template <class T> T * addVectors(T *vec1, T *vec2, int r) {

	if (vec1 == NULL || vec2 == NULL)
		return NULL;

	T * res;

	int i;

	res = new T [r];
	for(i=0; i < r; i++)
		res[i] = vec1[i] + vec2[i];

	return res;
}
template <class T> bool addVectors(T *vec1, T *vec2, int r, T * res) {

	if (vec1 == NULL || vec2 == NULL || res == NULL)
		return false;

	int i;

	for(i=0; i < r; i++)
		res[i] = vec1[i] + vec2[i];

	return true;
}
template <class T> T * subtractVectors(T *vec1, T *vec2, int r) {

	if (vec1 == NULL || vec2 == NULL)
		return NULL;

	T * res;

	int i;

	res = new T [r];
	for(i=0; i < r; i++)
		res[i] = vec1[i] - vec2[i];

	return res;
}
template <class T> bool subtractVectors(T *vec1, T *vec2, int r, T * res) {

	if (vec1 == NULL || vec2 == NULL || res == NULL)
		return false;

	int i;

	for(i=0; i < r; i++)
		res[i] = vec1[i] - vec2[i];

	return true;
}
template <class T> T * multiplyVectorByConstant(T *vec, T val, int r) {

	if (vec == NULL)
		return NULL;

	T * res;

	int i;

	res = new T [r];
	for(i=0; i < r; i++)
		res[i] = vec[i] * val;

	return res;
}
template <class T> bool multiplyVectorByConstant(T *vec, T val, int r, T * res) {

	if (vec == NULL || res == NULL)
		return false;

	int i;

	for(i=0; i < r; i++)
		res[i] = vec[i] * val;

	return true;
}
template <class T> T dotProduct(T * vec1, T * vec2, int e) {
	if (vec1 == NULL || vec2 == NULL)
		return 0;

	int i;

	T res;

	res = 0;

	for (i = 0; i < e; i++)
		res += vec1[i] * vec2[i];

	return res;
}
template <class T> T** vectorProduct(T * vec1, T * vec2, int e) {

	if (vec1 == NULL || vec2 == NULL)
		return NULL;

	int i, j;

	T ** mat = new T* [e];

	for (i = 0; i < e; i++) {
		mat[i] = new T[e];
		for (j = 0; j < e; j++)
			mat[i][j] = vec1[i] * vec2[j];
	}

	return mat;
}
template <class T> bool vectorProduct(T * vec1, T * vec2, T **mat, int e) {

	if (vec1 == NULL || vec2 == NULL)
		return false;

	int i, j;

	for (i = 0; i < e; i++)
		for (j = 0; j < e; j++)
			mat[i][j] = vec1[i] * vec2[j];

	return true;
}
template <class T> double variance(T * vec, int sz) {

	T inv;

	if (vec == NULL)
		return invalid(inv);

	double sum = 0;
	double sumsq = 0;
	int i;

	for (i = 0; i < sz; i++) {
		sum += vec[i];
		sumsq += vec[i] * vec[i];
	}

	return (sumsq - (double)sum * sum / sz) / (sz - 1);
}
template <class T> double standardDeviation(T * vec, int sz) {

	T inv;

	if (vec == NULL)
		return invalid(inv);

	return sqrt(variance(vec, sz));
}
template <class T> T median(T * vec, int sz, bool allowmodification) {

	T inv;

	if (vec == NULL)
		return invalid(inv);

	T* nvec = NULL;

	if (allowmodification)
		nvec = vec;
	else
		nvec = cloneVector(vec, sz);

	quicksort(nvec, 0, sz -1);

	T val = nvec[sz/2];

	if (!allowmodification)
		delete [] nvec;

	return val;
}
template <class T> T maximum(T * vec, int sz) {

	T inv;

	if (vec == NULL)
		return invalid(inv);

	int i;

	T m = vec[0];

	for (i=1; i < sz; i++)
		if (m < vec[i])
			m = vec[i];

	return m;
}
template <class T> T maximum(T * vec, int sz, int & index) {

	T inv;

	if (vec == NULL)
		return invalid(inv);

	int i;

	T m = vec[0];
	index = 0;

	for (i=1; i < sz; i++)
		if (m < vec[i]) {
			m = vec[i];
			index = i;
		}

	return m;
}
template <class T> T minimum(T * vec, int sz) {

	T inv;

	if (vec == NULL)
		return invalid(inv);

	int i;

	T m = vec[0];

	for (i=1; i < sz; i++)
		if (m > vec[i])
			m = vec[i];

	return m;
}
template <class T> T minimum(T * vec, int sz, int & index) {

	T inv;

	if (vec == NULL)
		return invalid(inv);

	int i;

	T m = vec[0];
	index = 0;

	for (i=1; i < sz; i++)
		if (m > vec[i]) {
			m = vec[i];
			index = i;
		}

	return m;
}

#endif
