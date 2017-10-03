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

#include "BState.h"

#pragma warning( once : 4018 )
#pragma warning( once : 4996 )
#pragma warning( once : 4244 )


BState::BState(): maxstates(0), maxobjs(0), statedefno(BSTATENUMBEROFDEFAULTSTATES),
                  objdefno(1), curobj(0), objcurstate(NULL), objdesc(NULL), statedesc(NULL) {
	maxstates = 1 << BSTATENUMBEROFDIGITSFORERRORS;
	maxobjs = maxstates;
	objcurstate = new unsigned int [maxobjs];
	objdesc = new char * [maxobjs];
	statedesc = new char * [maxstates];
	for (int i = 0; i < maxstates; i++) {
		objcurstate[i] = BSTATEOK;
		statedesc[i] = NULL;
		objdesc[i] = NULL;
	}
	objdesc[BSTATEDEFAULTOBJECT] = new char [strlen(BSTATEDEFAULTOBJECTDESCRIPTION)+1];
	strcpy(objdesc[BSTATEDEFAULTOBJECT], BSTATEDEFAULTOBJECTDESCRIPTION);
	statedesc[BSTATEOK] = new char [strlen(BSTATEOKDESCRIPTION)+1];
	strcpy(statedesc[BSTATEOK], BSTATEOKDESCRIPTION);
	statedesc[BSTATEUNKOWNERROR] = new char [strlen(BSTATEUNKOWNERRORDESCRIPTION)+1];
	strcpy(statedesc[BSTATEUNKOWNERROR], BSTATEUNKOWNERRORDESCRIPTION);
	statedesc[BSTATEUNEXPECTEDERROR] = new char [strlen(BSTATEUNEXPECTEDERRORDESCRIPTION)+1];
	strcpy(statedesc[BSTATEUNEXPECTEDERROR], BSTATEUNEXPECTEDERRORDESCRIPTION);
	statedesc[BSTATEERRORINVALIDINPUT] = new char [strlen(BSTATEERRORINVALIDINPUTDESCRIPTION)+1];
	strcpy(statedesc[BSTATEERRORINVALIDINPUT], BSTATEERRORINVALIDINPUTDESCRIPTION);
	statedesc[BSTATEERRORMAXOBJECTS] = new char [strlen(BSTATEERRORMAXOBJECTSDESCRIPTION)+1];
	strcpy(statedesc[BSTATEERRORMAXOBJECTS], BSTATEERRORMAXOBJECTSDESCRIPTION);
	statedesc[BSTATEERRORMAXSTATES] = new char [strlen(BSTATEERRORMAXSTATESDESCRIPTION)+1];
	strcpy(statedesc[BSTATEERRORMAXSTATES], BSTATEERRORMAXSTATESDESCRIPTION);

	curobj = BSTATEDEFAULTOBJECT;
}
BState::~BState() {
	int i;
	for (i = 0; i < maxstates; i++) {
		if (statedesc[i] != NULL)
			delete [] statedesc[i];
		if (objdesc[i] != NULL)
			delete [] objdesc[i];
	}
	delete [] statedesc;
	delete [] objdesc;
	delete [] objcurstate;
}
int BState::defineObject(char * text) {
	if (objdefno >= maxobjs) {
		objcurstate[BSTATEDEFAULTOBJECT] = BSTATEERRORMAXOBJECTS;
		return BSTATEDEFAULTOBJECT;
	}
	curobj = objdefno;
	objdefno++;
	if (text != NULL) {
		objdesc[curobj] = new char [strlen(text)+1];
		strcpy(objdesc[curobj], text);
	}
	return curobj;
}
int BState::defineState(char * text) {
	if (statedefno >= maxstates) {
		objcurstate[curobj] = BSTATEERRORMAXSTATES;
		return BSTATEERRORMAXSTATES;
	}
	int curstate = statedefno;
	statedefno++;
	if (text != NULL) {
		statedesc[curstate] = new char [strlen(text)+1];
		strcpy(statedesc[curstate], text);

	}
	return curstate;
}
bool BState::setState(int objid, int stateno) {
	if (objid >= objdefno) {
		objcurstate[BSTATEDEFAULTOBJECT] = BSTATEERRORINVALIDINPUT;
		return false;
	}
	curobj = objid;
	return setState(stateno);
}
bool BState::setState(int stateno) {
	if (stateno >= statedefno) {
		objcurstate[curobj] = BSTATEERRORINVALIDINPUT;
		return false;
	}
	objcurstate[curobj] = stateno;
	return true;
}
int BState::getState(int objid) {
	if (objid >= objdefno) {
		objcurstate[BSTATEDEFAULTOBJECT] = BSTATEERRORINVALIDINPUT;
		return BSTATEERRORINVALIDINPUT;
	}
	curobj = objid;
	return getState();
}
char *  BState::getStateDescription(int stateno) {
	if (stateno >= statedefno) {
		objcurstate[curobj] = BSTATEERRORINVALIDINPUT;
		return NULL;
	}
	if (statedesc[stateno] == NULL)
		return "No Description Available";

	return statedesc[stateno];
}
char *  BState::getObjectDescription(int objid) {
	if (objid >= objdefno) {
		objcurstate[curobj] = BSTATEERRORINVALIDINPUT;
		return NULL;
	}
	curobj = objid;
	if (objdesc[curobj] == NULL)
		return "No Description Available";

	return objdesc[curobj];
}
void BState::printDefinitions(char * name, int t) { printDefinitions(NULL, name, t);};
void BState::printDefinitions(FILE * f, char * name, int t) {

	if (t < 0) t = 0;
	char *strtab = new char [t+1];

	strtab[0] = '\0';
	for (int i=0; i < t; i++) strtab[i] = '\t';
	strtab[t] = '\0';
	

	FILE * file = f == NULL ? stderr : f;

	fprintf(file,"\n%sStates Definitions: ",strtab); 
	if (name != NULL)
		fprintf(file,"%s", name);
	fprintf(file,"\t{\n\n");
	fprintf(file,"%s\tObjects List:\t{\n",strtab);
	int i;
	for (i = 0; i < objdefno; i++)
		fprintf(file,"%s\t\t%4d:%s\n",strtab, i, getObjectDescription(i));
	fprintf(file,"%s\t}\n",strtab);
	fprintf(file,"\n%s\tStates List:\t{\n",strtab);
	for (i = 0; i < statedefno; i++)
		fprintf(file,"%s\t\t%4d:%s\n",strtab, i, getStateDescription(i));
	fprintf(file,"%s\t}\n",strtab);
	fprintf(file,"%s}\n",strtab);
	delete [] strtab;
}
void BState::printObjectStates(char * name, int t) { printObjectStates(NULL, name, t);};
void BState::printObjectStates(FILE * f, char * name, int t) {

	if (t < 0) t = 0;
	char *strtab = new char [t+1];

	strtab[0] = '\0';
	for (int i=0; i < t; i++) strtab[i] = '\t';
	strtab[t] = '\0';
	

	FILE * file = f == NULL ? stderr : f;

	fprintf(file,"\n%sObject States: ",strtab); 
	if (name != NULL)
		fprintf(file,"%s", name);
	fprintf(file,"\t{\n\n");
	fprintf(file,"%s\tState List:\t{\n",strtab);
	int i;
	for (i = 0; i < objdefno; i++)
		fprintf(file,"%s\t\tObject:%4d >> %s\n",strtab, i, getStateDescription(objcurstate[i]));
	fprintf(file,"%s\t}\n",strtab);
	fprintf(file,"%s}\n",strtab);
	delete [] strtab;
}




