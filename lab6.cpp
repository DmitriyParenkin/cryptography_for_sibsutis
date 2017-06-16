#include "lib.h"
#include "algorithm"
#include "fstream"
// powMod(a,b,p)
// evklid_nod(a,b) evklid_x(a,b) evklid_y(a,b)
// test_Ferma(p)
// Diffi_Hellman() random(p,q,g)
// mladenes_velikan(a,p,y)

using namespace std;

// Первая строка n и m - количество вершин и количество ребер графа. Числа порядка 10^6. 
// В следующих n строках идет перечисление ребер графа в виде двух чисел (номера вершин, которые соединяют ребро).
// В последней строке задаются цвета каждой вершины.
struct graf {
	long long vertex1; 
	long long vertex2;  
};

bool Zero_knowledge_proof1() {
	FILE *file;
	srand(time(NULL));
	file = fopen("input1.txt", "r");
        long long n=0,m=0;
	fscanf(file, "%d %d", &n,&m);
	char color_name[] = {' ','R','B','Y'};
	char color_name_shuffle[3];
	struct graf graf1[m];
	char color[10000]; char color_shuffle[10000];
	 
	for (int i = 1; i <= m; i++) fscanf(file, "%d %d", &(graf1[i].vertex1), &(graf1[i].vertex2));
	for (int i = 1; i <= n; i++) fscanf(file, "%s", &color[i]);		
	//for (int i = 1; i <= n; i++) cout<<color[i]<<" ";
	random_shuffle(&color_name[1], &color_name[4]);
	for (int i = 1; i <= 3; i++) color_name_shuffle[i]=color_name[i];
	for (int i = 1; i <= n; i++) {
	switch(color[i]) {
		case 'R':{ color_shuffle[i] = color_name_shuffle[1];break; }
		case 'B':{ color_shuffle[i] = color_name_shuffle[2];break; }
		case 'Y':{ color_shuffle[i] = color_name_shuffle[3];break; } 
	}
	}
	long long N,P,Q,f,D[n],C[n],R[n],Z[n]; int count1=0; int rand1,rand2; long long check1,check2;
        while(1) {
	while(1) { P = rand() % 30000; if (test_Ferma(P)==1) break;}
        while(1) { Q = rand() % 30000; if (test_Ferma(Q)==1) break;}
        if ((P!=Q) && (P!=1) && (Q!=1)) break;
    	}
    	N = P*Q;
    	f = (P-1) * (Q-1);
	for (int i = 1; i <= n; i++) {
	switch(color_shuffle[i]) {
		case 'R':{ R[i] = ((((rand()<<4) | rand())) * 4 + 0) % N;break; }
		case 'B':{ R[i] = ((((rand()<<4) | rand())) * 4 + 1) % N;break; }
		case 'Y':{ R[i] = ((((rand()<<4) | rand())) * 4 + 2) % N;break; } 
		} 
	}
	for (int i = 1; i <= n; i++) { D[i]=0; C[i]=0; Z[i]=0; }
	for (int i = 1; i <= n; i++){
	while(1) {
    	D[i] = ((rand()<<15) | rand()) % (f);
    	if (evklid_nod(D[i],f)==1) { count1++; break;}
    	}
    	if (count1 == n) break;
    	}
    	for (int i = 1; i <= n; i++) { C[i] = evklid_y(D[i],f);  if (C[i]<0) C[i] = C[i] + (f);}
	for (int i = 1; i <= n; i++) { Z[i] = powMod(R[i],D[i],N); }
	rand1 = 1 + rand() % m;
       	check1 = powMod(Z[graf1[rand1].vertex1],C[graf1[rand1].vertex1],N);
	check2 = powMod(Z[graf1[rand1].vertex2],C[graf1[rand1].vertex2],N);
	fclose(file);
	if ((check1 % 4) != (check2 % 4)) return true; else return false;
}

void Generate_graf() {
	FILE *file;
	srand(time(NULL));
	file = fopen("input1.txt", "w");
        long long n=1000,m=1000;
	fprintf(file, "%i ", n); fprintf(file, "%i\n", m);
	struct graf graf1[10000];
	char color[10000];
	char color_name[] = {' ','R','B','Y'}; int count1;
	for (int i = 1; i <= m; i++) {
	graf1[i].vertex1 = i;
	if (i==m) graf1[i].vertex2 = 1; else graf1[i].vertex2 = i+1; 
	}
        for (int i = 1; i <= m; i++) cout<<graf1[i].vertex1<<" "<<graf1[i].vertex2<<endl;
	for (int i = 1; i <= m; i++) {
	fprintf(file, "%d ", graf1[i].vertex1); fprintf(file, "%d\n", graf1[i].vertex2);
	}
	for (int i = 1; i <= n; i++) cout<<color[i]<<" ";
	
	for (int i = 1; i <= n-1; i++) {
	count1 = 1 + i % 3;
	if (count1==1) fprintf(file, "%s ","R");
	if (count1==2) fprintf(file, "%s ","B");
	if (count1==3) fprintf(file, "%s ","Y");	
	}
	fprintf(file, "%s ","Y");		
}


int main() {
	int count1=0,count2=0;
	for (int i = 0; i < 10000; i++) if (Zero_knowledge_proof1()==1) count1++; else count2++; 
	cout<<"Correct = "<<count1<<endl<<"Incorrect = "<<count2<<endl;
	//Generate_graf();
	system("pause");
return 0;
}