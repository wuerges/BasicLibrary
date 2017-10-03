#define FLOAT double


/****************** nrutil.c *******************************/

/* CAUTION: This is the ANSI C (only) version of the Numerical Recipes
   utility file nrutil.c.  Do not confuse this file with the same-named
   file nrutil.c that is supplied in the same subdirectory or archive
   as the header file nrutil.h.  *That* file contains both ANSI and
   traditional K&R versions, along with #ifdef macros to select the
   correct version.  *This* file contains only ANSI C.               */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#define NR_END 1
#define FREE_ARG char*

void nrerror(char error_text[])
/* Numerical Recipes standard error handler */
{

fprintf(stderr,"Numerical Recipes run-time error...\n");

fprintf(stderr,"%s\n",error_text);

fprintf(stderr,"...now exiting to system...\n");

exit(1);
}

FLOAT *vector(long nl, long nh)
/* allocate a FLOAT vector with subscript range v[nl..nh] */
{

FLOAT *v;


v=(FLOAT *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(FLOAT)));

if (!v) nrerror("allocation failure in vector()");

return v-nl+NR_END;
}

int *ivector(long nl, long nh)
/* allocate an int vector with subscript range v[nl..nh] */
{

int *v;


v=(int *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(int)));

if (!v) nrerror("allocation failure in ivector()");

return v-nl+NR_END;
}

unsigned char *cvector(long nl, long nh)
/* allocate an unsigned char vector with subscript range v[nl..nh] */
{

unsigned char *v;


v=(unsigned char *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(unsigned char)));

if (!v) nrerror("allocation failure in cvector()");

return v-nl+NR_END;
}

unsigned long *lvector(long nl, long nh)
/* allocate an unsigned long vector with subscript range v[nl..nh] */
{

unsigned long *v;


v=(unsigned long *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(long)));

if (!v) nrerror("allocation failure in lvector()");

return v-nl+NR_END;
}

double *dvector(long nl, long nh)
/* allocate a double vector with subscript range v[nl..nh] */
{

double *v;


v=(double *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(double)));

if (!v) nrerror("allocation failure in dvector()");

return v-nl+NR_END;
}

FLOAT **matrix(long nrl, long nrh, long ncl, long nch)
/* allocate a FLOAT matrix with subscript range m[nrl..nrh][ncl..nch] */
{

long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;

FLOAT **m;


/* allocate pointers to rows */

m=(FLOAT **) malloc((size_t)((nrow+NR_END)*sizeof(FLOAT*)));

if (!m) nrerror("allocation failure 1 in matrix()");

m += NR_END;

m -= nrl;


/* allocate rows and set pointers to them */

m[nrl]=(FLOAT *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(FLOAT)));

if (!m[nrl]) nrerror("allocation failure 2 in matrix()");

m[nrl] += NR_END;

m[nrl] -= ncl;


for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;


/* return pointer to array of pointers to rows */

return m;
}

double **dmatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a double matrix with subscript range m[nrl..nrh][ncl..nch] */
{

long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;

double **m;


/* allocate pointers to rows */

m=(double **) malloc((size_t)((nrow+NR_END)*sizeof(double*)));

if (!m) nrerror("allocation failure 1 in matrix()");

m += NR_END;

m -= nrl;


/* allocate rows and set pointers to them */

m[nrl]=(double *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(double)));

if (!m[nrl]) nrerror("allocation failure 2 in matrix()");

m[nrl] += NR_END;

m[nrl] -= ncl;


for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;


/* return pointer to array of pointers to rows */

return m;
}

int **imatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a int matrix with subscript range m[nrl..nrh][ncl..nch] */
{

long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;

int **m;


/* allocate pointers to rows */

m=(int **) malloc((size_t)((nrow+NR_END)*sizeof(int*)));

if (!m) nrerror("allocation failure 1 in matrix()");

m += NR_END;

m -= nrl;



/* allocate rows and set pointers to them */

m[nrl]=(int *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(int)));

if (!m[nrl]) nrerror("allocation failure 2 in matrix()");

m[nrl] += NR_END;

m[nrl] -= ncl;


for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;


/* return pointer to array of pointers to rows */

return m;
}

FLOAT **submatrix(FLOAT **a, long oldrl, long oldrh, long oldcl, long oldch,

long newrl, long newcl)
/* point a submatrix [newrl..][newcl..] to a[oldrl..oldrh][oldcl..oldch] */
{

long i,j,nrow=oldrh-oldrl+1,ncol=oldcl-newcl;

FLOAT **m;


/* allocate array of pointers to rows */

m=(FLOAT **) malloc((size_t) ((nrow+NR_END)*sizeof(FLOAT*)));

if (!m) nrerror("allocation failure in submatrix()");

m += NR_END;

m -= newrl;


/* set pointers to rows */

for(i=oldrl,j=newrl;i<=oldrh;i++,j++) m[j]=a[i]+ncol;


/* return pointer to array of pointers to rows */

return m;
}

FLOAT **convert_matrix(FLOAT *a, long nrl, long nrh, long ncl, long nch)
/* allocate a FLOAT matrix m[nrl..nrh][ncl..nch] that points to the matrix
declared in the standard C manner as a[nrow][ncol], where nrow=nrh-nrl+1
and ncol=nch-ncl+1. The routine should be called with the address
&a[0][0] as the first argument. */
{

long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1;

FLOAT **m;


/* allocate pointers to rows */

m=(FLOAT **) malloc((size_t) ((nrow+NR_END)*sizeof(FLOAT*)));

if (!m) nrerror("allocation failure in convert_matrix()");

m += NR_END;

m -= nrl;


/* set pointers to rows */

m[nrl]=a-ncl;

for(i=1,j=nrl+1;i<nrow;i++,j++) m[j]=m[j-1]+ncol;

/* return pointer to array of pointers to rows */

return m;
}

FLOAT ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh)
/* allocate a FLOAT 3tensor with range t[nrl..nrh][ncl..nch][ndl..ndh] */
{

long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1,ndep=ndh-ndl+1;

FLOAT ***t;


/* allocate pointers to pointers to rows */

t=(FLOAT ***) malloc((size_t)((nrow+NR_END)*sizeof(FLOAT**)));

if (!t) nrerror("allocation failure 1 in f3tensor()");

t += NR_END;

t -= nrl;


/* allocate pointers to rows and set pointers to them */

t[nrl]=(FLOAT **) malloc((size_t)((nrow*ncol+NR_END)*sizeof(FLOAT*)));

if (!t[nrl]) nrerror("allocation failure 2 in f3tensor()");

t[nrl] += NR_END;

t[nrl] -= ncl;


/* allocate rows and set pointers to them */

t[nrl][ncl]=(FLOAT *) malloc((size_t)((nrow*ncol*ndep+NR_END)*sizeof(FLOAT)));

if (!t[nrl][ncl]) nrerror("allocation failure 3 in f3tensor()");

t[nrl][ncl] += NR_END;

t[nrl][ncl] -= ndl;


for(j=ncl+1;j<=nch;j++) t[nrl][j]=t[nrl][j-1]+ndep;

for(i=nrl+1;i<=nrh;i++) {


t[i]=t[i-1]+ncol;


t[i][ncl]=t[i-1][ncl]+ncol*ndep;


for(j=ncl+1;j<=nch;j++) t[i][j]=t[i][j-1]+ndep;

}


/* return pointer to array of pointers to rows */

return t;
}

void free_vector(FLOAT *v, long nl, long nh)
/* free a FLOAT vector allocated with vector() */
{

free((FREE_ARG) (v+nl-NR_END));
}

void free_ivector(int *v, long nl, long nh)
/* free an int vector allocated with ivector() */
{

free((FREE_ARG) (v+nl-NR_END));
}

void free_cvector(unsigned char *v, long nl, long nh)
/* free an unsigned char vector allocated with cvector() */
{

free((FREE_ARG) (v+nl-NR_END));
}

void free_lvector(unsigned long *v, long nl, long nh)
/* free an unsigned long vector allocated with lvector() */
{

free((FREE_ARG) (v+nl-NR_END));
}

void free_dvector(double *v, long nl, long nh)
/* free a double vector allocated with dvector() */
{

free((FREE_ARG) (v+nl-NR_END));
}

void free_matrix(FLOAT **m, long nrl, long nrh, long ncl, long nch)
/* free a FLOAT matrix allocated by matrix() */
{

free((FREE_ARG) (m[nrl]+ncl-NR_END));

free((FREE_ARG) (m+nrl-NR_END));
}

void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch)
/* free a double matrix allocated by dmatrix() */
{

free((FREE_ARG) (m[nrl]+ncl-NR_END));

free((FREE_ARG) (m+nrl-NR_END));
}

void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch)
/* free an int matrix allocated by imatrix() */
{

free((FREE_ARG) (m[nrl]+ncl-NR_END));

free((FREE_ARG) (m+nrl-NR_END));
}

void free_submatrix(FLOAT **b, long nrl, long nrh, long ncl, long nch)
/* free a submatrix allocated by submatrix() */
{

free((FREE_ARG) (b+nrl-NR_END));
}

void free_convert_matrix(FLOAT **b, long nrl, long nrh, long ncl, long nch)
/* free a matrix allocated by convert_matrix() */
{

free((FREE_ARG) (b+nrl-NR_END));
}

void free_f3tensor(FLOAT ***t, long nrl, long nrh, long ncl, long nch,

long ndl, long ndh)
/* free a FLOAT f3tensor allocated by f3tensor() */
{

free((FREE_ARG) (t[nrl][ncl]+ndl-NR_END));

free((FREE_ARG) (t[nrl]+ncl-NR_END));

free((FREE_ARG) (t+nrl-NR_END));
}


/********** jacobi.c ***********************/
#include <math.h>
#define NRANSI
#define ROTATE(a,i,j,k,l) g=a[i][j];h=a[k][l];a[i][j]=g-s*(h+g*tau); a[k][l]=h+s*(g-h*tau);

void jacobi(FLOAT **a, int n, FLOAT d[], FLOAT **v, int *nrot)
{

int j,iq,ip,i;

FLOAT tresh,theta,tau,t,sm,s,h,g,c,*b,*z;


b=vector(1,n);

z=vector(1,n);

for (ip=1;ip<=n;ip++) {


for (iq=1;iq<=n;iq++) v[ip][iq]=0.0;


v[ip][ip]=1.0;

}

for (ip=1;ip<=n;ip++) {


b[ip]=d[ip]=a[ip][ip];


z[ip]=0.0;

}

*nrot=0;

for (i=1;i<=50;i++) {


sm=0.0;


for (ip=1;ip<=n-1;ip++) {



for (iq=ip+1;iq<=n;iq++)




sm += fabs(a[ip][iq]);


}


if (sm == 0.0) {



free_vector(z,1,n);



free_vector(b,1,n);



return;


}


if (i < 4)



tresh=0.2*sm/(n*n);


else



tresh=0.0;


for (ip=1;ip<=n-1;ip++) {



for (iq=ip+1;iq<=n;iq++) {




g=100.0*fabs(a[ip][iq]);




if (i > 4 && (FLOAT)(fabs(d[ip])+g) == (FLOAT)fabs(d[ip])





&& (FLOAT)(fabs(d[iq])+g) == (FLOAT)fabs(d[iq]))





a[ip][iq]=0.0;




else if (fabs(a[ip][iq]) > tresh) {





h=d[iq]-d[ip];





if ((FLOAT)(fabs(h)+g) == (FLOAT)fabs(h))






t=(a[ip][iq])/h;





else {






theta=0.5*h/(a[ip][iq]);






t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));






if (theta < 0.0) t = -t;





}





c=1.0/sqrt(1+t*t);





s=t*c;





tau=s/(1.0+c);





h=t*a[ip][iq];





z[ip] -= h;





z[iq] += h;





d[ip] -= h;





d[iq] += h;





a[ip][iq]=0.0;





for (j=1;j<=ip-1;j++) {






ROTATE(a,j,ip,j,iq)





}





for (j=ip+1;j<=iq-1;j++) {






ROTATE(a,ip,j,j,iq)





}





for (j=iq+1;j<=n;j++) {






ROTATE(a,ip,j,iq,j)





}





for (j=1;j<=n;j++) {






ROTATE(v,j,ip,j,iq)





}





++(*nrot);




}



}


}


for (ip=1;ip<=n;ip++) {



b[ip] += z[ip];



d[ip]=b[ip];



z[ip]=0.0;


}

}

nrerror("Too many iterations in routine jacobi");
}
#undef ROTATE
#undef NRANSI


/**************** ludcmp.c *************************/
#include <math.h>
#define NRANSI
#define TINY 1.0e-20;

void ludcmp(FLOAT **a, int n, int *indx, FLOAT *d)
{

int i,imax,j,k;

FLOAT big,dum,sum,temp;

FLOAT *vv;


vv=vector(1,n);

*d=1.0;

for (i=1;i<=n;i++) {


big=0.0;


for (j=1;j<=n;j++)



if ((temp=fabs(a[i][j])) > big) big=temp;


if (big == 0.0) nrerror("Singular matrix in routine ludcmp");


vv[i]=1.0/big;

}

for (j=1;j<=n;j++) {


for (i=1;i<j;i++) {



sum=a[i][j];



for (k=1;k<i;k++) sum -= a[i][k]*a[k][j];



a[i][j]=sum;


}


big=0.0;


for (i=j;i<=n;i++) {



sum=a[i][j];



for (k=1;k<j;k++)




sum -= a[i][k]*a[k][j];



a[i][j]=sum;



if ( (dum=vv[i]*fabs(sum)) >= big) {




big=dum;




imax=i;



}


}


if (j != imax) {



for (k=1;k<=n;k++) {




dum=a[imax][k];




a[imax][k]=a[j][k];




a[j][k]=dum;



}



*d = -(*d);



vv[imax]=vv[j];


}


indx[j]=imax;


if (a[j][j] == 0.0) a[j][j]=TINY;


if (j != n) {



dum=1.0/(a[j][j]);



for (i=j+1;i<=n;i++) a[i][j] *= dum;


}

}

free_vector(vv,1,n);
}
#undef TINY
#undef NRANSI



/************************ lubksb.c ***************************/

void lubksb(FLOAT **a, int n, int *indx, FLOAT b[])
{

int i,ii=0,ip,j;

FLOAT sum;


for (i=1;i<=n;i++) {


ip=indx[i];


sum=b[ip];


b[ip]=b[i];


if (ii)



for (j=ii;j<=i-1;j++) sum -= a[i][j]*b[j];


else if (sum) ii=i;


b[i]=sum;

}

for (i=n;i>=1;i--) {


sum=b[i];


for (j=i+1;j<=n;j++) sum -= a[i][j]*b[j];


b[i]=sum/a[i][i];

}
}


/****************** mprove.c ************************/
#define NRANSI

void mprove(FLOAT **a, FLOAT **alud, int n, int indx[], FLOAT b[], FLOAT x[])
{

void lubksb(FLOAT **a, int n, int *indx, FLOAT b[]);

int j,i;

double sdp;

FLOAT *r;


r=vector(1,n);

for (i=1;i<=n;i++) {


sdp = -b[i];


for (j=1;j<=n;j++) sdp += a[i][j]*x[j];


r[i]=sdp;

}

lubksb(alud,n,indx,r);

for (i=1;i<=n;i++) x[i] -= r[i];

free_vector(r,1,n);
}
#undef NRANSI


/*************** svbksb.c ***********************/

#define NRANSI

void svbksb(FLOAT **u, FLOAT w[], FLOAT **v, int m, int n, FLOAT b[], FLOAT x[])
{
	int jj,j,i;
	FLOAT s,*tmp;

	tmp=vector(1,n);
	for (j=1;j<=n;j++) {
		s=0.0;
		if (w[j]) {
			for (i=1;i<=m;i++) s += u[i][j]*b[i];
			s /= w[j];
		}
		tmp[j]=s;
	}
	for (j=1;j<=n;j++) {
		s=0.0;
		for (jj=1;jj<=n;jj++) s += v[j][jj]*tmp[jj];
		x[j]=s;
	}
	free_vector(tmp,1,n);
}
#undef NRANSI


/********************** svdcmp.c ************************/

#include <math.h>
#include "nrutil.h"
#define NRANSI

void svdcmp(FLOAT **a, int m, int n, FLOAT w[], FLOAT **v)
{

FLOAT pythag(FLOAT a, FLOAT b);

int flag,i,its,j,jj,k,l,nm;

FLOAT anorm,c,f,g,h,s,scale,x,y,z,*rv1;


rv1=vector(1,n);

g=scale=anorm=0.0;

for (i=1;i<=n;i++) {


l=i+1;


rv1[i]=scale*g;


g=s=scale=0.0;


if (i <= m) {



for (k=i;k<=m;k++) scale += fabs(a[k][i]);



if (scale) {




for (k=i;k<=m;k++) {





a[k][i] /= scale;





s += a[k][i]*a[k][i];




}




f=a[i][i];




g = -SIGN(sqrt(s),f);




h=f*g-s;




a[i][i]=f-g;




for (j=l;j<=n;j++) {





for (s=0.0,k=i;k<=m;k++) s += a[k][i]*a[k][j];





f=s/h;





for (k=i;k<=m;k++) a[k][j] += f*a[k][i];




}




for (k=i;k<=m;k++) a[k][i] *= scale;



}


}


w[i]=scale *g;


g=s=scale=0.0;


if (i <= m && i != n) {



for (k=l;k<=n;k++) scale += fabs(a[i][k]);



if (scale) {




for (k=l;k<=n;k++) {





a[i][k] /= scale;





s += a[i][k]*a[i][k];




}




f=a[i][l];




g = -SIGN(sqrt(s),f);




h=f*g-s;




a[i][l]=f-g;




for (k=l;k<=n;k++) rv1[k]=a[i][k]/h;




for (j=l;j<=m;j++) {





for (s=0.0,k=l;k<=n;k++) s += a[j][k]*a[i][k];





for (k=l;k<=n;k++) a[j][k] += s*rv1[k];




}




for (k=l;k<=n;k++) a[i][k] *= scale;



}


}


anorm=FMAX(anorm,(fabs(w[i])+fabs(rv1[i])));

}

for (i=n;i>=1;i--) {


if (i < n) {



if (g) {




for (j=l;j<=n;j++)





v[j][i]=(a[i][j]/a[i][l])/g;




for (j=l;j<=n;j++) {





for (s=0.0,k=l;k<=n;k++) s += a[i][k]*v[k][j];





for (k=l;k<=n;k++) v[k][j] += s*v[k][i];




}



}



for (j=l;j<=n;j++) v[i][j]=v[j][i]=0.0;


}


v[i][i]=1.0;


g=rv1[i];


l=i;

}

for (i=IMIN(m,n);i>=1;i--) {


l=i+1;


g=w[i];


for (j=l;j<=n;j++) a[i][j]=0.0;


if (g) {



g=1.0/g;



for (j=l;j<=n;j++) {




for (s=0.0,k=l;k<=m;k++) s += a[k][i]*a[k][j];




f=(s/a[i][i])*g;




for (k=i;k<=m;k++) a[k][j] += f*a[k][i];



}



for (j=i;j<=m;j++) a[j][i] *= g;


} else for (j=i;j<=m;j++) a[j][i]=0.0;


++a[i][i];

}

for (k=n;k>=1;k--) {


for (its=1;its<=30;its++) {



flag=1;



for (l=k;l>=1;l--) {




nm=l-1;




if ((FLOAT)(fabs(rv1[l])+anorm) == anorm) {





flag=0;





break;




}




if ((FLOAT)(fabs(w[nm])+anorm) == anorm) break;



}



if (flag) {




c=0.0;




s=1.0;




for (i=l;i<=k;i++) {





f=s*rv1[i];





rv1[i]=c*rv1[i];





if ((FLOAT)(fabs(f)+anorm) == anorm) break;





g=w[i];





h=pythag(f,g);





w[i]=h;





h=1.0/h;





c=g*h;





s = -f*h;





for (j=1;j<=m;j++) {






y=a[j][nm];






z=a[j][i];






a[j][nm]=y*c+z*s;






a[j][i]=z*c-y*s;





}




}



}



z=w[k];



if (l == k) {




if (z < 0.0) {





w[k] = -z;





for (j=1;j<=n;j++) v[j][k] = -v[j][k];




}




break;



}



if (its == 30) nrerror("no convergence in 30 svdcmp iterations");



x=w[l];



nm=k-1;



y=w[nm];



g=rv1[nm];



h=rv1[k];



f=((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y);



g=pythag(f,1.0);



f=((x-z)*(x+z)+h*((y/(f+SIGN(g,f)))-h))/x;



c=s=1.0;



for (j=l;j<=nm;j++) {




i=j+1;




g=rv1[i];




y=w[i];




h=s*g;




g=c*g;




z=pythag(f,h);




rv1[j]=z;




c=f/z;




s=h/z;




f=x*c+g*s;




g = g*c-x*s;




h=y*s;




y *= c;




for (jj=1;jj<=n;jj++) {





x=v[jj][j];





z=v[jj][i];





v[jj][j]=x*c+z*s;





v[jj][i]=z*c-x*s;




}




z=pythag(f,h);




w[j]=z;




if (z) {





z=1.0/z;





c=f*z;





s=h*z;




}




f=c*g+s*y;




x=c*y-s*g;




for (jj=1;jj<=m;jj++) {





y=a[jj][j];





z=a[jj][i];





a[jj][j]=y*c+z*s;





a[jj][i]=z*c-y*s;




}



}



rv1[l]=0.0;



rv1[k]=f;



w[k]=x;


}

}

free_vector(rv1,1,n);
}
#undef NRANSI


/****************** pythag.c **************************/

#include <math.h>
#define NRANSI
#include "nrutil.h"

FLOAT pythag(FLOAT a, FLOAT b)
{

FLOAT absa,absb;

absa=fabs(a);

absb=fabs(b);

if (absa > absb) return absa*sqrt(1.0+SQR(absb/absa));

else return (absb == 0.0 ? 0.0 : absb*sqrt(1.0+SQR(absa/absb)));
}
#undef NRANSI


/************* betacf.c ************/
#include <math.h>
#define MAXIT 100
#define EPS 3.0e-7
#define FPMIN 1.0e-30

FLOAT betacf(FLOAT a, FLOAT b, FLOAT x)
{

void nrerror(char error_text[]);

int m,m2;

FLOAT aa,c,d,del,h,qab,qam,qap;


qab=a+b;

qap=a+1.0;

qam=a-1.0;

c=1.0;

d=1.0-qab*x/qap;

if (fabs(d) < FPMIN) d=FPMIN;

d=1.0/d;

h=d;

for (m=1;m<=MAXIT;m++) {


m2=2*m;


aa=m*(b-m)*x/((qam+m2)*(a+m2));


d=1.0+aa*d;


if (fabs(d) < FPMIN) d=FPMIN;


c=1.0+aa/c;


if (fabs(c) < FPMIN) c=FPMIN;


d=1.0/d;


h *= d*c;


aa = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2));


d=1.0+aa*d;


if (fabs(d) < FPMIN) d=FPMIN;


c=1.0+aa/c;


if (fabs(c) < FPMIN) c=FPMIN;


d=1.0/d;


del=d*c;


h *= del;


if (fabs(del-1.0) < EPS) break;

}

if (m > MAXIT) nrerror("a or b too big, or MAXIT too small in betacf");

return h;
}
#undef MAXIT
#undef EPS
#undef FPMIN


/************* gammln.c ************/
#include <math.h>

FLOAT gammln(FLOAT xx)
{

double x,y,tmp,ser;

static double cof[6]={76.18009172947146,-86.50532032941677,


24.01409824083091,-1.231739572450155,


0.1208650973866179e-2,-0.5395239384953e-5};

int j;


y=x=xx;

tmp=x+5.5;

tmp -= (x+0.5)*log(tmp);

ser=1.000000000190015;

for (j=0;j<=5;j++) ser += cof[j]/++y;

return -tmp+log(2.5066282746310005*ser/x);
}

/************* betai.c *************/
#include <math.h>

FLOAT betai(FLOAT a, FLOAT b, FLOAT x)
{

FLOAT betacf(FLOAT a, FLOAT b, FLOAT x);

FLOAT gammln(FLOAT xx);

void nrerror(char error_text[]);

FLOAT bt;


if (x < 0.0 || x > 1.0) nrerror("Bad x in routine betai");

if (x == 0.0 || x == 1.0) bt=0.0;

else


bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));

if (x < (a+1.0)/(a+b+2.0))


return bt*betacf(a,b,x)/a;

else


return 1.0-bt*betacf(b,a,1.0-x)/b;
}


/************* pearsn.c ************/

#define TINY 1.0e-20

void pearsn(FLOAT x[], FLOAT y[], unsigned long n, FLOAT *r, FLOAT *prob, FLOAT *z)
{

FLOAT betai(FLOAT a, FLOAT b, FLOAT x);

FLOAT erfcc(FLOAT x);

unsigned long j;

FLOAT yt,xt,t,df;

FLOAT syy=0.0,sxy=0.0,sxx=0.0,ay=0.0,ax=0.0;


for (j=1;j<=n;j++) {


ax += x[j];


ay += y[j];

}

ax /= n;

ay /= n;

for (j=1;j<=n;j++) {


xt=x[j]-ax;


yt=y[j]-ay;


sxx += xt*xt;


syy += yt*yt;


sxy += xt*yt;

}

*r=sxy/sqrt(sxx*syy);

*z=0.5*log((1.0+(*r)+TINY)/(1.0-(*r)+TINY));

df=n-2;

t=(*r)*sqrt(df/((1.0-(*r)+TINY)*(1.0+(*r)+TINY)));

/* *prob=betai(0.5*df,0.5,df/(df+t*t)); */
}
#undef TINY

