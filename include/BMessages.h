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

#if !defined(_BMessages_H_)
#define _BMessages_H_

#ifdef _WIN32
#include <conio.h>
#endif // _WIN32

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BPoint.h"
#include <stdarg.h>
#if defined (_OPENCV)
#include "cv.h"
#include "openCVImage.h"
#endif
#if defined (_WINDOWS)
#include <afxwin.h>
#endif
#include "BFile.h"

#if !defined (MAXTEXTLENGTH)
#define MAXTEXTLENGTH 6144
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
//#define AT __FILE__ " at line " TOSTRING(__LINE__)
#define __STRLINE__ TOSTRING(__LINE__)

class BMessages {
public:

	BMessages();
	BMessages(char *);
	~BMessages();
	bool enable();
	void setFileName(char *);
	void disable();
	void printBooleanVector(char *, bool *, int);
	template <class T> void printPoint(char *, T, T);
	template <class T> void printPoint(char *, T);
	template <class T> void printPoints(char *, T, T);
	template <class T> void printVector(char *, char *, T *, int);
	template <class T> void printVectorOfPoints(char *, T *, int);
	template <class T> void print2DMatrix(char *, T **, int, int);
	template <class T> void print3DMatrix(char *, T ***, int, int, int);
	template <class T> void print4DMatrix(char *, T ****,int, int, int, int);
	void printState(char*, char*, char*, ...);
	void printWarning(char*, char*, char*, ...);
	void printInfo(char*, char*, char*, ...);
	void print(char*, ...);
	void printHistogram(char*, double *, int);
	void flush();
	// static functions
	static void sprintBooleanVector(char *, bool *, int);
	template <class T> static void sprintPoint(char *, T, T);
	template <class T> static void sprintPoint(char *, T);
	template <class T> static void sprintPoints(char *, T, T);
	template <class T> static void sprintVector(char *, char *, T *, int);
	template <class T> static void sprintVectorOfPoints(char *, T *, int);
	template <class T> static void sprint2DMatrix(char *, T **, int, int);
	template <class T> static void sprint3DMatrix(char *, T ***, int, int, int);
	template <class T> static void sprint4DMatrix(char *, T ****,int, int, int, int);
	static void sprintState(char*, char*, char*, ...);
	static void sprintWarning(char*, char*, char*, ...);
	static void sprintInfo(char*, char*, char*, ...);
	static void sprintWarningAndWaitKey(char*, char*, char*, ...);
	static void sprintInfoAndWaitKey(char*, char*, char*, ...);
	static void sprint(char*, ...);
	static void sprintHistogram(char*, double *, int);
	static void sflush();
#if defined (_OPENCV)
	void printCvVector(char *,   CvArr *,    int);
	void print2DCvMatrix(char *,   CvArr *, int, int);
	void printImageRoi(char*, IplImage *, IntegerPointType, IntegerPointType);
	static void sprintCvVector(char *,   CvArr *,    int);
	template <class T> static void sprintCvPointsVector(char *, T *, int);
	static void sprint2DCvMatrix(char *,   CvArr *, int, int);
	static void sprintImageContent(char * title, IplImage * img, int r, int c);
#endif
//	char text[MAXTEXTLENGTH];

protected:
	BFile * logfile;
	FILE * filedesc;
	bool active;
};

template <class T> void BMessages::printPoint(char * title, T x, T y) {
	if (!active)
		return;

	char * format = getOutputFormat(x);
	fprintf(filedesc, "Point %s: (", title);
	fprintf(filedesc, format, x);
	fprintf(filedesc, ", ");
	fprintf(filedesc, format, y);
	fprintf(filedesc, ")\n");
}
template <class T> void BMessages::printPoint(char * title, T p) {
	if (!active)
		return;

	char * str = pointToString(p);
	fprintf(filedesc, "Point %s: %s\n", title, str);
	delete [] str;
}
template <class T> void BMessages::printPoints(char * title, T p1, T p2) {
	if (!active)
		return;

	char * str1 = pointToString(p1);
	char * str2 = pointToString(p2);
	fprintf(filedesc, "Point %s: %s - %s\n", title, str1, str2);
	delete [] str1;
	delete [] str2;
}
template <class T> void BMessages::printVector(char * title, char * format, T *vec, int r) {
	if (!active || vec == NULL)
		return;

	int i;

	fprintf(filedesc,"\nVector:%s Elements: %d\n", title, r);

	for(i=0;i<r;i++)
		fprintf(filedesc, format, vec[i]);

	fprintf(filedesc,"\n");
}
template <class T> void BMessages::printVectorOfPoints(char * title, T *vec, int r) {
	if (!active || vec == NULL)
		return;

	int i;
	char str[64];

	fprintf(stderr,"\nPoint BVector:%s\n", title);

	for(i=0;i<r;i++) {
		pointToString(vec[i],str);
		fprintf(filedesc,"%s ", str);
	}
	fprintf(filedesc,"\n");
}
template <class T> void BMessages::print2DMatrix(char * title, T **mat, int r, int c) {

	if (!active || mat == NULL)
		return;

	int i,j;

	fprintf(filedesc,"\nMatrix 2D:%s\n", title);

	T v;

	char * format = getOutputFormat(v);

	for(i=0;i<r;i++) {
		for (j=0;j<c;j++) {
			fprintf(filedesc, format, mat[i][j]);
			fprintf(filedesc, " ");
		}
		fprintf(filedesc,"\n");
	}
}
template <class T> void BMessages::print3DMatrix(char * title, T ***mat, int r, int c, int e) {

	if (!active || mat == NULL)
		return;

	int i,j,k;

	fprintf(filedesc,"\nMatrix 3D:%s\n", title);

	T v;

	char * format = getOutputFormat(v);

	for (k=0; k < e; k++) {
		fprintf(stderr, "\nelement %d\n", k);
		for(i=0;i<r;i++) {
			for (j=0;j<c;j++) {
				fprintf(stderr, format, mat[i][j][k]);
				fprintf(stderr, " ");
			}
		}
	}
}
template <class T> void BMessages::sprintPoint(char * title, T x, T y) {
	T v;

	char * format = getOutputFormat(v);
	fprintf(stderr, "Point %s: (", title);
	fprintf(stderr, format, x);
	fprintf(stderr, ", ");
	fprintf(stderr, format, y);
	fprintf(stderr, ")\n");
}
template <class T> void BMessages::sprintPoint(char * title, T p) {
	char * str = pointToString(p);
	fprintf(stderr, "Point %s: %s\n", title, str);
	delete [] str;
}
template <class T> void BMessages::sprintPoints(char * title, T p1, T p2) {
	char * str1 = pointToString(p1);
	char * str2 = pointToString(p2);
	fprintf(stderr, "Point %s: %s - %s\n", title, str1, str2);
	delete [] str1;
	delete [] str2;
}
template <class T> void BMessages::sprintVector(char * title, char * format, T *vec, int r) {
	if (vec == NULL)
		return;

	int i;

	fprintf(stderr,"\nVector:%s\n", title);

	for(i=0;i<r;i++)
		fprintf(stderr,format, vec[i]);
	fprintf(stderr,"\n");
}
template <class T> void BMessages::sprintVectorOfPoints(char * title, T *vec, int r) {
	if (vec == NULL)
		return;

	int i;
	char str[64];

	fprintf(stderr,"\nPoint BVector:%s\n", title);

	for(i=0;i<r;i++) {
		pointToString(vec[i],str);
		fprintf(stderr,"%s ", str);
	}
	fprintf(stderr,"\n");
}
template <class T> void BMessages::sprint2DMatrix(char * title, T **mat, int r, int c) {

	if (mat == NULL)
		return;

	int i,j;

	fprintf(stderr,"\nMatrix 2D:%s\n", title);

	T v;

	char * format = getOutputFormat(v);

	for(i=0;i<r;i++) {
		for (j=0;j<c;j++) {
			fprintf(stderr, format, mat[i][j]);
			fprintf(stderr, " ");
		}
		fprintf(stderr,"\n");
	}

}
template <class T> void BMessages::sprint3DMatrix(char * title, T ***mat, int r, int c, int e) {

	if (mat == NULL)
		return;

	int i,j,k;

	fprintf(stderr,"\nMatrix 3D:%s\n", title);

	T v;

	char * format = getOutputFormat(v);

	for (k=0; k < e; k++) {
		fprintf(stderr, "\nelement %d\n", k);
		for(i=0;i<r;i++) {
			for (j=0;j<c;j++) {
				fprintf(stderr, format, mat[i][j][k]);
				fprintf(stderr, " ");
			}
		}
	}
}

#endif // !defined(_BMessages_H_)
