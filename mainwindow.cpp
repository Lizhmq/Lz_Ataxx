#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent){
    xPressed = yPressed = 100;
    count = 4;
    turn = 1;
    notfirst = 0;
    memset(board, 0, sizeof board);
    board[0][0] = board[6][6] = 1;
    board[6][0] = board[0][6] = -1;
    setMinimumSize(720,950);
    setMaximumSize(720,950);

    //font
    font1 = QFont("Brush Script MT",20);
    font2 = QFont("Informal Roman",22);

    //PVP
    NewPVP = new QPushButton("New PVP",this);
    NewPVP -> setGeometry(90,770,150,50);
    NewPVP -> setFont(font2);
    connect(NewPVP, SIGNAL(clicked()), this, SLOT(clean1()));

    //PVE
    NewPVE = new QPushButton("New PVE", this);
    NewPVE -> setGeometry(90,840,150,50);
    NewPVE -> setFont(font2);
    connect(NewPVE, SIGNAL(clicked()), this, SLOT(clean2()));

    //Save
    Save = new QPushButton("Save",this);
    Save -> setGeometry(295,770,150,50);
    Save -> setFont(font2);
    connect(Save, SIGNAL(clicked()), this, SLOT(save()));

    //Load
    Load = new QPushButton("Load",this);
    Load -> setGeometry(295,840,150,50);
    Load -> setFont(font2);
    connect(Load, SIGNAL(clicked()), this, SLOT(load()));

    //Pass
    Pass = new QPushButton("Pass",this);
    Pass -> setGeometry(500,770,150,50);
    Pass -> setFont(font2);
    connect(Pass, SIGNAL(clicked()), this, SLOT(pass()));

    //Tips
    Tips = new QPushButton("Tips",this);
    Tips -> setGeometry(500,840,150,50);
    Tips -> setFont(font2);
    connect(Tips, SIGNAL(clicked()), this, SLOT(tips()));

    Switch = new QPushButton("Switch", this);
    Switch -> setGeometry(550, 88, 100, 50);
    Switch -> setFont(font2);
    connect(Switch, SIGNAL(clicked()), this, SLOT(sswitch()));

}


MainWindow::~MainWindow(){

}

void MainWindow::save(){
    freopen("back","w",stdout);
    for(int i=0;i<7;i++)
        for(int j=0;j<7;j++)
            printf("%d ",board[i][j]);
    printf("%d %d %d",int(WhiteTurn), count, human);
    fclose(stdout);
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.setFont(font1);

    //Welcome
    QRectF welcome(0,0,720,40);
    painter.drawText(welcome, Qt::AlignHCenter, "Welcome to play Ataxx");

    for(int i=1;i<=7;i++){
        QRectF temp(30,110+80*i,40,80);
        char a[2];
        a[1]='\0';
        a[0]=i+'0';
        painter.drawText(temp,Qt::AlignCenter, a);
    }
    for(int i=1;i<=7;i++){
        QRectF temp(10+80*i,150,80,40);
        char a[2]={' ','\0'};
        a[0]=i+'A'-1;
        painter.drawText(temp,Qt::AlignCenter,a);
    }

    QPixmap pix[49];
    //count    chess
    QFont font2("MONACO",14);
    QBrush brush;
    painter.setFont(font2);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(WhiteTurn ? Qt::white : Qt::black);
    painter.setBrush(brush);
    painter.drawEllipse(170,98,40,40);
    int count1 = 0;
    int count2 = 0;
    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 7; ++j) {
            if (board[i][j] == 0) {
                pix[i * 7 + j].load("image/10007.png");
            }
            else if (board[i][j] == 1) {
                pix[i * 7 + j].load("image/1.png");
                count1++;
            }
            else {
                pix[i * 7 + j].load("image/2.png");
                count2++;
            }
            painter.drawPixmap(90 + 80 * i, 190 + 80 * j, 80, 80, pix[i * 7 + j]);
        }

    QFont font4("MV Boli", 15);
    char s1[30]="Black Counts: ",s2[30]="White Counts: ";
    int l1=(int)strlen(s1),l2=(int)strlen(s2);
    s1[l1]=count1/10+'0';  s1[l1+1]=count1%10+'0'; s1[l1+2]='\0';
    s2[l2]=count2/10+'0';  s2[l2+1]=count2%10+'0'; s2[l2+2]='\0';
    QRectF text1(70,50,300,30), text2(360,50,300,30);
    painter.setFont(font4);
    painter.drawText(text1,Qt::AlignLeft,s1);
    painter.setFont(font4);
    painter.drawText(text2,Qt::AlignLeft,s2);

    QFont font3("MV Boli",19);
    painter.setFont(font3);
    QRectF text3(60,90,100,50);
    char s3[10]="  Turn: ";
    painter.drawText(text3,Qt::AlignCenter,s3);
    QRectF text4(300, 90, 150, 50);
    const char *s4 = "  Level: ";
    painter.drawText(text4,Qt::AlignLeft,s4);
    QRectF text5(430, 90, 130, 50);
    const char *s5 = Easy ? "Easy" : "Normal";
    painter.drawText(text5,Qt::AlignLeft,s5);

    QFont font5("", 10);
    painter.setFont(font5);;
    QRectF text6(220, 900, 300, 30);
    const char *s6 = "copyright © 1926---...    by Lzzz x)";
    painter.drawText(text6,Qt::AlignCenter,s6);

    // available places
    for (int i = -2; i <= 2; ++i)
        for (int j = -2; j <= 2; ++j)
            if (xPressed + i < 7 && xPressed + i >= 0
                && yPressed + j < 7 && yPressed + j >= 0
                && !board[xPressed + i][yPressed + j]) {
                    int xx = xPressed + i, yy = yPressed + j;
                    if (xx < 0 || xx >= 7 || yy < 0 || yy >= 7)
                        continue;
                    if (abs(i) <= 1 && abs(j) <= 1)
                        pix[xx * 7 + yy].load("image/10008.png");
                    else
                        pix[xx * 7 + yy].load("image/10009.png");
                    painter.drawPixmap(90 + 80 * xx, 190 + 80 * yy, 80, 80, pix[(xPressed + i) * 7 + yPressed + j]);
                }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    int x=float(event->x());
    int y=float(event->y());
    if(x<90||x>650||y<190||y>750||human == -1)
        return;
    x=(x-90)/80;
    y=(y-190)/80;
    turn = WhiteTurn ? -1 : 1;
    if(notfirst){
        if(board[x][y]==turn){
            xPressed = x;
            yPressed = y;
            update();
            return;
        }
        int dx = abs(x - xPressed),dy = abs(y - yPressed);
        int dis = dx > dy ? dx : dy;
        if(dis > 2||board[x][y])
            return;
        if(dis == 2)
            board[xPressed][yPressed]=0;

        board[x][y]=WhiteTurn ? -1 : 1;
        for(int i=-1;i<=1;i++)
            for(int j=-1;j<=1;j++)
                if(x+i>=0&&x+i<=6&&y+j<=6&&y+j>=0&&board[x+i][y+j])
                    board[x+i][y+j]=turn;count = 0;
        for(int i=0;i<7;i++)
            for(int j = 0;j<7;j++)
                if(board[i][j]) count ++;
        xPressed = yPressed = 100;
        notfirst = 0;
        WhiteTurn ^= 1;
        repaint();
        win(blackwin());
        if(!human){
            AI(board,WhiteTurn ? -1 : 1);
            WhiteTurn ^= 1;
            repaint();
            count = 0;
            for(int i=0;i<7;i++)
                for(int j = 0;j<7;j++)
                    if(board[i][j]) count ++;
            win(blackwin());
        }
    }
    else{
        if(board[x][y]!=turn)
            return;
        xPressed = x;
        yPressed = y;
        notfirst = 1;
    }
    repaint();
    win(blackwin());


}

void MainWindow::load(){
    freopen("back","r",stdin);
    for(int i=0;i<7;i++)
        for(int j=0;j<7;j++)
            scanf("%d ", &board[i][j]);
    int ha;
    scanf("%d %d %d", &ha, &count, &human);
    WhiteTurn = ha;
    turn = WhiteTurn ? -1 : 1;
    update();
}

void MainWindow::clean1(){
    memset(board,0,sizeof board);
    board[0][0]=board[6][6]=1;
    board[0][6]=board[6][0]=-1;
    count = 4;
    WhiteTurn = 0;
    xPressed = yPressed = 100;
    human = 1;
    update();
}

void MainWindow::clean2(){
    memset(board,0,sizeof board);
    board[0][0]=board[6][6]=1;
    board[0][6]=board[6][0]=-1;
    count = 4;
    WhiteTurn = 0;
    xPressed = yPressed = 100;
    human = 0;
    update();
}
//空手一步
void MainWindow::pass(){
    WhiteTurn ^= 1;
    xPressed = yPressed =100;
    repaint();
    if(!human){
        AI(board,WhiteTurn ? -1 : 1);
        WhiteTurn ^= 1;
        repaint();
        count = 0;
        for(int i=0;i<7;i++)
            for(int j = 0;j<7;j++)
                if(board[i][j]) count ++;
        win(blackwin());
    }
}

void MainWindow::win(int blackwin){
    if(blackwin==0)
        return;
    char s1[30] = "Black wins! Congratulations!";
    char s2[30] = "White wins! Congratulations!";
    char s3[30] = "Ha Ha Ha! You win~~~ ^_^";
    char s4[35] = "I'm sorry... But, you lose. T_T";
    if(!human){
        QMessageBox::information(NULL, "Game Over!", blackwin == 1 ? s3 : s4, "Try Again", NULL);
    }
    else QMessageBox::information(NULL, "Game Over!", blackwin == 1 ? s1 : s2, "Try Again", NULL);
    clean1();
    human = -1;
}
//判断游戏是否结束
int MainWindow::blackwin(){
    int blackcount = 0;
    count = 0;
    for(int i = 0;i<7;i++)
        for(int j = 0;j < 7;j++)
            if(board[i][j]) count ++;
    if(count == 49){
        for(int i=0;i<7;i++)
            for(int j=0;j<7;j++)
                if(board[i][j]==1)
                    blackcount++;
        if(blackcount>24)
            return 1;
        else
            return -1;
    }
    int temp=0;
    for(int i=0;i<7;i++)
        for(int j=0;j<7;j++)
            temp+=board[i][j];
    if(temp==count)
        return 1;
    else if(temp==-count)
        return -1;
    return 0;
}
//计算我方棋子
int MainWindow::cal(Board current, int color) {
    int mynum = 0;
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            if (current.chess[i][j] == color)
                mynum += 1;
            else if (current.chess[i][j] == color)
                mynum -= 1;
    return mynum;
}

int MainWindow::countchess(Board current, int color) {
    int mynum = 0;
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            if (current.chess[i][j] == color)
                mynum++;
    return mynum;
}

void MainWindow::myprocStep(int x0, int y0, int x1, int y1, int color, int chess[][7]) {
    int max = 0;
    max = abs(x0 - x1) > abs(y0 - y1) ? abs(x0 - x1) : abs(y0 - y1);
    if (max == 2) chess[x0][y0] = 0;
    chess[x1][y1] = color;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (x1 + i >= 0 && x1 + i < 7 && y1 + j >= 0 && y1 + j < 7 && chess[x1 + i][y1 + j])
                chess[x1 + i][y1 + j] = color;
    return;
}

int MainWindow::attempt(Board current, int depth, int alpha, int beta) {
    int score;
//    got = 0;
    if (depth == 0) return cal(current, WhiteTurn ? -1 : 1);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (current.chess[i][j]) continue;
            for (int k = 0; k < 8; k++) {
                int x1 = i + dx1[k], y1 = j + dy1[k];
                if (x1 >= 0 && x1 < 7 && y1 >= 0 && y1 < 7 && current.chess[x1][y1] == current.color) {
                    if (!got) {
                        valway.startx = x1; valway.starty = y1;
                        valway.endx = i; valway.endy = j;
                        got = 1;
                    }
                    Board temp = current;
                    myprocStep(x1, y1, i, j, temp.color, temp.chess);
                    if (temp.color == 1) temp.color = -1;
                    else temp.color = 1;
                    if (countall(temp) == 49)
                        if (countchess(temp, WhiteTurn ? -1 : 1) > 24)
                            return 10000;
                        else
                            return -10000;
                    score = attempt(temp, depth - 1, alpha, beta);
                    if ((ddl - depth) % 2 != 0) {
                        if (score < beta)
                            beta = score;
                        if (alpha > beta)
                            return beta;
                    }
                    else {
                        if (score > alpha) {
                            alpha = score;
                            if (depth == ddl) {
                                valway.startx = x1; valway.starty = y1;
                                valway.endx = i; valway.endy = j;
                            }
                        }
                        if (alpha > beta)
                            return alpha;
                    }
                }
            }
            for (int k = 0; k < 16; k++) {
                int x1 = i + dx2[k], y1 = j + dy2[k];
                if (x1 >= 0 && x1 < 7 && y1 >= 0 && y1 < 7 && current.chess[x1][y1] == current.color) {
                    if (!got) {
                        valway.startx = x1; valway.starty = y1;
                        valway.endx = i; valway.endy = j;
                        got = 1;
                    }
                    Board temp = current;
                    myprocStep(x1, y1, i, j, temp.color, temp.chess);
                    if (temp.color == 1) temp.color = -1;
                    else temp.color = 1;
                    if(blackwin() == 1){
                        if(WhiteTurn) return -49;
                        else return 49;
                    }
                    else if(blackwin() == -1){
                        if(WhiteTurn) return 49;
                        else return -49;
                    }
                    score = attempt(temp, depth - 1, alpha, beta);
                    if ((ddl - depth) % 2 != 0) {
                        if (score < beta)
                            beta = score;
                        if (alpha > beta)
                            return beta;
                    }
                    else {
                        if (score > alpha) {
                            alpha = score;
                            if (depth == ddl) {
                                valway.startx = x1; valway.starty = y1;
                                valway.endx = i; valway.endy = j;
                            }
                        }
                        if (alpha > beta)
                            return alpha;
                    }
                }
            }
        }
    }
    return ((ddl - depth) % 2) == 0 ? alpha : beta;
}

void MainWindow::AI(int chess[7][7], int color){
    got = 0;
    valway.startx = -1;
    Board temp;
    memcpy(temp.chess, chess, sizeof(temp.chess));
    temp.color = color;
    if (Easy)
        simple_greedy(temp);
    else
        attempt(temp, ddl, -50, 50);
    delay();
    if(valway.startx != -1)
        myprocStep(valway.startx,valway.starty,valway.endx,valway.endy,color,chess);
}

void MainWindow::tips(){
    AI(board,WhiteTurn ? -1 : 1);
    WhiteTurn ^= 1;
    win(blackwin());
    repaint();
    if(!human){
        AI(board,WhiteTurn ? -1 : 1);
        WhiteTurn ^= 1;
        win(blackwin());
    }
    update();
}

int MainWindow::delay(){
    QTime t;
    t.start();
    while(t.elapsed()<650)
        QCoreApplication::processEvents();
    return 0;
}

int MainWindow::countall(Board current) {
    int num = 0;
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            if (current.chess[i][j])
                num++;
    return num;
}

void MainWindow::sswitch()
{
    Easy ^= 1;
    repaint();
}

void MainWindow::simple_greedy(Board current)
{
    int score = -10000;
    got = 0;
     for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (current.chess[i][j]) continue;
            for (int k = 0; k < 8; k++) {
                int x1 = i + dx1[k], y1 = j + dy1[k];
                if (x1 >= 0 && x1 < 7 && y1 >= 0 && y1 < 7 && current.chess[x1][y1] == current.color) {
                    if (!got) {
                        valway.startx = x1; valway.starty = y1;
                        valway.endx = i; valway.endy = j;
                        got = 1;
                    }
                    Board temp = current;
                    myprocStep(x1, y1, i, j, temp.color, temp.chess);
                    int tmpscore;
                    if ((tmpscore = cal(temp, temp.color)) > score) {
                        score = tmpscore;
                        valway.startx = x1;
                        valway.starty = y1;
                        valway.endx = i;
                        valway.endy = j;
                        got = 1;
                    }
                }
            }
            for (int k = 0; k < 16; k++) {
                int x1 = i + dx2[k], y1 = j + dy2[k];
                if (x1 >= 0 && x1 < 7 && y1 >= 0 && y1 < 7 && current.chess[x1][y1] == current.color) {
                    if (!got) {
                        valway.startx = x1; valway.starty = y1;
                        valway.endx = i; valway.endy = j;
                        got = 1;
                    }
                    Board temp = current;
                    myprocStep(x1, y1, i, j, temp.color, temp.chess);
                    int tmpscore;
                    if ((tmpscore = cal(temp, temp.color)) > score) {
                        score = tmpscore;
                        valway.startx = x1;
                        valway.starty = y1;
                        valway.endx = i;
                        valway.endy = j;
                        got = 1;
                    }
                }
            }
        }
    }
    return;
}

