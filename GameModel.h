#ifndef GAMEMODEL_H
#define GAMEMODEL_H


//---五子棋游戏模型类---//
#include<vector>

//游戏类型，双人还是AI
enum GameType
{
    Man,//双人对战模式
    AI//人机对弈模式
};

//游戏状态
enum GameStatus
{
    PLAYING,//游戏中
    WIN,//赢
    DEAD//输
};

//棋盘尺寸
const int BOARD_GRAD_SIZE=15;

const int MARGIN=30;//棋盘边缘空隙
const int CHESS_RADIUS=15;//棋子半径
const int MARK_SIZE=6;//落子标记边长
const int BLOCK_SIZE=40;//格子的大小
const int POS_OFFSET=BLOCK_SIZE*0.4;//鼠标点击的模糊距离上限

const int AI_THINK_TIME=700;//AI下棋的思考时间

class GameModel
{
public:
    GameModel(){};

    //存储当前游戏棋盘和棋子的情况，空白为0，黑子1，白子-1
    std::vector<std::vector<int>> gameMapVec;

    //储存各个点位的评分情况，作为AI下棋的依据
    std::vector<std::vector<int>>scoreMapVec;

    //标识下棋方，true：黑棋方   false：AI 白棋方
    bool playerFlag;

    GameType gameType;//游戏模式：人机对弈还是双人

    GameStatus gameStatus;//游戏状态

    void startGame(GameType type);

    void actionByPerson(int row,int col);
    void updateGameMap(int row,int col);

    bool isWin(int row,int col);
    void calulateScore();
    void actionByAI(int &clickrow,int& clickcol);

};

#endif // GAMEMODEL_H
