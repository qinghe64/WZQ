#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"GameModel.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    GameModel* game;//游戏指针
    GameType game_type;//存储游戏类型

    int clickPosRow,clickPosCol;//储存点击的位置
    bool selectPos=false;//是否移动到合适位置，以选中交叉点

    //绘制
    void paintEvent(QPaintEvent *event);

    void initGame();
   void initAIGame();

    void mouseMoveEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);

    void  chessOneByPerson();

   private slots:
    void chessOneByAI();

};
#endif // MAINWINDOW_H










