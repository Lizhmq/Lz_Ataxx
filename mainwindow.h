#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QBrush>
#include <QMouseEvent>
#include <QColor>
#include <QDebug>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *mouseEvent);

    bool notfirst;
    int turn;
    int xPressed, yPressed;
    int count;
    bool WhiteTurn;
    int board[7][7];
    struct Board {
        int chess[7][7];
        int color;
    };
    int dx1[8] = { 1,1,1,0,0,-1,-1,-1 }, dy1[8] = { 1,0,-1,1,-1,1,0,-1 };
    int dx2[16] = { 2,2,2,2,2,1,1,0,0,-1,-1,-2,-2,-2,-2,-2 }, dy2[16] = { 2,1,0,-1,-2,2,-2,2,-2,2,-2,2,1,0,-1,-2 };
    const int ddl = 3;
    struct way {
        int startx, starty;
        int endx, endy;
    }valway;
    int human = -1;
    bool got;


    QFont font;
    QPushButton *NewPVP, *NewPVE, *Load, *Save, *Pass, *Tips;

public slots:
    void win(int blackwin);
    int blackwin();
    void clean1();
    void clean2();
    void save();
    void load();
    void pass();
    int cal(Board current, int color);
    int countchess(Board current, int color);
    void myprocStep(int x0, int y0, int x1, int y1, int color, int chess[][7]);
    int attempt(Board current, int depth, int alpha, int beta);
    void AI(int chess[][7], int color);
    void tips();
    void delay();
    int countall(Board current);
};
#endif // MAINWINDOW_H
