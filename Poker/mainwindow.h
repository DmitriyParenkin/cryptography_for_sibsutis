#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>



namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void* show_kart1(int i, long long* karta1);
    void* show_kart2(int i, long long* karta2);

    void* show_hide(int n);
    void* show_hide1(int n);



private slots:
    int on_pushButton_clicked();
    void start_poker(int n);
    void* show_kart5(int i, long long* kart5);

private:
    Ui::MainWindow *ui;
    int n;
};

#endif // MAINWINDOW_H
