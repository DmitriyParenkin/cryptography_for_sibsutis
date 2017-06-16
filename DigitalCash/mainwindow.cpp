#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <lib.h>
#include <QDebug>
#include <QCryptographicHash>
#include <QtMath>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     show_money();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::show_money() {
    ui->money_client->setText(QString::number(Client_money));
    ui->money_store->setText(QString::number(Store_money));
    ui->Transaction->setText(QString::number(Transaction));
}

void MainWindow::start_DigitalCash(int n){
    srand(time(NULL));
    int Number_money[11]; int sum = 0;
    long long P,Q,N,f,C[10],D[10]; int count1; QString dec;
    while(1) {
        while(1) { P = rand() % 30000; if (test_Ferma(P)==1) break;}
        cout<<endl;
        while(1) { Q = rand() % 30000; if (test_Ferma(Q)==1) break;}
        if ((P!=Q) && (P!=1) && (Q!=1)) break;
    }
    N = P*Q;
    f = (P-1) * (Q-1);
    //qDebug() <<"P = "<<P;
    //qDebug() <<"Q = "<<Q;
    //qDebug() <<"N = "<<N;
    //qDebug() <<"f = "<<f;
    for (int i=0;i<11;i++){ D[i] = 0; C[i] = 0; }
    for (int i=0;i<11;i++){
    while(1) {
    D[i] = ((rand()<<15) | rand()) % (f);
    if (evklid_nod(D[i],f)==1) { count1++; break;}
    }
    if (count1 == 11) break;
    }
    for (int i = 0; i < 11; i++) { C[i] = evklid_y(D[i],f);  if (C[i]<0) C[i] = C[i] + (f);}
    //for (int i = 0; i < 11; i++) qDebug()<<i<<" "<<D[i];
    //qDebug()<<endl;
    //for (int i = 0; i < 11; i++) qDebug()<<i<<" "<<C[i];
    for (int i = 0; i <= 11; i++) Number_money[i]=0;
    split_money(n, Number_money);
    Transaction++;
    for (int i = 0; i < 11; i++)  if (Number_money[i]!= 0) {  sum = sum + check_money(i);}
    if (Client_money < sum) {
        QMessageBox msgBox;
        msgBox.setText("Не хватает денег");
        msgBox.exec();
    } else //for (int i = 0; i < 11; i++){
        //if (Number_money[i]!= 0) {

            //start_Transaction(i,C,D,N);
        //}
        for (int i = 0; i < 11; i++) {

        asd:
        if (Number_money[i]!=0) {
            start_Transaction(i,C,D,N);
            Number_money[i]--; goto asd;



        }
        //while(1) {
        //if (Number_money[i]!=0) start_Transaction(i,C,D,N); Number_money[i]--;
        //if (Number_money[i]==0) break;
        //}
        //}
        }
}

long long MainWindow::start_hash(QString s) {
    //QString s = "201";
    QByteArray ba = s.toUtf8();
    QString hash1 = QCryptographicHash::hash(ba, QCryptographicHash::Sha3_512).toHex();
    long long sum=0;
     QChar *data = hash1.data();
     while (!data->isNull()) {
         sum = sum + data->unicode();
         ++data;
     }
     return sum;
}

void MainWindow::start_Transaction(int index_money, long long C[], long long D[],long long N) {
   long long r,r1,n,n1,s,s1,s2,hash_n; int summa = 0;QString dec;
   //qDebug()<<index_money;
   summa = check_money(index_money);
   //qDebug()<<"summa = "<<summa;

   while (1) {
       r = (1+(rand()<<15) | rand()) % (N-1);
       if (evklid_nod(r,N)==1) break;
   }
   //qDebug()<<"r = "<<r;
   r1 = evklid_y(r,N); if (r1<0) r1 = r1 + N;
   //qDebug()<<"r1 = "<<r1;
   n = 1 + rand() % N;
   //qDebug()<<"n = "<<n;
   dec = QString::number(n);
   //qDebug()<<"dec = "<<dec;
   hash_n = start_hash(dec);
   n1 = ((hash_n % N) * powMod(r,D[index_money],N)) % N;
   //qDebug()<<"n1 = "<<n1;
   s1 = powMod(n1,C[index_money],N);
   //qDebug()<<"s1 = "<<s1;
   s = (powMod(s1,1,N) * powMod(r1,1,N)) % N;
   //qDebug()<<"s = "<<s;
   // передаем n и s
   s2 = powMod(s,D[index_money],N);
   //s1 = powMod(hash_n,C[index_money],N);
   //s2 = powMod(s1,D[index_money],N);
  // qDebug()<<"s2 = "<<s2;
  // qDebug()<<"Подписи";
  // qDebug()<<endl;
  //qDebug()<<"s1 = "<<s1;
  //qDebug()<<"hash_n = "<<hash_n;
  //qDebug()<<"s2 = "<<s2;
   if ((hash_n==s2) && (summa<=Client_money)) {
       Client_money = Client_money - summa;
       Store_money = Store_money + summa;

   }
    show_money();
}

int MainWindow::check_money(int index_money) {
    switch(index_money) {
        case 0: { return 1;break;}
        case 1: { return 2;break;}
        case 2: { return 5;break;}
        case 3: { return 10;break;}
        case 4: { return 50;break;}
        case 5: { return 100;break;}
        case 6: { return 200;break;}
        case 7: { return 500;break;}
        case 8: { return 1000;break;}
        case 9: { return 2000;break;}
        case 10: { return 5000;break;}
    }
}

void MainWindow::split_money(int n, int* Number_money) {
    int count5000=0,count2000=0,count1000=0,count500=0,count200=0,count100=0,count50=0,count10=0,count5=0,count2=0,count1=0;
    int temp = n;
    while (temp>=5000) { temp-=5000; count5000++; }
    while (temp>=2000) { temp-=2000; count2000++; }
    while (temp>=1000) { temp-=1000; count1000++; }
    while (temp>=500) { temp-=500; count500++; }
    while (temp>=200) { temp-=200; count200++; }
    while (temp>=100) { temp-=100; count100++; }
    while (temp>=50) { temp-=50; count50++; }
    while (temp>=10) { temp-=10; count10++; }
    while (temp>=5) { temp-=5; count5++; }
    while (temp>=2) { temp-=2; count2++; }
    while (temp>=1) { temp-=1; count1++; }
    Number_money[0] = count1;
    Number_money[1] = count2;
    Number_money[2] = count5;
    Number_money[3] = count10;
    Number_money[4] = count50;
    Number_money[5] = count100;
    Number_money[6] = count200;
    Number_money[7] = count500;
    Number_money[8] = count1000;
    Number_money[9] = count2000;
    Number_money[10] = count5000;
}

void MainWindow::on_pushButton_clicked()
{
   emit start_DigitalCash(350);
}

void MainWindow::on_pushButton_2_clicked()
{
   emit start_DigitalCash(550);
}

void MainWindow::on_pushButton_4_clicked()
{
    emit start_DigitalCash(100);
}


void MainWindow::on_pushButton_5_clicked()
{
    bool ok;
        QString w = ui->lineEdit->text();
        int count_money = w.toInt(&ok);
        emit start_DigitalCash(count_money);

}
