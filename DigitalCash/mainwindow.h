#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

static int Client_money = 2000;
static int Store_money = 10000;
static int Transaction = 0;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void start_DigitalCash(int n);
    void start_Transaction(int index_money, long long C[], long long D[],long long N);
    void split_money(int n, int* Number_money);
    void show_money();
    long long  start_hash(QString s);
    void on_pushButton_4_clicked();
    int check_money(int index_money);

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
