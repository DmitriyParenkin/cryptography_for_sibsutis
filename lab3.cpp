#include "lib.h"
#include "md5.h"
#include "fstream"


// powMod(a,b,p)
// evklid_nod(a,b) evklid_x(a,b) evklid_y(a,b)
// test_Ferma(p)
// Diffi_Hellman() random(p,q,g)
// mladenes_velikan(a,p,y)

int hex (char chr) {
    if (chr >= '0' && chr <= '9')
        return chr - '0';
    else if (chr >= 'A' && chr <= 'F')
        return chr - 'A' + 10;
    else if (chr >= 'a' && chr <= 'f')
        return chr - 'a' + 10; 
    return -1;
}

long long MD5(char FileName[]) {
  //Находим md5 строки
  //char src []= "01234";
  char rez[50]; long long sum = 0;
  //GetMD5(src, 5, rez);
  //printf (rez);
  //////////////////////////////////////////////////////////
  //Находим md5 файла
  //char file_name []= "Ryabko.pdf";
  
  HANDLE  hFile = CreateFile(FileName, GENERIC_READ | GENERIC_WRITE,
    0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
 
 
  HANDLE  hMapping = CreateFileMapping(
        hFile,     // дескриптор открытого файла
        NULL,      // атрибуты защиты по умолчанию
        PAGE_READWRITE,  // режим доступа
        0, 0,      // размер объекта отображения равен размеру файла
        NULL);     // имя не используем
 
  // создаем вид файла
  char* ptr = (char*)MapViewOfFile(
      hMapping,    // дескриптор объекта отображения
      FILE_MAP_WRITE,    // режим доступа к виду
      0, 0,        // отображаем файл с начала
      0);          // отображаем весь файл
 
  
  long int Razmer_Faila= (long int)GetFileSize(hFile, 0);
 
  GetMD5(ptr, Razmer_Faila, rez);
  //printf (rez);
  for (int i=0;i<32;i++) {
	//printf("%i ",hex(rez[i]));
	sum = (sum<<1) + hex(rez[i]); 
  }
  UnmapViewOfFile(ptr); 
  CloseHandle(hMapping);
  CloseHandle(hFile);
  return sum; 
}



void El_Gamal_sign(char FileName[]){
	srand(time(0));
	char FileName1[70]=""; char str1[70] = ".elgamal.sign";strcat(FileName1,FileName);strcat(FileName1,str1);
	long long p,q,g=0; long long k,k1,r; long long y; long long x; long long u,s,h;
	char buf[1];
	random(p,q,g);
	x = ((rand()<<15) | rand()) % (p-1);
	y = powMod(g,x,p);// Открытый ключ
	h = MD5(FileName) % (p-1); 
	cout<<h<<endl;
	while (1) {
	k = ((rand()<<15) | rand()) % (p - 1);	if (evklid_nod(k,p-1)==1)   break;
	}
	r = powMod(g,k,p);
	u = (powMod((h-x*r),1,(p-1))+(p-1)) % (p-1);// cout<<"u = "<<u<<endl;
	cout<<u<<endl;
	//u = (h-x*r) % (p-1); if (u<0) u = u + (p - 1);
	//k1 = evklid_y(k,p-1);
	k1 = (evklid_y(k,p-1)+(p-1)) % (p-1);
	s = ((k1 % (p-1))*(u % (p-1))) % (p-1); 
	ofstream fout(FileName1,ios::binary);
	fout<<p<<endl<<g<<endl<<y<<endl<<r<<endl<<s;
	cout<<"The file was successfully signed"<<endl;
	fout.close();
}

void El_Gamal_verify(char FileName[]) {
	char FileName1[70]=""; char str1[70] = ".elgamal.sign";strcat(FileName1,FileName);strcat(FileName1,str1);
	char buff[100]; long long A[5]; int i=0; long long h; long long buf1, buf2;
	ifstream fin(FileName1);
	
	if (fin.good()) {
	while (1) { if (fin.eof()) break; fin.getline(buff, sizeof(buff)); A[i]=_atoi64(buff); i++; } 
	}
	
	fin.close();// p = A[0] g = A[1] y = A[2] r = A[3] s = A[4] h = A[5]
	//for (int i=0;i<6;i++) cout<<A[i]<<endl;
	
	h = MD5(FileName) % (A[0]-1);//cout<<h<<endl;
	buf1 = (powMod(A[2],A[3],A[0])*powMod(A[3],A[4],A[0])) % A[0];
	buf2 = powMod(A[1],h,A[0]);
	//cout<<"buf1 = "<<buf1<<endl;	//cout<<"buf2 = "<<buf2<<endl;
	if (buf1 == buf2) cout<<"The sign is correct"<<endl; else cout<<"The sign is incorrect"<<endl;			
}

int prompt_menu_item()
{
    int variant;
    cout << "Select option\n" << endl;
    cout << "1. Sign\n"
         << "2. Verify sign\n"
         << "3. Exit\n" << endl;
    cout << ">>> ";
    cin >> variant;
    return variant;
}

void El_Gamal_main() {
	int variant = prompt_menu_item();
	switch (variant) {
        case 1:{
            cout << "Sign file..." << endl;
	    char filename[70] = "";
	    cout<<"Enter the file name with the extension"<<endl;
	    scanf("%s", filename);
	    El_Gamal_sign(filename);
            break;
		}
        case 2:{
            cout << "Verify sign..." << endl;
	    char filename[70] = "";
	    cout<<"Enter the file name with the extension"<<endl;
	    scanf("%s", filename);
	    El_Gamal_verify(filename);
            break;
	       } 
        case 3:
            cout << "Quit..." << endl;
            exit(EXIT_SUCCESS);
            break;
        default:
            cerr << "You selected the wrong option" << endl;
            exit(EXIT_FAILURE);			
}
}

void RSA_sign(char FileName[]) {
	srand(time(0));
	char FileName1[70]=""; char str1[70] = ".rsa.sign";strcat(FileName1,FileName);strcat(FileName1,str1);
	long long Pa,Qa,Na,fa; long long Ca, Da; long long h,s; char buf[1];
	while(1) { Pa = rand() % 31600; if (test_Ferma(Pa)==1) break; }
	while(1) { Qa = rand() % 31600; if (test_Ferma(Qa)==1) break; }
	Na = Pa*Qa;
	fa = (Pa - 1)*(Qa - 1);
	while (1) {
	Da = ((rand()<<15) | rand()) % (fa + 1);
	if (evklid_nod(Da,fa)==1) break;
	}
	Ca = evklid_y(fa,Da); if (Ca<0) Ca = Ca+fa; 
        h = MD5(FileName) % Na;
        s= powMod(h,Ca,Na);
	ofstream fout(FileName1,ios::binary);
	if (fout.good()) {
	fout<<s<<endl<<Da<<endl<<Na;
	}
	fout.close();
	cout<<"The file was successfully signed"<<endl;
}

void RSA_verify (char FileName[]){
	char FileName1[70]=""; char str1[70] = ".rsa.sign";strcat(FileName1,FileName);strcat(FileName1,str1);
	char buff[100];long long A[3];long long h1,h2; int i = 0;
	ifstream fin1(FileName1,ios::binary);
        if (fin1.good()) {
	while (1) { if (fin1.eof()) break; fin1.getline(buff, sizeof(buff));	A[i]=_atoi64(buff); i++; } 
	}
	fin1.close();
	h1 = MD5(FileName) % A[2];
	h2 = powMod(A[0],A[1],A[2]);
	if (h1 == h2) cout<<"The sign is correct"<<endl; else cout<<"The sign is incorrect"<<endl;			
}
	
	
void RSA_main() {
	int variant = prompt_menu_item();
	switch (variant) {
        case 1:{
            cout << "Sign file..." << endl;
	    char filename[70] = "";
	    cout<<"Enter the file name with the extension"<<endl;
	    scanf("%s", filename);
	    RSA_sign(filename);
            break;
		}
        case 2:{
            cout << "Verify sign..." << endl;
	    char filename[70] = "";
	    cout<<"Enter the file name with the extension"<<endl;
	    scanf("%s", filename);
	    RSA_verify(filename);
            break;
	       } 
        case 3:
            cout << "Quit..." << endl;
            exit(EXIT_SUCCESS);
            break;
        default:
            cerr << "You selected the wrong option" << endl;
            exit(EXIT_FAILURE);			
}
}

void GOST_sign(char FileName[]) {
	srand(time(0));
	char FileName1[70]=""; char str1[70] = ".gost.sign";strcat(FileName1,FileName);strcat(FileName1,str1);
	long long q,p,b,a,g; long long x,y,h,r,s,k;// q,b - 15 bit
	/*
	while (1) {
	q = ((rand()<<15) | rand()) % 30000;
	if (test_Ferma(q)==true) {
		b = ((rand()<<15) | rand()) % 30000;
		p = b * q + 1;
		//cout<<"q = "<<q<<" ";	//cout<<"b = "<<b<<" "; //cout<<"Ishem 1...";	//cout<<" p = "<<p<<endl;
		if (test_Ferma(p)==true) {
		a = rand()+1; cout<<"Ishem...";
		if ((a>0)&&(powMod(a,q,p)==1)) break;
		}
	}
	}
	*/
	while (1) {
	q = ((rand()<<15) | rand()) % 30000;
	if (test_Ferma(q)==true) {
		b = ((rand()<<15) | rand()) % 30000;
		p = b * q + 1;
		//cout<<"q = "<<q<<" ";	//cout<<"b = "<<b<<" "; //cout<<"Ishem 1...";	//cout<<" p = "<<p<<endl;
		if (test_Ferma(p)==true) {
		label1:
		g = ((rand()<<15) | rand()) % 30000;
		a = powMod(g,(p-1)/q,p);
		if (a>1) break;
		if (a==1) goto label1;
		//cout<<"Ishem...";
		//if ((a>0)&&(powMod(a,q,p)==1)) break;
		}
	}
	}
	//cout<<"DOSHEL"<<endl;
	//cout<<"q = "<<q<<endl;
	//cout<<"b = "<<b<<endl;
	//cout<<"p = "<<p<<endl;
	//cout<<"a = "<<a<<endl;

	x = ((rand()<<15) | rand()) % q; // Секретный ключ
	//cout<<"x = "<<x<<endl;
	y = powMod(a,x,p); // Открытый ключ
	h = MD5(FileName) % q;
	//cout<<"y = "<<y<<endl;
	//cout<<"h = "<<h<<endl;
	while(1) {
	label2:
	k = ((rand()<<15) | rand()) % q;
	r = powMod(a,k,p) % q;
	if (r == 0 ) goto label2;  
	s = ((k % q * h % q) % q + (x % q * r % q) % q) % q;
	if (s == 0 ) goto label2;
	break;
	}
	//cout<<"r = "<<r<<endl;
	//cout<<"s = "<<s<<endl;
	ofstream fout(FileName1,ios::binary);
	if (fout.good()) {
	fout<<s<<endl<<r<<endl<<q<<endl<<y<<endl<<a<<endl<<p;
	}
	fout.close();
	if ((r<q) && (s<q)) cout<<"The file was successfully signed"<<endl; else cout<<"The file was not successfully signed"<<endl;
}

void GOST_verify (char FileName[]){
	char FileName1[70]=""; char str1[70] = ".gost.sign";strcat(FileName1,FileName);strcat(FileName1,str1);
	char buff[100];long long A[6];long long h,u1,u2,v,h1,r,s; int i = 0;
	ifstream fin1(FileName1,ios::binary);
        if (fin1.good()) {
	while (1) { if (fin1.eof()) break; fin1.getline(buff, sizeof(buff));	A[i]=_atoi64(buff); i++; } 
	}
	fin1.close();
	h = MD5(FileName) % A[2];
	if (((A[1]>0) && (A[1]<A[2])) && ((A[0]>0) && (A[0]<A[2]))) {
	h1 = evklid_y(A[2],h); if (h1<0) h1 = h1 + A[2]; //cout<<"h1 = "<<h1<<endl;
	u1 = (A[0] % A[2] * h1 % A[2]) % A[2]; //cout<<"u1 = "<<u1<<endl;
	u2 = (-A[1] % A[2] * h1 % A[2]) % A[2]; if (u2<0) u2 = u2 + A[2];  //cout<<"u2 = "<<u2<<endl;  
	v = ((powMod(A[4],u1,A[5])*powMod(A[3],u2,A[5])) % A[5]) % A[2];  //cout<<"v = "<<v<<endl;
	//cout<<"r = "<<A[1]<<endl;
	} else cout<<"Uslovie ne sovpadaet"<<endl; 
	if (v == A[1]) cout<<"The sign is correct"<<endl; else cout<<"The sign is incorrect"<<endl;			
}

void GOST_main() {
	int variant = prompt_menu_item();
	switch (variant) {
        case 1:{
            cout << "Sign file..." << endl;
	    char filename[70] = "";
	    cout<<"Enter the file name with the extension"<<endl;
	    scanf("%s", filename);
	    GOST_sign(filename);
            break;
		}
        case 2:{
            cout << "Verify sign..." << endl;
	    char filename[70] = "";
	    cout<<"Enter the file name with the extension"<<endl;
	    scanf("%s", filename);
	    GOST_verify(filename);
            break;
	       } 
        case 3:
            cout << "Quit..." << endl;
            exit(EXIT_SUCCESS);
            break;
        default:
            cerr << "You selected the wrong option" << endl;
            exit(EXIT_FAILURE);			
}
}



int prompt_menu_item_main()
{
    int variant;
    cout << "Выберите вариант\n" << endl;
    cout << "1. El Gamal \n"
         << "2. RSA\n"
	 << "3. GOST\n"
         << "4. Exit\n" << endl;
    cout << ">>> ";
    cin >> variant;
    return variant;
}


int main() {
	setlocale (0,"Rus");
	int variant = prompt_menu_item_main();
	
	switch (variant) {
        case 1:{
            cout << "Выбран вариант El Gamal" << endl;
	    El_Gamal_main();
            break;
		}
        case 2:{
            cout << "Выбран вариант RSA" << endl;
	    RSA_main();
            break;
	       }
        case 3:{
            cout << "Выбран вариант Gost" << endl;
	    GOST_main();
            break;
	       } 
        case 4:
            cout << "Выход из программы..." << endl;
            exit(EXIT_SUCCESS);
            break;
        default:
            cerr << "Вы выбрали неверный вариант" << endl;
            exit(EXIT_FAILURE);			
}
	system("pause");	
}
