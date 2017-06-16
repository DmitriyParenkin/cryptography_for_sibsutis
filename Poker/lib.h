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
                     

long long* zamok_shuffle(long long* koloda, long long* C, int j, int p) {   // u1 = a^ca mod p
    for (int i = 2; i < 55; i++) {
    koloda[i] = powMod(koloda[i],C[j],p);
    }
    //cout<<endl<<"Bez sort"<<endl;
    //for (int i = 2; i < 55; i++) cout<<koloda[i]<<" ";
    random_shuffle(&koloda[2], &koloda[55]);
    //cout<<endl<<"S sort"<<endl;
    //for (int i = 2; i < 55; i++) cout<<koloda[i]<<" ";
    return koloda;
}


void* razdacha_kart(long long* karta1, long long* karta2, long long* koloda, int i) {
    long long rnd1,rnd2;
    while(1) {
    rnd1 = 2+rand() % 51;
    rnd2 = 2+rand() % 51;
    if ((rnd1!=rnd2) && (koloda[rnd1]!=0) && (koloda[rnd2]!=0)) {
    karta1[i] = koloda[rnd1]; karta2[i] = koloda[rnd2];
    koloda[rnd1] = 0; koloda[rnd2] = 0;
    }
    if ((karta1[i] && karta2[i])!=0) break;
    }
}

void* razdacha_kart5(long long* kart5, long long* koloda, int i) {
    long long rnd1;
    while(1) {
    rnd1 = 2+rand() % 51;
    if (koloda[rnd1]!=0) {
    kart5[i] = koloda[rnd1];
    koloda[rnd1] = 0;
    }
    if ((kart5[i])!=0) break;
    }
}
