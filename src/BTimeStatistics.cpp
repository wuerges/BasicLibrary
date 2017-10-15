#include "BTimeStatistics.h"
#pragma warning( once : 4996 )

BTimeObject::BTimeObject(char * nm) : name(NULL) {

	name = NULL;
	init = false;

	if (nm != NULL) {
		name = new char [strlen(nm) + 1];
		strcpy(name, nm);
	}

	n = n0 = 0;

	loop = false;
	missing = false;
	misname = NULL;

#ifdef _WIN32
	tfirst = new LARGE_INTEGER;
	tstart = new LARGE_INTEGER;
	tstop = new LARGE_INTEGER;
	tlast = new LARGE_INTEGER;
	tsum = new LARGE_INTEGER;
	diff = new LARGE_INTEGER;
	tickspersec = new LARGE_INTEGER;
	QueryPerformanceFrequency(tickspersec);
	tsum->QuadPart = 0;
#else
	tsum = 0;
#endif

}
BTimeObject * BTimeObject::clone() {

	BTimeObject * obj = new BTimeObject (name);

	obj->init = init;
	obj->n = n;
	obj->n0 = n0;
	obj->loop = loop;
	obj->missing = missing;
	obj->misname = ::clone(misname);

#ifdef _WIN32
	*(obj->tfirst) = *tfirst;
	*(obj->tstart) = *tstart;
	*(obj->tstop) = *tstop;
	*(obj->tlast) = *tlast;
	*(obj->tsum) = *tsum;
	*(obj->diff) = *diff;
	*(obj->tickspersec) = *tickspersec;
	QueryPerformanceFrequency(obj->tickspersec);
	obj->tsum->QuadPart = tsum->QuadPart;
#else
	obj->tfirst = tfirst;
	obj->tstart = tstart;
	obj->tstop = tstop;
	obj->tlast = tlast;
	obj->tsum = tsum;
	obj->diff = diff;
	obj->tsum = tsum;
#endif

	return obj;

}

BTimeObject::~BTimeObject() {

	if (name != NULL)
		delete [] name;
	if (misname != NULL)
		delete [] misname;

#ifdef _WIN32
	delete tfirst;
	delete tstart;
	delete tstop;
	delete tlast;
	delete tsum;
	delete diff;
	delete tickspersec;
#endif
}

#ifdef _WIN32
LARGE_INTEGER * BTimeObject::start() {

	QueryPerformanceCounter(tstart);

	if (!init) {
		*tfirst = *tstart;
		init = true;
	}

	return tstart;
}
#else
clock_t BTimeObject::start() {

	tstart = clock();

	if (!init) {
		tfirst = tstart;
		init = true;
	}

	return tstart;
}
#endif
#ifdef _WIN32
LARGE_INTEGER * BTimeObject::stop() {

	if (!init)
		return NULL;

	QueryPerformanceCounter(tstop);
	*tlast = *tstop;
	n++;
	diff->QuadPart = (tstop->QuadPart - tstart->QuadPart);
	if (diff->QuadPart == 0)
		n0++;
	else
		tsum->QuadPart += diff->QuadPart;
	return tstop;
}
#else
clock_t BTimeObject::stop() {

	if (!init)
		return 0;

	tstop = clock();
	tlast = tstop;
	n++;
	diff = (tstop - tstart);
	if (diff == 0)
		n0++;
	else
		tsum += diff;
	return tstop;
}
#endif
void BTimeObject::print(FILE *log, int t) {

	if (!init)
		return;

#ifdef _WIN32
	char * str1 = ticksToTime(tsum->QuadPart, tickspersec->QuadPart);
	char * str2 = NULL;
	if (n != 0)
		str2 = ticksToTime(tsum->QuadPart / n, tickspersec->QuadPart);
	else
		str2 = ticksToTime(tsum->QuadPart, tickspersec->QuadPart);
#else
	char * str1 = clocksToTime(tsum);
	char * str2 = NULL;
	if (n != 0)
		str2 = clocksToTime(tsum / n);
	else
		str2 = clocksToTime(tsum);
#endif
	int i;
	for (i = 0; i < t; i++)
		fprintf(log, "|\t");
	fprintf(log,"Statistics: %s\n", name);
	for (i = 0; i < t; i++)
		fprintf(log, "|\t");
	//fprintf(log, "|______ ");
	fprintf(log,"Elapsed Time:%s\n", str1);
	for (i = 0; i < t; i++)
		fprintf(log, "|\t");
	//fprintf(log, "\t");
	fprintf(log,"Average Time:%s\n", str2);
	for (i = 0; i < t; i++)
		fprintf(log, "|\t");
	//fprintf(log, "\t");
	fprintf(log,"Executions: %d\n", n);
	if (n0 != 0 || loop || missing) {
		for (i = 0; i < t; i++)
			fprintf(log, "|\t");
		fprintf(log,">>>>> WARNINGS:");
		if (loop) {
			fprintf(log,"> This Time counter is recursive, this will result in wrong time values\n");
			if (n0 != 0 || missing)
				for (i = 0; i < t; i++)
					fprintf(log, "|\t");
		}
		if (missing) {
			fprintf(log,"> This Time counter has missing sub conters stops, this will result in wrong time values\n");
			for (i = 0; i < t; i++)
				fprintf(log, "|\t");
			fprintf(log,"                 Missing stops: %s\n", misname);
			if (n0 != 0)
				for (i = 0; i < t; i++)
					fprintf(log, "|\t");
		}
		if (n0 != 0)
			fprintf(log,"               > %d zero-ticks executions detected (%6.2f%% of executions)\n", n0, (double)n0/n * 100);
	}
	for (i = 0; i < t; i++)
		fprintf(log, "|\t");
	fprintf(log, "\n");


	delete [] str1;
	delete [] str2;
}

void BTimeObject::setMissing(char * mname) {
	missing = true;
	bool first = false;
	if (misname == NULL) {
		misname = new char[MAXTEXTLENGTH];
		strcpy(misname,"");
		first = true;
	}
	char * p = strstr(misname, mname);
	if (p == NULL && strlen(misname) + strlen(mname) + 3 < MAXTEXTLENGTH) {
		if (!first)
			strcat(misname, " + ");
		strcat(misname,mname);
	}
};

void BTimeObject::printStatistics(FILE *log, int t) {

	if (!init)
		return;

#ifdef _WIN32
	char * str1 = ticksToTime(tsum->QuadPart, tickspersec->QuadPart);
	char * str2 = NULL;
	if (n != 0)
		str2 = ticksToTime(tsum->QuadPart / n, tickspersec->QuadPart);
	else
		str2 = ticksToTime(tsum->QuadPart, tickspersec->QuadPart);
#else
	char * str1 = clocksToTime(tsum);
	char * str2 = NULL;
	if (n != 0)
		str2 = clocksToTime(tsum / n);
	else
		str2 = clocksToTime(tsum);
#endif
	int i;
	for (i = 0; i < t; i++)
		fprintf(log, "|\t");
	//fprintf(log, "|______ ");
	fprintf(log,"Elapsed Time:%s\n", str1);
	for (i = 0; i < t; i++)
		fprintf(log, "|\t");
	//fprintf(log, "\t");
	fprintf(log,"Average Time:%s\n", str2);
	for (i = 0; i < t; i++)
		fprintf(log, "|\t");
	//fprintf(log, "\t");
	fprintf(log,"Executions: %d\n", n);
	if (n0 != 0 || loop) {
		for (i = 0; i < t; i++)
			fprintf(log, "|\t");
		fprintf(log,">>>>> WARNINGS:");
		if (loop) {
			fprintf(log,"- This Time counter is recursive, this will result in wrong time values\n");
			for (i = 0; i < t; i++)
				fprintf(log, "|\t");
			fprintf(log,"                 This may be caused by a recursive start or a missing stop\n");
			if (n0 != 0)
				for (i = 0; i < t; i++)
					fprintf(log, "|\t");
		}
		if (n0 != 0)
			fprintf(log,"               - %d zero-ticks executions detected (%6.2f%% of executions)\n", n0, (double)n0/n * 100);
	}
	for (i = 0; i < t; i++)
		fprintf(log, "|\t");
	fprintf(log, "\n");

	delete [] str1;
	delete [] str2;
}
void BTimeObject::printName(FILE *log, int t) {

	if (!init)
		return;

	for (int i = 0; i < t; i++)
		fprintf(log, "|\t");
	fprintf(log,"Statistics: %s\n", name);
}
#ifdef _WIN32
char * ticksToTime(LONGLONG tm, LONGLONG tickspersec)
{

	char * str = new char[24];

	long int
		mis,
		ms,
		s,
		m,
		h;

	long double aux = tm / ((long double)tickspersec / 1000);
	long double aux1 = aux - (long int)aux;
	mis = (long int)(aux1 * 1000);
	ms = (long int)aux;
	s = ms / 1000;
	m = s / 60;
	h = m / 60;
	ms = ms % 1000;
	s = s % 60;
	m = m % 60;

	sprintf(str,"%02d:%02d:%02d:%03d:%03d", h, m, s, ms, mis);

	return str;

}
#endif
char * BTimeObject::getName() {

	return name;
}
char * BTimeObject::getName( BTimeObject * obj) {

	if (obj != NULL)
		return obj->getName();

	return NULL;
}

char * clocksToTime(clock_t tm) {

	char * str = new char[64];

	long int ms,
		s,
		m,
		h, cks;

	ms = (long long)tm * 1000 / CLOCKS_PER_SEC;
	s = ms / 1000;
	m = s / 60;
	h = m / 60;
	ms = ms % 1000;
	s = s % 60;
	m = m % 60;
	cks = (long int)tm;


    sprintf(str,"%02ld:%02ld:%02ld:%03ld (%ld cliks)", h, m, s, ms, cks);

	return str;

}
char * timeToString(tm * t) {

	char * str = new char[20];

	sprintf(str,"%03d_%02d_%02d_%02d", t->tm_yday, t->tm_hour, t->tm_min, t->tm_sec);

	return str;

}

BTimeStatistics::BTimeStatistics(char * name): overhead(NULL)  {


	overhead.start();

	init = false;

	filename = NULL;
	fileok = false;
	char * timestr = NULL;

	if (name != NULL) {
		filename = new char [strlen(name) + 18];
		time_t t = time(NULL);
		timestr = timeToString(localtime(&t));
		sprintf(filename, "%s_%s.txt", name, timestr);
		delete [] timestr;
		char * path = getFullPath(filename);
		if (!existPath(path))
			createDirectory(filename);
		log = fopen(filename, "w");
		delete [] path;
		if (log != NULL) {
			fileok = true;
			printf("BTimeStatistics: File %s opened.\n", filename);
		}
	}
	if (!fileok)
		log = stdout;

	tobj = new BTreeNode<BTimeObject*>(NULL);
	current = tobj;



#ifdef _WIN32
	tickspersec = new LARGE_INTEGER;
	QueryPerformanceFrequency(tickspersec);
#else
	tickspersec = CLOCKS_PER_SEC;
#endif

	overhead.stop();

}



BTimeStatistics::~BTimeStatistics(){
	BTreeNode<BTimeObject*>::remove(tobj);
	if (filename != NULL)
		delete [] filename;
}
BTreeNode<BTimeObject*> * BTimeStatistics::getChildBTimeObject(char* ton) {

	BTreeNode<BTimeObject*> * pt = current->getFirstChild();
	//char * name;
    //if (pt != NULL)
    //    name = pt->getData()->getName();
	while (pt != NULL && strcmp(pt->getData()->getName(), ton) != 0) {
        //if (pt != NULL)
        //    name = pt->getData()->getName();
		pt = current->getNextChild();
    }

	return pt;
}
BTreeNode<BTimeObject*> * BTimeStatistics::getSiblingBTimeObject(char* ton) {

	if (current->isRoot())
		return NULL;

	BTreeNode<BTimeObject*> * curpar = current->getParent();
	BTreeNode<BTimeObject*> * pt = curpar->getFirstChild();
	while (pt != NULL && strcmp(pt->getData()->getName(), ton) != 0)
		pt = curpar->getNextChild();

	return pt;

}
BTreeNode<BTimeObject*> * BTimeStatistics::getParentBTimeObject(char* ton) {

	if (current->isRoot())
		return NULL;

	BTreeNode<BTimeObject*> * pt = current->getParent();
	while (!pt->isRoot() && strcmp(pt->getData()->getName(), ton) != 0)
		pt = pt->getParent();

	if (pt->isRoot())
		return NULL;

	return pt;

}


void BTimeStatistics::startBTimeObject(char* ton) {

	overhead.start();

	BTreeNode<BTimeObject*> * ptto = getChildBTimeObject(ton);
	if (ptto == NULL) {
		ptto = getParentBTimeObject(ton);
		if (ptto == NULL) {
			BTimeObject * po = new BTimeObject(ton);
			current = current->addChild(po);
		} else if (!ptto->getData()->hasLoop())
				ptto->getData()->setLoop();
	} else
		current = ptto;

	current->getData()->start();

	overhead.stop();
}
void BTimeStatistics::stopBTimeObject(char* ton) {

	if (current == tobj)
		return;

	overhead.start();

	current->getData()->stop();
	BTreeNode<BTimeObject*> * node = current;
	current = current->getParent();
	if (strcmp(node->getData()->getName(), ton) == 0) {
		overhead.stop();
		return;
	}

	//stopBTimeObject(ton);

	node->getData()->setMissing(ton);

	overhead.stop();
}

clock_t BTimeStatistics::getTotalBTimeObject(char* ton) {

	overhead.start();

	BTreeNode<BTimeObject*> * ptto = getChildBTimeObject(ton);
	if (ptto == NULL)
	    return 0;

	clock_t val = ptto->getData()->getTotal();

	overhead.stop();

	return val;
}

void BTimeStatistics::report() {

	BTreeNode<BTimeObject*> * pt = tobj->getFirstChild();
	while (pt != NULL) {
		printReport(0, pt);
		pt = tobj->getNextChild();
	}


#ifdef _WIN32
	LONGLONG et = overhead.getElapsedTime();
	char * str1 = ticksToTime(et, tickspersec->QuadPart);
	et = 2 * et;
	char * str2 = ticksToTime(et, tickspersec->QuadPart);
#else
	clock_t et = overhead.getElapsedTime();
	char * str1 = clocksToTime(et);
	et = 2 * et;
	char * str2 = clocksToTime(et);
#endif
	fprintf(log, "Time Statistics overhead: from %s up to %s\n", str1, str2);
	delete [] str1;
	delete [] str2;
}
void BTimeStatistics::printReport(int n, BTreeNode<BTimeObject*> * p) {

	if (p->isLeaf()) {
		p->getData()->print(log, n);
		return;
	}

	p->getData()->printName(log, n);

	BTreeNode<BTimeObject*> * pc = p->getFirstChild();
	while (pc != NULL) {
		printReport(n+1, pc);
		pc = p->getNextChild();
	}

	p->getData()->printStatistics(log, n);
	return;
}

char * BTimeStatistics::getTopName( BTreeNode<BTimeObject*>  * obj) {

	if (obj != NULL)
		return BTimeObject::getName(obj->getData());

	return "NULL";
}




