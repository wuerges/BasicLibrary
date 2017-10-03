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

#include "BMessages.h"

BMessages::BMessages() {
	logfile = NULL;
	filedesc = NULL;
	active = false;
}
BMessages::BMessages(char * name) {
	logfile = NULL;
	filedesc = NULL;
	active = false;
	logfile = new BFile(name);
	filedesc = logfile->getDescriptor();
}

BMessages::~BMessages() {
	if (logfile != NULL)
		delete logfile;
}

void BMessages::setFileName(char * name) {

	if (logfile == NULL)
		logfile = new BFile(name);
	else
		logfile->setFileName(name);
}
bool BMessages::enable() {

	if (! active) {
		if (logfile == NULL)
			logfile = new BFile();
		if (!logfile->forceOpen("w"))
			fprintf(stderr,"##########################\nERROR: Could not open file %s\n##########################\n", logfile->getFullName());
		else {
			fprintf(stderr,"------ BMessages::%s opened\n", logfile->getName());
			active = true;
		}
	}

	return active;

}

void BMessages::disable() {

	active = false;
}



void BMessages::printBooleanVector(char * title, bool *vec, int r) {
	if (!active || logfile == NULL || vec == NULL)
		return;

	int i;

	fprintf(filedesc,"\nVector:%s\n", title);

	for(i=0;i<r;i++)
		fprintf(filedesc,"%7s ", boolToString(vec[i]));

		fprintf(filedesc,"\n");
}
void BMessages::sprintBooleanVector(char * title, bool *vec, int r) {
	if (vec == NULL)
		return;

	int i;

	printf("\nVector:%s\n", title);

	for(i=0;i<r;i++)
		printf("%7s ", boolToString(vec[i]));

		printf("\n");
}



template <class T> void BMessages::print4DMatrix(char * title, T ****mat, int r, int c, int e, int maxcols) {

	if (!active || logfile == NULL || mat == NULL)
		return;

	int i,j,k1, k2;
	int
		l1 = min(e, maxcols),
		l2 = min(r, maxcols),
		l3 = min(c, maxcols);

	int sz = 0;

	char * format = getFormatAndSize(mat[0][0][0][0], sz);
	sz++;

	int p1, p2;
	p1 = (sz * l1 - 5) / 2;
	p2 = (sz * l1 + 3) - p1 - 5;
	int a = 0;

	fprintf(filedesc,"\nMatrix 4D:%s\n", title);

	for(i=0;i<r;i++) {
		for (j=0;j<l3;j++) {
			for (a=0; a< p1; a++)
				fprintf(filedesc," ");
			fprintf(filedesc, "(%d,%d)", i, j);
			for (a=0; a< p2; a++)
				fprintf(filedesc," ");
		}
		fprintf(filedesc,"\n");
		for (k1=0; k1 < l1; k1++) {
			for (j=0;j<l3;j++) {
				for (k2=0; k2 < l1; k2++) {
					fprintf(filedesc, format, mat[i][j][k1][k2]);
					fprintf(filedesc," ");
				}
				fprintf(filedesc," | ");
				flush();
			}
			fprintf(filedesc,"\n");
		}
	}
}


void BMessages::printState(char * loc, char * line, char * formatstring, ...) {

	if (!active || logfile == NULL)
		return;

    va_list args;
    va_start(args, formatstring);

	char str[MAXTEXTLENGTH];

	vsprintf(str, formatstring, args);

//	perror (str);

	fprintf(filedesc,"####################################################\nERROR:    %s\nLocation: File %s at Line %s\n\n####################################################\n", str, skipPath(loc), line);

	va_end (args);
}
void BMessages::printWarning(char * loc, char * line, char * formatstring, ...) {

	if (!active || logfile == NULL)
		return;

    va_list args;
    va_start(args, formatstring);

	char str[MAXTEXTLENGTH];

	vsprintf(str, formatstring, args);

//	perror (str);

	fprintf(filedesc,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nWARNING:  %s\nLocation: File %s at Line %s\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", str, skipPath(loc), line);

	va_end (args);
}
void BMessages::printInfo(char * loc, char * line, char * formatstring, ...) {

	if (!active || logfile == NULL)
		return;

    va_list args;
    va_start(args, formatstring);

	char str[MAXTEXTLENGTH];

	vsprintf(str, formatstring, args);

//	perror (str);

	fprintf(filedesc,"----------------------------------------------------\nINFO:     %s\nLocation: File %s at Line %s\n \n----------------------------------------------------\n", str, skipPath(loc), line);

	va_end (args);
}
void BMessages::print(char * formatstring, ...) {

	if (!active || logfile == NULL)
		return;

    va_list args;
    va_start(args, formatstring);

	char str[MAXTEXTLENGTH];

	vsprintf(str, formatstring, args);

//	perror (str);

	fprintf(filedesc, "%s", str);

	va_end (args);
}
void BMessages::flush() {

	if (logfile == NULL)
		return;

	fflush(filedesc);
}

template <class T> void BMessages::sprint4DMatrix(char * title, T ****mat, int r, int c, int e, int maxcols) {

	if (mat == NULL)
		return;

	int i,j,k1, k2;
	int
		l1 = min(e, maxcols),
		l2 = min(r, maxcols),
		l3 = min(c, maxcols);
	int sz = 0;

	char * format = getFormatAndSize(mat[0][0][0][0], sz);
	sz++;

	int p1, p2;
	p1 = (sz * l1 - 5) / 2;
	p2 = (sz * l1 + 3) - p1 - 5;
	int a = 0;

	fprintf(stderr,"\nMatrix 4D:%s\n", title);

	for(i=0;i<r;i++) {
		for (j=0;j<l3;j++) {
			for (a=0; a< p1; a++)
				fprintf(stderr," ");
			fprintf(stderr, "(%d,%d)", i, j);
			for (a=0; a< p2; a++)
				fprintf(stderr," ");
		}
		fprintf(stderr,"\n");
		for (k1=0; k1 < l1; k1++) {
			for (j=0;j<l3;j++) {
				for (k2=0; k2 < l1; k2++) {
					fprintf(stderr, format, mat[i][j][k1][k2]);
					fprintf(stderr," ");
				}
				fprintf(stderr," | ");
			}
			fprintf(stderr,"\n");
		}
	}
}

void BMessages::sprintState(char * loc, char * line, char * formatstring, ...) {

    va_list args;
    va_start(args, formatstring);

	char str[MAXTEXTLENGTH];

	vsprintf(str, formatstring, args);

//	perror (str);

#if defined (_WINDOWS)
	char str2[512];
	sprintf(str2, "ERROR:    %s  \nLocation:  File %s at Line %s", str, removePath(loc), line);
	CString str3(str2);
	AfxMessageBox(str3);
	exit(EXIT_FAILURE);
#else
	fprintf(stderr,"###############################################\nERROR:     %s\nLocation:  File %s at Line %s\n\n###############################################\n", str, skipPath(loc), line);
#if defined _DEBUG
	fprintf(stderr,"\nPress any key to continue...\n");
	getchar();
#endif
	exit(EXIT_FAILURE);
#endif
	va_end (args);
}
void BMessages::sprintWarning(char * loc, char * line, char * formatstring, ...) {

    va_list args;
    va_start(args, formatstring);

	char str[MAXTEXTLENGTH];

	vsprintf(str, formatstring, args);

	//perror (str);
#if defined (_WINDOWS)
	char str2[512];
	sprintf(str2, "WARNING:  %s  \nLocation:  File %s at Line %s", str, skipPath(loc), line);
	CString str3(str2);
	AfxMessageBox(str3);
#else
	fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nWARNING:   %s\nLocation:  File %s at Line %s\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", str, skipPath(loc), line);
#endif

	va_end (args);
}
void BMessages::sprintWarningAndWaitKey(char * loc, char * line, char * formatstring, ...) {

    va_list args;
    va_start(args, formatstring);

	char str[MAXTEXTLENGTH];

	vsprintf(str, formatstring, args);

	//perror (str);
#if defined (_WINDOWS)
	char str2[512];
	sprintf(str2, "WARNING:  %s  \nLocation:  File %s at Line %s", str, skipPath(loc), line);
	CString str3(str2);
	AfxMessageBox(str3);
#else
	fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nWARNING:  %s\nLocation:  File %s at Line %s\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", str, skipPath(loc), line);
	fprintf(stderr,"\nPress any key to continue...\n");
	getchar();
#endif

	va_end (args);
}
void BMessages::sprintInfo(char * loc, char * line, char * formatstring, ...) {

    va_list args;
    va_start(args, formatstring);

	char str[MAXTEXTLENGTH];

	vsprintf(str, formatstring, args);

//	perror (str);

#if defined (_WINDOWS)
	char str2[512];
	sprintf(str2, "INFO:     %s  \nLocation:  File %s at Line %s", str, skipPath(loc), line);
	CString str3(str2);
	AfxMessageBox(str3);
#else
	fprintf(stderr,"--------------------------\nINFO:     %s\nLocation:  File %s at Line %s\n\n--------------------------\n", str, skipPath(loc), line);
#endif

	va_end (args);
}
void BMessages::sprintInfoAndWaitKey(char * loc, char * line, char * formatstring, ...) {

    va_list args;
    va_start(args, formatstring);

	char str[MAXTEXTLENGTH];

	vsprintf(str, formatstring, args);

//	perror (str);

#if defined (_WINDOWS)
	char str2[512];
	sprintf(str2, "INFO:     %s  \nLocation:  File %s at Line %s", str, skipPath(loc), line);
	CString str3(str2);
	AfxMessageBox(str3);
#else
	fprintf(stderr,"--------------------------\nINFO:     %s\nLocation:  File %s at Line %s\n\n--------------------------\n", str, skipPath(loc), line);
	fprintf(stderr,"\nPress any key to continue...\n");
	getchar();
#endif

	va_end (args);
}
void BMessages::sprint(char * formatstring, ...) {

    va_list args;
    va_start(args, formatstring);

	char str[MAXTEXTLENGTH];

	vsprintf(str, formatstring, args);

//	perror (str);

	fprintf(stderr, "%s", str);

	va_end (args);
}
void BMessages::sflush() {

	fflush(stderr);
}
void BMessages::printHistogram(char* text, double * h, int sz) {
	if (!active || logfile == NULL || h == NULL || sz == 0)
		return;
	int i;
	fprintf(filedesc, "Histogram:%s\n-------------------------\n", text);
	for (i=0; i < sz; i++)
		if (h[i] > 0)
			fprintf(filedesc, "h[%d]=%f\n", i, h[i]);
	fprintf(filedesc, "-------------------------\n");
}
void BMessages::sprintHistogram(char* text, double * h, int sz) {
	if (h == NULL || sz == 0)
		return;
	int i;
	printf("Histogram:%s\n-------------------------\n", text);
	for (i=0; i < sz; i++)
		if (h[i] > 0)
			printf("h[%d]=%f\n", i, h[i]);
	printf("-------------------------\n");
}
#if defined (_OPENCV)
void BMessages::printCvVector(char * title, CvArr *vec, int r) {
	if (!active || logfile == NULL || vec == NULL)
		return;

	int i;

	fprintf(filedesc,"\nVector:%s\n", title);

	for(i=0;i<r;i++)
		fprintf(filedesc,"%13.2f ", cvGetReal1D(vec, i));

		fprintf(filedesc,"\n");
}

void BMessages::print2DCvMatrix(char * title, CvArr *mat, int r, int c) {

	if (!active || logfile == NULL || mat == NULL)
		return;

	int i,j;

	fprintf(filedesc,"\nMatrix 2D:%s\n", title);

	for(i=0;i<r;i++) {
		for (j=0;j<c;j++)
//			fprintf(filedesc,"%13.2f ", cvGetReal2D(mat, i, j));
			fprintf(filedesc,"%.10lf ", cvGetReal2D(mat, i, j));
		fprintf(filedesc,"\n");
	}
}
void BMessages::sprintCvVector(char * title, CvArr *vec, int r) {
	if (vec == NULL)
		return;

	int i;

	fprintf(stderr,"\nVector:%s\n", title);

	for(i=0;i<r;i++)
		fprintf(stderr,"%13.2f ", cvGetReal1D(vec, i));

		fprintf(stderr,"\n");
}
void BMessages::sprintImageContent(char * title, IplImage * img, int r, int c) {

	if (img == NULL)
		return;

	int i,j;

	int h = minValue(r, img->height);
	int w = minValue(c, img->width);

	BwImage im(img);

	fprintf(stderr,"\nImage Content:%s\n", title);

	for(i=0;i<h;i++) {
		fprintf(stderr, "%3d: ", i);
		for (j=0;j<w;j++)
			fprintf(stderr,"%u ", im[i][j]);
		fprintf(stderr,"\n");
	}
}
void BMessages::sprint2DCvMatrix(char * title, CvArr *mat, int r, int c) {

	if (mat == NULL)
		return;

	int i,j;

	fprintf(stderr,"\nMatrix 2D:%s\n", title);

	for(i=0;i<r;i++) {
		for (j=0;j<c;j++)
//			fprintf(stderr,"%13.2f ", cvGetReal2D(mat, i, j));
			fprintf(stderr,"%.10lf ", cvGetReal2D(mat, i, j));
		fprintf(stderr,"\n");
	}
}
void BMessages::printImageRoi(char * text, IplImage * img, IntegerPointType tl, IntegerPointType br) {
	if (img == NULL)
		return;

	RgbImage rgbimg(img);

	fprintf(filedesc,"Image %s: ROI [(%3d,%3d)->(%3d,%3d)]\n", text, tl.x, tl.y, br.x, br.y);

	int i, j;

	fprintf(filedesc,"      ");
	for (j=tl.x; j <= br.x; j++)
		fprintf(filedesc,"     %3d     |", j);
	fprintf(filedesc,"\n     ");
	for (j=tl.x; j <= br.x; j++)
		fprintf(filedesc,"--------------");
	fprintf(filedesc,"\n");

	for (i = tl.y; i <= br.y; i++) {
		fprintf(filedesc,"%3d | ", i);
		for (j=tl.x; j <= br.x; j++)
			fprintf(filedesc,"(%3d,%3d,%3d) ", rgbimg[i][j].r, rgbimg[i][j].g, rgbimg[i][j].b);
		fprintf(filedesc,"\n");
	}
}
#endif
