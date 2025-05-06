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
        if(col-i>0&&
            row+i>0&&
            col-i+4<BOARD_GRAD_SIZE&&
            row+i-4<BOARD_GRAD_SIZE&&
            gameMapVec[row+i][col-i]==gameMapVec[row+i-1][col-i+1]&&
            gameMapVec[row+i][col-i]==gameMapVec[row+i-2][col-i+2]&&
            gameMapVec[row+i][col-i]==gameMapVec[row+i-3][col-i+3]&&
            gameMapVec[row+i][col-i]==gameMapVec[row+i-4][col-i+4])
            return true;
    }
    return false;
}

void GameModel::calulateScore()
{
    //统计玩家或者ai连成的子数
    int personNum=0;//玩家
    int botNum=0;//ai
    int emptyNum=0;//各个方向上的空白位数
    //清空评分数组
    scoreMapVec.clear();
    for(int i=0;i<BOARD_GRAD_SIZE;i++)
    {
        std::vector<int>lineScore;
        for(int j=0;j<BOARD_GRAD_SIZE;j++)
        {
            lineScore.push_back(0);
        }
        scoreMapVec.push_back(lineScore);
    }
    for (int row = 0; row < BOARD_GRAD_SIZE; row++)
        for (int col = 0; col < BOARD_GRAD_SIZE; col++)
        {
            // 空白点就算
            if (row > 0 && col > 0 &&
                gameMapVec[row][col] == 0)
            {
                // 遍历周围八个方向
                for (int y = -1; y <= 1; y++)
                    for (int x = -1; x <= 1; x++)
                    {
                        // 重置
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;

                        // 原坐标不算
                        if (!(y == 0 && x == 0))
                        {
                            // 每个方向延伸4个子

                            // 对玩家黑子评分（正反两个方向）
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y > 0 && row + i * y < BOARD_GRAD_SIZE&&
                                    col + i * x > 0 && col + i * x < BOARD_GRAD_SIZE&&
                                    gameMapVec[row + i * y][col + i * x] == 1) // 玩家的子
                                {
                                    personNum++;
                                }
                                else if (row + i * y > 0 && row + i * y < BOARD_GRAD_SIZE &&
                                         col + i * x > 0 && col + i * x < BOARD_GRAD_SIZE &&
                                         gameMapVec[row + i * y][col + i * x] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 4; i++)
                            {
                                if (row - i * y > 0 && row - i * y < BOARD_GRAD_SIZE &&
                                    col - i * x > 0 && col - i * x < BOARD_GRAD_SIZE &&
                                    gameMapVec[row - i * y][col - i * x] == 1) // 玩家的子
                                {
                                    personNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < BOARD_GRAD_SIZE &&
                                         col - i * x > 0 && col - i * x < BOARD_GRAD_SIZE &&
                                         gameMapVec[row - i * y][col - i * x] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (personNum == 1)                      // 杀二
                                scoreMapVec[row][col] += 10;
                            else if (personNum == 2)                 // 杀三
                            {
                                if (emptyNum == 1)
                                    scoreMapVec[row][col] += 30;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 40;
                            }
                            else if (personNum == 3)                 // 杀四
                            {
                                // 量变空位不一样，优先级不一样
                                if (emptyNum == 1)
                                    scoreMapVec[row][col] += 60;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 110;
                            }
                            else if (personNum == 4)                 // 杀五
                                scoreMapVec[row][col] += 10100;

                            // 进行一次清空
                            emptyNum = 0;

                            // 对AI白子评分
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y > 0 && row + i * y < BOARD_GRAD_SIZE &&
                                    col + i * x > 0 && col + i * x < BOARD_GRAD_SIZE &&
                                    gameMapVec[row + i * y][col + i * x] == 1) // 玩家的子
                                {
                                    botNum++;
                                }
                                else if (row + i * y > 0 && row + i * y < BOARD_GRAD_SIZE &&
                                         col + i * x > 0 && col + i * x < BOARD_GRAD_SIZE &&
                                         gameMapVec[row +i * y][col + i * x] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 4; i++)
                            {
                                if (row - i * y > 0 && row - i * y < BOARD_GRAD_SIZE &&
                                    col - i * x > 0 && col - i * x < BOARD_GRAD_SIZE &&
                                    gameMapVec[row - i * y][col - i * x] == -1) // AI的子
                                {
                                    botNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < BOARD_GRAD_SIZE &&
                                         col - i * x > 0 && col - i * x < BOARD_GRAD_SIZE &&
                                         gameMapVec[row - i * y][col - i * x] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (botNum == 0)                      // 普通下子
                                scoreMapVec[row][col] += 5;
                            else if (botNum == 1)                 // 活二
                                scoreMapVec[row][col] += 10;
                            else if (botNum == 2)
                            {
                                if (emptyNum == 1)                // 死三
                                    scoreMapVec[row][col] += 25;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 50;  // 活三
                            }
                            else if (botNum == 3)
                            {
                                if (emptyNum == 1)                // 死四
                                    scoreMapVec[row][col] += 55;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 100; // 活四
                            }
                            else if (botNum >= 4)
                                scoreMapVec[row][col] += 10000;   // 活五

                        }
                    }

            }
        }
}









