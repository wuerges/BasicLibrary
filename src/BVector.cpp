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

#include "BVector.h"

BVector::BVector() {
	tail = zeroPointDouble();
	head = zeroPointDouble();
	length = -1;
}
BVector::BVector(DoublePointType h) {
	tail = zeroPointDouble();
	head = h;
	length = -1;
}
BVector::BVector(DoublePointType t, DoublePointType h) {
	tail = t;
	head = h;
	length = -1;
}
BVector::BVector(FloatPointType t, FloatPointType h) {
	tail = floatToDouble(t);
	head = floatToDouble(h);
	length = -1;
}
BVector::BVector(FloatPointType h) {
	tail = zeroPointDouble();
	head = floatToDouble(h);
	length = -1;
}
BVector::BVector(IntegerPointType t, IntegerPointType h) {
	tail = integerToDouble(t);
	head = integerToDouble(h);
	length = -1;
}
BVector::BVector(IntegerPointType h) {
	tail = zeroPointDouble();
	head = integerToDouble(h);
	length = -1;
}
BVector::~BVector() {
}

void BVector::resetTail() {
	tail = zeroPointDouble();
	length = -1;
}
void BVector::setTail(DoublePointType t) {
	tail = t;
	length = -1;
}
void BVector::setTail(FloatPointType t) {
	tail = floatToDouble(t);
	length = -1;
}
void BVector::setTail(IntegerPointType t) {
	tail = integerToDouble(t);
	length = -1;
}
void BVector::setHead(DoublePointType h) {
	head = h;
	length = -1;
}
void BVector::setHead(FloatPointType h) {
	head = floatToDouble(h);
	length = -1;
}
void BVector::setHead(IntegerPointType h) {
	head = integerToDouble(h);
	length = -1;
}

double BVector::getLength() {
	if (length == -1)
		length = distancePoints(tail, head);
	return length;
}
bool BVector::atOrigin() {
	if (tail.x == 0 && tail.y == 0)
		return true;
	return false;
};
bool BVector::null() {
	if (head.x == 0 && head.y == 0 && tail.x == 0 && tail.y == 0)
		return true;
	return false;
};
BVector BVector::getOriginVector() {
	return BVector(subtractPoints(head, tail));
}
void BVector::putAtOrigin() {
	head = subtractPoints(head, tail);
	tail = zeroPointDouble();
}
void BVector::move(DoublePointType t) {
	head = addPoints(t, subtractPoints(head, tail));
	tail = t;
}
void BVector::move(FloatPointType t) {
	DoublePointType t1 = floatToDouble(t);
	head = addPoints(t1, subtractPoints(head, tail));
	tail = t1;
}
void BVector::move(IntegerPointType t) {
	DoublePointType t1 = integerToDouble(t);
	head = addPoints(t1, subtractPoints(head, tail));
	tail = t1;
}
void BVector::subtract(BVector v) {
	setTail(head);
	setHead(v.getHead());
}
void BVector::subtract(BVector *v) {
	setTail(head);
	setHead(v->getHead());
}

double BVector::distance(BVector v) {

	BVector v1 = copy();
	v1.subtract(v);
	return v1.getLength();
}
double BVector::distance(BVector *v) {

	BVector v1 = copy();
	v1.subtract(v);
	//printf("Distancia (%7.3f, %7.3f)->(%7.3f, %7.3f) ===> (%7.3f, %7.3f)->(%7.3f, %7.3f) = %f\n", tail.x, tail.y, head.x, head.y, v->getTail().x, v->getTail().y, v->getHead().x, v->getHead().y, v1.getLength());
	return v1.getLength();
}
bool BVector::equal(BVector v) {

	if (head.x != v.getHead().x ||
		head.y != v.getHead().y ||
		tail.x != v.getTail().x ||
		tail.y != v.getTail().y )
		return false;
	return true;
}
bool BVector::equal(BVector *v) {

	if (head.x != v->getHead().x ||
		head.y != v->getHead().y ||
		tail.x != v->getTail().x ||
		tail.y != v->getTail().y )
		return false;
	return true;
}
double BVector::slope() {

	return slopePoints(head, tail);
}

void BVector::add(BVector v) {
	if (pointsAreEqual(head, v.getTail()))
		setHead(v.getHead());

	BVector o1 = getOriginVector();
	BVector o2 = v.getOriginVector();
	setHead(DoublePointConstructor(tail.x + o1.getHead().x + o2.getHead().x, tail.y + o1.getHead().y + o2.getHead().y));
}
void BVector::add(BVector * v) {
	if (pointsAreEqual(head, v->getTail()))
		setHead(v->getHead());

	BVector o1 = getOriginVector();
	BVector o2 = v->getOriginVector();

	setHead(DoublePointConstructor(tail.x + o1.getHead().x + o2.getHead().x, tail.y + o1.getHead().y + o2.getHead().y));
}
void BVector::multiply(double c) {
	if (!atOrigin()) {
		BVector o = getOriginVector();
		setHead(DoublePointConstructor(tail.x + c * o.getHead().x, tail.y + c * o.getHead().y));
	} else 
		setHead(DoublePointConstructor(tail.x + c * head.x, tail.y + c * head.y));
}

BVector * BVector::clone() {
	BVector *nv = new BVector(tail, head);
	nv->length = length;
	return nv;
}
BVector BVector::copy() {
	BVector nv = BVector(tail, head);
	nv.length = length;
	return nv;
}

double BVector::dotProduct(BVector v) {

	BVector o1 = getOriginVector();
	BVector o2 = v.getOriginVector();

	return (o1.getHead().x * o2.getHead().x + o1.getHead().y * o2.getHead().y);
}
double BVector::dotProduct(BVector * v) {

	BVector o1 = getOriginVector();
	BVector o2 = v->getOriginVector();

	return (o1.getHead().x * o2.getHead().x + o1.getHead().y * o2.getHead().y);
}
double BVector::cosine(BVector v) {
	if (getLength() == 0 || v.getLength() == 0)
		return dotProduct(v) / SMALLVALUEDIFFERENTFROMZERO;
	else  {
		double cosi = dotProduct(v) / (getLength() * v.getLength());
		if (cosi > 1.0) cosi = 1.0;
		return cosi;
	}
}
double BVector::cosine(BVector *v) {
	if (getLength() == 0 || v->getLength() == 0)
		return dotProduct(v) / SMALLVALUEDIFFERENTFROMZERO;
	else  {
		double cosi = dotProduct(v) / (getLength() * v->getLength());
		if (cosi > 1.0) cosi = 1.0;
		return cosi;
	}
}
double BVector::angle(BVector v) {
	if (getLength() == 0 || v.getLength() == 0)
		return acos(dotProduct(v) / SMALLVALUEDIFFERENTFROMZERO);
	else {
		double cosi = dotProduct(v) / (getLength() * v.getLength());
		if (cosi > 1.0) cosi = 1.0;
		return acos(cosi);
	}
}
double BVector::angle(BVector *v) {
	if (getLength() == 0 || v->getLength() == 0)
		return acos(dotProduct(v) / SMALLVALUEDIFFERENTFROMZERO);
	else {
		double cosi = dotProduct(v) / (getLength() * v->getLength());
		if (cosi > 1.0) cosi = 1.0;
		return acos(cosi);
	}
}
double BVector::radiansToDegrees(double ang) {

	return ang * RADTODEGREE;

}
void BVector::normalize() {

	if (!atOrigin())
		putAtOrigin();
	head.x /= getLength();
	head.y /= getLength();
	
}
#if defined _OPENCV
double BVector::project(CvPoint2D64f p) {
	if (!atOrigin()) {
		CvPoint2D64f h = getOriginVector().getHead();
		return h.x * p.x + h.y * p.y;
	}

	return head.x * p.x + head.y * p.y;
}
double BVector::project(double px, double py) {
	if (!atOrigin()) {
		CvPoint2D64f h = getOriginVector().getHead();
		return h.x * px + h.y * py;
	}

	return head.x * px + head.y * py;
}
#endif
void BVector::print() {
#ifdef _BMESSAGES_H_
	BMessages::sprint("Tail:(%6.2f, %6.2f) --> Head:(%6.2f, %6.2f)\n",
					   tail.x, tail.y, head.x, head.y);
#else
	printf("Tail:(%6.2f, %6.2f) --> Head:(%6.2f, %6.2f)\n",
					   tail.x, tail.y, head.x, head.y);
#endif
}
#ifdef _BMESSAGES_H_
void BVector::print(BMessages * f) {

	f->print("Tail:(%6.2f, %6.2f) --> Head:(%6.2f, %6.2f)\n",
					   tail.x, tail.y, head.x, head.y);
}
#endif
void BVector::print(FILE * f) {

	fprintf(f,"Tail:(%6.2f, %6.2f) --> Head:(%6.2f, %6.2f)\n",
					   tail.x, tail.y, head.x, head.y);
}


BWeightedVector::BWeightedVector(): BVector() {
	weight = 0;
	error = 1;
	dist = 1;
	avg = 0;
	std = 1;
	fw = fe = fd = false;
	locus = 0;
}
BWeightedVector::BWeightedVector(DoublePointType h) : BVector(h) {
	weight = 0;
	error = 1;
	dist = 1;
	avg = 0;
	std = 1;
	fw = fe = fd = false;
	locus = 0;
}
BWeightedVector::BWeightedVector(FloatPointType h) : BVector(h) {
	weight = 0;
	error = 1;
	dist = 1;
	avg = 0;
	std = 1;
	fw = fe = fd = false;
	locus = 0;
}
BWeightedVector::BWeightedVector(IntegerPointType h) : BVector(h) {
	weight = 0;
	error = 1;
	dist = 1;
	avg = 0;
	std = 1;
	fw = fe = fd = false;
	locus = 0;
}
BWeightedVector::BWeightedVector(DoublePointType t, DoublePointType h): BVector(t, h) {
	weight = 0;
	error = 1;
	dist = 1;
	avg = 0;
	std = 1;
	fw = fe = fd = false;
	locus = 0;
}
BWeightedVector::BWeightedVector(FloatPointType t, FloatPointType h): BVector(t, h) {
	weight = 0;
	error = 1;
	dist = 1;
	avg = 0;
	std = 1;
	fw = fe = fd = false;
	locus = 0;
}
BWeightedVector::BWeightedVector(IntegerPointType t, IntegerPointType h): BVector(t, h) {
	weight = 0;
	error = 1;
	dist = 1;
	avg = 0;
	std = 1;
	fw = fe = fd = false;
	locus = 0;
}
BWeightedVector::~BWeightedVector() {
}
void BWeightedVector::resetTail() {
	tail = zeroPointDouble();
	length = -1;
}
void BWeightedVector::setTail(DoublePointType t) {
	tail = t;
	length = -1;
}
void BWeightedVector::setTail(FloatPointType t) {
	tail = floatToDouble(t);
	length = -1;
}
void BWeightedVector::setTail(IntegerPointType t) {
	tail = integerToDouble(t);
	length = -1;
}
void BWeightedVector::setHead(DoublePointType h) {
	head = h;
	length = -1;
}
void BWeightedVector::setHead(FloatPointType h) {
	head = floatToDouble(h);
	length = -1;
}
void BWeightedVector::setHead(IntegerPointType h) {
	head = integerToDouble(h);
	length = -1;
}

void BWeightedVector::setLocus(int l) {
	locus = l;
};
void BWeightedVector::setWeight(double w) {
	weight = w;
	fw = true;
	fe = false;
	fd = false;
};
double BWeightedVector::getWeight() {
	if (fw)
		return weight;
	if (fe)
		return (1-error);
	if (fd)
		return (1 - getNormalizedDistance());

	return weight;
};
void BWeightedVector::setState(double e) {
	error = e;
	fe = true;
	fw = false;
	fd = false;
};
double BWeightedVector::getState() {
	if (fe)
		return error;
	if (fd)
		return getNormalizedDistance();
	if (fw)
		return (1 - weight);

	return error;
};
void BWeightedVector::setDistance(double d, double a, double s) {
	dist = d;
	if (std == 0) {		// assumes normalization by the highest value
		avg = 0;
		if (a == 0)		// if Highest value = 0 assumes no normalization (divide by 1)
			std = 1;
		else
			std = a;	// puts highest value on the std (divisor)
	} else {			// assumes normalization with avg and std
		avg = a;		// saves avg
		if (a == 0)		// if avg = 0 assumes no normalization (divide by 1)
			std = 1;
		else
			std = s;	// saves std
	}
	fd = true;
	fw = false;
	fe = false;
};
double BWeightedVector::getDistance() {
	return dist;
};
double BWeightedVector::getNormalizedDistance() {
	if (fd) {
		if (avg != 0 || std != 1)
			return (dist - avg) / std;
		else
			return dist;
	}
	if (fe)
		return error;
	if (fw)
		return (1 - weight);

	if (avg != 0 || std != 1)
		return (dist - avg) / std;
	
	return dist;
};
BWeightedVector * BWeightedVector::clone() {
	BWeightedVector *nv = new BWeightedVector(tail, head);
	nv->weight = weight;
	nv->error = error;
	nv->dist = dist;
	nv->avg = avg;
	nv->std = std;
	nv->fw = fw;
	nv->fe = fe;
	nv->fd = fd;
	nv->locus = locus;

	return nv;
}
BWeightedVector BWeightedVector::copy() {
	BWeightedVector nv = BWeightedVector(tail, head);
	nv.weight = weight;
	nv.error = error;
	nv.dist = dist;
	nv.avg = avg;
	nv.std = std;
	nv.fw = fw;
	nv.fe = fe;
	nv.fd = fd;
	nv.locus = locus;

	return nv;
}

void BWeightedVector::print() {

#ifdef _BMESSAGES_H_
	BMessages::sprint("Tail:(%6.2f, %6.2f) --> Head:(%6.2f, %6.2f) ", tail.x, tail.y, head.x, head.y);
	if (fw) 
		BMessages::sprint("Weight:%6.3f  ", weight);
	if (fe) 
		BMessages::sprint("State:%6.3f  ", error);
	if (fd) 
		BMessages::sprint("Distance:%6.3f  Normalization(avg/std):(%6.3f/%6.3f)", dist, avg, std);
	BMessages::sprint("Locus:%d", locus);
	BMessages::sprint("\n");
#else
	printf("Tail:(%6.2f, %6.2f) --> Head:(%6.2f, %6.2f) ", tail.x, tail.y, head.x, head.y);
	if (fw) 
		printf("Weight:%6.3f  ", weight);
	if (fe) 
		printf("State:%6.3f  ", error);
	if (fd) 
		printf("Distance:%6.3f  Normalization(avg/std):(%6.3f/%6.3f)", dist, avg, std);
	printf("Locus:%d", locus);
	printf("\n");
#endif
}
#ifdef _BMESSAGES_H_
void BWeightedVector::print(BMessages * f) {

	f->print("Tail:(%6.2f, %6.2f) --> Head:(%6.2f, %6.2f) ", tail.x, tail.y, head.x, head.y);
	if (fw) 
		f->print("Weight:%6.3f  ", weight);
	if (fe) 
		f->print("State:%6.3f  ", error);
	if (fd) 
		f->print("Distance:%6.3f  Normalization(avg/std):(%6.3f/%6.3f)", dist, avg, std);
	f->print("Locus:%d", locus);
	f->print("\n");
}
#endif
void BWeightedVector::print(FILE * f) {

	fprintf(f, "Tail:(%6.2f, %6.2f) --> Head:(%6.2f, %6.2f) ", tail.x, tail.y, head.x, head.y);
	if (fw) 
		fprintf(f, "Weight:%6.3f  ", weight);
	if (fe) 
		fprintf(f, "State:%6.3f  ", error);
	if (fd) 
		fprintf(f, "Distance:%6.3f  Normalization(avg/std):(%6.3f/%6.3f)", dist, avg, std);
	fprintf(f, "Locus:%d", locus);
	fprintf(f, "\n");
}

void BWeightedVector::multiply(double c) {
	if (!atOrigin()) {
		BWeightedVector o = getOriginVector();
		setHead(DoublePointConstructor(tail.x + c * o.getHead().x, tail.y + c * o.getHead().y));
	} else 
		setHead(DoublePointConstructor(tail.x + c * head.x, tail.y + c * head.y));
}

BWeightedVector BWeightedVector::getOriginVector() {

	BWeightedVector nv = copy();
	nv.resetTail();
	nv.setHead(subtractPoints(head, tail));
	return nv;
}
void BWeightedVector::subtract(BWeightedVector v) {
	setTail(head);
	setHead(v.getHead());
}
void BWeightedVector::subtract(BWeightedVector *v) {
	setTail(head);
	setHead(v->getHead());
}
void BWeightedVector::add(BWeightedVector v) {
	if (pointsAreEqual(head, v.getTail())) 
		setHead(v.getHead());
	else {
		BWeightedVector o1 = getOriginVector();
		BWeightedVector o2 = v.getOriginVector();
		setHead(DoublePointConstructor(tail.x + o1.getHead().x + o2.getHead().x, tail.y + o1.getHead().y + o2.getHead().y));
	}
}
void BWeightedVector::add(BWeightedVector * v) {
	if (pointsAreEqual(head, v->getTail())) 
		setHead(v->getHead());
	else {
		BWeightedVector o1 = getOriginVector();
		BWeightedVector o2 = v->getOriginVector();
		setHead(DoublePointConstructor(tail.x + o1.getHead().x + o2.getHead().x, tail.y + o1.getHead().y + o2.getHead().y));
	}
}


BVector convert(BWeightedVector v) {
	return BVector(v.getTail(), v.getHead());
}
BWeightedVector convert(BVector v) {
	return BWeightedVector(v.getTail(), v.getHead());
}
BVector * convert(BWeightedVector *v) {
	return new BVector(v->getTail(), v->getHead());
}
BWeightedVector * convert(BVector *v) {
	return new BWeightedVector(v->getTail(), v->getHead());
}
