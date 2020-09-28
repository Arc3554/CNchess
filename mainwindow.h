#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QMouseEvent>
#include <QObject>
#include <QString>


namespace Ui {
class MainWindow;
}



class button : public QPushButton
{
    Q_OBJECT
public:
    int x;
    int y;
    int character;
    int color;
};

class controller
{public:
    int x;
    int y;
    int color=0;
    int character=0;
    button *use;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QLabel *board;
    button *pawn[10];
    button *cannon[4];
    button *advisor[4];
    button *elephant[4];
    button *rook[4];
    button *knight[4];
    button *cancel;
    button *king[2];
    button *red[90];
    button *btn1;
    button *btn2;
    button *playmode;
    button *editmode;
    button *Done;
    button *redfirst;
    button *blackfirst;
    button *back;
    button *pre;
    button *death[32];
    QLabel *label1;
    QLabel *turn;
    QLabel *title;
    controller ctrl[90];
    int round=1;
    int i,j;
    int temp1;
    int temp2;
    int c;
    int mode=0;
private slots:
    void play();
    void edit();
    void buttonpush();
    void buttoncancel();
    void buttonmove();
    void done();
    void rf();
    void bf();
    void previous();
};
#endif // MAINWINDOW_H
