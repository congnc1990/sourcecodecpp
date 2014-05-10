#include <conio.h>
#include <stdio.h>
#include<stdlib.h>
#include<iostream.h>
const _rand=-1<<32;
unsigned long ucln(long aa,long bb)
{
 long rr;
 while(bb!=0) {rr=aa % bb;aa=bb;bb=rr;}
 return (aa>0)? aa:-aa;
}
unsigned long bcnn(long aa,long bb)
{
 return aa*bb/ucln(aa,bb);
}

unsigned long factorial(unsigned char n) // =n!
{
  if (n==0) return 1;
  else return n*factorial(n-1);
}

unsigned long combination(unsigned char k,unsigned char n) // = nCk
{
  if (k==1) return n;
  else
  {   //memmoria
   unsigned char i,j;
   unsigned long *kq;*kq=1;
   for (i=n,j=1;j<=k;i--,j++) *kq =*kq*i/j;
   return *kq;
  }
}
	//******************************
typedef struct phanso
{
 long ts,ms;
}fraction,phanso;
const phanso PS0={0,1};
phanso randps(long c)
{
 phanso _ps;
if (c!=_rand) {_ps.ms=1;_ps.ts=c;}
else
{
 if (random(1000)%3) _ps.ms=1,_ps.ts=(rand()-rand())%10;
 else {do _ps.ms=rand()%10;while (_ps.ms==0); _ps.ts=(rand()-rand())%100;}
} return _ps;
}

void toigian(phanso *ps)
{
  long *t;
  *t=ucln(ps->ts,ps->ms);
  *t=(ps->ms>0)? *t:-*t;
  ps->ts/=*t; ps->ms/=*t;
}

phanso tichps(phanso psa,phanso psb)
{
 phanso ps;
 ps.ts=psa.ts*psb.ts; ps.ms=psa.ms*psb.ms;
 toigian(&ps);
 return ps;
}

phanso tongps(phanso psa,phanso psb)
{
  phanso ps;
  if (psa.ms!=psb.ms) {
    long bs=bcnn(psa.ms,psb.ms);
    psa.ts*=bs/psa.ms;psb.ts*=bs/psb.ms;psa.ms=psb.ms=bs;
   }
  ps.ms=psa.ms,ps.ts=psa.ts+psb.ts; toigian(&ps);
  return ps;
}
phanso hieups(phanso psa,phanso psb)
{
  psb.ts=-psb.ts;return tongps(psa,psb);
}
	//**************************
	//**********MATRIX**********
	//**************************

/*typedef struct matrixs
{
	unsigned char m,n;
	phanso matrix[30][30];
}matrixs;

matrixs randmatrix(unsigned char p,unsigned char q)
{
matrixs m; unsigned char i,j;
m.m=p;m.n=q;
for (i=1;i<=p;i++)
  for (j=1;j<=q;j++)
  m.matrix[i][j]=randps(_rand);// (rand()-rand())%10;
 return m;
}

void showmatrix(matrixs mm)
{
 unsigned char i,j;
 for (i=1;i<=mm.m;i++)
 {
   for (j=1;j<=mm.n;j++) {
	printf("%6ld",mm.matrix[i][j].ts);
	if (mm.matrix[i][j].ms==1||mm.matrix[i][j].ts==0)printf("     ");
	else printf("/%-4ld",mm.matrix[i][j].ms);  }
   printf("\n");
 }
}
/*
matrixs tongmt(matrixs a,matrixs b)
{
 unsigned char i,j;
 matrixs m;
 m.m=a.m;m.n=b.n;
 if ((a.m==b.m)&&(a.n==b.n))
  for (i=1;i<=a.m;i++)
   for (j=1;j<=b.n;j++)
	m.matrix[i][j]=tongps(a.matrix[i][j],b.matrix[i][j]);
 return m;
}
matrixs nhanmt(matrixs a, phanso k)
{
  matrixs m;
switch (k.ts/k.ms)
{
 case 0 : m;break;
 case 1 : m=a;break;
 default :
  {
  unsigned char i,j;
  m.m=a.m;m.n=a.n;
  for (i=1;i<=a.m;i++)
   for (j=1;j<=a.n;j++)
	 m.matrix[i][j]=tichps(a.matrix[i][j],k);
  }
}
  return m;
}

matrixs tichmt(matrixs a, matrixs b)
{
 matrixs m;
 if (a.n==b.m)
 {
  unsigned char i,j,k;
  m.m=a.m; m.n=b.n;
  for (i=1;i<=a.m;i++)
  for (j=1;j<=b.n;j++)
  {
   phanso h=PS0;//h.ms=1,h.ts=0;
	for (k=1;k<=a.n;k++) h=tongps(h,tichps(a.matrix[i][k],b.matrix[k][j]));
   m.matrix[i][j]=h;
  }
 }
 return m;
}

matrixs submatrix(matrixs a,int ii,int jj)
{
 unsigned char l,k;
 for (l=ii;l<a.m;l++)
  for (k=1;k<=a.n;k++) a.matrix[l][k]=a.matrix[l+1][k];a.m--;
 for (l=jj;l<a.n;l++)
  for (k=1;k<=a.m;k++) a.matrix[k][l]=a.matrix[k][l+1];a.n--;
 return a;
}
	   //**************************
long int detint(matrixs a,unsigned char n)
{
 long gt[30];unsigned char i;
 gt[n]=0;
 if (n<=1) gt[n]=a.matrix[1][1];
}

phanso detps(matrixs a,unsigned char n)
{
 static phanso gt[30]; unsigned char i;
 gt[n]=PS0;
 if (n<=1) gt[n]=a.matrix[1][1];
 else  {
  for (i=1;i<=n;i++)
   if (a.matrix[n][i].ts!=0)
	 switch ((i+n)&1) {
	  case 0:
gt[n]=tongps(gt[n],tichps(a.matrix[n][i],det(submatrix(a,n,i),n-1)));
	   break;
	  case 1:
gt[n]=hieups(gt[n],tichps(a.matrix[n][i],det(submatrix(a,n,i),n-1)));
	   break;	       }}
 return gt[n];
}

phanso detmt3(matrixs a)
{
 phanso ps=PS0;
 if (a.m==3&&a.m==3)
  ps=
 hieups(
  tongps(
	tongps( tichps(tichps(a.matrix[1][1],a.matrix[2][2]),a.matrix[3][3]),
	 tichps(tichps(a.matrix[1][2],a.matrix[2][3]),a.matrix[3][1]) ),
	tichps(tichps(a.matrix[1][3],a.matrix[2][1]),a.matrix[3][2])  ),
  tongps(
	tongps( tichps(tichps(a.matrix[3][1],a.matrix[2][2]),a.matrix[1][3]),
	 tichps(tichps(a.matrix[3][2],a.matrix[2][3]),a.matrix[1][1]) ),
	tichps(tichps(a.matrix[3][3],a.matrix[2][1]),a.matrix[1][2])  ) );
 return ps;
}
*/
