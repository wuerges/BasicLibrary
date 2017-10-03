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

#include "BFile.h"

char * getNextToken(char *& instr, char del) {

	if (instr == NULL)
		return NULL;

	int i, n;
	char  *outstr = NULL;
	char del2[2];
	del2[0] = del;
	del2[1] = '\0';

	i = strcspn(instr, del2);
	n = strcspn(instr, "\0");

	outstr = new char [i+1];
	strncpy(outstr, instr, i);
	outstr[i] = '\0';
	if (i+1 >= n)
		instr = NULL;
	else
		instr = instr+i+1;

	return outstr;
}

char * getFullPath(char * fname, bool keep, bool backslash) {

	if (fname == NULL)
		return NULL;

	char slash = backslash ? '\\' : '/';

	char * rest = strrchr(fname, slash);

	if (rest == NULL)
		return fname;

	int k = keep ? 1 : 0,
		l = strlen(fname) - strlen(rest);

	char * path = new char [l + k + 1];

	strncpy(path, fname, l + k);
	path[l+k] = '\0';

	return path;
}
char * skipPath(char * fname, bool backslash) {

	if (fname == NULL)
		return NULL;

	char slash = backslash ? '\\' : '/';

	char * rest = strrchr(fname, slash);

	rest = (rest != NULL) ? rest+1 : rest;

	if (rest != NULL)
		return rest;
	return fname;
}
bool hasAbsolutePath(char * fname, bool backslash) {

	if (fname == NULL)
		return false;

	char slash = backslash ? '\\' : '/';

	char * str = strchr(fname,':');
	if (str == NULL)
		return false;

	int sz1 = strlen(fname);
	int sz2 = strlen(str);
	int sz3 = sz1 - sz2;
	if (sz3 < 1 || sz3 > 2 || sz2 < 2 || str[1] != slash)
		return false;
	return true;

}
bool existPath(char * pname, bool backslash) {

	if (pname == NULL)
		return false;

	char slash = backslash ? '\\' : '/';

	char *fname = new char [strlen(pname)+5];

	sprintf(fname, "%s%c_s_", pname,slash);

	FILE * f = NULL;

	f = fopen(fname,"r");
	if (f != NULL){
		fclose(f);
		return true;
	};
	f = fopen(fname,"w");
	if (f != NULL){
		fclose(f);
		remove(fname);
		return true;
	};

	return false;

}
void createPath(char * pname, bool backslash) {

	if (pname == NULL)
		return;

	char slash = backslash ? '\\' : '/';

    int le = strlen(pname);
	char * path = new char [le+2];
	path[0] = '\0';
	char * part = new char[le+2];
	char * tok = getNextToken(pname,slash);
 	strcpy(part, tok);
    strcatcar(part,slash);
    while (tok != NULL) {
		strcat(path, part);
		createDirectory(path);
		delete [] tok;
		tok = getNextToken(pname,slash);
		if (tok != NULL) {
            strcpy(part,tok);
            strcatcar(part,slash);
		}
	}

	if (tok != NULL)
		delete [] tok;
	if (part != NULL)
		delete [] part;
	if (path != NULL)
		delete [] path;

}
char * putPath(char * path, char * file, bool backslash) {
	if (file == NULL)
		return NULL;

	int len =0;

	if (path != NULL && !hasAbsolutePath(file))
		len += strlen(path) + 1;
	len += strlen(file) + 1;
	char * res = new char [len];
	res[0] = '\0';
	if (path != NULL && !hasAbsolutePath(file)){
		char slash = backslash ? '\\' : '/';
		strcpy(res,path);
		strcatcar(res,slash);
	}
	strcat(res, file);
	return res;
}
char * putPath(char * path, char * file, char * ext, bool backslash) {

	if (file == NULL)
		return NULL;

	int len = 0;

	if (path != NULL && !hasAbsolutePath(file))
		len += strlen(path) + 1;
	len += strlen(file) + strlen(ext) + 2;
	char * res = new char [len];
	res[0] = '\0';
	if (path != NULL && !hasAbsolutePath(file)){
		char slash = backslash ? '\\' : '/';
		strcpy(res,path);
		strcatcar(res,slash);
	}
	strcat(res, file);
	strcat(res, ".");
	strcat(res, ext);
	fflush(stdout);
	return res;
}

char * removeFileExtension(char * fname) {

	if(fname == NULL)
		return NULL;

	int n = -1,
		i = 0;
	while (fname[i] != '\0') {
		if (fname[i] == '.')
			n = i;
		i++;
	}
	char * rest = NULL;

	if (n == -1) {
		rest = new char [strlen(fname)+1];
		strcpy(rest,fname);
	} else {
		rest = new char [n+1];
		strncpy(rest, fname, n);
		rest[n] = '\0';
	}

	return rest;
}
char * getFileExtension(char * fname) {

	if(fname == NULL)
		return NULL;

	int n = -1,
		i = 0;
	while (fname[i] != '\0') {
		if (fname[i] == '.')
			n = i;
		i++;
	}
	char * rest = NULL;

	if (n != -1) {
		rest = new char [strlen(fname) - n];
		strcpy(rest, fname + n + 1);
	}

	return rest;
}
char * getWorkingDirectory() {
	char *dir;

	dir = getcwd(NULL,0);

	return dir;
}

bool createDirectory(char * dir) {
#ifdef _WIN32
	if (mkdir(dir) == -1)
		return false;
#else
	if (mkdir(dir,0777) == -1)
		return false;
#endif // __GNUC__

	return true;
}

BFile::BFile(){
	pathname = NULL;
	filename = new char[5];
	strcpy(filename,"NONE");
	fileextension = NULL;
	fullname = NULL;
	filedescriptor = NULL;

}
BFile::BFile(char * fname){

	pathname = NULL;
	filename = NULL;
	fileextension = NULL;
	fullname = NULL;
	filedescriptor = NULL;


	if (fname == NULL)
		return;

	fullname = new char [strlen(fname)+1];
	strcpy(fullname, fname);
	pathname = getFullPath(fullname);
	char * aux  = skipPath(fullname);
	filename = removeFileExtension(aux);
	fileextension = getFileExtension(aux);
}
BFile::~BFile(){
	if (pathname != NULL)
		delete [] pathname;
	if (filename != NULL)
		delete [] filename;
	if (fileextension != NULL)
		delete [] fileextension;
	if (pathname != NULL)
		delete [] pathname;
	if (filedescriptor != NULL)
		close();


}
bool BFile::forceOpen(char * mode){
	if (pathname != NULL && !existPath(pathname)) {
		createPath(pathname);
		if (existPath(pathname))
			return open(mode);
	} else
		return open(mode);

	return false;

}
bool BFile::open(char * mode){
	if (mode == NULL)
		return false;
	if (filedescriptor != NULL)
		return false;

	if (fullname != NULL) {
		filedescriptor = fopen(fullname,mode);
		if (filedescriptor == NULL)
			return false;
		else
			return true;
	}

	if (strcmp(mode,"w") == 0)
		filedescriptor = stdout;
	else if (strcmp(mode,"r") == 0)
		filedescriptor = stdin;
	else
		return false;

	return true;
}
bool BFile::open(char * fname, char * mode){
	if (mode == NULL)
		return false;

	if (filedescriptor != NULL)
		return false;

	if (fname != NULL) {
		if (pathname != NULL)
			delete [] pathname;
		if (filename != NULL)
			delete [] filename;
		if (fileextension != NULL)
			delete [] fileextension;
		if (pathname != NULL)
			delete [] pathname;
		fullname = new char [strlen(fname)+1];
		strcpy(fullname, fname);
		pathname = getFullPath(fullname);
		char * aux  = skipPath(fullname);
		filename = removeFileExtension(aux);
		fileextension = getFileExtension(aux);
	}
	if (fname != NULL) {
		filedescriptor = fopen(fullname,mode);
		if (filedescriptor == NULL)
			return false;
		else
			return true;
	}

	if (strcmp(mode,"w") == 0)
		filedescriptor = stdout;
	else if (strcmp(mode,"r") == 0)
		filedescriptor = stdin;
	else
		return false;

	return true;
}
bool BFile::setFileName(char* fname){
	if (filedescriptor != NULL)
		return false;

	if (fname == NULL)
		return false;

	if (pathname != NULL)
		delete [] pathname;
	if (filename != NULL)
		delete [] filename;
	if (fileextension != NULL)
		delete [] fileextension;
	if (pathname != NULL)
		delete [] pathname;
	fullname = new char [strlen(fname)+1];
	strcpy(fullname, fname);
	pathname = getFullPath(fullname);
	char * aux  = skipPath(fullname);
	filename = removeFileExtension(aux);
	fileextension = getFileExtension(aux);
	return true;
}
bool BFile::close(){
	if (filedescriptor == NULL)
		return false;

	fclose(filedescriptor);

	return true;
}
