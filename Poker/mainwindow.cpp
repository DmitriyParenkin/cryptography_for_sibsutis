#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "algorithm"
#include "QVector"
#include "qiterator.h"
#include "time.h"
#include "lib.h"
#include "QDebug"
#include "QTimer"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_poker(int n){

    srand(time(NULL));
    long long p,C[n],D[n],koloda[60],karta1[52],karta2[52],kart5[5]; int count1;
    while (1) { p = ((rand()<<15) | rand()); if (test_Ferma(p)==1) break; }
    for (int i=0;i<n;i++){
    while(1) {
    C[i] = ((rand()<<15) | rand()) % (p-1);
    if (evklid_nod(C[i],p-1)==1) { count1++; break;}
    }
    if (count1 == n) break;
    }
    for (int i = 0; i < n; i++) { D[i] = evklid_y(C[i],p-1);  if (D[i]<0) D[i] = D[i] + (p-1);}
    for (int i = 2; i < 55; i++) {
    koloda[i] = i;
    }
    for (int i = 0; i < n; i++) qDebug()<<D[i];
    qDebug()<<endl;
    for (int i = 0; i < n; i++) qDebug()<<C[i];
    for (int i = 0; i < n; i++) zamok_shuffle(koloda,C,i,p);
    for (int i = 0; i < n; i++) {   karta1[i] = 0; karta2[i] = 0; }
    for (int i = 0; i < 5;i++) kart5[i]=0;
    for (int i = 0; i < n;i++) razdacha_kart(karta1,karta2,koloda,i);

    for (int i = 0; i<n; i++)
    for (int j = 0; j<n; j++) {
       if (i == j) {

       } else {
           karta1[i] = powMod(karta1[i],D[j],p);
           karta2[i] = powMod(karta2[i],D[j],p);
       }
    }

    for (int i = 0; i<n; i++)  {
        karta1[i] = powMod(karta1[i],D[i],p);
        karta2[i] = powMod(karta2[i],D[i],p);
    }

    for (int i = 2; i<55; i++)
    for (int j = 0; j<n; j++) {
      koloda[i] = powMod(koloda[i],D[j],p);
    }

    MainWindow::show_hide(n);
    MainWindow::show_hide1(n);
    for (int i = 0; i < n; i++) MainWindow::show_kart1(i,karta1);
    for (int i = 0; i < n; i++) MainWindow::show_kart2(i,karta2);
    for (int i = 0; i < 5;i++) razdacha_kart5(kart5, koloda, i);

    for (int i = 0; i < 5;i++) {
        MainWindow::show_kart5(i,kart5);
    }
}

int MainWindow::on_pushButton_clicked()
{
    bool ok;
    QString w = ui->lineEdit->text();
    int number_player = w.toInt(&ok);
    if (number_player>10) {
        QMessageBox msgBox;
        msgBox.setText("Введите число меньше 11");
        msgBox.exec();
    } else emit start_poker(number_player);
}


void* MainWindow::show_hide(int n) {
    QLabel* mas[10];
    QLabel* mas1[10];
    mas[0] = ui->player1_1card;    mas[1] = ui->player2_1card;    mas[2] = ui->player3_1card;    mas[3] = ui->player4_1card;
    mas[4] = ui->player5_1card;    mas[5] = ui->player6_1card;    mas[6] = ui->player7_1card;    mas[7] = ui->player8_1card;
    mas[8] = ui->player9_1card;    mas[9] = ui->player10_1card;    mas1[0] = ui->player1_2card;    mas1[1] = ui->player2_2card;
    mas1[2] = ui->player3_2card;    mas1[3] = ui->player4_2card;    mas1[4] = ui->player5_2card;    mas1[5] = ui->player6_2card;
    mas1[6] = ui->player7_2card;    mas1[7] = ui->player8_2card;    mas1[8] = ui->player9_2card;    mas1[9] = ui->player10_2card;
    for (int i = 0; i < 10; i++) { mas[i]->hide(); mas1[i]->hide(); }
}

void* MainWindow::show_hide1(int n) {
    QLabel* mas[10];
    QLabel* mas1[10];
    mas[0] = ui->player1_1card;    mas[1] = ui->player2_1card;    mas[2] = ui->player3_1card;    mas[3] = ui->player4_1card;
    mas[4] = ui->player5_1card;    mas[5] = ui->player6_1card;    mas[6] = ui->player7_1card;    mas[7] = ui->player8_1card;
    mas[8] = ui->player9_1card;    mas[9] = ui->player10_1card;    mas1[0] = ui->player1_2card;    mas1[1] = ui->player2_2card;
    mas1[2] = ui->player3_2card;    mas1[3] = ui->player4_2card;    mas1[4] = ui->player5_2card;    mas1[5] = ui->player6_2card;
    mas1[6] = ui->player7_2card;    mas1[7] = ui->player8_2card;    mas1[8] = ui->player9_2card;    mas1[9] = ui->player10_2card;
    for (int i = 0; i < n; i++) { mas[i]->show(); mas1[i]->show(); }
}

void* MainWindow::show_kart1(int i, long long* karta1){

    long long buf1 = karta1[i];
    QLabel* mas[10];
    mas[0] = ui->player1_1card;
    mas[1] = ui->player2_1card;
    mas[2] = ui->player3_1card;
    mas[3] = ui->player4_1card;
    mas[4] = ui->player5_1card;
    mas[5] = ui->player6_1card;
    mas[6] = ui->player7_1card;
    mas[7] = ui->player8_1card;
    mas[8] = ui->player9_1card;
    mas[9] = ui->player10_1card;

    switch (buf1) {
        case 2:{
        QPixmap card2(":/images/images/Сердце/Червь 2.png");card2 = card2.scaled(81,123);
        mas[i]->setPixmap(card2); break;
        }
        case 3:{
        QPixmap card3(":/images/images/Сердце/Червь 3.png");card3 = card3.scaled(81,123);
        mas[i]->setPixmap(card3); break;
        }
        case 4:{
        QPixmap card4(":/images/images/Сердце/Червь 4.png");card4 = card4.scaled(81,123);
        mas[i]->setPixmap(card4); break;
        }
        case 5:{
        QPixmap card5(":/images/images/Сердце/Червь 5.png");card5 = card5.scaled(81,123);
        mas[i]->setPixmap(card5); break;
        }
        case 6:{
        QPixmap card6(":/images/images/Сердце/Червь 6.png");card6 = card6.scaled(81,123);
        mas[i]->setPixmap(card6); break;
        }
        case 7:{
        QPixmap card7(":/images/images/Сердце/Червь 7.png");card7 = card7.scaled(81,123);
        mas[i]->setPixmap(card7); break;
        }
        case 8:{
        QPixmap card8(":/images/images/Сердце/Червь 8.png");card8 = card8.scaled(81,123);
        mas[i]->setPixmap(card8); break;
        }
        case 9:{
        QPixmap card9(":/images/images/Сердце/Червь 9.png");card9 = card9.scaled(81,123);
        mas[i]->setPixmap(card9); break;
        }
        case 10:{
        QPixmap card10(":/images/images/Сердце/Червь 10.png");card10 = card10.scaled(81,123);
        mas[i]->setPixmap(card10); break;
        }
        case 11:{
        QPixmap card11(":/images/images/Сердце/Червь В.png");card11 = card11.scaled(81,123);
        mas[i]->setPixmap(card11); break;
        }
        case 12:{
        QPixmap card12(":/images/images/Сердце/Червь Д.png");card12 = card12.scaled(81,123);
        mas[i]->setPixmap(card12); break;
        }
        case 13:{
        QPixmap card13(":/images/images/Сердце/Червь К.png");card13 = card13.scaled(81,123);
        mas[i]->setPixmap(card13); break;
        }
        case 14:{
        QPixmap card14(":/images/images/Сердце/Червь Т.png");card14 = card14.scaled(81,123);
        mas[i]->setPixmap(card14); break;
        }
        case 15:{
        QPixmap card15(":/images/images/Пики/Пики 2.png");card15 = card15.scaled(81,123);
        mas[i]->setPixmap(card15); break;
        }
        case 16:{
        QPixmap card16(":/images/images/Пики/Пики 3.png");card16 = card16.scaled(81,123);
        mas[i]->setPixmap(card16); break;
        }
        case 17:{
        QPixmap card17(":/images/images/Пики/Пики 4.png");card17 = card17.scaled(81,123);
        mas[i]->setPixmap(card17); break;
        }
        case 18:{
        QPixmap card18(":/images/images/Пики/Пики 5.png");card18 = card18.scaled(81,123);
        mas[i]->setPixmap(card18); break;
        }
        case 19:{
        QPixmap card19(":/images/images/Пики/Пики 6.png");card19 = card19.scaled(81,123);
        mas[i]->setPixmap(card19); break;
        }
        case 20:{
        QPixmap card20(":/images/images/Пики/Пики 7.png");card20 = card20.scaled(81,123);
        mas[i]->setPixmap(card20); break;
        }
        case 21:{
        QPixmap card21(":/images/images/Пики/Пики 8.png");card21 = card21.scaled(81,123);
        mas[i]->setPixmap(card21); break;
        }
        case 22:{
        QPixmap card22(":/images/images/Пики/Пики 9.png");card22 = card22.scaled(81,123);
        mas[i]->setPixmap(card22); break;
        }
        case 23:{
        QPixmap card23(":/images/images/Пики/Пики 10.png");card23 = card23.scaled(81,123);
        mas[i]->setPixmap(card23); break;
        }
        case 24:{
        QPixmap card24(":/images/images/Пики/Пики В.png");card24 = card24.scaled(81,123);
        mas[i]->setPixmap(card24); break;
        }
        case 25:{
        QPixmap card25(":/images/images/Пики/Пики Д.png");card25 = card25.scaled(81,123);
        mas[i]->setPixmap(card25); break;
        }
        case 26:{
        QPixmap card26(":/images/images/Пики/Пики К.png");card26 = card26.scaled(81,123);
        mas[i]->setPixmap(card26); break;
        }
        case 27:{
        QPixmap card27(":/images/images/Пики/Пики Т.png");card27 = card27.scaled(81,123);
        mas[i]->setPixmap(card27); break;
        }
        case 28:{
        QPixmap card28(":/images/images/Бубны/Бубны 2.png");card28 = card28.scaled(81,123);
        mas[i]->setPixmap(card28); break;
        }
        case 29:{
        QPixmap card29(":/images/images/Бубны/Бубны 3.png");card29 = card29.scaled(81,123);
        mas[i]->setPixmap(card29); break;
        }
        case 30:{
        QPixmap card30(":/images/images/Бубны/Бубны 4.png");card30 = card30.scaled(81,123);
        mas[i]->setPixmap(card30); break;
        }
        case 31:{
        QPixmap card31(":/images/images/Бубны/Бубны 5.png");card31 = card31.scaled(81,123);
        mas[i]->setPixmap(card31); break;
        }
        case 32:{
        QPixmap card32(":/images/images/Бубны/Бубны 6.png");card32 = card32.scaled(81,123);
        mas[i]->setPixmap(card32); break;
        }
        case 33:{
        QPixmap card33(":/images/images/Бубны/Бубны 7.png");card33 = card33.scaled(81,123);
        mas[i]->setPixmap(card33); break;
        }
        case 34:{
        QPixmap card34(":/images/images/Бубны/Бубны 8.png");card34 = card34.scaled(81,123);
        mas[i]->setPixmap(card34); break;
        }
        case 35:{
        QPixmap card35(":/images/images/Бубны/Бубны 9.png");card35 = card35.scaled(81,123);
        mas[i]->setPixmap(card35); break;
        }
        case 36:{
        QPixmap card36(":/images/images/Бубны/Бубны 10.png");card36 = card36.scaled(81,123);
        mas[i]->setPixmap(card36); break;
        }
        case 37:{
        QPixmap card37(":/images/images/Бубны/Бубны В.png");card37 = card37.scaled(81,123);
        mas[i]->setPixmap(card37); break;
        }
        case 38:{
        QPixmap card38(":/images/images/Бубны/Бубны Д.png");card38 = card38.scaled(81,123);
        mas[i]->setPixmap(card38); break;
        }
        case 39:{
        QPixmap card39(":/images/images/Бубны/Бубны К.png");card39 = card39.scaled(81,123);
        mas[i]->setPixmap(card39); break;
        }
        case 40:{
        QPixmap card40(":/images/images/Бубны/Бубны Т.png");card40 = card40.scaled(81,123);
        mas[i]->setPixmap(card40); break;
        }
        case 41:{
        QPixmap card41(":/images/images/Трефи/Трефи 2.png");card41 = card41.scaled(81,123);
        mas[i]->setPixmap(card41); break;
        }
        case 42:{
        QPixmap card42(":/images/images/Трефи/Трефи 3.png");card42 = card42.scaled(81,123);
        mas[i]->setPixmap(card42); break;
        }
        case 43:{
        QPixmap card43(":/images/images/Трефи/Трефи 4.png");card43 = card43.scaled(81,123);
        mas[i]->setPixmap(card43); break;
        }
        case 44:{
        QPixmap card44(":/images/images/Трефи/Трефи 5.png");card44 = card44.scaled(81,123);
        mas[i]->setPixmap(card44); break;
        }
        case 45:{
        QPixmap card45(":/images/images/Трефи/Трефи 6.png");card45 = card45.scaled(81,123);
        mas[i]->setPixmap(card45); break;
        }
        case 46:{
        QPixmap card46(":/images/images/Трефи/Трефи 7.png");card46 = card46.scaled(81,123);
        mas[i]->setPixmap(card46); break;
        }
        case 47:{
        QPixmap card47(":/images/images/Трефи/Трефи 8.png");card47 = card47.scaled(81,123);
        mas[i]->setPixmap(card47); break;
        }
        case 48:{
        QPixmap card48(":/images/images/Трефи/Трефи 9.png");card48 = card48.scaled(81,123);
        mas[i]->setPixmap(card48); break;
        }
        case 49:{
        QPixmap card49(":/images/images/Трефи/Трефи 10.png");card49 = card49.scaled(81,123);
        mas[i]->setPixmap(card49); break;
        }
        case 50:{
        QPixmap card50(":/images/images/Трефи/Трефи В.png");card50 = card50.scaled(81,123);
        mas[i]->setPixmap(card50); break;
        }
        case 51:{
        QPixmap card51(":/images/images/Трефи/Трефи Д.png");card51 = card51.scaled(81,123);
        mas[i]->setPixmap(card51); break;
        }
        case 52:{
        QPixmap card52(":/images/images/Трефи/Трефи К.png");card52 = card52.scaled(81,123);
        mas[i]->setPixmap(card52); break;
        }
        case 53:{
        QPixmap card53(":/images/images/Трефи/Трефи Т.png");card53 = card53.scaled(81,123);
        mas[i]->setPixmap(card53); break;
        }
    }
}

void* MainWindow::show_kart2(int i, long long* karta2){

    long long buf1 = karta2[i];
    QLabel* mas[10];
    mas[0] = ui->player1_2card;
    mas[1] = ui->player2_2card;
    mas[2] = ui->player3_2card;
    mas[3] = ui->player4_2card;
    mas[4] = ui->player5_2card;
    mas[5] = ui->player6_2card;
    mas[6] = ui->player7_2card;
    mas[7] = ui->player8_2card;
    mas[8] = ui->player9_2card;
    mas[9] = ui->player10_2card;

    switch (buf1) {
        case 2:{
        QPixmap card2(":/images/images/Сердце/Червь 2.png");card2 = card2.scaled(81,123);
        mas[i]->setPixmap(card2); break;
        }
        case 3:{
        QPixmap card3(":/images/images/Сердце/Червь 3.png");card3 = card3.scaled(81,123);
        mas[i]->setPixmap(card3); break;
        }
        case 4:{
        QPixmap card4(":/images/images/Сердце/Червь 4.png");card4 = card4.scaled(81,123);
        mas[i]->setPixmap(card4); break;
        }
        case 5:{
        QPixmap card5(":/images/images/Сердце/Червь 5.png");card5 = card5.scaled(81,123);
        mas[i]->setPixmap(card5); break;
        }
        case 6:{
        QPixmap card6(":/images/images/Сердце/Червь 6.png");card6 = card6.scaled(81,123);
        mas[i]->setPixmap(card6); break;
        }
        case 7:{
        QPixmap card7(":/images/images/Сердце/Червь 7.png");card7 = card7.scaled(81,123);
        mas[i]->setPixmap(card7); break;
        }
        case 8:{
        QPixmap card8(":/images/images/Сердце/Червь 8.png");card8 = card8.scaled(81,123);
        mas[i]->setPixmap(card8); break;
        }
        case 9:{
        QPixmap card9(":/images/images/Сердце/Червь 9.png");card9 = card9.scaled(81,123);
        mas[i]->setPixmap(card9); break;
        }
        case 10:{
        QPixmap card10(":/images/images/Сердце/Червь 10.png");card10 = card10.scaled(81,123);
        mas[i]->setPixmap(card10); break;
        }
        case 11:{
        QPixmap card11(":/images/images/Сердце/Червь В.png");card11 = card11.scaled(81,123);
        mas[i]->setPixmap(card11); break;
        }
        case 12:{
        QPixmap card12(":/images/images/Сердце/Червь Д.png");card12 = card12.scaled(81,123);
        mas[i]->setPixmap(card12); break;
        }
        case 13:{
        QPixmap card13(":/images/images/Сердце/Червь К.png");card13 = card13.scaled(81,123);
        mas[i]->setPixmap(card13); break;
        }
        case 14:{
        QPixmap card14(":/images/images/Сердце/Червь Т.png");card14 = card14.scaled(81,123);
        mas[i]->setPixmap(card14); break;
        }
        case 15:{
        QPixmap card15(":/images/images/Пики/Пики 2.png");card15 = card15.scaled(81,123);
        mas[i]->setPixmap(card15); break;
        }
        case 16:{
        QPixmap card16(":/images/images/Пики/Пики 3.png");card16 = card16.scaled(81,123);
        mas[i]->setPixmap(card16); break;
        }
        case 17:{
        QPixmap card17(":/images/images/Пики/Пики 4.png");card17 = card17.scaled(81,123);
        mas[i]->setPixmap(card17); break;
        }
        case 18:{
        QPixmap card18(":/images/images/Пики/Пики 5.png");card18 = card18.scaled(81,123);
        mas[i]->setPixmap(card18); break;
        }
        case 19:{
        QPixmap card19(":/images/images/Пики/Пики 6.png");card19 = card19.scaled(81,123);
        mas[i]->setPixmap(card19); break;
        }
        case 20:{
        QPixmap card20(":/images/images/Пики/Пики 7.png");card20 = card20.scaled(81,123);
        mas[i]->setPixmap(card20); break;
        }
        case 21:{
        QPixmap card21(":/images/images/Пики/Пики 8.png");card21 = card21.scaled(81,123);
        mas[i]->setPixmap(card21); break;
        }
        case 22:{
        QPixmap card22(":/images/images/Пики/Пики 9.png");card22 = card22.scaled(81,123);
        mas[i]->setPixmap(card22); break;
        }
        case 23:{
        QPixmap card23(":/images/images/Пики/Пики 10.png");card23 = card23.scaled(81,123);
        mas[i]->setPixmap(card23); break;
        }
        case 24:{
        QPixmap card24(":/images/images/Пики/Пики В.png");card24 = card24.scaled(81,123);
        mas[i]->setPixmap(card24); break;
        }
        case 25:{
        QPixmap card25(":/images/images/Пики/Пики Д.png");card25 = card25.scaled(81,123);
        mas[i]->setPixmap(card25); break;
        }
        case 26:{
        QPixmap card26(":/images/images/Пики/Пики К.png");card26 = card26.scaled(81,123);
        mas[i]->setPixmap(card26); break;
        }
        case 27:{
        QPixmap card27(":/images/images/Пики/Пики Т.png");card27 = card27.scaled(81,123);
        mas[i]->setPixmap(card27); break;
        }
        case 28:{
        QPixmap card28(":/images/images/Бубны/Бубны 2.png");card28 = card28.scaled(81,123);
        mas[i]->setPixmap(card28); break;
        }
        case 29:{
        QPixmap card29(":/images/images/Бубны/Бубны 3.png");card29 = card29.scaled(81,123);
        mas[i]->setPixmap(card29); break;
        }
        case 30:{
        QPixmap card30(":/images/images/Бубны/Бубны 4.png");card30 = card30.scaled(81,123);
        mas[i]->setPixmap(card30); break;
        }
        case 31:{
        QPixmap card31(":/images/images/Бубны/Бубны 5.png");card31 = card31.scaled(81,123);
        mas[i]->setPixmap(card31); break;
        }
        case 32:{
        QPixmap card32(":/images/images/Бубны/Бубны 6.png");card32 = card32.scaled(81,123);
        mas[i]->setPixmap(card32); break;
        }
        case 33:{
        QPixmap card33(":/images/images/Бубны/Бубны 7.png");card33 = card33.scaled(81,123);
        mas[i]->setPixmap(card33); break;
        }
        case 34:{
        QPixmap card34(":/images/images/Бубны/Бубны 8.png");card34 = card34.scaled(81,123);
        mas[i]->setPixmap(card34); break;
        }
        case 35:{
        QPixmap card35(":/images/images/Бубны/Бубны 9.png");card35 = card35.scaled(81,123);
        mas[i]->setPixmap(card35); break;
        }
        case 36:{
        QPixmap card36(":/images/images/Бубны/Бубны 10.png");card36 = card36.scaled(81,123);
        mas[i]->setPixmap(card36); break;
        }
        case 37:{
        QPixmap card37(":/images/images/Бубны/Бубны В.png");card37 = card37.scaled(81,123);
        mas[i]->setPixmap(card37); break;
        }
        case 38:{
        QPixmap card38(":/images/images/Бубны/Бубны Д.png");card38 = card38.scaled(81,123);
        mas[i]->setPixmap(card38); break;
        }
        case 39:{
        QPixmap card39(":/images/images/Бубны/Бубны К.png");card39 = card39.scaled(81,123);
        mas[i]->setPixmap(card39); break;
        }
        case 40:{
        QPixmap card40(":/images/images/Бубны/Бубны Т.png");card40 = card40.scaled(81,123);
        mas[i]->setPixmap(card40); break;
        }
        case 41:{
        QPixmap card41(":/images/images/Трефи/Трефи 2.png");card41 = card41.scaled(81,123);
        mas[i]->setPixmap(card41); break;
        }
        case 42:{
        QPixmap card42(":/images/images/Трефи/Трефи 3.png");card42 = card42.scaled(81,123);
        mas[i]->setPixmap(card42); break;
        }
        case 43:{
        QPixmap card43(":/images/images/Трефи/Трефи 4.png");card43 = card43.scaled(81,123);
        mas[i]->setPixmap(card43); break;
        }
        case 44:{
        QPixmap card44(":/images/images/Трефи/Трефи 5.png");card44 = card44.scaled(81,123);
        mas[i]->setPixmap(card44); break;
        }
        case 45:{
        QPixmap card45(":/images/images/Трефи/Трефи 6.png");card45 = card45.scaled(81,123);
        mas[i]->setPixmap(card45); break;
        }
        case 46:{
        QPixmap card46(":/images/images/Трефи/Трефи 7.png");card46 = card46.scaled(81,123);
        mas[i]->setPixmap(card46); break;
        }
        case 47:{
        QPixmap card47(":/images/images/Трефи/Трефи 8.png");card47 = card47.scaled(81,123);
        mas[i]->setPixmap(card47); break;
        }
        case 48:{
        QPixmap card48(":/images/images/Трефи/Трефи 9.png");card48 = card48.scaled(81,123);
        mas[i]->setPixmap(card48); break;
        }
        case 49:{
        QPixmap card49(":/images/images/Трефи/Трефи 10.png");card49 = card49.scaled(81,123);
        mas[i]->setPixmap(card49); break;
        }
        case 50:{
        QPixmap card50(":/images/images/Трефи/Трефи В.png");card50 = card50.scaled(81,123);
        mas[i]->setPixmap(card50); break;
        }
        case 51:{
        QPixmap card51(":/images/images/Трефи/Трефи Д.png");card51 = card51.scaled(81,123);
        mas[i]->setPixmap(card51); break;
        }
        case 52:{
        QPixmap card52(":/images/images/Трефи/Трефи К.png");card52 = card52.scaled(81,123);
        mas[i]->setPixmap(card52); break;
        }
        case 53:{
        QPixmap card53(":/images/images/Трефи/Трефи Т.png");card53 = card53.scaled(81,123);
        mas[i]->setPixmap(card53); break;
        }
    }
}

void* MainWindow::show_kart5(int i, long long* kart5){

    long long buf1 = kart5[i];
    QLabel* mas[5];
    mas[0] = ui->label_koloda1;
    mas[1] = ui->label_koloda2;
    mas[2] = ui->label_koloda3;
    mas[3] = ui->label_koloda4;
    mas[4] = ui->label_koloda5;
    switch (buf1) {
        case 2:{
        QPixmap card2(":/images/images/Сердце/Червь 2.png");card2 = card2.scaled(81,123);
        mas[i]->setPixmap(card2); break;
        }
        case 3:{
        QPixmap card3(":/images/images/Сердце/Червь 3.png");card3 = card3.scaled(81,123);
        mas[i]->setPixmap(card3); break;
        }
        case 4:{
        QPixmap card4(":/images/images/Сердце/Червь 4.png");card4 = card4.scaled(81,123);
        mas[i]->setPixmap(card4); break;
        }
        case 5:{
        QPixmap card5(":/images/images/Сердце/Червь 5.png");card5 = card5.scaled(81,123);
        mas[i]->setPixmap(card5); break;
        }
        case 6:{
        QPixmap card6(":/images/images/Сердце/Червь 6.png");card6 = card6.scaled(81,123);
        mas[i]->setPixmap(card6); break;
        }
        case 7:{
        QPixmap card7(":/images/images/Сердце/Червь 7.png");card7 = card7.scaled(81,123);
        mas[i]->setPixmap(card7); break;
        }
        case 8:{
        QPixmap card8(":/images/images/Сердце/Червь 8.png");card8 = card8.scaled(81,123);
        mas[i]->setPixmap(card8); break;
        }
        case 9:{
        QPixmap card9(":/images/images/Сердце/Червь 9.png");card9 = card9.scaled(81,123);
        mas[i]->setPixmap(card9); break;
        }
        case 10:{
        QPixmap card10(":/images/images/Сердце/Червь 10.png");card10 = card10.scaled(81,123);
        mas[i]->setPixmap(card10); break;
        }
        case 11:{
        QPixmap card11(":/images/images/Сердце/Червь В.png");card11 = card11.scaled(81,123);
        mas[i]->setPixmap(card11); break;
        }
        case 12:{
        QPixmap card12(":/images/images/Сердце/Червь Д.png");card12 = card12.scaled(81,123);
        mas[i]->setPixmap(card12); break;
        }
        case 13:{
        QPixmap card13(":/images/images/Сердце/Червь К.png");card13 = card13.scaled(81,123);
        mas[i]->setPixmap(card13); break;
        }
        case 14:{
        QPixmap card14(":/images/images/Сердце/Червь Т.png");card14 = card14.scaled(81,123);
        mas[i]->setPixmap(card14); break;
        }
        case 15:{
        QPixmap card15(":/images/images/Пики/Пики 2.png");card15 = card15.scaled(81,123);
        mas[i]->setPixmap(card15); break;
        }
        case 16:{
        QPixmap card16(":/images/images/Пики/Пики 3.png");card16 = card16.scaled(81,123);
        mas[i]->setPixmap(card16); break;
        }
        case 17:{
        QPixmap card17(":/images/images/Пики/Пики 4.png");card17 = card17.scaled(81,123);
        mas[i]->setPixmap(card17); break;
        }
        case 18:{
        QPixmap card18(":/images/images/Пики/Пики 5.png");card18 = card18.scaled(81,123);
        mas[i]->setPixmap(card18); break;
        }
        case 19:{
        QPixmap card19(":/images/images/Пики/Пики 6.png");card19 = card19.scaled(81,123);
        mas[i]->setPixmap(card19); break;
        }
        case 20:{
        QPixmap card20(":/images/images/Пики/Пики 7.png");card20 = card20.scaled(81,123);
        mas[i]->setPixmap(card20); break;
        }
        case 21:{
        QPixmap card21(":/images/images/Пики/Пики 8.png");card21 = card21.scaled(81,123);
        mas[i]->setPixmap(card21); break;
        }
        case 22:{
        QPixmap card22(":/images/images/Пики/Пики 9.png");card22 = card22.scaled(81,123);
        mas[i]->setPixmap(card22); break;
        }
        case 23:{
        QPixmap card23(":/images/images/Пики/Пики 10.png");card23 = card23.scaled(81,123);
        mas[i]->setPixmap(card23); break;
        }
        case 24:{
        QPixmap card24(":/images/images/Пики/Пики В.png");card24 = card24.scaled(81,123);
        mas[i]->setPixmap(card24); break;
        }
        case 25:{
        QPixmap card25(":/images/images/Пики/Пики Д.png");card25 = card25.scaled(81,123);
        mas[i]->setPixmap(card25); break;
        }
        case 26:{
        QPixmap card26(":/images/images/Пики/Пики К.png");card26 = card26.scaled(81,123);
        mas[i]->setPixmap(card26); break;
        }
        case 27:{
        QPixmap card27(":/images/images/Пики/Пики Т.png");card27 = card27.scaled(81,123);
        mas[i]->setPixmap(card27); break;
        }
        case 28:{
        QPixmap card28(":/images/images/Бубны/Бубны 2.png");card28 = card28.scaled(81,123);
        mas[i]->setPixmap(card28); break;
        }
        case 29:{
        QPixmap card29(":/images/images/Бубны/Бубны 3.png");card29 = card29.scaled(81,123);
        mas[i]->setPixmap(card29); break;
        }
        case 30:{
        QPixmap card30(":/images/images/Бубны/Бубны 4.png");card30 = card30.scaled(81,123);
        mas[i]->setPixmap(card30); break;
        }
        case 31:{
        QPixmap card31(":/images/images/Бубны/Бубны 5.png");card31 = card31.scaled(81,123);
        mas[i]->setPixmap(card31); break;
        }
        case 32:{
        QPixmap card32(":/images/images/Бубны/Бубны 6.png");card32 = card32.scaled(81,123);
        mas[i]->setPixmap(card32); break;
        }
        case 33:{
        QPixmap card33(":/images/images/Бубны/Бубны 7.png");card33 = card33.scaled(81,123);
        mas[i]->setPixmap(card33); break;
        }
        case 34:{
        QPixmap card34(":/images/images/Бубны/Бубны 8.png");card34 = card34.scaled(81,123);
        mas[i]->setPixmap(card34); break;
        }
        case 35:{
        QPixmap card35(":/images/images/Бубны/Бубны 9.png");card35 = card35.scaled(81,123);
        mas[i]->setPixmap(card35); break;
        }
        case 36:{
        QPixmap card36(":/images/images/Бубны/Бубны 10.png");card36 = card36.scaled(81,123);
        mas[i]->setPixmap(card36); break;
        }
        case 37:{
        QPixmap card37(":/images/images/Бубны/Бубны В.png");card37 = card37.scaled(81,123);
        mas[i]->setPixmap(card37); break;
        }
        case 38:{
        QPixmap card38(":/images/images/Бубны/Бубны Д.png");card38 = card38.scaled(81,123);
        mas[i]->setPixmap(card38); break;
        }
        case 39:{
        QPixmap card39(":/images/images/Бубны/Бубны К.png");card39 = card39.scaled(81,123);
        mas[i]->setPixmap(card39); break;
        }
        case 40:{
        QPixmap card40(":/images/images/Бубны/Бубны Т.png");card40 = card40.scaled(81,123);
        mas[i]->setPixmap(card40); break;
        }
        case 41:{
        QPixmap card41(":/images/images/Трефи/Трефи 2.png");card41 = card41.scaled(81,123);
        mas[i]->setPixmap(card41); break;
        }
        case 42:{
        QPixmap card42(":/images/images/Трефи/Трефи 3.png");card42 = card42.scaled(81,123);
        mas[i]->setPixmap(card42); break;
        }
        case 43:{
        QPixmap card43(":/images/images/Трефи/Трефи 4.png");card43 = card43.scaled(81,123);
        mas[i]->setPixmap(card43); break;
        }
        case 44:{
        QPixmap card44(":/images/images/Трефи/Трефи 5.png");card44 = card44.scaled(81,123);
        mas[i]->setPixmap(card44); break;
        }
        case 45:{
        QPixmap card45(":/images/images/Трефи/Трефи 6.png");card45 = card45.scaled(81,123);
        mas[i]->setPixmap(card45); break;
        }
        case 46:{
        QPixmap card46(":/images/images/Трефи/Трефи 7.png");card46 = card46.scaled(81,123);
        mas[i]->setPixmap(card46); break;
        }
        case 47:{
        QPixmap card47(":/images/images/Трефи/Трефи 8.png");card47 = card47.scaled(81,123);
        mas[i]->setPixmap(card47); break;
        }
        case 48:{
        QPixmap card48(":/images/images/Трефи/Трефи 9.png");card48 = card48.scaled(81,123);
        mas[i]->setPixmap(card48); break;
        }
        case 49:{
        QPixmap card49(":/images/images/Трефи/Трефи 10.png");card49 = card49.scaled(81,123);
        mas[i]->setPixmap(card49); break;
        }
        case 50:{
        QPixmap card50(":/images/images/Трефи/Трефи В.png");card50 = card50.scaled(81,123);
        mas[i]->setPixmap(card50); break;
        }
        case 51:{
        QPixmap card51(":/images/images/Трефи/Трефи Д.png");card51 = card51.scaled(81,123);
        mas[i]->setPixmap(card51); break;
        }
        case 52:{
        QPixmap card52(":/images/images/Трефи/Трефи К.png");card52 = card52.scaled(81,123);
        mas[i]->setPixmap(card52); break;
        }
        case 53:{
        QPixmap card53(":/images/images/Трефи/Трефи Т.png");card53 = card53.scaled(81,123);
        mas[i]->setPixmap(card53); break;
        }
    }
}


