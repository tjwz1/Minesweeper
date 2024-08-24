//
// Created by tjzha on 4/8/2024.
//
#include<iostream>
#include<string>
#include<vector>
using namespace std;
#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H
struct Cells
{
    bool flag;
    bool visited;
    int value;
    Cells(bool flag, bool visited, int value)
    {
        this->flag  = flag;
        this->visited = visited;
        this->value = value;
    }
    void reset()
    {
        this->flag = false;
        this->visited = false;
        this->value = 0;
    }
};
class Board
{
    vector<vector<Cells*>> grid;
    int height;
    int width;
    int minecount = 0;
    int count;
    public:
        Board(int height, int width, int minecount)
        {
            this->height = height;
            this->width = width;
            this->minecount = minecount;
            this->count = minecount;
            for(int i = 0; i<height; i++)
            {
                vector<Cells*> temp ;
                for(int j = 0; j<width; j++)
                {
                    Cells* c = new Cells(false, false, 0);
                    temp.push_back(c);
                }
                grid.push_back(temp);
            }
        }
        vector<vector<Cells*>> getGrid()
        {
            return grid;
        }

        int getCount()
        {
            return count;
        }
        void changeCount(bool flag)
        {
            if(flag == true)
            {
                count--;
            }
            if(flag == false)
            {
                count++;
            }
        }
        void setMines()
        {
            vector<int> position;
            int tempCount = 0;
            while(tempCount != minecount)
            {
                int i = rand() % height;
                int j = rand() % width;
                if(grid[i][j]->value !=9) //board[i][j]!=9
                {
                    //board[i][j]=9;
                    grid[i][j]->value = 9;
                    tempCount++;
                }
            }
            //cout << "Number of mines" << tempCount << endl;
        }

        void setGrid() {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (grid[i][j]->value != 9) {
                        int count = 0;
                        if (i > 0 && grid[i - 1][j]->value == 9) //board[i-1][j] == 9
                        {
                            count++;
                        }
                        if (i > 0 && j > 0 && grid[i - 1][j - 1]->value == 9)  //board[i-1][j-1] == 9
                        {
                            count++;
                        }
                        if (j > 0 && grid[i][j - 1]->value == 9)  //board[i][j - 1] == 9
                        {
                            count++;
                        }
                        if (i < height - 1 && j > 0 && grid[i + 1][j - 1]->value == 9) //board[i + 1][j - 1] == 9
                        {
                            count++;
                        }
                        if (i < height - 1 && grid[i + 1][j]->value == 9) //board[i + 1][j] == 9
                        {
                            count++;
                        }
                        if (i < height - 1 && j < width - 1 && grid[i + 1][j + 1]->value == 9) //board[i + 1][j + 1] == 9
                        {
                            count++;
                        }
                        if (j < width - 1 && grid[i][j + 1]->value == 9) //board[i][j + 1] == 9
                        {
                            count++;
                        }
                        if (i > 0 && j < width - 1 && grid[i - 1][j + 1]->value == 9) //board[i - 1][j + 1] == 9
                        {
                            count++;
                        }
                        grid[i][j]->value = count;
                    }
                }
            }
        }

        void play(int x, int y)
        {
            if(grid[x][y]->value == 9 || grid[x][y]->visited == true)  // board[x][y]==9 && player[x][y]=='-'
            {
                return;
            }
            if(grid[x][y]->value > 0 && grid[x][y]->value < 9)
            {
                grid[x][y]->visited = true;
                return;
            }
            else
            {
                grid[x][y]->visited = true;
                if(grid[x][y]->value == 0)
                {
                    if(x>0 && y>0 && grid[x-1][y-1]->visited==false)  // player[x-1][y-1]=='-'
                    {
                        play(x-1, y-1);
                    }
                    if(y>0 && grid[x][y-1]->visited==false)    //player[x][y-1]=='-'
                    {
                        play(x,y-1);
                    }
                    if(x<height-1 && y>0 && grid[x+1][y-1]->visited==false)  //player[x+1][y-1]=='-'
                    {
                        play(x+1, y-1);
                    }
                    if(x<height-1 && grid[x+1][y]->visited==false)  //player[x+1][y]=='-'
                    {
                        play(x+1,y);
                    }
                    if(x<height-1 && y<width-1 && grid[x+1][y+1]->visited==false) //player[x+1][y+1]=='-'
                    {
                        play(x+1, y+1);
                    }
                    if(y<width-1 && grid[x][y+1]->visited==false)  //player[x][y+1]=='-'
                    {
                        play(x, y+1);
                    }
                    if(x>0 && y<width-1 && grid[x-1][y+1]->visited==false) //player[x-1][y+1]=='-'
                    {
                        play(x-1, y+1);
                    }
                    if(x>0 && grid[x-1][y]->visited==false)  //player[x-1][y]=='-'
                    {
                        play(x-1,y);
                    }
                }
            }
        }

        void printGrid()
        {
            for(int i = 0; i<height; i++)
            {
                for(int j = 0; j<width; j++)
                {
                    if(j == width-1)
                    {
                        cout << grid[i][j]->value << endl;
                    }
                    else
                    {
                        cout << grid[i][j]->value << " | ";
                    }
                }
            }
        }

        void resetBoard()
        {
            for(int i = 0; i<height; i++)
            {
                for(int j = 0; j<width; j++)
                {
                    grid[i][j]->reset();
                }
            }
        }

        void resetCount()
        {
            count = minecount;
        }
        bool checkwin()
        {
            int unvisitedcount = 0;
            int mcount = 0;
            for(int i = 0; i<height; i++)
            {
                for(int j = 0; j<width; j++)
                {
                    if(grid[i][j]->visited == false)
                    {
                        unvisitedcount++;
                    }
                    if(grid[i][j]->value==9)
                    {
                        mcount++;
                    }
                }
            }
            if(unvisitedcount==mcount)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        ~Board()
        {
            for(int i = 0; i<height; i++)
            {
                for(int j = 0; j<width; j++)
                {
                    delete grid[i][j];
                }
            }
        }

};
#endif //MINESWEEPER_BOARD_H
