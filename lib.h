#include <iostream> 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <cstring>


using namespace std;

long long powMod(long long a, long long b,long long p) {
    long long y = 1;
    while (b) {
        if (b & 1) y = (y*a) % p; 
        b = b >> 1; 
        a = (a*a) % p;  
	}
    return y;
}

long long evklid_nod(long long a, long long b) {
	long long temp;
	if (b>a) { temp=a; a=b; b=temp; }
	long long q=0;
	long long U[]={a,1,0}, V[]={b,0,1}, T[]={0,0,0};
	while (V[0]!=0) {
		q = U[0]/V[0];
		T[0]=U[0]-q*V[0]; T[1]=U[1]-q*V[1]; T[2]=U[2]-q*V[2];
		U[0]=V[0]; U[1]=V[1]; U[2]=V[2]; 
		V[0]=T[0]; V[1]=T[1]; V[2]=T[2];
	}
	return U[0];
}
long long evklid_x(long long a, long long b) {
	long long temp;
	if (b>a) { temp=a; a=b; b=temp; }
	long long q=0;
	long long U[]={a,1,0}, V[]={b,0,1}, T[]={0,0,0};
	while (V[0]!=0) {
		q = U[0]/V[0];
		T[0]=U[0]-q*V[0]; T[1]=U[1]-q*V[1]; T[2]=U[2]-q*V[2];
		U[0]=V[0]; U[1]=V[1]; U[2]=V[2]; 
		V[0]=T[0]; V[1]=T[1]; V[2]=T[2];
	}
	return U[1];
}

long long evklid_y(long long a, long long b) {
	long long temp;
	if (b>a) { temp=a; a=b; b=temp; }
	long long q=0;
	long long U[]={a,1,0}, V[]={b,0,1}, T[]={0,0,0};
	while (V[0]!=0) {
		q = U[0]/V[0];
		T[0]=U[0]-q*V[0]; T[1]=U[1]-q*V[1]; T[2]=U[2]-q*V[2];
		U[0]=V[0]; U[1]=V[1]; U[2]=V[2]; 
		V[0]=T[0]; V[1]=T[1]; V[2]=T[2];
	}
	return U[2];
}

bool test_Ferma(long long p) { 
	if (p==0) return false;
	long long a,b;
	for (int i = 0;i < 100;i++) {
	a = rand()%p+1;
	b = powMod(a,(p-1),p); 
	if (evklid_nod(a,p)!=1) return false;
	if (b!=1) return false;
	}
	return true;
}
                     

void random(long long &p,long long &q,long long &g) {
	while (1) {
	p = (rand()<<15) | rand(); //cout<<"p = "<<p;
	if (test_Ferma(p)==true) q=(p-1)/2; if (test_Ferma(q)==true) break;
	}
	while (1) { g=((rand()<<15) | rand()) % (p-1); if (powMod(g,q,p)!=1) break; }
	//cout<<"p = "<<p<<endl;cout<<"q = "<<q<<endl;cout<<"g = "<<g<<endl;
}

long long Diffi_Hellman(){
	srand(time(0));
	long long Xa,Xb, Ya, Yb, Zab, Zba;
	long long q = 0, g = 0, p = 0;
	random(q,g,p);
		Xa=(rand()<<15) | rand();Xb=(rand()<<15) | rand(); 
		Ya=powMod(g,Xa,p);Yb=powMod(g,Xb,p);
		//cout<<"Xa = "<<Xa<<" ";cout<<"Xb = "<<Xb<<endl;
		//cout<<"Ya = "<<Ya<<" ";cout<<"Yb = "<<Yb<<endl;
		Zab=powMod(Yb,Xa,p);Zba=powMod(Ya,Xb,p);
		//if (Zab==Zba) cout<<"Zab = Zba = "<<Zab<<" = "<<Zba<<endl;
	if (Zab==Zba) return Zab;	                                                                              	
}

void quickSort(long long arr[], int arr_number[], int left, int right) {
      int i = left, j = right;  long long tmp; int tmp_number;  long long x = arr[(left + right) / 2];
      while (i <= j) {
            while (arr[i] < x)  i++;
            while (arr[j] > x)  j--;
            if (i <= j) {
                  tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp; 
		  tmp_number = arr_number[i]; arr_number[i] = arr_number[j]; arr_number[j] = tmp_number;
		  i++; j--;
            }
      };
      if (left < j) quickSort(arr, arr_number, left, j);
      if (i < right) quickSort(arr, arr_number, i, right);
}

void Binary_Search(long long X,long long B[], int B_number[], int A_number[], int right,int count1,int &ires, int &jres,bool &check) {
		int L = 0, R = right;
		while (L<R) {
		int m=(L+R)/2;
		if (B[m]<X) L=m+1; else R=m;
		}
		if (B[R]==X) { ires=B_number[R]; jres=A_number[count1]; check = true;}		  				
}

long long mladenes_velikan(long long a, long long p, long long y) {
	long long m,k=0; int ires,jres=0; m=sqrt(p)+1; k=m; bool check=false;
	long long A[m];	long long B[m]; long long x;
	int A_number[m];int B_number[m];
	for (int j=0;j<k;j++) { A[j]=powMod(a,j,p)*y%p; A_number[j]=j; } 
	for (int i=1;i<=k;i++) { B[i]=powMod(a,m*i,p); B_number[i]=i; }
	quickSort(B,B_number,1,m);	
	for (int i=0;i<k;i++) { Binary_Search(A[i],B,B_number,A_number,m,i,ires,jres,check); if (check == true) break;}
	x=ires*m-jres;
	return powMod(x,1,p-1);
} 
