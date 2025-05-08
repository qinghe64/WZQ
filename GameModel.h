#ifndef GAMEMODEL_H
#define GAMEMODEL_H

// ---- 五子棋游戏模型类 ---- //
#include <vector>
#include<QVector>

// 游戏类型，双人还是AI（目前固定让AI下黑子）
enum GameType
{
    PERSON,
    BOT
};

// 游戏状态
enum GameStatus
{
    PLAYING,
    WIN,
    DEAD
};


const int kBoardSizeNum = 15;// 棋盘尺寸


// 新增：保存每一步的结构体（包含坐标、棋子颜色、是否为AI落子）
struct Move {
    int row;       // 行坐标
    int col;       // 列坐标
    int color;     // 棋子颜色（1=白棋，-1=黑棋）
    bool isAI;     // 是否为AI落子
};

class GameModel
{

public:
    GameModel();

public:
    std::vector<std::vector<int>> gameMapVec; // 存储当前游戏棋盘和棋子的情况,空白为0，白子1，黑子-1
    std::vector<std::vector<int>> scoreMapVec; // 存储各个点位的评分情况，作为AI下棋依据
    bool playerFlag; // 标示下棋方
    GameType gameType; // 游戏模式
    GameStatus gameStatus; // 游戏状态

    void startGame(GameType type); // 开始游戏
    void calculateScore(); // 计算评分
    void actionByPerson(int row, int col); // 人执行下棋
    void actionByAI(int &clickRow, int &clickCol); // 机器执行下棋
    void updateGameMap(int row, int col); // 每次落子后更新游戏棋盘
    bool isWin(int row, int col); // 判断游戏是否胜利
    bool isDeadGame(); // 判断是否和棋
    QVector<Move> moveHistory;  // 历史落子记录
    bool undo();  // 悔棋方法（撤销最后一步）
    int lastMoveRow;  // 记录最新落子的行坐标
    int lastMoveCol;  // 记录最新落子的列坐标
    // 新增获取最新落子坐标的方法
    int getLastMoveRow() const { return lastMoveRow; }
    int getLastMoveCol() const { return lastMoveCol; }
};


#endif // GAMEMODEL_H
