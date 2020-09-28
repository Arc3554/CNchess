#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QEvent>
#include <QObject>
#include <QString>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1200,900);
    QPixmap bd(":/pic/pj2src/piece/chessdesktop0726.png");
    board = new QLabel(this);
    board->setGeometry(75,50,760,760);
    board->setPixmap(bd.scaled(760,760,Qt::KeepAspectRatioByExpanding));
    board->show();

    title=new QLabel(this);
    title->setText("象棋的啦");
    title->setGeometry(300,165,400,200);
    title->setFont(QFont("Courier New" ,56,QFont::StyleItalic,Qt::white));
    title->setStyleSheet("border:none");
    title->show();

    playmode=new button();
    playmode->setParent(this);
    playmode->setText("Playmode");
    playmode->setGeometry(110,350,350,150);
    playmode->setFont(QFont("Courier New" ,50,QFont::StyleItalic,Qt::white));
    playmode->setStyleSheet("border:none");
    connect(playmode,SIGNAL(clicked(bool)),this,SLOT(play()));

    editmode=new button();
    editmode->setParent(this);
    editmode->setText("Editmode");
    editmode->setGeometry(445,350,350,150);
    editmode->setFont(QFont("Courier New" ,50,QFont::StyleItalic,Qt::white));
    editmode->setStyleSheet("border:none");
    connect(editmode,SIGNAL(clicked(bool)),this,SLOT(edit()));

    turn=new QLabel(this);
    turn->setGeometry(850,600,350,200);
    turn->setAlignment(Qt::AlignCenter);
    turn->setFont(QFont("Timers", 28, QFont::Bold));
    turn->close();

    back=new button();
    back->setParent(this);
    back->setGeometry(850,700,200,100);
    back->setText("上一步");
    back->setFont(QFont("Courier New" ,30,QFont::StyleItalic,Qt::white));
    back->setStyleSheet("border:none");
    connect(back,SIGNAL(clicked()),this,SLOT(previous()));
    back->close();

    for(i=0;i<5;i++)
    {
    death[11+i] = new button();
    death[11+i]->setParent(this);
    death[11+i]->setGeometry(900+i*50,45,50,50);
    death[11+i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sd1.svg.png"));
    death[11+i]->setIconSize(death[11+i]->size());
    death[11+i]->setStyleSheet("border:none");
    death[11+i]->character=12+i;
    death[11+i]->color=2;
    death[11+i]->close();
    }

    for(i=5;i<10;i++)
    {
    death[11+i] = new button();
    death[11+i]->setParent(this);
    death[11+i]->setGeometry(900+(i-5)*50,95,50,50);
    death[11+i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sl1.svg.png"));
    death[11+i]->setIconSize(death[11+i]->size());
    death[11+i]->setStyleSheet("border:none");
    death[11+i]->character=12+i;
    death[11+i]->color=1;
    death[11+i]->close();
    }

    for(i=0;i<2;i++)
    {
    death[i*8] = new button();
    death[i*8]->setParent(this);
    death[i*8]->setGeometry(900+i*50,145,50,50);
    death[i*8]->x=900+i*50;
    death[i*8]->y=145;
    death[i*8]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_rd1.svg.png"));
    death[i*8]->setIconSize(death[i*8]->size());
    death[i*8]->setStyleSheet("border:none");
    death[i*8]->character=1+i*8;
    death[i*8]->color=2;
    death[i*8]->close();
    }
    for(i=0;i<2;i++)
    {
    death[23+i*8] = new button();
    death[23+i*8]->setParent(this);
    death[23+i*8]->setGeometry(1000+i*50,145,50,50);
    death[23+i*8]->x=1000+i*50;
    death[23+i*8]->y=145;
    death[23+i*8]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_rl1.svg.png"));
    death[23+i*8]->setIconSize(death[23+i*8]->size());
    death[23+i*8]->setStyleSheet("border:none");
    death[23+i*8]->character=24+i*8;
    death[23+i*8]->color=1;
    death[23+i*8]->close();
    }
    for(i=0;i<2;i++)
    {
    death[1+i*6] = new button();
    death[1+i*6]->setParent(this);
    death[1+i*6]->setGeometry(900+i*50,195,50,50);
    death[1+i*6]->x=900+i*50;
    death[1+i*6]->y=195;
    death[1+i*6]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_hd1.svg.png"));
    death[1+i*6]->setIconSize(death[1+6*i]->size());
    death[1+i*6]->setStyleSheet("border:none");
    death[1+i*6]->character=2+i*6;
    death[1+i*6]->color=2;
    death[1+i*6]->close();
    }
    for(i=0;i<2;i++)
    {
    death[24+i*6] = new button();
    death[24+i*6]->setParent(this);
    death[24+i*6]->setGeometry(1000+i*50,195,50,50);
    death[24+i*6]->x=1000+i*50;
    death[24+i*6]->y=195;
    death[24+i*6]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_hl1.svg (1).png"));
    death[24+i*6]->setIconSize(death[24+i*6]->size());
    death[24+i*6]->setStyleSheet("border:none");
    death[24+i*6]->character=25+i*6;
    death[24+i*6]->color=1;
    death[24+i*6]->close();
    }
    for(i=0;i<2;i++)
    {
    death[2+i*4] = new button();
    death[2+i*4]->setParent(this);
    death[2+i*4]->setGeometry(900+i*50,245,50,50);
    death[2+i*4]->x=900+i*50;
    death[2+i*4]->y=245;
    death[2+i*4]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_ed1.svg.png"));
    death[2+i*4]->setIconSize(death[2+4*i]->size());
    death[2+i*4]->setStyleSheet("border:none");
    death[2+i*4]->character=3+i*4;
    death[2+i*4]->color=2;
    death[2+i*4]->close();
    }
    for(i=0;i<2;i++)
    {
    death[25+i*4] = new button();
    death[25+i*4]->setParent(this);
    death[25+i*4]->setGeometry(1000+i*50,245,50,50);
    death[25+i*4]->x=1000+i*50;
    death[25+i*4]->y=245;
    death[25+i*4]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_el1.svg.png"));
    death[25+i*4]->setIconSize(death[i*4+25]->size());
    death[25+i*4]->setStyleSheet("border:none");
    death[25+i*4]->character=26+i*4;
    death[25+i*4]->color=1;
    death[25+i*4]->close();
    }
    for(i=0;i<2;i++)
    {
    death[3+i*2] = new button();
    death[3+i*2]->setParent(this);
    death[3+i*2]->setGeometry(900+i*50,295,50,50);
    death[3+i*2]->x=900+i*50;
    death[3+i*2]->y=295;
    death[3+i*2]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_ad1.svg (1).png"));
    death[3+i*2]->setIconSize(death[3+i*2]->size());
    death[3+i*2]->setStyleSheet("border:none");
    death[3+i*2]->character=4+i*2;
    death[3+i*2]->color=2;
    death[3+i*2]->close();
    }
    for(i=0;i<2;i++)
    {
    death[26+i*2] = new button();
    death[26+i*2]->setParent(this);
    death[26+i*2]->setGeometry(1000+i*50,295,50,50);
    death[26+i*2]->x=1000+i*50;
    death[26+i*2]->y=295;
    death[26+i*2]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_al1.svg.png"));
    death[26+i*2]->setIconSize(death[26+i*2]->size());
    death[26+i*2]->setStyleSheet("border:none");
    death[26+i*2]->character=27+i*2;
    death[26+i*2]->color=1;
    death[26+i*2]->close();
    }
    death[4] = new button();
    death[4]->setParent(this);
    death[4]->setGeometry(900,345,50,50);
   death[4]->x=900;
    death[4]->y=345;
    death[4]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_gd1.svg (1).png"));
    death[4]->setIconSize(death[4]->size());
    death[4]->setStyleSheet("border:none");
    death[4]->character=5;
    death[4]->color=2;
    death[4]->close();

    death[27] = new button();
    death[27]->setParent(this);
    death[27]->setGeometry(950,345,50,50);
    death[27]->x=950;
    death[27]->y=345;
    death[27]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_gl1.svg.png"));
    death[27]->setIconSize(death[27]->size());
    death[27]->setStyleSheet("border:none");
    death[27]->character=28;
    death[27]->color=1;
    death[27]->close();

    for(i=0;i<2;i++)
    {
    death[9+i] = new button();
    death[9+i]->setParent(this);
    death[9+i]->setGeometry(900+i*50,395,50,50);
    death[9+i]->x=900+i*50;
    death[9+i]->y=395;
    death[9+i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_cd1.svg.png"));
    death[9+i]->setIconSize(death[9+i]->size());
    death[9+i]->setStyleSheet("border:none");
    death[9+i]->character=10+i;
    death[9+i]->color=2;
    death[9+i]->close();
    }
    for(i=0;i<2;i++)
    {
    death[21+i] = new button();
    death[21+i]->setParent(this);
    death[21+i]->setGeometry(1000+i*50,395,50,50);
    death[21+i]->x=1000+i*50;
    death[21+i]->y=395;
    death[21+i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_cl1.svg.png"));
    death[21+i]->setIconSize(death[i+21]->size());
    death[21+i]->setStyleSheet("border:none");
    death[21+i]->character=22+i;
    death[21+i]->color=1;
    death[21+i]->close();
    }
}

void MainWindow::buttonpush()
{
    btn1 = dynamic_cast<button*>(sender());
    back->close();
    if(mode==1)
    {
        if(btn1->x>=900)
        {cancel->setGeometry(btn1->x,btn1->y,50,50);
            cancel->x=btn1->x;
            cancel->y=btn1->y;
            cancel->show();
            for(i=0;i<10;i++)
            {

                for(j=0;j<9;j++)
                {
                    red[i*9+j]->close();
                    if(btn1->character==4||btn1->character==6)
                    {if(ctrl[i*9+j].color==0&&(i*9+j==3||i*9+j==5||i*9+j==13||i*9+j==21||i*9+j==23)){red[i*9+j]->show();}}
                    else if(btn1->character==27||btn1->character==29)
                    {if(ctrl[i*9+j].color==0&&(i*9+j==66||i*9+j==68||i*9+j==76||i*9+j==84||i*9+j==86)){red[i*9+j]->show();}}
                    else if(btn1->character==3||btn1->character==7)
                    {if(ctrl[i*9+j].color==0&&(i*9+j==2||i*9+j==6||i*9+j==18||i*9+j==22||i*9+j==26||i*9+j==38||i*9+j==42)){red[i*9+j]->show();}}
                    else if(btn1->character==26||btn1->character==30)
                    {if(ctrl[i*9+j].color==0&&(i*9+j==47||i*9+j==51||i*9+j==63||i*9+j==67||i*9+j==71||i*9+j==83||i*9+j==87)){red[i*9+j]->show();}}
                    else if(btn1->character>=12&&btn1->character<=16)
                    {if(ctrl[i*9+j].color==0&&(i*9+j==27||i*9+j==29||i*9+j==31||i*9+j==33||i*9+j==35||i*9+j==36||i*9+j==38||i*9+j==40||i*9+j==42||i*9+j==44||i*9+j>=45)){red[i*9+j]->show();}}
                    else if(btn1->character>=17&&btn1->character<=21)
                    {if(ctrl[i*9+j].color==0&&(i*9+j==45||i*9+j==47||i*9+j==49||i*9+j==51||i*9+j==53||i*9+j==54||i*9+j==56||i*9+j==58||i*9+j==60||i*9+j==62||i*9+j<=44)){red[i*9+j]->show();}}
                    else if(btn1->character==5)
                    {if(ctrl[i*9+j].color==0&&(i*9+j==3||i*9+j==4||i*9+j==5||i*9+j==12||i*9+j==13||i*9+j==14||i*9+j==21||i*9+j==22||i*9+j==23)){red[i*9+j]->show();}
                        if(king[1]->x<900){if(ctrl[i*9+j].character==28){temp1=i*9+j;}}
                    }
                    else if(btn1->character==28)
                    {if(ctrl[i*9+j].color==0&&(i*9+j==66||i*9+j==67||i*9+j==68||i*9+j==75||i*9+j==76||i*9+j==77||i*9+j==84||i*9+j==85||i*9+j==86)){red[i*9+j]->show();}
                        if(king[0]->x<900){if(ctrl[i*9+j].character==5){temp1=i*9+j;}}
                    }

                    else if(ctrl[i*9+j].color==0)
                    {
                        red[i*9+j]->show();
                    }

                }
            }
            if(king[1]->x<900&&btn1->character==5){for(i=temp1-9;i>=0;i-=9){if(ctrl[i].color==0){red[i]->close();}else{break;}}}
            if(king[0]->x<900&&btn1->character==28){for(i=temp1+9;i<90;i+=9){if(ctrl[i].color==0){red[i]->close();}else{break;}}}
        }
    }
    else if(mode==0){
    for(i=0;i<10;i++)
    {

        for(j=0;j<9;j++)
        {
            red[i*9+j]->close();
            if(ctrl[i*9+j].character==btn1->character)
            {
                temp1=i*9+j;
            }
        }
    }
    if(ctrl[temp1].color==round)
    {cancel->setGeometry(ctrl[temp1].x,ctrl[temp1].y,50,50);
    cancel->x=ctrl[temp1].x;
    cancel->y=ctrl[temp1].y;
    cancel->show();
    int can=0;
    switch(ctrl[temp1].character){
    case 1:cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_rd1.svg.png"));
        for(i=temp1+1;i<9*((temp1/9)+1);i++)
        {
            if(ctrl[i].color==0){red[i]->show();}
            else if(ctrl[i].color!=round){red[i]->show();break;}
            else if(ctrl[i].color==round){break;}
        }
        for(i=temp1-1;i>=9*(temp1/9);i--)
        {
            if(ctrl[i].color==0){red[i]->show();}
            else if(ctrl[i].color!=round){red[i]->show();break;}
            else if(ctrl[i].color==round){break;}
        }
        for(i=temp1+9;i<90;i+=9)
        {
            if(ctrl[i].color==0){red[i]->show();}
            else if(ctrl[i].color!=round){red[i]->show();break;}
            else if(ctrl[i].color==round){break;}
        }
        for(i=temp1-9;i>=0;i-=9)
        {
            if(ctrl[i].color==0){red[i]->show();}
            else if(ctrl[i].color!=round){red[i]->show();break;}
            else if(ctrl[i].color==round){break;}
        }
            break;
    case 9:cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_rd1.svg.png"));
        for(i=temp1+1;i<9*((temp1/9)+1);i++)
        {
            if(ctrl[i].color==0){red[i]->show();}
            else if(ctrl[i].color!=round){red[i]->show();break;}
            else if(ctrl[i].color==round){break;}
        }
        for(i=temp1-1;i>=9*(temp1/9);i--)
        {
            if(ctrl[i].color==0){red[i]->show();}
            else if(ctrl[i].color!=round){red[i]->show();break;}
            else if(ctrl[i].color==round){break;}
        }
        for(i=temp1+9;i<90;i+=9)
        {
            if(ctrl[i].color==0){red[i]->show();}
            else if(ctrl[i].color!=round){red[i]->show();break;}
            else if(ctrl[i].color==round){break;}
        }
        for(i=temp1-9;i>=0;i-=9)
        {
            if(ctrl[i].color==0){red[i]->show();}
            else if(ctrl[i].color!=round){red[i]->show();break;}
            else if(ctrl[i].color==round){break;}
        }
        break;
    case 2:cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_hd1.svg.png"));
        i=temp1;
        if(i>17&&ctrl[i-9].color==0){

        if(i%9!=0){if(ctrl[i-19].color!=round){red[i-19]->show();}}
        if(i%9!=8){if(ctrl[i-17].color!=round){red[i-17]->show();}}
        }

        if(i%9>1&&ctrl[i-1].color==0){

        if(i/9!=0){if(ctrl[i-11].color!=round){red[i-11]->show();}}
        if(i/9!=9){if(ctrl[i+7].color!=round){red[i+7]->show();}}
        }

        if(i<72&&ctrl[i+9].color==0){

        if(i%9!=0){if(ctrl[i+17].color!=round){red[i+17]->show();}}
        if(i%9!=8){if(ctrl[i+19].color!=round){red[i+19]->show();}}
        }
        if(i%9<7&&ctrl[i+1].color==0){

        if(i/9!=0){if(ctrl[i-7].color!=round){red[i-7]->show();}}
        if(i/9!=9){if(ctrl[i+11].color!=round){red[i+11]->show();}}
        }
        break;
    case 8:cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_hd1.svg.png"));
        i=temp1;
        if(i>17&&ctrl[i-9].color==0){

        if(i%9!=0){if(ctrl[i-19].color!=round){red[i-19]->show();}}
        if(i%9!=8){if(ctrl[i-17].color!=round){red[i-17]->show();}}
        }

        if(i%9>1&&ctrl[i-1].color==0){

        if(i/9!=0){if(ctrl[i-11].color!=round){red[i-11]->show();}}
        if(i/9!=9){if(ctrl[i+7].color!=round){red[i+7]->show();}}
        }

        if(i<72&&ctrl[i+9].color==0){

        if(i%9!=0){if(ctrl[i+17].color!=round){red[i+17]->show();}}
        if(i%9!=8){if(ctrl[i+19].color!=round){red[i+19]->show();}}
        }
        if(i%9<7&&ctrl[i+1].color==0){

        if(i/9!=0){if(ctrl[i-7].color!=round){red[i-7]->show();}}
        if(i/9!=9){if(ctrl[i+11].color!=round){red[i+11]->show();}}
        }
        break;
    case 3:cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_ed1.svg.png"));
        i=temp1;
        if(i==2)
        {
        if(ctrl[10].color==0&&ctrl[18].color!=round){red[18]->show();}
        if(ctrl[12].color==0&&ctrl[22].color!=round){red[22]->show();}
        }
        else if(i==6){
            if(ctrl[14].color==0&&ctrl[22].color!=round){red[22]->show();}
        if(ctrl[16].color==0&&ctrl[26].color!=round){red[26]->show();}
        }
        else if(i==38)
        {
        if(ctrl[28].color==0&&ctrl[18].color!=round){red[18]->show();}
        if(ctrl[30].color==0&&ctrl[22].color!=round){red[22]->show();}
        }
        else if(i==42){
            if(ctrl[32].color==0&&ctrl[22].color!=round){red[22]->show();}
        if(ctrl[34].color==0&&ctrl[26].color!=round){red[26]->show();}
        }
        else if(i==18)
        {
        if(ctrl[10].color==0&&ctrl[2].color!=round){red[2]->show();}
        if(ctrl[28].color==0&&ctrl[38].color!=round){red[38]->show();}
        }
        else if(i==26)
        {
        if(ctrl[16].color==0&&ctrl[6].color!=round){red[6]->show();}
        if(ctrl[34].color==0&&ctrl[42].color!=round){red[42]->show();}
        }
        else if(i==22)
        {
        if(ctrl[12].color==0&&ctrl[2].color!=round){red[2]->show();}
        if(ctrl[14].color==0&&ctrl[6].color!=round){red[6]->show();}
        if(ctrl[30].color==0&&ctrl[38].color!=round){red[38]->show();}
        if(ctrl[32].color==0&&ctrl[42].color!=round){red[42]->show();}
        }
        break;
    case 7:cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_ed1.svg.png"));
        i=temp1;
        if(i==2)
        {
        if(ctrl[10].color==0&&ctrl[18].color!=round){red[18]->show();}
        if(ctrl[12].color==0&&ctrl[22].color!=round){red[22]->show();}
        }
        else if(i==6){
            if(ctrl[14].color==0&&ctrl[22].color!=round){red[22]->show();}
        if(ctrl[16].color==0&&ctrl[26].color!=round){red[26]->show();}
        }
        else if(i==38)
        {
        if(ctrl[28].color==0&&ctrl[18].color!=round){red[18]->show();}
        if(ctrl[30].color==0&&ctrl[22].color!=round){red[22]->show();}
        }
        else if(i==42){
            if(ctrl[32].color==0&&ctrl[22].color!=round){red[22]->show();}
        if(ctrl[34].color==0&&ctrl[26].color!=round){red[26]->show();}
        }
        else if(i==18)
        {
        if(ctrl[10].color==0&&ctrl[2].color!=round){red[2]->show();}
        if(ctrl[28].color==0&&ctrl[38].color!=round){red[38]->show();}
        }
        else if(i==26)
        {
        if(ctrl[16].color==0&&ctrl[6].color!=round){red[6]->show();}
        if(ctrl[34].color==0&&ctrl[42].color!=round){red[42]->show();}
        }
        else if(i==22)
        {
        if(ctrl[12].color==0&&ctrl[2].color!=round){red[2]->show();}
        if(ctrl[14].color==0&&ctrl[6].color!=round){red[6]->show();}
        if(ctrl[30].color==0&&ctrl[38].color!=round){red[38]->show();}
        if(ctrl[32].color==0&&ctrl[42].color!=round){red[42]->show();}
        }
        break;
    case 4:cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_ad1.svg (1).png"));
        i=temp1;
        if(i==3){if(ctrl[13].color!=round){red[13]->show();}}
        if(i==5){if(ctrl[13].color!=round){red[13]->show();}}
        if(i==21){if(ctrl[13].color!=round){red[13]->show();}}
        if(i==23){if(ctrl[13].color!=round){red[13]->show();}}
        if(i==13){if(ctrl[3].color!=round){red[3]->show();}
        if(ctrl[5].color!=round){red[5]->show();}
        if(ctrl[21].color!=round){red[21]->show();}
        if(ctrl[23].color!=round){red[23]->show();}}
        break;
    case 6:cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_ad1.svg (1).png"));
        i=temp1;
        if(i==3){if(ctrl[13].color!=round){red[13]->show();}}
        if(i==5){if(ctrl[13].color!=round){red[13]->show();}}
        if(i==21){if(ctrl[13].color!=round){red[13]->show();}}
        if(i==23){if(ctrl[13].color!=round){red[13]->show();}}
        if(i==13){if(ctrl[3].color!=round){red[3]->show();}
        if(ctrl[5].color!=round){red[5]->show();}
        if(ctrl[21].color!=round){red[21]->show();}
        if(ctrl[23].color!=round){red[23]->show();}}
        break;
    case 5:cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_gd1.svg (1).png"));
        i=temp1;
        if(i/9!=0){if(ctrl[i-9].color!=round){red[i-9]->show();}}
        if(i/9!=2){if(ctrl[i+9].color!=round){red[i+9]->show();}}
        if(i%9!=3){if(ctrl[i-1].color!=round){red[i-1]->show();}}
        if(i%9!=5){if(ctrl[i+1].color!=round){red[i+1]->show();}}
        break;
    case 10:cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_cd1.svg.png"));
        for(i=temp1+1;i<9*((temp1/9)+1);i++)
        {
            if(ctrl[i].color==0&&can==0){red[i]->show();}
            else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
        }
        can=0;
        for(i=temp1-1;i>=9*(temp1/9);i--)
        {
            if(ctrl[i].color==0&&can==0){red[i]->show();}
            else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
        }
        can=0;
        for(i=temp1+9;i<90;i+=9)
        {
            if(ctrl[i].color==0&&can==0){red[i]->show();}
            else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
        }
        can=0;
        for(i=temp1-9;i>=0;i-=9)
        {
            if(ctrl[i].color==0&&can==0){red[i]->show();}
            else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
        }
            can=0;
        break;
    case 11:cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_cd1.svg.png"));
        for(i=temp1+1;i<9*((temp1/9)+1);i++)
        {
            if(ctrl[i].color==0&&can==0){red[i]->show();}
            else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
        }
        can=0;
        for(i=temp1-1;i>=9*(temp1/9);i--)
        {
            if(ctrl[i].color==0&&can==0){red[i]->show();}
            else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
        }
        can=0;
        for(i=temp1+9;i<90;i+=9)
        {
            if(ctrl[i].color==0&&can==0){red[i]->show();}
            else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
        }
        can=0;
        for(i=temp1-9;i>=0;i-=9)
        {
            if(ctrl[i].color==0&&can==0){red[i]->show();}
            else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
        }
            can=0;
        break;
    case 12:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sd1.svg.png"));
    i=temp1;if(i<81&&ctrl[i+9].color!=round){red[i+9]->show();}
    if(i>44)
    {
        if(i%9!=8&&ctrl[i+1].color!=round){red[i+1]->show();}
        if(i%9!=0&&ctrl[i-1].color!=round){red[i-1]->show();}
    }
        break;
    case 13:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sd1.svg.png"));
    i=temp1;if(i<81&&ctrl[i+9].color!=round){red[i+9]->show();}
    if(i>44)
    {
        if(i%9!=8&&ctrl[i+1].color!=round){red[i+1]->show();}
        if(i%9!=0&&ctrl[i-1].color!=round){red[i-1]->show();}
    }
        break;
    case 14:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sd1.svg.png"));
    i=temp1;if(i<81&&ctrl[i+9].color!=round){red[i+9]->show();}
    if(i>44)
    {
        if(i%9!=8&&ctrl[i+1].color!=round){red[i+1]->show();}
        if(i%9!=0&&ctrl[i-1].color!=round){red[i-1]->show();}
    }
        break;
    case 15:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sd1.svg.png"));
    i=temp1;if(i<81&&ctrl[i+9].color!=round){red[i+9]->show();}
    if(i>44)
    {
        if(i%9!=8&&ctrl[i+1].color!=round){red[i+1]->show();}
        if(i%9!=0&&ctrl[i-1].color!=round){red[i-1]->show();}
    }
        break;
    case 16:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sd1.svg.png"));
    i=temp1;if(i<81&&ctrl[i+9].color!=round){red[i+9]->show();}
    if(i>44)
    {
        if(i%9!=8&&ctrl[i+1].color!=round){red[i+1]->show();}
        if(i%9!=0&&ctrl[i-1].color!=round){red[i-1]->show();}
    }
        break;
    case 17:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sl1.svg.png"));
    i=temp1;if(i>8&&ctrl[i-9].color!=round){red[i-9]->show();}
    if(i<45)
    {
        if(i%9!=8&&ctrl[i+1].color!=round){red[i+1]->show();}
        if(i%9!=0&&ctrl[i-1].color!=round){red[i-1]->show();}
    }
        break;
    case 18:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sl1.svg.png"));
    i=temp1;if(i>8&&ctrl[i-9].color!=round){red[i-9]->show();}
    if(i<45)
    {
        if(i%9!=8&&ctrl[i+1].color!=round){red[i+1]->show();}
        if(i%9!=0&&ctrl[i-1].color!=round){red[i-1]->show();}
    }
        break;
    case 19:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sl1.svg.png"));
    i=temp1;if(i>8&&ctrl[i-9].color!=round){red[i-9]->show();}
    if(i<45)
    {
        if(i%9!=8&&ctrl[i+1].color!=round){red[i+1]->show();}
        if(i%9!=0&&ctrl[i-1].color!=round){red[i-1]->show();}
    }
        break;
    case 20:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sl1.svg.png"));
    i=temp1;if(i>8&&ctrl[i-9].color!=round){red[i-9]->show();}
    if(i<45)
    {
        if(i%9!=8&&ctrl[i+1].color!=round){red[i+1]->show();}
        if(i%9!=0&&ctrl[i-1].color!=round){red[i-1]->show();}
    }
        break;
    case 21:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sl1.svg.png"));
    i=temp1;if(i>8&&ctrl[i-9].color!=round){red[i-9]->show();}
    if(i<45)
    {
        if(i%9!=8&&ctrl[i+1].color!=round){red[i+1]->show();}
        if(i%9!=0&&ctrl[i-1].color!=round){red[i-1]->show();}
    }
        break;
    case 22:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_cl1.svg.png"));
    for(i=temp1+1;i<9*((temp1/9)+1);i++)
    {
        if(ctrl[i].color==0&&can==0){red[i]->show();}
        else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
    }
    can=0;
    for(i=temp1-1;i>=9*(temp1/9);i--)
    {
        if(ctrl[i].color==0&&can==0){red[i]->show();}
        else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
    }
    can=0;
    for(i=temp1+9;i<90;i+=9)
    {
        if(ctrl[i].color==0&&can==0){red[i]->show();}
        else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
    }
    can=0;
    for(i=temp1-9;i>=0;i-=9)
    {
        if(ctrl[i].color==0&&can==0){red[i]->show();}
        else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
    }
        can=0;
        break;
    case 23:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_cl1.svg.png"));
    for(i=temp1+1;i<9*((temp1/9)+1);i++)
    {
        if(ctrl[i].color==0&&can==0){red[i]->show();}
        else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
    }
    can=0;
    for(i=temp1-1;i>=9*(temp1/9);i--)
    {
        if(ctrl[i].color==0&&can==0){red[i]->show();}
        else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
    }
    can=0;
    for(i=temp1+9;i<90;i+=9)
    {
        if(ctrl[i].color==0&&can==0){red[i]->show();}
        else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
    }
    can=0;
    for(i=temp1-9;i>=0;i-=9)
    {
        if(ctrl[i].color==0&&can==0){red[i]->show();}
        else {if(can==0){can=1;}else if(can==1&&ctrl[i].color!=round&&ctrl[i].color!=0){red[i]->show();break;}}
    }
        can=0;
        break;
    case 24:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_rl1.svg.png"));
    for(i=temp1+1;i<9*((temp1/9)+1);i++)
    {
        if(ctrl[i].color==0){red[i]->show();}
        else if(ctrl[i].color!=round){red[i]->show();break;}
        else if(ctrl[i].color==round){break;}
    }
    for(i=temp1-1;i>=9*(temp1/9);i--)
    {
        if(ctrl[i].color==0){red[i]->show();}
        else if(ctrl[i].color!=round){red[i]->show();break;}
        else if(ctrl[i].color==round){break;}
    }
    for(i=temp1+9;i<90;i+=9)
    {
        if(ctrl[i].color==0){red[i]->show();}
        else if(ctrl[i].color!=round){red[i]->show();break;}
        else if(ctrl[i].color==round){break;}
    }
    for(i=temp1-9;i>=0;i-=9)
    {
        if(ctrl[i].color==0){red[i]->show();}
        else if(ctrl[i].color!=round){red[i]->show();break;}
        else if(ctrl[i].color==round){break;}
    }
        break;
    case 32:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_rl1.svg.png"));
    for(i=temp1+1;i<9*((temp1/9)+1);i++)
    {
        if(ctrl[i].color==0){red[i]->show();}
        else if(ctrl[i].color!=round){red[i]->show();break;}
        else if(ctrl[i].color==round){break;}
    }
    for(i=temp1-1;i>=9*(temp1/9);i--)
    {
        if(ctrl[i].color==0){red[i]->show();}
        else if(ctrl[i].color!=round){red[i]->show();break;}
        else if(ctrl[i].color==round){break;}
    }
    for(i=temp1+9;i<90;i+=9)
    {
        if(ctrl[i].color==0){red[i]->show();}
        else if(ctrl[i].color!=round){red[i]->show();break;}
        else if(ctrl[i].color==round){break;}
    }
    for(i=temp1-9;i>=0;i-=9)
    {
        if(ctrl[i].color==0){red[i]->show();}
        else if(ctrl[i].color!=round){red[i]->show();break;}
        else if(ctrl[i].color==round){break;}
    }
        break;
    case 25:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_hl1.svg (1).png"));
    i=temp1;
    if(i>17&&ctrl[i-9].color==0){

    if(i%9!=0){if(ctrl[i-19].color!=round){red[i-19]->show();}}
    if(i%9!=8){if(ctrl[i-17].color!=round){red[i-17]->show();}}
    }

    if(i%9>1&&ctrl[i-1].color==0){

    if(i/9!=0){if(ctrl[i-11].color!=round){red[i-11]->show();}}
    if(i/9!=9){if(ctrl[i+7].color!=round){red[i+7]->show();}}
    }

    if(i<72&&ctrl[i+9].color==0){

    if(i%9!=0){if(ctrl[i+17].color!=round){red[i+17]->show();}}
    if(i%9!=8){if(ctrl[i+19].color!=round){red[i+19]->show();}}
    }
    if(i%9<7&&ctrl[i+1].color==0){

    if(i/9!=0){if(ctrl[i-7].color!=round){red[i-7]->show();}}
    if(i/9!=9){if(ctrl[i+11].color!=round){red[i+11]->show();}}
    }
        break;
    case 31:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_hl1.svg (1).png"));
    i=temp1;
    if(i>17&&ctrl[i-9].color==0){

    if(i%9!=0){if(ctrl[i-19].color!=round){red[i-19]->show();}}
    if(i%9!=8){if(ctrl[i-17].color!=round){red[i-17]->show();}}
    }

    if(i%9>1&&ctrl[i-1].color==0){

    if(i/9!=0){if(ctrl[i-11].color!=round){red[i-11]->show();}}
    if(i/9!=9){if(ctrl[i+7].color!=round){red[i+7]->show();}}
    }

    if(i<72&&ctrl[i+9].color==0){

    if(i%9!=0){if(ctrl[i+17].color!=round){red[i+17]->show();}}
    if(i%9!=8){if(ctrl[i+19].color!=round){red[i+19]->show();}}
    }
    if(i%9<7&&ctrl[i+1].color==0){

    if(i/9!=0){if(ctrl[i-7].color!=round){red[i-7]->show();}}
    if(i/9!=9){if(ctrl[i+11].color!=round){red[i+11]->show();}}
    }
        break;
    case 26:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_el1.svg.png"));
    i=temp1;
    if(i==83)
    {
    if(ctrl[73].color==0&&ctrl[63].color!=round){red[63]->show();}
    if(ctrl[75].color==0&&ctrl[67].color!=round){red[67]->show();}
    }
    else if(i==87){
        if(ctrl[77].color==0&&ctrl[67].color!=round){red[67]->show();}
    if(ctrl[79].color==0&&ctrl[71].color!=round){red[71]->show();}
    }
    else if(i==47)
    {
    if(ctrl[55].color==0&&ctrl[63].color!=round){red[63]->show();}
    if(ctrl[57].color==0&&ctrl[67].color!=round){red[67]->show();}
    }
    else if(i==51){
        if(ctrl[59].color==0&&ctrl[67].color!=round){red[67]->show();}
    if(ctrl[61].color==0&&ctrl[71].color!=round){red[71]->show();}
    }
    else if(i==63)
    {
    if(ctrl[55].color==0&&ctrl[47].color!=round){red[47]->show();}
    if(ctrl[73].color==0&&ctrl[83].color!=round){red[83]->show();}
    }
    else if(i==71)
    {
    if(ctrl[61].color==0&&ctrl[51].color!=round){red[51]->show();}
    if(ctrl[79].color==0&&ctrl[87].color!=round){red[87]->show();}
    }
    else if(i==67)
    {
    if(ctrl[57].color==0&&ctrl[47].color!=round){red[47]->show();}
    if(ctrl[75].color==0&&ctrl[83].color!=round){red[83]->show();}
    if(ctrl[59].color==0&&ctrl[51].color!=round){red[51]->show();}
    if(ctrl[77].color==0&&ctrl[87].color!=round){red[87]->show();}
    }
        break;
    case 30:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_el1.svg.png"));
    i=temp1;
    if(i==83)
    {
    if(ctrl[73].color==0&&ctrl[63].color!=round){red[63]->show();}
    if(ctrl[75].color==0&&ctrl[67].color!=round){red[67]->show();}
    }
    else if(i==87){
        if(ctrl[77].color==0&&ctrl[67].color!=round){red[67]->show();}
    if(ctrl[79].color==0&&ctrl[71].color!=round){red[71]->show();}
    }
    else if(i==47)
    {
    if(ctrl[55].color==0&&ctrl[63].color!=round){red[63]->show();}
    if(ctrl[57].color==0&&ctrl[67].color!=round){red[67]->show();}
    }
    else if(i==51){
        if(ctrl[59].color==0&&ctrl[67].color!=round){red[67]->show();}
    if(ctrl[61].color==0&&ctrl[71].color!=round){red[71]->show();}
    }
    else if(i==63)
    {
    if(ctrl[55].color==0&&ctrl[47].color!=round){red[47]->show();}
    if(ctrl[73].color==0&&ctrl[83].color!=round){red[83]->show();}
    }
    else if(i==71)
    {
    if(ctrl[61].color==0&&ctrl[51].color!=round){red[51]->show();}
    if(ctrl[79].color==0&&ctrl[87].color!=round){red[87]->show();}
    }
    else if(i==67)
    {
    if(ctrl[57].color==0&&ctrl[47].color!=round){red[47]->show();}
    if(ctrl[75].color==0&&ctrl[83].color!=round){red[83]->show();}
    if(ctrl[59].color==0&&ctrl[51].color!=round){red[51]->show();}
    if(ctrl[77].color==0&&ctrl[87].color!=round){red[87]->show();}
    }
        break;
    case 27:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_al1.svg.png"));
    i=temp1;
    if(i==84){if(ctrl[76].color!=round){red[76]->show();}}
    if(i==86){if(ctrl[76].color!=round){red[76]->show();}}
    if(i==66){if(ctrl[76].color!=round){red[76]->show();}}
    if(i==68){if(ctrl[76].color!=round){red[76]->show();}}
    if(i==76)
    {if(ctrl[84].color!=round){red[84]->show();}
    if(ctrl[86].color!=round){red[86]->show();}
    if(ctrl[66].color!=round){red[66]->show();}
    if(ctrl[68].color!=round){red[68]->show();}}
        break;
    case 29:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_al1.svg.png"));
    i=temp1;
    if(i==84){if(ctrl[76].color!=round){red[76]->show();}}
    if(i==86){if(ctrl[76].color!=round){red[76]->show();}}
    if(i==66){if(ctrl[76].color!=round){red[76]->show();}}
    if(i==68){if(ctrl[76].color!=round){red[76]->show();}}
    if(i==76)
    {if(ctrl[84].color!=round){red[84]->show();}
    if(ctrl[86].color!=round){red[86]->show();}
    if(ctrl[66].color!=round){red[66]->show();}
    if(ctrl[68].color!=round){red[68]->show();}}
        break;
    case 28:
    cancel->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_gl1.svg.png"));
    i=temp1;
    if(i/9!=7){if(ctrl[i-9].color!=round){red[i-9]->show();}}
    if(i/9!=9){if(ctrl[i+9].color!=round){red[i+9]->show();}}
    if(i%9!=3){if(ctrl[i-1].color!=round){red[i-1]->show();}}
    if(i%9!=5){if(ctrl[i+1].color!=round){red[i+1]->show();}}
        break;
}
    can=0;
    cancel->setIconSize(pawn[0]->size());
    cancel->setStyleSheet("border:none");
    if(king[0]->x==king[1]->x&&king[0]->x==btn1->x)
    {
     for(i=temp1;i<90;i+=9)
     {
         if(ctrl[i].character==28){break;}
         else if(ctrl[i].color!=0&&ctrl[i].character!=5&&ctrl[i].y<king[1]->y){can++;}
     }
      for(i=temp1-9;i>=0;i-=9)
      {
          if(ctrl[i].character==5){break;}
          else if(ctrl[i].color!=0&&ctrl[i].y>king[0]->y){can++;}
      }
      if(can==1&&btn1->character!=5&&btn1->character!=28){    for(i=0;i<10;i++)
          {
              for(j=0;j<9;j++)
              {
                  if((i*9+j)%9!=temp1%9){red[i*9+j]->close();}
                  if(ctrl[i*9+j].y<king[0]->y){red[i*9+j]->close();}
                  if(ctrl[i*9+j].y>king[1]->y){red[i*9+j]->close();}
              }
          }}
      else if(btn1->character==5&&ctrl[temp1+9].color!=0&&can==1){red[temp1+9]->close();}
      else if(btn1->character==28&&ctrl[temp1-9].color!=0&&can==1){red[temp1-9]->close();}
    }
    else if(king[0]->x==king[1]->x-80)
    {
        if(btn1->character==5)
        {
            for(i=temp1+9;i<90;i+=9)
            {
                if(ctrl[i+1].character==28){break;}
                else if(ctrl[i+1].color!=0){can++;}
            }
            if(can==0){red[temp1+1]->close();}
        }
        else if(btn1->character==28)
        {
            for(i=temp1-9;i>=0;i-=9)
            {
                if(ctrl[i-1].character==5){break;}
                else if(ctrl[i-1].color!=0){can++;}
            }
            if(can==0){red[temp1-1]->close();}
        }
    }
    else if(king[0]->x==king[1]->x+80)
    {
        if(btn1->character==5)
        {
            for(i=temp1+9;i<90;i+=9)
            {
                if(ctrl[i-1].character==28){break;}
                else if(ctrl[i-1].color!=0){can++;}
            }
            if(can==0){red[temp1-1]->close();}
        }
        else if(btn1->character==28)
        {
            for(i=temp1-9;i>=0;i-=9)
            {
                if(ctrl[i+1].character==5){break;}
                else if(ctrl[i+1].color!=0){can++;}
            }
            if(can==0){red[temp1+1]->close();}
        }
    }
}
}
}
void MainWindow::buttoncancel()
{
    for(i=0;i<10;i++)
    {
        for(j=0;j<9;j++)
        {
            red[i*9+j]->close();
        }
    }
    cancel->close();
}
void MainWindow::play()
{
    title->close();
    playmode->close();
    editmode->close();
    for(i=0;i<5;i++)
    {
    pawn[i] = new button();
    pawn[i]->setParent(this);
    pawn[i]->setGeometry(110+i*160,285,50,50);
    pawn[i]->x=110+i*160;
    pawn[i]->y=285;
    pawn[i]->show();
    pawn[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sd1.svg.png"));
    pawn[i]->setIconSize(pawn[i]->size());
    pawn[i]->setStyleSheet("border:none");
    pawn[i]->color=2;
    connect(pawn[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[27+i*2].color=2;
    pawn[i]->character=ctrl[27+i*2].character=12+i;
    ctrl[27+i*2].use=pawn[i];
}
    for(i=5;i<10;i++)
    {
    pawn[i] = new button();
    pawn[i]->setParent(this);
    pawn[i]->setGeometry(110+(i-5)*160,525,50,50);
    pawn[i]->x=110+(i-5)*160;
    pawn[i]->y=525;
    pawn[i]->show();
    pawn[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sl1.svg.png"));
    pawn[i]->setIconSize(pawn[i]->size());
    pawn[i]->setStyleSheet("border:none");
    pawn[i]->color=1;
    connect(pawn[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[54+(i-5)*2].color=1;
    pawn[i]->character=ctrl[54+(i-5)*2].character=12+i;
    ctrl[54+(i-5)*2].use=pawn[i];
}
    for(i=0;i<2;i++)
    {
    rook[i] = new button();
    rook[i]->setParent(this);
    rook[i]->setGeometry(110+i*640,45,50,50);
    rook[i]->x=110+i*640;
    rook[i]->y=45;
    rook[i]->show();
    rook[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_rd1.svg.png"));
    rook[i]->setIconSize(rook[i]->size());
    rook[i]->setStyleSheet("border:none");
    rook[i]->color=2;
    connect(rook[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[i*8].color=2;
    rook[i]->character=ctrl[i*8].character=1+i*8;
    ctrl[i*8].use=rook[i];
}
    for(i=0;i<2;i++)
    {
    rook[i+2] = new button();
    rook[i+2]->setParent(this);
    rook[i+2]->setGeometry(110+i*640,765,50,50);
    rook[i+2]->x=110+i*640;
    rook[i+2]->y=765;
    rook[i+2]->show();
    rook[i+2]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_rl1.svg.png"));
    rook[i+2]->setIconSize(rook[i+2]->size());
    rook[i+2]->setStyleSheet("border:none");
    rook[i+2]->color=1;
    connect(rook[i+2],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[81+i*8].color=1;
    rook[i+2]->character=ctrl[81+i*8].character=24+i*8;
    ctrl[81+i*8].use=rook[i+2];
}
    for(i=0;i<2;i++)
    {
    knight[i] = new button();
    knight[i]->setParent(this);
    knight[i]->setGeometry(190+i*480,45,50,50);
    knight[i]->x=190+i*480;
    knight[i]->y=45;
    knight[i]->show();
    knight[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_hd1.svg.png"));
    knight[i]->setIconSize(knight[i]->size());
    knight[i]->setStyleSheet("border:none");
    knight[i]->color=2;
    connect(knight[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[1+i*6].color=2;
    knight[i]->character=ctrl[1+i*6].character=2+i*6;
    ctrl[1+i*6].use=knight[i];
}
    for(i=0;i<2;i++)
    {
    knight[i+2] = new button();
    knight[i+2]->setParent(this);
    knight[i+2]->setGeometry(190+i*480,765,50,50);
    knight[i+2]->x=190+i*480;
    knight[i+2]->y=45;
    knight[i+2]->show();
    knight[i+2]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_hl1.svg (1).png"));
    knight[i+2]->setIconSize(knight[i+2]->size());
    knight[i+2]->setStyleSheet("border:none");
    knight[i+2]->color=1;
    connect(knight[i+2],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[82+i*6].color=1;
    knight[i+2]->character=ctrl[82+i*6].character=25+i*6;
    ctrl[82+i*6].use=knight[i+2];
}
    for(i=0;i<2;i++)
    {
    elephant[i] = new button();
    elephant[i]->setParent(this);
    elephant[i]->setGeometry(270+i*320,45,50,50);
    elephant[i]->x=270+i*320;
    elephant[i]->y=45;
    elephant[i]->show();
    elephant[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_ed1.svg.png"));
    elephant[i]->setIconSize(elephant[i]->size());
    elephant[i]->setStyleSheet("border:none");
    elephant[i]->color=2;
    connect(elephant[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[2+i*4].color=2;
    elephant[i]->character=ctrl[2+i*4].character=3+i*4;
    ctrl[2+i*4].use=elephant[i];
}
    for(i=0;i<2;i++)
    {
    elephant[i+2] = new button();
    elephant[i+2]->setParent(this);
    elephant[i+2]->setGeometry(270+i*320,765,50,50);
    elephant[i+2]->x=270+i*320;
    elephant[i+2]->y=765;
    elephant[i+2]->show();
    elephant[i+2]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_el1.svg.png"));
    elephant[i+2]->setIconSize(elephant[i+2]->size());
    elephant[i+2]->setStyleSheet("border:none");
    elephant[i+2]->color=1;
    connect(elephant[i+2],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[83+i*4].color=1;
    elephant[i+2]->character=ctrl[83+i*4].character=26+i*4;
    ctrl[83+i*4].use=elephant[i+2];
}
    for(i=0;i<2;i++)
    {
    advisor[i] = new button();
    advisor[i]->setParent(this);
    advisor[i]->setGeometry(350+i*160,45,50,50);
    advisor[i]->x=350+i*160;
    advisor[i]->y=45;
    advisor[i]->show();
    advisor[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_ad1.svg (1).png"));
    advisor[i]->setIconSize(advisor[i]->size());
    advisor[i]->setStyleSheet("border:none");
    advisor[i]->color=2;
    connect(advisor[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[3+i*2].color=2;
    advisor[i]->character=ctrl[3+i*2].character=4+i*2;
    ctrl[3+i*2].use=advisor[i];
}
    for(i=0;i<2;i++)
    {
    advisor[i+2] = new button();
    advisor[i+2]->setParent(this);
    advisor[i+2]->setGeometry(350+i*160,765,50,50);
    advisor[i+2]->x=350+i*160;
    advisor[i+2]->y=765;
    advisor[i+2]->show();
    advisor[i+2]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_al1.svg.png"));
    advisor[i+2]->setIconSize(advisor[i+2]->size());
    advisor[i+2]->setStyleSheet("border:none");
    advisor[i+2]->color=1;
    connect(advisor[i+2],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[84+i*2].color=1;
    advisor[i+2]->character=ctrl[84+i*2].character=27+i*2;
    ctrl[84+i*2].use=advisor[i+2];
}
    king[0] = new button();
    king[0]->setParent(this);
    king[0]->setGeometry(430,45,50,50);
    king[0]->x=430;
    king[0]->y=45;
    king[0]->show();
    king[0]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_gd1.svg (1).png"));
    king[0]->setIconSize(king[0]->size());
    king[0]->setStyleSheet("border:none");
    king[0]->color=2;
    connect(king[0],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[4].color=2;
    king[0]->character=ctrl[4].character=5;
    ctrl[4].use=king[0];

    king[1] = new button();
    king[1]->setParent(this);
    king[1]->setGeometry(430,765,50,50);
    king[1]->x=430;
    king[1]->y=765;
    king[1]->show();
    king[1]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_gl1.svg.png"));
    king[1]->setIconSize(king[1]->size());
    king[1]->setStyleSheet("border:none");
    king[1]->color=1;
    connect(king[1],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[85].color=1;
    king[1]->character=ctrl[85].character=28;
    ctrl[85].use=king[1];

    for(i=0;i<2;i++)
    {
    cannon[i] = new button();
    cannon[i]->setParent(this);
    cannon[i]->setGeometry(190+i*480,205,50,50);
    cannon[i]->x=190+i*480;
    cannon[i]->y=205;
    cannon[i]->show();
    cannon[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_cd1.svg.png"));
    cannon[i]->setIconSize(cannon[i]->size());
    cannon[i]->setStyleSheet("border:none");
    cannon[i]->color=2;
    connect(cannon[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[19+i*6].color=2;
    cannon[i]->character=ctrl[19+i*6].character=10+i;
    ctrl[19+i*6].use=cannon[i];
}
    for(i=0;i<2;i++)
    {
    cannon[i+2] = new button();
    cannon[i+2]->setParent(this);
    cannon[i+2]->setGeometry(190+i*480,605,50,50);
    cannon[i+2]->x=190+i*480;
    cannon[i+2]->y=605;
    cannon[i+2]->show();
    cannon[i+2]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_cl1.svg.png"));
    cannon[i+2]->setIconSize(cannon[i+2]->size());
    cannon[i+2]->setStyleSheet("border:none");
    cannon[i+2]->color=1;
    connect(cannon[i+2],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
    ctrl[64+i*6].color=1;
    cannon[i+2]->character=ctrl[64+i*6].character=22+i;
    ctrl[64+i*6].use=cannon[i+2];
}
    for(i=0;i<10;i++)
    {
        for(j=0;j<9;j++)
        {
        red[i*9+j] = new button();
        red[i*9+j]->setParent(this);
        red[i*9+j]->setGeometry(80*j+125,80*i+60,20,20);
        red[i*9+j]->x=80*j+125;
        red[i*9+j]->y=80*i+60;
        red[i*9+j]->setIcon(QIcon(":/pic/pj2src/piece/3257456390b33e6-removebg.png"));
        red[i*9+j]->setIconSize(red[i*9+j]->size());
        red[i*9+j]->setStyleSheet("border:none");
        red[i*9+j]->close();
        connect(red[i*9+j],SIGNAL(clicked(bool)),this,SLOT(buttonmove()));
        ctrl[i*9+j].x=110+80*j;
        ctrl[i*9+j].y=45+80*i;
        }
    }
    cancel = new button();
    cancel->setParent(this);
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(buttoncancel()));
    cancel->close();
    redfirst = new button();
    redfirst->setParent(this);
    redfirst->setText(tr("RED FIRST"));
    redfirst->setGeometry(900,600,200,100);
    redfirst->show();
    connect(redfirst,SIGNAL(clicked(bool)),this,SLOT(rf()));

    blackfirst = new button();
    blackfirst->setText(tr("BLACK FIRST"));
    blackfirst->setParent(this);
    blackfirst->setGeometry(900,700,200,100);
    blackfirst->show();
    connect(blackfirst,SIGNAL(clicked(bool)),this,SLOT(bf()));
    mode=2;
}
void MainWindow::edit()
{
mode=1;
title->close();
playmode->close();
editmode->close();
for(i=0;i<5;i++)
{
pawn[i] = new button();
pawn[i]->setParent(this);
pawn[i]->setGeometry(900+i*50,45,50,50);
pawn[i]->x=900+i*50;
pawn[i]->y=45;
pawn[i]->show();
pawn[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sd1.svg.png"));
pawn[i]->setIconSize(pawn[i]->size());
pawn[i]->setStyleSheet("border:none");
connect(pawn[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
pawn[i]->character=12+i;
pawn[i]->color=2;
}
for(i=5;i<10;i++)
{
pawn[i] = new button();
pawn[i]->setParent(this);
pawn[i]->setGeometry(900+(i-5)*50,95,50,50);
pawn[i]->x=900+(i-5)*50;
pawn[i]->y=95;
pawn[i]->show();
pawn[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_sl1.svg.png"));
pawn[i]->setIconSize(pawn[i]->size());
pawn[i]->setStyleSheet("border:none");
connect(pawn[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
pawn[i]->character=12+i;
pawn[i]->color=1;
}
for(i=0;i<2;i++)
{
rook[i] = new button();
rook[i]->setParent(this);
rook[i]->setGeometry(900+i*50,145,50,50);
rook[i]->x=900+i*50;
rook[i]->y=145;
rook[i]->show();
rook[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_rd1.svg.png"));
rook[i]->setIconSize(rook[i]->size());
rook[i]->setStyleSheet("border:none");
connect(rook[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
rook[i]->character=1+i*8;
rook[i]->color=2;
}
for(i=0;i<2;i++)
{
rook[i+2] = new button();
rook[i+2]->setParent(this);
rook[i+2]->setGeometry(1000+i*50,145,50,50);
rook[i+2]->x=1000+i*50;
rook[i+2]->y=145;
rook[i+2]->show();
rook[i+2]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_rl1.svg.png"));
rook[i+2]->setIconSize(rook[i+2]->size());
rook[i+2]->setStyleSheet("border:none");
connect(rook[i+2],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
rook[i+2]->character=24+i*8;
rook[i+2]->color=1;
}
for(i=0;i<2;i++)
{
knight[i] = new button();
knight[i]->setParent(this);
knight[i]->setGeometry(900+i*50,195,50,50);
knight[i]->x=900+i*50;
knight[i]->y=195;
knight[i]->show();
knight[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_hd1.svg.png"));
knight[i]->setIconSize(knight[i]->size());
knight[i]->setStyleSheet("border:none");
connect(knight[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
knight[i]->character=2+i*6;
knight[i]->color=2;
}
for(i=0;i<2;i++)
{
knight[i+2] = new button();
knight[i+2]->setParent(this);
knight[i+2]->setGeometry(1000+i*50,195,50,50);
knight[i+2]->x=1000+i*50;
knight[i+2]->y=195;
knight[i+2]->show();
knight[i+2]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_hl1.svg (1).png"));
knight[i+2]->setIconSize(knight[i+2]->size());
knight[i+2]->setStyleSheet("border:none");
connect(knight[i+2],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
knight[i+2]->character=25+i*6;
knight[i+2]->color=1;
}
for(i=0;i<2;i++)
{
elephant[i] = new button();
elephant[i]->setParent(this);
elephant[i]->setGeometry(900+i*50,245,50,50);
elephant[i]->x=900+i*50;
elephant[i]->y=245;
elephant[i]->show();
elephant[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_ed1.svg.png"));
elephant[i]->setIconSize(elephant[i]->size());
elephant[i]->setStyleSheet("border:none");
connect(elephant[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
elephant[i]->character=3+i*4;
elephant[i]->color=2;
}
for(i=0;i<2;i++)
{
elephant[i+2] = new button();
elephant[i+2]->setParent(this);
elephant[i+2]->setGeometry(1000+i*50,245,50,50);
elephant[i+2]->x=1000+i*50;
elephant[i+2]->y=245;
elephant[i+2]->show();
elephant[i+2]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_el1.svg.png"));
elephant[i+2]->setIconSize(elephant[i+2]->size());
elephant[i+2]->setStyleSheet("border:none");
connect(elephant[i+2],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
elephant[i+2]->character=26+i*4;
elephant[i+2]->color=1;
}
for(i=0;i<2;i++)
{
advisor[i] = new button();
advisor[i]->setParent(this);
advisor[i]->setGeometry(900+i*50,295,50,50);
advisor[i]->x=900+i*50;
advisor[i]->y=295;
advisor[i]->show();
advisor[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_ad1.svg (1).png"));
advisor[i]->setIconSize(advisor[i]->size());
advisor[i]->setStyleSheet("border:none");
connect(advisor[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
advisor[i]->character=4+i*2;
advisor[i]->color=2;
}
for(i=0;i<2;i++)
{
advisor[i+2] = new button();
advisor[i+2]->setParent(this);
advisor[i+2]->setGeometry(1000+i*50,295,50,50);
advisor[i+2]->x=1000+i*50;
advisor[i+2]->y=295;
advisor[i+2]->show();
advisor[i+2]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_al1.svg.png"));
advisor[i+2]->setIconSize(advisor[i+2]->size());
advisor[i+2]->setStyleSheet("border:none");
connect(advisor[i+2],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
advisor[i+2]->character=27+i*2;
advisor[i+2]->color=1;
}
king[0] = new button();
king[0]->setParent(this);
king[0]->setGeometry(900,345,50,50);
king[0]->x=900;
king[0]->y=345;
king[0]->show();
king[0]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_gd1.svg (1).png"));
king[0]->setIconSize(king[0]->size());
king[0]->setStyleSheet("border:none");
connect(king[0],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
king[0]->character=5;
king[0]->color=2;

king[1] = new button();
king[1]->setParent(this);
king[1]->setGeometry(950,345,50,50);
king[1]->x=950;
king[1]->y=345;
king[1]->show();
king[1]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_gl1.svg.png"));
king[1]->setIconSize(king[1]->size());
king[1]->setStyleSheet("border:none");
connect(king[1],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
king[1]->character=28;
king[1]->color=1;

for(i=0;i<2;i++)
{
cannon[i] = new button();
cannon[i]->setParent(this);
cannon[i]->setGeometry(900+i*50,395,50,50);
cannon[i]->x=900+i*50;
cannon[i]->y=395;
cannon[i]->show();
cannon[i]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_cd1.svg.png"));
cannon[i]->setIconSize(cannon[i]->size());
cannon[i]->setStyleSheet("border:none");
connect(cannon[i],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
cannon[i]->character=10+i;
cannon[i]->color=2;
}
for(i=0;i<2;i++)
{
cannon[i+2] = new button();
cannon[i+2]->setParent(this);
cannon[i+2]->setGeometry(1000+i*50,395,50,50);
cannon[i+2]->x=1000+i*50;
cannon[i+2]->y=395;
cannon[i+2]->show();
cannon[i+2]->setIcon(QIcon(":/pic/pj2src/piece/Xiangqi_cl1.svg.png"));
cannon[i+2]->setIconSize(cannon[i+2]->size());
cannon[i+2]->setStyleSheet("border:none");
connect(cannon[i+2],SIGNAL(clicked(bool)),this,SLOT(buttonpush()));
cannon[i+2]->character=22+i;
cannon[i+2]->color=1;
}
cancel = new button();
cancel->setParent(this);
connect(cancel,SIGNAL(clicked(bool)),this,SLOT(buttoncancel()));
cancel->close();

Done = new button();
Done->setParent(this);
Done->setText("Done");
connect(Done,SIGNAL(clicked(bool)),this,SLOT(done()));
Done->setGeometry(900,495,250,150);
Done->setFont(QFont("Courier New" ,50,QFont::StyleItalic,Qt::white));
Done->show();
for(i=0;i<10;i++)
{
    for(j=0;j<9;j++)
    {
    red[i*9+j] = new button();
    red[i*9+j]->setParent(this);
    red[i*9+j]->setGeometry(80*j+125,80*i+60,20,20);
    red[i*9+j]->x=80*j+125;
    red[i*9+j]->y=80*i+60;
    red[i*9+j]->setIcon(QIcon(":/pic/pj2src/piece/3257456390b33e6-removebg.png"));
    red[i*9+j]->setIconSize(red[i*9+j]->size());
    red[i*9+j]->setStyleSheet("border:none");
    red[i*9+j]->close();
    connect(red[i*9+j],SIGNAL(clicked(bool)),this,SLOT(buttonmove()));
    ctrl[i*9+j].x=110+80*j;
    ctrl[i*9+j].y=45+80*i;
    }
}
label1 = new QLabel(this);
label1->setText(tr("You must put both king on the board"));
label1->setGeometry(850,650,300,100);
label1->setAlignment(Qt::AlignCenter);
label1->close();
}

void MainWindow::done()
{

    if(king[0]->x>=900||king[1]->x>=900)
    {

            label1->show();
    }
    else
    {
        back->close();
    for(i=0;i<4;i++)
    {
        if(advisor[i]->x>=900){advisor[i]->close();}
        if(elephant[i]->x>=900){elephant[i]->close();}
        if(knight[i]->x>=900){knight[i]->close();}
        if(rook[i]->x>=900){rook[i]->close();}
        if(cannon[i]->x>=900){cannon[i]->close();}
    }
    for(i=0;i<10;i++)
    {
        if(pawn[i]->x>=900){pawn[i]->close();}
    }
    Done->close();
    label1->close();

    redfirst = new button();
    redfirst->setParent(this);
    redfirst->setText(tr("RED FIRST"));
    redfirst->setGeometry(900,600,200,100);
    redfirst->show();
    connect(redfirst,SIGNAL(clicked(bool)),this,SLOT(rf()));

    blackfirst = new button();
    blackfirst->setText(tr("BLACK FIRST"));
    blackfirst->setParent(this);
    blackfirst->setGeometry(900,700,200,100);
    blackfirst->show();
    connect(blackfirst,SIGNAL(clicked(bool)),this,SLOT(bf()));

    }
}

void MainWindow::rf()
{
    mode=0;
    round=1;
    redfirst->close();
    blackfirst->close();
    turn->setText(tr("Red side turn"));
    turn->show();
}
void MainWindow::bf()
{
    mode=0;
    round=2;
    redfirst->close();
    blackfirst->close();
    turn->setText(tr("Black side turn"));
    turn->show();
}
void MainWindow::buttonmove()
{
    btn2 = dynamic_cast<button*>(sender());
        back->show();
    for(i=0;i<10;i++)
    {

        for(j=0;j<9;j++)
        {
            red[i*9+j]->close();
            if(ctrl[i*9+j].x==btn2->x-15&&ctrl[i*9+j].y==btn2->y-15)
            {
                temp2=i*9+j;
            }
        }
    }
    if(mode==1){
       btn1->move(ctrl[temp2].x,ctrl[temp2].y);
       ctrl[temp2].use=btn1;
       cancel->close();
       ctrl[temp2].color= btn1->color;
       ctrl[temp2].character= btn1->character;
       btn1->x=ctrl[temp2].x;
       btn1->y=ctrl[temp2].y;
    }
    else{
    if(ctrl[temp2].color!=round||ctrl[temp2].color==0)
    {
        if(ctrl[temp2].color!=0)
        {
            death[ctrl[temp2].character-1]->show();
            pre=ctrl[temp2].use;
            ctrl[temp2].use->close();
            if(ctrl[temp2].character==5){mode=2;}else if(ctrl[temp2].character==28){mode=2;}
        }
        c=ctrl[temp2].color;
        btn1->move(ctrl[temp2].x,ctrl[temp2].y);
        ctrl[temp2].use=btn1;
        cancel->close();
        ctrl[temp2].color= ctrl[temp1].color;
        ctrl[temp2].character= ctrl[temp1].character;
    ctrl[temp1].color=0;ctrl[temp1].character=0;
    btn1->x=ctrl[temp2].x;
    btn1->y=ctrl[temp2].y;
    }
    if(round==1){round=2;turn->setText(tr("Black side turn"));}
    else {round=1;turn->setText(tr("Red side turn"));}
     if(round==2&&mode==2){turn->setText(tr("Red side win!"));back->close();}else if(round==1&&mode==2){turn->setText(tr("Black side win!"));back->close();}
    }

}

void MainWindow::previous()
{
    back->close();
        cancel->close();
    if(mode==1){
        btn1->move(cancel->x,cancel->y);
        ctrl[temp2].color= 0;
        ctrl[temp2].character= 0;
        btn1->x=cancel->x;
        btn1->y=cancel->y;
    }
    else if(mode==0){
        for(i=0;i<90;i++){red[i]->close();}
        if(c!=0){pre->show();ctrl[temp2].character= pre->character;ctrl[temp2].use=pre;ctrl[temp2].color=c;}
        else if(c==0){ctrl[temp2].character=0;ctrl[temp2].color=0;}
        btn1->move(cancel->x,cancel->y);
        ctrl[temp1].use=btn1;
        ctrl[temp1].color=btn1->color;
        ctrl[temp1].character=btn1->character;

    btn1->x=cancel->x;
    btn1->y=cancel->y;
    if(round==1){round=2;turn->setText(tr("Black side turn"));}
    else {round=1;turn->setText(tr("Red side turn"));}
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

