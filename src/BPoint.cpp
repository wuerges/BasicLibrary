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

#include "BPoint.h"

BIntegerPoint::BIntegerPoint() {
	x = 0;
	y = 0;
}
BIntegerPoint::BIntegerPoint(int a, int b) {
	x = a;
	y = b;
}
BIntegerPoint::~BIntegerPoint() {
}
int BIntegerPoint::getX() {
	return x;
}
int BIntegerPoint::getY() {
	return y;
}
bool BIntegerPoint::setPoint(int a, int b) {
	x = a;
	y = b;
	return true;
}
BIntegerPoint * BIntegerPoint::clone() {

	BIntegerPoint * p = new BIntegerPoint(x, y);
	return p;
}
BFloatPoint::BFloatPoint() {
	x = 0;
	y = 0;
}
BFloatPoint::BFloatPoint(float a, float b) {
	x = a;
	y = b;
}
BFloatPoint::~BFloatPoint() {
}
float BFloatPoint::getX() {
	return x;
}
float BFloatPoint::getY() {
	return y;
}
bool BFloatPoint::setPoint(float a, float b) {
	x = a;
	y = b;
	return true;
}
BFloatPoint * BFloatPoint::clone() {

	BFloatPoint * p = new BFloatPoint(x, y);
	return p;
}
BDoublePoint::BDoublePoint() {
	x = 0;
	y = 0;
}
BDoublePoint::BDoublePoint(double a, double b) {
	x = a;
	y = b;
}
BDoublePoint::~BDoublePoint() {
}
double BDoublePoint::getX() {
	return x;
}
double BDoublePoint::getY() {
	return y;
}
bool BDoublePoint::setPoint(double a, double b) {
	x = a;
	y = b;
	return true;
}
BDoublePoint * BDoublePoint::clone() {

	BDoublePoint * p = new BDoublePoint(x, y);
	return p;
}


double slopePoints(DoublePointType p1, DoublePointType p2) {
	if (p1.x == p2.x)
		return (p1.y - p2.y) / SMALLVALUEDIFFERENTFROMZERO;
	else
		return (p1.y - p2.y) / (p1.x - p2.x);
}
//#if !defined (_POINTDOUBLE_)
//double slopePoints(PointType p1, PointType p2) {
//	if (p1.x == p2.x)
//		return (p1.y - p2.y) / SMALLVALUEDIFFERENTFROMZERO;
//	else
//		return (p1.y - p2.y) / (p1.x - p2.x);
//}
//#endif

PointType  absoluteCoordinates(PointType p) {
	if (p.x < 0)
		p.x = p.x * -1;
	if (p.y < 0)
		p.y = p.y * -1;

	return p;
}
#if defined (_POINTFLOAT_)
List<PointType> * convertFromFloat(List<FloatPointType> * l1) {
	return l1;
}
#elif defined (_POINTINTEGER_)
List<PointType> * convertFromFloat(List<FloatPointType> * l1) {
	List<PointType> * l2 = new List<PointType>;
	FloatPointType * p1 = l1->getFirst();
	PointType * p2;
	while (p1 != NULL) {
		p2 = new PointType;
		p2->x = round(p1->x);
		p2->y = round(p1->y);
		l2->add(p2);
		p1 = l1->getNext();
	}
	return l2;
}
#elif defined (_BLIST_H_)
List<PointType> * convertFromFloat(List<FloatPointType> * l1) {
	List<PointType> * l2 = new List<PointType>;
	FloatPointType * p1 = l1->getFirst();
	PointType * p2;
	while (p1 != NULL) {
		p2 = new PointType;
		p2->x = p1->x;
		p2->y = p1->y;
		l2->add(p2);
		p1 = l1->getNext();
	}
	return l2;
}
#endif
