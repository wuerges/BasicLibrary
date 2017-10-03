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

/***********************************************************************

	Precompiler directives:

	_OpenCV         : for OpenCV points
    _POINTINTEGER_  : for using integer point as the default point
    _POINTFLOAT_    : for using float point as the default point
    _POINTDOUBLE_   : for using double point as the default point

************************************************************************/

#if !defined(_BPOINT_H_)
#define _BPOINT_H_

#include <stdio.h>
#include "BFunctions.h"

//#if defined _OPENCV
//#include "cv.h"
//#ifdef _POINTINTEGER_
//#define PointType CvPoint
//#define PointConstructor cvPoint
//#define PointCoordinateType int
//#elif defined _POINTFLOAT_
//#define PointType CvPoint2D32f
//#define PointConstructor cvPoint2D32f
//#define PointCoordinateType float
//#elif defined _POINTDOUBLE_
//#define PointType CvPoint2D64f
//#define PointConstructor cvPoint2D64f
//#define PointCoordinateType double
//#else
//#define _POINTDOUBLE_
//#define PointType CvPoint2D64f
//#define PointConstructor cvPoint2D64f
//#define PointCoordinateType double
//#endif
//#define IntegerPointType CvPoint
//#define IntegerPointConstructor cvPoint
//#define FloatPointType CvPoint2D32f
//#define FloatPointConstructor cvPoint2D32f
//#define DoublePointType CvPoint2D64f
//#define DoublePointConstructor cvPoint2D64f
//#else
//#ifdef _POINTINTEGER_
//#define PointType BIntegerPoint
//#define PointConstructor BIntegerPoint
//#define PointCoordinateType int
//#elif defined _POINTFLOAT_
//#define PointType BFloatPoint
//#define PointConstructor BFloatPoint
//#define PointCoordinateType float
//#elif defined _POINTDOUBLE_
//#define PointType BDoublePoint
//#define PointConstructor BDoublePoint
//#define PointCoordinateType double
//#else
//#define _POINTDOUBLE_
#define PointType BDoublePoint
#define PointConstructor BDoublePoint
#define PointCoordinateType double
//#endif
#define IntegerPointType BIntegerPoint
#define IntegerPointConstructor BIntegerPoint
#define FloatPointType BFloatPoint
#define FloatPointConstructor BFloatPoint
#define DoublePointType BDoublePoint
#define DoublePointConstructor BDoublePoint
//#endif

class BIntegerPoint {
public:
	BIntegerPoint();
	BIntegerPoint(int, int);
	~BIntegerPoint();
	int getX();
	int getY();
	bool setPoint(int,int);
	BIntegerPoint * clone();
	int x, y;
};
class BFloatPoint {
public:
	BFloatPoint();
	BFloatPoint(float, float);
	~BFloatPoint();
	float getX();
	float getY();
	bool setPoint(float,float);
	BFloatPoint * clone();
	float x, y;
};
class BDoublePoint {
public:
	BDoublePoint();
	BDoublePoint(double, double);
	~BDoublePoint();
	double getX();
	double getY();
	bool setPoint(double,double);
	BDoublePoint * clone();
	double x, y;
};


inline IntegerPointType round(IntegerPointType p)	{ return p;}
//inline IntegerPointType round(DoublePointType p)	{ return IntegerPointConstructor(round(p.x), round(p.y));}
//inline IntegerPointType round(DoublePointType *p)	{ return IntegerPointConstructor(round(p->x), round(p->y));}
inline IntegerPointType round(FloatPointType p)		{ return IntegerPointConstructor(round(p.x), round(p.y));}
inline IntegerPointType round(FloatPointType *p)	{ return IntegerPointConstructor(round(p->x), round(p->y));}

inline char * getOutputFormat(IntegerPointType p)		{ return "(%03d, %03d)";}
inline char * getOutputFormat(FloatPointType p)		    { return "(%8.4f, %8.4f)";}
inline char * getOutputFormat(DoublePointType p)		{ return "(%8.4f, %8.4f)";}

// ******* convert ************
inline DoublePointType	floatToDouble(FloatPointType p)		{ return DoublePointConstructor(p.x, p.y);}
inline FloatPointType	doubleToFloat(DoublePointType p)	{ return FloatPointConstructor(p.x, p.y);}
inline DoublePointType	integerToDouble(IntegerPointType p)	{ return DoublePointConstructor(p.x, p.y);}
//inline IntegerPointType	doubleToInteger(DoublePointType p)	{ return IntegerPointConstructor(round(p.x), round(p.y));}
inline FloatPointType	integerToFloat(IntegerPointType p)	{ return FloatPointConstructor(p.x, p.y);}
inline IntegerPointType	floatToInteger(FloatPointType p)	{ return IntegerPointConstructor(round(p.x), round(p.y));}

#if defined (_BLIST_H_)
BList<PointType> *	convertFromFloat(BList<FloatPointType> *);
#endif

//inline void	convertFromDouble(DoublePointType p, IntegerPointType &q)	{ q.x = round(p.x);  q.y = round(p.y);}
inline void	convertFromDouble(DoublePointType p, FloatPointType &q)		{ q.x = (float)p.x;  q.y = (float)p.y;}
inline void	convertFromDouble(DoublePointType p, DoublePointType &q)	{ q.x = p.x;  q.y = p.y;}

#if defined( _POINTDOUBLE_)
inline DoublePointType	convertToDouble(PointType p)			{ return p;}
inline PointType		convertFromDouble(DoublePointType p)	{ return p;}
inline IntegerPointType	convertToInteger(PointType p)			{ return IntegerPointConstructor(round(p.x), round(p.y));}
inline PointType		convertFromInteger(IntegerPointType p)	{ return PointConstructor(p.x, p.y);}
inline FloatPointType	convertToFloat(PointType p)				{ return FloatPointConstructor(p.x, p.y);}
inline PointType		convertFromFloat(FloatPointType p)		{ return PointConstructor(p.x, p.y);}
#elif defined (_PointInteger_)
inline DoublePointType	convertToDouble(PointType p)			{ return DoublePointConstructor(p.x, p.y);}
inline PointType		convertFromDouble(DoublePointType p)	{ return PointConstructor(round(p.x), round(p.y));}
inline IntegerPointType	convertToInteger(PointType p)			{ return p;}
inline PointType		(IntegerPointType p)					{ return p;}
inline FloatPointType	convertToFloat(PointType p)				{ return FloatPointConstructor(p.x, p.y);}
inline PointType		convertFromFloat(FloatPointType p)		{ return PointConstructor(round(p.x), round(p.y));}
#else
inline DoublePointType	convertToDouble(PointType p)			{ return DoublePointConstructor(p.x, p.y);}
inline PointType		convertFromDouble(DoublePointType p)	{ return PointConstructor(p.x, p.y);}
//inline IntegerPointType	convertToInteger(PointType p)			{ return IntegerPointConstructor(round(p.x), round(p.y));}
inline PointType		convertFromInteger(IntegerPointType p)	{ return PointConstructor(p.x, p.y);}
inline FloatPointType	convertToFloat(PointType p)				{ return FloatPointConstructor(p.x, p.y);}
inline PointType		convertFromFloat(FloatPointType p)		{ return PointConstructor(p.x, p.y);}
#endif

inline IntegerPointType	addPoints(IntegerPointType p1, IntegerPointType p2)		{ return IntegerPointConstructor(p1.x + p2.x, p1.y + p2.y);}
inline FloatPointType	addPoints(FloatPointType p1, FloatPointType p2)			{ return FloatPointConstructor(p1.x + p2.x, p1.y + p2.y);}
inline DoublePointType	addPoints(DoublePointType p1, DoublePointType p2)		{ return DoublePointConstructor(p1.x + p2.x, p1.y + p2.y);}
inline IntegerPointType	subtractPoints(IntegerPointType p1, IntegerPointType p2){ return IntegerPointConstructor(p1.x - p2.x, p1.y - p2.y);}
inline FloatPointType	subtractPoints(FloatPointType p1, FloatPointType p2)	{ return FloatPointConstructor(p1.x - p2.x, p1.y - p2.y);}
inline DoublePointType	subtractPoints(DoublePointType p1, DoublePointType p2)	{ return DoublePointConstructor(p1.x - p2.x, p1.y - p2.y);}
inline double		distancePoints(IntegerPointType p1, IntegerPointType p2){ return sqrt((double)(p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));}
inline double		distancePoints(FloatPointType p1, FloatPointType p2)	{ return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));}
inline double		distancePoints(DoublePointType p1, DoublePointType p2)	{ return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));}
inline double		distancePointToOrigin(IntegerPointType p1)			{ return sqrt((double)p1.x  * p1.x + p1.y * p1.y);}
inline double		distancePointToOrigin(FloatPointType p1)			{ return sqrt(p1.x  * p1.x + p1.y * p1.y);}
inline double		distancePointToOrigin(DoublePointType p1)			{ return sqrt(p1.x  * p1.x + p1.y * p1.y);}

inline PointType		zeroPoint()					{ return PointConstructor(0,0);}
inline IntegerPointType	zeroPointInteger()			{ return IntegerPointConstructor(0,0);}
inline DoublePointType	zeroPointDouble()			{ return DoublePointConstructor(0,0);}
inline PointType		unityPoint()				{ return PointConstructor(1,1);}
inline IntegerPointType	unityPointInteger()			{ return IntegerPointConstructor(1,1);}
inline DoublePointType	unityPointDouble()			{ return DoublePointConstructor(1.0,1.0);}
inline PointType		invalidPoint()				{ return PointConstructor(-1, -1);}
inline IntegerPointType	invalidPointInteger()		{ return IntegerPointConstructor(-1,-1);}
inline DoublePointType	invalidPointDouble()		{ return DoublePointConstructor(-1,-1);}
template <class T> bool isInvalidPoint(T p)			{return (p.x == - 1 && p.y  == -1) ? true : false;}

template <class T> char * pointToString(T p);
template <class T> void   pointToString(T p, char * str);

inline PointType	incrementPoint(PointType p)	{ return PointConstructor(p.x+1,p.y+1);}

template <class T> T		absoluteCoordinates(T);
template <class T> double	slopePoints(T, T);
template <class T> bool		pointsAreEqual(T p, T q)		{ return (p.x == q.x && p.y == q.y) ? true : false;}
template <class T> bool		lowerBoundOk(T p)				{ return (p.x >= 0 && p.y >= 0) ? true : false;}
template <class T> bool		isZeroPoint(T p)				{ return (p.x == 0 && p.y == 0) ? true : false;}
template <class T> bool		greaterEqual(T p, T q) 			{ return (p.x >= q.x || p.y >= q.y) ? true : false;}
template <class T> T		rotate(T, T, double);

template <class T> char * pointToString(T p) {
	char * format = getOutputFormat(p);
	char * str = new char [64];
	sprintf(str, format, p.x, p.y);
	return str;
}

template <class T> void   pointToString(T p, char * str) {
	char * format = getOutputFormat(p);
	sprintf(str, format, p.x, p.y);
}

template <class T> T  absoluteCoordinates(T p) {
	if (p.x < 0)
		p.x = p.x * -1;
	if (p.y < 0)
		p.y = p.y * -1;

	return p;
}
template <class T> double slopePoints(T p1, T p2) {
	if (p1.x == p2.x)
		return (p1.y - p2.y) / SMALLVALUEDIFFERENTFROMZERO;
	else
		return (double)(p1.y - p2.y) / (p1.x - p2.x);
}

template <class T> T rotate(T p, T c, double * mat) {
	DoublePointType aux;

	aux.x = ((p.x - c.x) * mat[0] - (p.y - c.y) * mat[1] + mat[2]);
	aux.y = ((p.x - c.x) * mat[1] + (p.y - c.y) * mat[0] + mat[3]);

	T res;

	convertFromDouble(aux, res);

	return res;
}
inline DoublePointType smoothPoints(DoublePointType p1, DoublePointType p2, double alpha)	{
	return DoublePointConstructor(p2.x * alpha + p1.x * (1 - alpha),
								  p2.y * alpha + p1.y * (1 - alpha));
}
#endif // !defined(_Point_H_)
