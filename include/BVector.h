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

#if !defined(_BVECTOR_H_)
#define _BVECTOR_H_

#include "BPoint.h"

#define RADTODEGREE 57.2957795785
#define PI 3.14159265



class BVector {
public:
	BVector();
	BVector(DoublePointType);
	BVector(DoublePointType, DoublePointType);
	BVector(FloatPointType);
	BVector(FloatPointType, FloatPointType);
	BVector(IntegerPointType);
	BVector(IntegerPointType, IntegerPointType);
	~BVector();
	void resetTail();
	void setTail(DoublePointType);
	void setTail(FloatPointType);
	void setTail(IntegerPointType);
	void setHead(DoublePointType);
	void setHead(FloatPointType);
	void setHead(IntegerPointType);
	double getLength();
	bool atOrigin();
	BVector getOriginVector();
	void putAtOrigin();
	double distance(BVector);
	void subtract(BVector);
	void add(BVector);
	double distance(BVector *);
	void subtract(BVector *);
	void add(BVector *);
	bool equal(BVector);
	bool equal(BVector *);
	double slope();
	bool null();
	void multiply(double);
	BVector * clone();
	BVector copy();
	double dotProduct(BVector);
	double dotProduct(BVector *);
	double angle(BVector);
	double angle(BVector *);
	double cosine(BVector);
	double cosine(BVector *);
	static double radiansToDegrees(double);
	void print();
#ifdef _BMESSAGES_H_
	void print(BMessages *);
#endif
	void print(FILE *);
	void move(DoublePointType);
	void move(FloatPointType);
	void move(IntegerPointType);
	DoublePointType getTail() { return tail;};
	DoublePointType getHead() { return head;};
	void normalize();
#if defined _OPENCV
	double project(CvPoint2D64f);
#endif
	double project(double, double);

protected:
	DoublePointType 
		tail,
		head;
	double 
		length;


};

class BWeightedVector : public BVector {
public:
	BWeightedVector();
	BWeightedVector(DoublePointType);
	BWeightedVector(FloatPointType);
	BWeightedVector(IntegerPointType);
	BWeightedVector(DoublePointType, DoublePointType);
	BWeightedVector(FloatPointType, FloatPointType);
	BWeightedVector(IntegerPointType, IntegerPointType);
	~BWeightedVector();
	void resetTail();
	void setTail(DoublePointType);
	void setTail(FloatPointType);
	void setTail(IntegerPointType);
	void setHead(DoublePointType);
	void setHead(FloatPointType);
	void setHead(IntegerPointType);
	void setWeight(double);
	double getWeight();
	void setState(double);
	double getState();
	void setDistance(double, double = 0, double = 0);
	double getDistance();
	double getNormalizedDistance();
	BWeightedVector * clone();
	BWeightedVector copy();
	void print();
#ifdef _BMESSAGES_H_
	void print(BMessages *);
#endif
	void print(FILE *);
	BWeightedVector getOriginVector();
	void subtract(BWeightedVector);
	void subtract(BWeightedVector *);
	void add(BWeightedVector);
	void add(BWeightedVector*);
	void multiply(double);
	DoublePointType getTail() { return tail;};
	DoublePointType getHead() { return head;};
	int getLocus() { return locus;};
	void setLocus(int);

protected:
	double 
		weight,
		error,
		dist,
		avg,
		std;
	bool 
		fw,
		fe,
		fd;
	int locus;
};

BVector * convert(BWeightedVector *);	
BWeightedVector * convert(BVector *);	
BVector convert(BWeightedVector);	
BWeightedVector convert(BVector);	



#endif // !defined(_VECTORS_)
