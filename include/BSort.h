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

#if !defined(_BSORT_H_)
#define _BSORT_H_

/// Function that exchange two variables, used in sort functions
#define SWAP(x, y, z) {(z) = (x); (x) = (y); (y) = (z);}
#define LT(x, y) ((x) < (y))								///< Comparison function
#define GT(x, y) ((x) > (y))								///< Comparison function
#define EQ(x, y) ((x) == (y))								///< Comparison function

template <class T> bool greater(T x, T y) { return GT(x,y);};
template <class T> bool greater(T *x, T *y) { return x->operator>(y);};
template <class T> bool lesser(T x, T y) { return LT(x,y);};
template <class T> bool lesser(T *x, T *y) { return x->operator<(y);};
template <class T> bool equal(T x, T y) { return EQ(x,y);};
template <class T> bool equal(T *x, T *y) { return x->operator==(y);};

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define ASCENDINGORDER      true
#define DESCENDINGORDER     false


/// Function that sorts a vector using a quicksort algorithm
template <class T> void	quickSort(T * vec,	///< [in] Vector to be sorted
								  int ind1,	///< [in] Index of the first element
								  int ind2,	///< [in] Index of the last element
								  bool asc = ASCENDINGORDER ///< [in] (optional) Order of sorting. Default is Ascending order.
								  );
/// Function that sorts a vector using a bublesort algorithm
template <class T> void	bubleSort(T * vec,	///< [in] Vector to be sorted
								  int n,	///< [in] Number of elementselement
								  bool asc = ASCENDINGORDER ///< [in] (optional) Order of sorting. Default is Ascending order.
								  );

template <class T> void quickSort(T * vec, int lower, int upper, bool asc) {
	int
		i,
		m;
	T
		temp,
		pivot;

	if (lower < upper) {
		SWAP(vec[lower], vec[(upper+lower)/2], temp);
		pivot = vec[lower];
		m = lower;
		for (i = lower + 1; i <= upper; i++) {
			if (asc && lesser(vec[i], pivot) || !asc && greater(vec[i], pivot)) {
				m++;
				SWAP(vec[m], vec[i], temp);
			}
		}
		SWAP(vec[lower], vec[m], temp);
		quickSort (vec, lower, m - 1, asc);
		quickSort (vec, m + 1, upper, asc);
	}
}
template <class T> void bubbleSort(T * vec, int n, bool asc) {

	bool t = true;
	int i;
	T temp;

	while (t) {
		t = false;
		for (i=0; i < n-1; i++) {
			if (lesser(vec[i], vec[i+1])) {
				SWAP(vec[i], vec[i+1], temp);
				t = true;
			}
		}
	}
}

#define SELECTPREVIOUS -1
#define SELECTEQUAL     0
#define SELECTNEXT      1

//template <class T> int binarySearch(T value, T * vec, int lower, int upper, bool asc, int which) {
//
//	int pivot;
//
//	if (asc && lesser(value,vec[lower]))
//		if (which == SELECTNEXT)
//			return lower;
//		else if (which == SELECTPREVIOUS)
//			return -1;
//	if (asc && equal(value,vec[lower]))
//		if (which == SELECTNEXT)
//			return lower+1;
//		else if (which == SELECTPREVIOUS)
//			return -1;
//		else
//			return lower;
//	if (asc && equal(value,vec[upper]))
//		if (which == SELECTNEXT)
//			return -1;
//		else if (which == SELECTPREVIOUS)
//			return upper - 1;
//		else
//			return upper;
//
//	while (true) {
//		pivot = lower + (upper - lower) / 2.0;
//		if (lower == pivot)
//			if (which == SELECTEQUAL)
//				return -1;
//			else if (asc && which == SELECTNEXT || !asc && which == SELECTPREVIOUS)
//				return pivot+1;
//			else
//				return pivot;
//
//		printf("value=%lf vec[lower=%d]=%lf vec[upper=%d]=%lf vec[pivot=%d]=%lf\n", value, lower, vec[lower], upper, vec[upper], pivot, vec[pivot]);
//		if (asc && lesser(value,vec[pivot]) || !asc && greater(value,vec[pivot]))
//			upper = pivot;
//		else if (asc && greater(value,vec[pivot]) || !asc && lesser(value,vec[pivot]))
//			lower = pivot;
//		else if (asc)
//			if (which == SELECTEQUAL)
//				return pivot;
//			else if (which == SELECTNEXT)
//				return pivot+1;
//			else
//				return pivot-1;
//	}
//};
template <class T> int binarySearch(T value, T * vec, int lower, int upper, bool asc) {

	if (asc && (lesser(value,vec[lower])  || greater(value,vec[upper])) ||
		!asc && (greater(value,vec[lower])  || lesser(value,vec[upper])))
		return -1;
	if (equal(value,vec[lower]))
		return lower;
	else if (equal(value,vec[upper]))
		return upper;
	int pivot;
	while (lower < upper - 1) {
		if (asc)
			pivot = lower + (upper -lower)/2;
		else
			pivot = lower + (upper - lower +1)/2;
//		printf("value=%lf vec[lower=%d]=%lf vec[upper=%d]=%lf vec[pivot=%d]=%lf\n", value, lower, vec[lower], upper, vec[upper], pivot, vec[pivot]);
//		printf("value=%d vec[lower=%d]=%d vec[upper=%d]=%d vec[pivot=%d]=%d\n", value, lower, vec[lower], upper, vec[upper], pivot, vec[pivot]);
		if (asc && lesser(value,vec[pivot]) || !asc && greater(value,vec[pivot]))
			upper = pivot;
		else if (asc && greater(value,vec[pivot]) || !asc && lesser(value,vec[pivot]))
			lower = pivot;
		else
			return pivot;
	}

	return -1;

};
template <class T> int linearSearch(T value, T * vec, int lower, int upper, bool asc) {

	if (asc && (lesser(value,vec[lower])  || greater(value,vec[upper])) ||
		!asc && (greater(value,vec[lower])  || lesser(value,vec[upper])))
		return -1;
	if (equal(value,vec[lower]))
		return lower;
	else if (equal(value,vec[upper]))
		return upper;
	int pivot;
	for (int i=lower; i < upper; i++) {
//		printf("value=%lf vec[lower=%d]=%lf vec[upper=%d]=%lf vec[i=%d]=%lf\n", value, lower, vec[lower], upper, vec[upper], i, vec[i]);
//		printf("value=%d vec[lower=%d]=%d vec[upper=%d]=%d vec[i=%d]=%d\n", value, lower, vec[lower], upper, vec[upper], i, vec[i]);
		if (equal(value,vec[i]))
			return i;
		else if (asc && lesser(value,vec[i]) || !asc && greater(value,vec[i]))
			break;
	}

	return -1;

};
template <class T> bool linearIntervalSearch(T value, T * vec, int &lower, int &upper, bool asc) {

//    printf(">> Entering linearIntervalSearch ::: value=%lf vec[lower=%d]=%lf vec[upper=%d]=%lf\n", value, lower, vec[lower], upper, vec[upper]);

	if (asc && (lesser(value,vec[lower])  || greater(value,vec[upper])) ||
		!asc && (greater(value,vec[lower])  || lesser(value,vec[upper])))
		return false;

 	if (equal(value,vec[lower])) {
		upper = lower+1;
		return true;
	} else if (equal(value,vec[upper])) {
		lower =  upper -1;
		return true;
	};
	int pivot;
	int i = lower;
	while (i<upper) {
//		printf("value=%lf vec[lower=%d]=%lf vec[upper=%d]=%lf vec[i=%d]=%lf\n", value, lower, vec[lower], upper, vec[upper], i, vec[i]);
//		printf("value=%d vec[lower=%d]=%d vec[upper=%d]=%d vec[i=%d]=%d\n", value, lower, vec[lower], upper, vec[upper], i, vec[i]);
		if (equal(value,vec[i]))
			return true;
		else if (asc && lesser(value,vec[i+1]) || !asc && greater(value,vec[i+1])){
			lower=i;
			upper=i+1;
			return true;
		} else
			i++;
	}

	return false;

};

template <class T> int binaryIntervalSearch(T value, T * vec, int lower, int upper, bool & outofbounds, bool asc) {

	outofbounds = false;
	if (asc && (lesser(value,vec[lower]) || greater(value,vec[upper])) ||
		!asc && (greater(value,vec[lower]) || lesser(value,vec[upper]))) {
		outofbounds = true;
		return -1;
	};
	int pivot = -1;
	while (lower != pivot) {
		if (asc)
			pivot = lower + (upper -lower)/2;
		else
			pivot = lower + (upper - lower +1)/2;
//		printf("value=%lf vec[lower=%d]=%lf vec[upper=%d]=%lf vec[pivot=%d]=%lf\n", value, lower, vec[lower], upper, vec[upper], pivot, vec[pivot]);
		printf("value=%d vec[lower=%d]=%d vec[upper=%d]=%d vec[pivot=%d]=%d\n", value, lower, vec[lower], upper, vec[upper], pivot, vec[pivot]);
		if (asc && lesser(value,vec[pivot]) || !asc && greater(value,vec[pivot]))
			upper = pivot;
		else if (asc && greater(value,vec[pivot]) || !asc && lesser(value,vec[pivot]))
			lower = pivot;
		else
			return pivot;
	}

	return -1;

};



#endif
