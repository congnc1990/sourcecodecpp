#include<stdio.h>
#include<conio.h>
#include<iostream.h>
#include<stdlib.h>
#include<string.h>

#define templateT template<class T>
#define writeln() printf("\n")
#define MAX max
#define MIN min
templateT inline T abs(T a)	{	return a>=0 ? a : -a;	}
templateT inline T max(T a,T b)	{	return	a > b ? a : b;	}
templateT inline T min(T a,T b)	{	return	a < b ? a : b;	}
templateT inline T max(T a,T b,T c)	{	return max(max(a,b),c);	}
templateT inline T min(T a,T b,T c)	{	return min(min(a,b),c);	}

templateT inline void swap(T &a,T &b)	{	T t=a;	a=b;	b=t;	}

templateT int Search(T*arr,int max,T t)
{
	for(int i=0;i<max && t!= arr[i]; i++);
	if(t==arr[i])	return i;
	return -1;
}


template<class T,class T1>
T1 LSearch(T t,T*arr,T1 max,int (*fcmp)(const void*,const void*,...))
{
	for (T1 i=0; i<max; i++)
		if (t==arr[i])
			return i;
	return -1;
}

template<class T,class T1,class T2>
int BinSearch(T t,T*arr,T1 max,T2 (*fcmp)(const void*,const void*,...))
{
	T1 y=max-1;
	T2 kq=fcmp(&t,arr+y);
	if(kq>0)	return -max-1;
	if(kq==0)	return max;
	kq=fcmp(&t,arr);
	if(kq<0)	return 0;
	if(kq==0)	return 1;
	T1 x=0,h;
	do{
		h=(x+y)/2;
		kq=fcmp(&t,arr+h);
		if(kq>0)	x=h;
		else if(kq<0)	y=h;
			else return h+1;
	}while ((y-x)>=2);
	if(kq==0)return y+1;
	return -y;
}

template<class T,class T1>
void SelectSort(T*arr, T1 num, int (*fcmp)(const void*,const void*,...))
{
	if(num<2)	return;
	for(T1 i=0;i<num-1;i++)
	{
		T m=i;
		for(T1 j=i+1;j<num;j++)
			if(fcmp(arr+m,arr+j)>0)	m=j;
		if(m!=i)	swap(arr[m],arr[i]);
	}
}

template<class T,class T1>
void InsSort(T*arr, T1 num, int (*fcmp)(const void*,const void*,...))
{
	if (num < 2)	return;
	T t;
	for(T1 i=1;i<num;i++)
	{
		T1 j=i-1;
		t=arr[i];
		while(fcmp(&t,arr+j)<0/*t<arr[j]*/ && j>=0)arr[j+1]=arr[j--];
		arr[j+1]=t;
	}
}

template<class T,class T1,class T2>
void QuickSort(T*arr,T1 max, T2 (*fcmp)(const void*,const void*,...))
{
	if(max<2)	return;
	char s=0;
	T1 left[32],right[32];
	T1 L,R,i,j;
	T X;
	left[s]=0;right[s]=max-1;
	s++;
	while(s!=0)
	{
		s--;	L=left[s];	R=right[s];
		if(R-L<10)	{	InsSort(arr+L,(R-L+1),fcmp);	continue;	}
		i=L;	j=R;
		X=arr[(L+R)/2];
		while(i<=j)
		{
			while(fcmp(arr+i,&X)<0)i++;
			while(fcmp(arr+j,&X)>0)j--;
			if(i<=j)
			{
				if(i!=j)swap(arr[i],arr[j]);
				i++;	j--;
			}
		}
		if(L<j)	{	left[s]=L;	right[s]=j;	s++;	}
		if(i<R)	{	left[s]=i;	right[s]=R;	s++;	}
	}
}
//templateT

inline int
fCmpInt(const void *a,const void *b,...){return *(int *)a - *(int *)b;}

inline int
fCmpChar(const void *a,const void *b,...){return *(char*)a-*(char*)b;}

inline int
fCmpStr(const void *a, const void *b,...){return strcmp((char *)a,(char *)b);}

void mains()
{
	clrscr();
	char list[]=" \'-.ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int len=strlen(list);
	QuickSort(list,len,fCmpChar);
	cout<<list<<endl;
	for(int k=0;k<len;k++)	cout<<(int)list[k]<<" ";
	return;
	randomize();
//	int a=rand()%256,b=rand()%256,c=rand()%256;
//	cout<<a<<" "<<b<<" "<<c<<endl;
//	cout.width(10);	cout<<max(a,b,c)<<" "<<min(a,b,c);
//	cout.width(10);	cout<<min(a,b)<<" "<<max(b,c);
	const long num=64;
	int arr[num];
	for(int i=0;i<num;i++)arr[i]=rand()%256;
	writeln();
	for(i=0;i<num;i++)printf("%5d",arr[i]);
	printf("\n%d\n",Search(arr,64,37));
	getch();
//	InsSort(arr+10,5,fcmp);
//	QuickSort(arr,256,fcmp);
	SelectSort(arr,64,fCmpInt);
	for(i=0;i<num;i++)printf("%5d",arr[i]);
	printf("  %d",BinSearch(35,arr,64,fCmpInt));
	getch();
}

/*
templateT
void QuickSort
	(T*arr,int l,int r, int (*fcmp)(const void*,const void*,...))
{
	if(l>=r)	return;
	int i=l,j=r;
	int x=	(l+r)/2;
	while(i<=j)
	{
		while( fcmp(arr+i,arr+x) <0) i++;
		while( fcmp(arr+j,arr+x) >0) j--;
		if(i<j)
		{
			swap(arr[i],arr[j]);
			i++; j--;
		}
	}
	for(i=0;i<16;i++)printf("%5d",arr[i]);

	QuickSort(arr,l,j-1,fcmp);
	QuickSort(arr,i+1,r,fcmp);
}*/
