#include "mainwindow.h"
#include "ui_mainwindow.h"


#include<QPainter>
#include<QMouseEvent>
#include<math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);

    //设置窗口大小
    setFixedSize(
        MARGIN*2+BLOCK_SIZE*BOARD_GRAD_SIZE,
        MARGIN*2+BLOCK_SIZE*BOARD_GRAD_SIZE);

    initGame();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing,true);//抗锯齿

    for(int i=0;i<BOARD_GRAD_SIZE+1;i++)
    {
        //从左到右，第（i+1）条竖线
        painter.drawLine(MARGIN+BLOCK_SIZE*i,MARGIN,
                         MARGIN+BLOCK_SIZE*i,size().height()-MARGIN);
        //从上到下，第（i+1）条横线
        painter.drawLine(MARGIN,MARGIN+BLOCK_SIZE*i,
                         size().width()-MARGIN,MARGIN+BLOCK_SIZE*i);
    }

    //绘制选中点
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    //绘制落子标记，防止鼠标出框越界
    if(clickPosRow>0&&clickPosRow<BOARD_GRAD_SIZE&&
        clickPosCol>0&&clickPosCol<BOARD_GRAD_SIZE&&
        game->gameMapVec[clickPosRow][clickPosCol]==0)
    {
        if(game->playerFlag)
            brush.setColor(QColorConstants::Black);
        else
            brush.setColor(QColorConstants::White) ;
        painter.setBrush(brush);
        painter.drawRect(MARGIN+BLOCK_SIZE*clickPosCol-MARK_SIZE/2,MARGIN+BLOCK_SIZE*clickPosRow-MARK_SIZE/2,MARK_SIZE,MARK_SIZE);


    }
    //绘制棋子
    for(int i=0;i<BOARD_GRAD_SIZE;i++)
        for(int j=0;j<BOARD_GRAD_SIZE;j++)
        {
            if(game->gameMapVec[i][j]==1)
            {
                brush.setColor(QColorConstants::Black);
                painter.setBrush(brush);
                painter.drawEllipse(MARGIN+BLOCK_SIZE*j-CHESS_RADIUS,MARGIN+BLOCK_SIZE*i-CHESS_RADIUS,2*CHESS_RADIUS,2*CHESS_RADIUS);
            }
            else             if(game->gameMapVec[i][j]==-1)
            {
                brush.setColor(QColorConstants::White);
                painter.setBrush(brush);
                painter.drawEllipse(MARGIN+BLOCK_SIZE*j-CHESS_RADIUS,MARGIN+BLOCK_SIZE*i-CHESS_RADIUS,2*CHESS_RADIUS,2*CHESS_RADIUS);
            }
        }
    //判断输赢


}

void MainWindow::initGame()
{
    //初始化游戏模型
    game=new GameModel;
    initAIGame();
}

void MainWindow::initAIGame()
{
    game_type=AI;
    game->gameStatus=PLAYING;

    //在数据模型中进行初始化功能
    game->startGame(game_type);
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //通过鼠标的hover确定落子的标记
    int x=event->x();
    int y=event->y();
    //棋盘边缘不能落子
    if(x>=MARGIN+BLOCK_SIZE/2&&
        x<size().width()-MARGIN-BLOCK_SIZE/2&&
        y>=MARGIN+BLOCK_SIZE/2&&
        y<size().height()-MARGIN-BLOCK_SIZE/2)
    {
        //获取最近的左上角的点
        //add by rock
        int col=(x-MARGIN)/BLOCK_SIZE;
        int row=(y-MARGIN)/BLOCK_SIZE;

        int leftTopPosX=MARGIN+BLOCK_SIZE*col;
        int leftTopPosY=MARGIN+BLOCK_SIZE*row;

        //根据距离算出合适的点击位置，一共四个点，根据半径距离选择最近的
        clickPosRow=-1;
        clickPosCol=-1;
        int len=0;//计算完后取整就可以了

        selectPos=false;

        //确定一个误差在范围内的点，且只可能确定一个出来

        //左上角
        len=sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY)*(y-leftTopPosY));
        if(len<POS_OFFSET)
        {
            clickPosRow=row;
            clickPosCol=col;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0)
            {
                selectPos=true;
            }
        }
        //右上角
        len=sqrt((x-leftTopPosX-BLOCK_SIZE)*(x-leftTopPosX-BLOCK_SIZE)+(y-leftTopPosY)*(y-leftTopPosY));
        if(len<POS_OFFSET)
        {
            clickPosRow=row;
            clickPosCol=col+1;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0)
            {
                selectPos=true;
            }
        }
        //左下角
        len=sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY-BLOCK_SIZE)*(y-leftTopPosY-BLOCK_SIZE));
        if(len<POS_OFFSET)
        {
            clickPosRow=row+1;
            clickPosCol=col;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0)
            {
                selectPos=true;
            }
        }
        //右下角
        len=sqrt((x-leftTopPosX-BLOCK_SIZE)*(x-leftTopPosX-BLOCK_SIZE)+(y-leftTopPosY-BLOCK_SIZE)*(y-leftTopPosY-BLOCK_SIZE));
        if(len<POS_OFFSET)
        {
            clickPosRow=row+1;
            clickPosCol=col+1;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0)
            {
                selectPos=true;
            }
        }
        if(selectPos)
        {
            update();
        }

    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(selectPos==false)
    {
        return;
    }
    else
    {
        //在落子之前，把落子再设置成false
        selectPos=false;
    }

    //由人来下棋
    chessOneByPerson();

    if(game_type==AI)
    {
        //人机模式
        //AI模式
    }
}


void MainWindow::chessOneByPerson()
{
    //根据当前储存的坐标下子
    //只有有效点击并且该处没有子才落子
    if(clickPosRow!=-1&&clickPosCol!=-1&&game->gameMapVec[clickPosRow][clickPosCol]==0)
    {
        //在游戏的数据模型中落子
        game->actionByPerson(clickPosRow,clickPosCol);
        //重绘
        update();
    }
}



















