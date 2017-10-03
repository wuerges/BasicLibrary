#if !defined(_BSTATISTICS_H_)
#define _BSTATISTICS_H_

//#ifdef _WIN32
#include <time.h>
//#endif // _WIN32

#include <stdio.h>
#include "BTree.h"
//#include "intrin.h"
#include "BFile.h"

#ifdef _WIN32
#include <windows.h>
#endif

#if !defined (MAXTEXTLENGTH)
#define MAXTEXTLENGTH 6144
#endif

char * timeToString(time_t);
char * clocksToTime(clock_t);


class BTimeObject {
public:
	BTimeObject(char *);
	~BTimeObject();
#ifdef _WIN32
	LARGE_INTEGER * start();
	LARGE_INTEGER * stop();
	LONGLONG getElapsedTime() { return tsum->QuadPart;};
#else
	clock_t start();
	clock_t stop();
	clock_t getElapsedTime() { return tsum;};
#endif
	void print(FILE *, int = 0);
	void printName(FILE *, int = 0);
	void printStatistics(FILE *, int = 0);
	char * getName();
	static char * getName(BTimeObject *);
	bool hasLoop() { return loop;};
	void setLoop() { loop = true;};
	void setMissing(char * mname);
	BTimeObject * clone();
	BTimeObject * copy() { return clone();};
#ifdef _WIN32
    LARGE_INTEGER getTotal();
#else
    clock_t getTotal() { return tsum; };
#endif

protected:
	bool init;
#ifdef _WIN32
	LARGE_INTEGER
		* tfirst,
		* tstart,
		* tstop,
		* tlast,
		* tsum,
		* diff,
		* tickspersec;
#else
	clock_t
		tfirst,
		tstart,
		tstop,
		tlast,
		tsum,
		diff;
#endif
	char * name;
	int n, n0;
	bool loop;
	bool missing;
	char *misname;
};

class BTimeStatistics {
public:
	BTimeStatistics(char *);
	~BTimeStatistics();
	void startBTimeObject(char*);
	void stopBTimeObject(char*);

	void report();
#ifdef _WIN32
    LARGE_INTEGER getTotalBTimeObject(char *);
#else
    clock_t getTotalBTimeObject(char *);
#endif


protected:
	bool
		init;

	FILE * log;
	char * filename;
	bool fileok;

	clock_t
		tickspersec;

	BTreeNode<BTimeObject*> * tobj;
	BTreeNode<BTimeObject*> * current;

	BTimeObject overhead;

	void printReport(int, BTreeNode<BTimeObject*> *);
	BTreeNode<BTimeObject*> * getChildBTimeObject(char *);
	BTreeNode<BTimeObject*> * getSiblingBTimeObject(char *);
	BTreeNode<BTimeObject*> * getParentBTimeObject(char *);

	char * getTopName(BTreeNode<BTimeObject*> *);

};

#ifdef _WIN32
char * ticksToTime(LONGLONG, LONGLONG);
#endif

#endif // !defined(_BOUNDINGBOX_)
