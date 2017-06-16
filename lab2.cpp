#include "lib.h"
#include "fstream"


// powMod(a,b,p)
// evklid_nod(a,b) evklid_x(a,b) evklid_y(a,b)
// test_Ferma(p)
// Diffi_Hellman() random(p,q,g)
// mladenes_velikan(a,p,y)

long long Shamir(long long m)  {
	srand(time(0));
	long long p=0;long long Ca,Cb,Da,Db=0;long long x1,x2,x3,x4=0;
	while (1) { p = (rand()<<15) | rand(); if (test_Ferma(p)==1) break;}
	while (1) {
	Ca = ((rand()<<15) | rand()) % (p-2)+1; Cb = ((rand()<<15) | rand()) % (p-2)+1;
	if ((evklid_nod(Ca,p-1)==1) && (evklid_nod(Cb,p-1)==1)) break;
	}
	Da = evklid_y(Ca,p-1); Db = evklid_y(Cb,p-1);
	if (Da<0) Da = Da + (p-1); if (Db<0) Db = Db + (p-1);
	x1 = powMod(m,Ca,p); x2 = powMod(x1,Cb,p); x3 = powMod(x2,Da,p); x4 = powMod(x3,Db,p);
	return x4;
}
 
void El_Gamal_encrypt(char FileName[]){
	srand(time(0));
	char FileName1[70]=""; char str1[70] = "_r.encrypt";strcat(FileName1,FileName);strcat(FileName1,str1);
	char FileName2[70]=""; char str2[70] = "_e.encrypt";strcat(FileName2,FileName);strcat(FileName2,str2);
	char FileName3[70]=""; char str3[70] = "_xb.encrypt";strcat(FileName3,FileName);strcat(FileName3,str3);
	long long p,q,g=0; long long k,r,e; long long yA, yB; long long xA, xB;
	char buf[1];
	random(p,q,g);
	xA = ((rand()<<15) | rand()) % (p-1);
	xB = ((rand()<<15) | rand()) % (p-1);
	yA = powMod(g,xA,p);  yB = powMod(g,xB,p);
	ifstream fin(FileName,ios::binary);
	if (fin.good()) {    
    	ofstream fout1(FileName1,ios::binary);
    	if (fout1.good()) {
	ofstream fout2(FileName2,ios::binary);
	if (fout2.good()) { 
        do {
            fin.read(&buf[0],1);
            if (fin.eof()) break;
	    k = (rand()% (p-2)+1);
	    r = powMod(g,k,p);  
	    fout1<<r<<" ";
	    e = powMod(yB,k,p)*buf[0]%p; 
	    fout2<<e<<" ";
        } while (!fin.eof());
    	fin.close();
    	fout1.close();
	fout2.close();
	ofstream fout3(FileName3);
	if (fout3.good()) fout3<<xB<<endl<<p;
    	}
	cout<<"Файл успешно зашифрован"<<endl;	
	}
	} else cout<<"Такого файла нет"<<endl;
}

void El_Gamal_decrypt(char FileName[]) {
	char FileName1[70]=""; char str1[70] = "_r.encrypt";strcat(FileName1,FileName);strcat(FileName1,str1);
	char FileName2[70]=""; char str2[70] = "_e.encrypt";strcat(FileName2,FileName);strcat(FileName2,str2);
	char FileName3[70]=""; char str3[70] = "_xb.encrypt";strcat(FileName3,FileName);strcat(FileName3,str3);
	char FileName4[70]=""; char str4[70] = ".decrypt";strcat(FileName4,FileName);strcat(FileName4,str4);
	char buf1[1],buf2[1],buf3[1]; char  buff[100]; long long A[2]; int i=0;	 long long m1,m2; long long e,r;
	ifstream fin1(FileName1,ios::binary);
	ifstream fin2(FileName2,ios::binary);
	ifstream fin3(FileName3);
	ofstream fout(FileName4,ios::binary);
	if (fin3.good()) {
	while (1) {
 	if (fin3.eof()) break;
 	fin3.getline(buff, sizeof(buff));
 	A[i]=_atoi64(buff); i++;
	} }
	fin3.close();
	if (fin1.good() && fin2.good() && fout.good()) { 
	do {
	    fin1>>r;
	    fin2>>e;
            if ((fin1.eof())&&(fin2.eof())) break;
	    m1 = (e%A[1]*powMod(r,A[1]-1-A[0],A[1]))%A[1]; //(a%p * b%p ) %p
            char m2 = static_cast<char>(m1);
            fout<<m2;
        } while ((!fin1.eof()) && (!fin2.eof()));
	cout<<"Файл успешно расшифрован"<<endl;
	} else cout<<"Такого файла нет"<<endl;
	fin1.close();fin2.close();fout.close();		
}

int prompt_menu_item()
{
    int variant;
    cout << "Выберите вариант\n" << endl;
    cout << "1. Зашифровать файл\n"
         << "2. Расшифровать файл\n"
         << "3. Выйти\n" << endl;
    cout << ">>> ";
    cin >> variant;
    return variant;
}

void El_Gamal_main() {
	int variant = prompt_menu_item();
	switch (variant) {
        case 1:{
            cout << "Зашифровать файл..." << endl;
	    char filename[70] = "";
	    cout<<"Введите имя файла с расширением"<<endl;
	    scanf("%s", filename);
	    El_Gamal_encrypt(filename);
            break;
		}
        case 2:{
            cout << "Расшифровать файл..." << endl;
	    char filename[70] = "";
	    cout<<"Введите имя файла с расширением"<<endl;
	    scanf("%s", filename);
	    El_Gamal_decrypt(filename);
            break;
	       } 
        case 3:
            cout << "Выход из программы..." << endl;
            exit(EXIT_SUCCESS);
            break;
        default:
            cerr << "Вы выбрали неверный вариант" << endl;
            exit(EXIT_FAILURE);			
}
}

long long RSA(long long m){
	long long Pa,Qa,Na,fa; long long Pb, Qb, Nb, fb; long long Ca, Da, Cb, Db; long long e,m1;
	Pa = ((rand()<<15) | rand()); Pb = ((rand()<<15) | rand());
	Qa = ((rand()<<15) | rand()); Qb = ((rand()<<15) | rand());
	fa = (Pa - 1)*(Qa - 1); fb = (Pb - 1)*(Qb - 1);
	cout<<fa<<" "<<fb;
	while (1) {
	Da = ((rand()<<15) | rand()) % (fa + 1);
	Db = ((rand()<<15) | rand()) % (fb + 1);
	if ((evklid_nod(Da,fa)==1) && (evklid_nod(Db,fb)==1))  break;
	}
	Ca = evklid_y(fa,Da); Cb = evklid_y(fb,Db);
	e = powMod(e,Db,Nb);
	m1 = powMod(e,Cb,Nb);
	return m1;
	}
void RSA_encrypt(char FileName[]) {
	srand(time(0));
	char FileName1[70]=""; char str1[70] = "_e.encrypt";strcat(FileName1,FileName);strcat(FileName1,str1);
	char FileName2[70]=""; char str2[70] = "_cbnb.encrypt";strcat(FileName2,FileName);strcat(FileName2,str2);
	long long Pa,Qa,Na,fa; long long Pb, Qb, Nb, fb; long long Ca, Da, Cb, Db; long long e,m1; char buf[1];
	while(1) { Pa = rand() % 30000; if (test_Ferma(Pa)==1) break; }
	while(1) { Pb = rand() % 30000; if (test_Ferma(Pb)==1) break; }
	while(1) { Qa = rand() % 30000; if (test_Ferma(Qa)==1) break; }
    while(1) { Qb = rand() % 30000; if (test_Ferma(Qb)==1) break; }
	Na = Pa*Qa; Nb = Pb*Qb;
	fa = (Pa - 1)*(Qa - 1); fb = (Pb - 1)*(Qb - 1);
	while (1) {
	Da = ((rand()<<15) | rand()) % (fa + 1);
	Db = ((rand()<<15) | rand()) % (fb + 1);
	if ((evklid_nod(Da,fa)==1) && (evklid_nod(Db,fb)==1))  break;
	}
	Ca = evklid_y(fa,Da); if (Ca<0) Ca = Ca+fa; 
	Cb = evklid_y(fb,Db); if (Cb<0) Cb = Cb+fb;
        ifstream fin(FileName,ios::binary);
	if (fin.good()) {    
    	ofstream fout1(FileName1,ios::binary);
    	if (fout1.good()) {
        do {
            fin.read(&buf[0],1);
 	    if (fin.eof()) break;
	    e = powMod(buf[0],Db,Nb); 
	    fout1<<e<<" ";
	} while (!fin.eof());
        fin.close();
    	fout1.close();
	ofstream fout2(FileName2);
	if (fout2.good()) fout2<<Cb<<endl<<Nb;
    	}
	cout<<"Файл успешно зашифрован"<<endl;
	} else cout<<"Не удается найти файл"<<endl;
}

void RSA_decrypt(char FileName[]){
	char FileName1[70]=""; char str1[70] = "_e.encrypt";strcat(FileName1,FileName);strcat(FileName1,str1);
	char FileName2[70]=""; char str2[70] = "_cbnb.encrypt";strcat(FileName2,FileName);strcat(FileName2,str2);
	char FileName3[70]=""; char str3[70] = ".decrypt";strcat(FileName3,FileName);strcat(FileName3,str3);
        char buff[100];long long A[2];long long e;long long m1,m2; int i = 0;
	ifstream fin1(FileName1,ios::binary);
	ifstream fin2(FileName2);
	ofstream fout(FileName3,ios::binary);
        if (fin2.good()) {
	while (1) { if (fin2.eof()) break; fin2.getline(buff, sizeof(buff));	A[i]=_atoi64(buff); i++; } 
	}
	fin2.close();
	if (fin1.good() && fout.good()) {
	do {
	if (fin1.eof()) break;
	fin1>>e;
	m1 = powMod(e,A[0],A[1]); 
	char m2 = static_cast<char>(m1);
        fout<<m2;
	} while (!fin1.eof());
	cout<<"Файл успешно расшифрован"<<endl;
	} else cout<<"Такого файла нет"<<endl;
	fin1.close();fin2.close();fout.close();
}
	
	
void RSA_main() {
	int variant = prompt_menu_item();
	switch (variant) {
        case 1:{
            cout << "Зашифровать файл..." << endl;
	    char filename[70] = "";
	    cout<<"Введите имя файла с расширением"<<endl;
	    scanf("%s", filename);
	    RSA_encrypt(filename);
            break;
		}
        case 2:{
            cout << "Расшифровать файл..." << endl;
	    char filename[70] = "";
	    cout<<"Введите имя файла с расширением"<<endl;
	    scanf("%s", filename);
	    RSA_decrypt(filename);
            break;
	       } 
        case 3:
            cout << "Выход из программы..." << endl;
            exit(EXIT_SUCCESS);
            break;
        default:
            cerr << "Вы выбрали неверный вариант" << endl;
            exit(EXIT_FAILURE);			
}
}

void Vernam_encrypt(char FileName[]) {
	srand(time(0));
	char FileName1[70]=""; char str1[70] = "_e.encrypt";strcat(FileName1,FileName);strcat(FileName1,str1);
	char FileName2[70]=""; char str2[70] = "_k.encrypt";strcat(FileName2,FileName);strcat(FileName2,str2);
	char e; char buf[1]; char k;
	ifstream fin(FileName,ios::binary);
	if (fin.good()) {    
    	ofstream fout1(FileName1,ios::binary);
    	if (fout1.good()) {
	ofstream fout2(FileName2,ios::binary);
	if (fout2.good()) {
        do {
	    if (fin.eof()) break;
            fin.read(&buf[0],1);   	    	
            k = rand() % 256;
            e =buf[0]^k;
            fout1.write(&e,1);
	    fout2.write(&k,1);
	} while (!fin.eof());
        fin.close();
    	fout1.close();
	fout2.close();
    	}
	}
	cout<<"Файл успешно зашифрован"<<endl;
	} else cout<<"Не удается найти файл"<<endl;		
}

void Vernam_decrypt(char FileName[]) {
	char FileName1[70]=""; char str1[70] = "_e.encrypt";strcat(FileName1,FileName);strcat(FileName1,str1);
	char FileName2[70]=""; char str2[70] = "_k.encrypt";strcat(FileName2,FileName);strcat(FileName2,str2);
	char FileName3[70]=""; char str3[70] = ".decrypt";strcat(FileName3,FileName);strcat(FileName3,str3);
	char m1,m2; char k,e; char buf1[1],buf2[1];
	ifstream fin1(FileName1,ios::binary);
	ifstream fin2(FileName2,ios::binary);
	ofstream fout(FileName3,ios::binary);
	if (fin1.good()) {
	do {
	fin1.read(&e,1);
	fin2.read(&k,1);
	m1 = e^k;
	 	fout.write(&m1,1);
	} while (!fin1.eof() && !fin2.eof());
	cout<<"Файл успешно расшифрован"<<endl;
	} else cout<<"Такого файла нет"<<endl;
	fin1.close();fin2.close();fout.close();
}

void Vernam_main() {
        int variant = prompt_menu_item();
	switch (variant) {
        case 1:{
            cout << "Зашифровать файл..." << endl;
	    char filename[70] = "";
	    cout<<"Введите имя файла с расширением"<<endl;
	    scanf("%s", filename);
	    Vernam_encrypt(filename);
            break;
		}
        case 2:{
            cout << "Расшифровать файл..." << endl;
	    char filename[70] = "";
	    cout<<"Введите имя файла с расширением"<<endl;
	    scanf("%s", filename);
	    Vernam_decrypt(filename);
            break;
	       } 
        case 3:
            cout << "Выход из программы..." << endl;
	    exit(EXIT_SUCCESS);
            break;
        default:
            cerr << "Вы выбрали неверный вариант" << endl;
            exit(EXIT_FAILURE);			
}
}


int prompt_menu_item_main()
{
    int variant;
    cout << "Выберите вариант\n" << endl;
    cout << "1. Shamir \n"
         << "2. El_Gamal\n"
	 << "3. RSA\n"
	 << "4. Vernam\n"
         << "5. Exit\n" << endl;
    cout << ">>> ";
    cin >> variant;
    return variant;
}


int main() {
	setlocale (0,"Rus");
	int variant = prompt_menu_item_main();
	
	switch (variant) {
        case 1:{
            cout << "Выбран вариант Shamir" << endl;
	    long long m; cout<< "Введите сообщение m"<<endl;
	    cin>>m;
	    cout<<"m = "<<Shamir(m)<<endl;
            break;
		}
        case 2:{
            cout << "Выбран вариант El_Gamal" << endl;
	    El_Gamal_main();
            break;
	       }
        case 3:{
            cout << "Выбран вариант RSA" << endl;
	    RSA_main();
            break;
	       }
        case 4:{
            cout << "Выбран вариант Vernam" << endl;
	    Vernam_main();
            break;
	       } 
        case 5:
            cout << "Выход из программы..." << endl;
            exit(EXIT_SUCCESS);
            break;
        default:
            cerr << "Вы выбрали неверный вариант" << endl;
            exit(EXIT_FAILURE);			
}
	system("pause");	
}
