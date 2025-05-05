#include"GameModel.h"

void GameModel::startGame(GameType type)
{
    gameType=type;

    //初始化棋盘
    gameMapVec.clear();
    for(int i=0;i<BOARD_GRAD_SIZE;i++)
    {
        std::vector<int>lineBoard;
        for(int j=0;j<BOARD_GRAD_SIZE;j++)
            lineBoard.push_back(0);
        gameMapVec.push_back(lineBoard);
    }
      //如果是AI模式，需要初始化评分数组
    if(gameType==AI)
    {
        scoreMapVec.clear();
        for(int i=0;i<BOARD_GRAD_SIZE;i++)
        {
            std::vector<int>lineScore;
            for(int j=0;j<BOARD_GRAD_SIZE;j++)
            {
                lineScore.push_back(0);
                scoreMapVec.push_back(lineScore);
            }
        }

        //轮到黑方为true，白方为false
        playerFlag=true;


    }

}

void GameModel::actionByPerson(int row,int col)
{
    updateGameMap(row,col);
}

void GameModel::updateGameMap(int row,int col)
{
    if(playerFlag)
        gameMapVec[row][col]=1;
    else
        gameMapVec[row][col]=-1;
    //换手
    playerFlag=!playerFlag;
}

bool GameModel::isWin(int row,int col)
{
    //水平方向
    for(int i=0;i<5;i++)
    {
        if(col-i>0&&
            col-i+4<BOARD_GRAD_SIZE&&
            gameMapVec[row][col-i]==gameMapVec[row][col-i+1]&&
             gameMapVec[row][col-i]==gameMapVec[row][col-i+2]&&
             gameMapVec[row][col-i]==gameMapVec[row][col-i+3]&&
             gameMapVec[row][col-i]==gameMapVec[row][col-i+4])
            return true;
    }
    //竖直方向
    for(int i=0;i<5;i++)
    {
        if(row-i>0&&
            row-i+4<BOARD_GRAD_SIZE&&
            gameMapVec[row-i][col]==gameMapVec[row-i+1][col]&&
            gameMapVec[row-i][col]==gameMapVec[row-i+2][col]&&
            gameMapVec[row-i][col]==gameMapVec[row-i+3][col]&&
            gameMapVec[row-i][col]==gameMapVec[row-i+4][col])
            return true;
    }
    //斜向左上方向
    for(int i=0;i<5;i++)
    {
        if(col-i>0&&
            row-i>0&&
            col-i+4<BOARD_GRAD_SIZE&&
            row-i+4<BOARD_GRAD_SIZE&&
            gameMapVec[row-i][col-i]==gameMapVec[row-i+1][col-i+1]&&
            gameMapVec[row-i][col-i]==gameMapVec[row-i+2][col-i+2]&&
            gameMapVec[row-i][col-i]==gameMapVec[row-i+3][col-i+3]&&
            gameMapVec[row-i][col-i]==gameMapVec[row-i+4][col-i+4])
            return true;
    }
    //斜向右上方向
    for(int i=0;i<5;i++)
    {
        if(col+i>0&&
            row-i>0&&
            col+i+4<BOARD_GRAD_SIZE&&
            row-i+4<BOARD_GRAD_SIZE&&
            gameMapVec[row-i][col+i]==gameMapVec[row-i+1][col+i+1]&&
            gameMapVec[row-i][col+i]==gameMapVec[row-i+2][col+i+2]&&
            gameMapVec[row-i][col+i]==gameMapVec[row-i+3][col+i+3]&&
            gameMapVec[row-i][col+i]==gameMapVec[row-i+4][col+i+4])
            return true;
    }
    return false;
}










