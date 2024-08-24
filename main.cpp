#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<vector>
#include "board.h"
#include<cctype>
#include<fstream>
#include<sstream>
#include<cstdio>
using namespace std;
void setText(sf::Text &text, float x, float y)
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void Gamescreen(Board &test, sf::RenderWindow &window, int r, int c, int &time, string &name);

void Leaderboard(int r, int c, int time, string &name);

void UpdateLeaderBoard(int time, string &name);

void Leaderboard(int r, int c, bool &leaderboardhit);

void welcomescreen(int width, int height, Board &test, sf::RenderWindow &window, int r, int c, int &time, string &n)
{
    sf::Font font;
    if(!font.loadFromFile("files/font.ttf"))
    {
        cout << "error" << endl;
    }
    sf::Text text, text1, input;

    input.setFont(font);
    text1.setFont(font);
    text.setFont(font);

    text.setString("WELCOME TO MINESWEEPER !");
    text1.setString("Enter your name:");
    input.setString(n + '|');

    text.setCharacterSize(24);
    text1.setCharacterSize(20);
    input.setCharacterSize(18);

    input.setFillColor(sf::Color::Yellow);
    text.setFillColor(sf::Color::White);
    text1.setFillColor(sf::Color::White);

    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text1.setStyle(sf::Text::Bold);
    input.setStyle(sf::Text::Bold);

    setText(text, width/2, height/2 - 150);
    setText(text1, width/2, height/2 - 75);
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.key.code == sf::Keyboard::Enter && n.size()>0)
            {
                window.close();
                sf::RenderWindow w(sf::VideoMode(width, height), "Minesweeper");
                Gamescreen(test, w, r, c, time, n);
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode != 8)
                {
                    if (n.size() < 10) {
                        char check = char(event.text.unicode);
                        if (isalpha(check))
                        {
                            if(n.empty())
                            {
                                char temp = (char)toupper(check);
                                check = temp;
                            }
                            else
                            {
                                char temp = (char)tolower(check);
                                check = temp;
                            }
                            n += check;
                        }
                    }
                }
                else
                {
                    if(n.size()>0)
                    {
                        n.erase(n.size() - 1, 1);
                    }
                }
            }
        }
        setText(input, width/2, height/2 - 45);
        input.setString(n + '|');
        window.clear(sf::Color::Blue);
        window.draw(text);
        window.draw(text1);
        window.draw(input);
        window.display();
    }
}

void reset(Board &test, vector<vector<Cells*>> &gamegrid)
{
    test.resetBoard();
    test.resetCount();
    test.setMines();
    test.setGrid();
    gamegrid = test.getGrid();
}

void Gamescreen(Board &test, sf::RenderWindow &window, int r, int c, int &t, string &name)
{
    vector<vector<Cells*>> gameGrid = test.getGrid();
    //loading uncovered cell
    sf::Texture cell;
    cell.loadFromFile("files/images/tile_revealed.png");

    //loading covered cell
    sf::Texture covered;
    covered.loadFromFile("files/images/tile_hidden.png");

    //Loading numbers and mines
    sf::Texture num1;
    num1.loadFromFile("files/images/number_1.png");
    sf::Texture num2;
    num2.loadFromFile("files/images/number_2.png");
    sf::Texture num3;
    num3.loadFromFile("files/images/number_3.png");
    sf::Texture num4;
    num4.loadFromFile("files/images/number_4.png");
    sf::Texture num5;
    num5.loadFromFile("files/images/number_5.png");
    sf::Texture num6;
    num6.loadFromFile("files/images/number_6.png");
    sf::Texture num7;
    num7.loadFromFile("files/images/number_7.png");
    sf::Texture num8;
    num8.loadFromFile("files/images/number_8.png");
    sf::Texture bomb;
    bomb.loadFromFile("files/images/mine.png");

    //loading flag
    sf::Texture flag;
    flag.loadFromFile("files/images/flag.png");

    //loading buttons
    sf::Texture happyface;
    happyface.loadFromFile("files/images/face_happy.png");
    sf::Texture lose;
    lose.loadFromFile("files/images/face_lose.png");
    sf::Texture cool;
    cool.loadFromFile("files/images/face_win.png");
    sf::Texture debug;
    debug.loadFromFile("files/images/debug.png");
    sf::Texture play, pause;
    play.loadFromFile("files/images/play.png");
    pause.loadFromFile("files/images/pause.png");
    sf::Texture leaderboad;
    leaderboad.loadFromFile("files/images/leaderboard.png");
    sf::Texture counter;
    counter.loadFromFile("files/images/digits.png");

    int tilesize = 32;
    int x = (window.getSize().y-100)/tilesize;
    int y = window.getSize().x/tilesize;

    //loading sprites for uncovered, covered, numbers, and flags
    sf::Sprite grid[x][y];
    sf::Sprite c_grid[x][y];
    sf::Sprite num_grid[x][y];
    sf::Sprite f[x][y];

    //loading sprites for buttons
    sf::Sprite losebutton;
    losebutton.setTexture(lose);
    sf::Sprite winbutton;
    winbutton.setTexture(cool);
    sf::Sprite hfbutton;
    hfbutton.setTexture(happyface);
    sf::Sprite dbutton;
    dbutton.setTexture(debug);
    sf::Sprite plbutton, pabutton;
    plbutton.setTexture(play);
    pabutton.setTexture(pause);
    sf::Sprite lbbutton;
    lbbutton.setTexture(leaderboad);

    //loading digits
    sf::Sprite count;
    count.setTexture(counter);
    sf::Sprite cl;
    cl.setTexture(counter);

    //setting position of buttons
    dbutton.setPosition((c * 32) - 304, 32 * (r + 0.5));
    hfbutton.setPosition(((c/2) * 32) - 32, 32 * (r + 0.5));
    losebutton.setPosition(((c/2) * 32) - 32, 32 * (r + 0.5));
    winbutton.setPosition(((c/2) * 32) - 32, 32 * (r + 0.5));
    plbutton.setPosition((c * 32) - 240, 32 * (r + 0.5));
    pabutton.setPosition((c * 32) - 240, 32 * (r + 0.5));
    lbbutton.setPosition((c * 32) - 176, 32 * (r + 0.5));

    //setting position of digits
    count.setPosition(33, 32 * (r + 0.5) + 16);

    //setting position of tiles
    for(int i = 0; i<x; i++)
    {
        for(int j = 0; j<y; j++)
        {
            grid[i][j].setTexture(cell);
            grid[i][j].setPosition(j*tilesize, i*tilesize);

            c_grid[i][j].setTexture(covered);
            c_grid[i][j].setPosition(j*tilesize, i*tilesize);

            f[i][j].setTexture(flag);
            f[i][j].setPosition(j*tilesize, i*tilesize);

            num_grid[i][j].setPosition(j*tilesize, i*tilesize);
            if(gameGrid[i][j]->value == 0)
            {
                num_grid[i][j].setTexture(cell);
            }
            else if(gameGrid[i][j]->value == 1)
            {
                num_grid[i][j].setTexture(num1);
            }
            else if(gameGrid[i][j]->value == 2)
            {
                num_grid[i][j].setTexture(num2);

            }
            else if(gameGrid[i][j]->value == 3)
            {
                num_grid[i][j].setTexture(num3);

            }
            else if(gameGrid[i][j]->value == 4)
            {
                num_grid[i][j].setTexture(num4);
            }
            else if(gameGrid[i][j]->value == 5)
            {
                num_grid[i][j].setTexture(num5);

            }
            else if(gameGrid[i][j]->value == 6)
            {
                num_grid[i][j].setTexture(num6);
            }
            else if(gameGrid[i][j]->value == 7)
            {
                num_grid[i][j].setTexture(num7);
            }
            else if(gameGrid[i][j]->value == 8)
            {
                num_grid[i][j].setTexture(num8);
            }
            else
            {
                num_grid[i][j].setTexture(bomb);
            }
        }
    }
    //booleans to track state of game screen
    bool debugpressed = false;
    bool isplay = true;
    bool bombhit = false;
    bool win = false;
    bool leaderboardhit = false;
    bool updated = false;
    sf::Clock clock;
    int timePlayed = 0;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                //reset button
                if(hfbutton.getGlobalBounds().contains((sf::Vector2f)position))
                {
                    if(leaderboardhit == false)
                    {
                        clock.restart();
                        cout << "Reset Button Clicked" << endl;
                        bombhit = false;
                        isplay = true;
                        debugpressed = false;
                        timePlayed = 0;
                        reset(test, gameGrid);
                        //reset sprites for grid values
                        for(int i = 0; i<r; i++)
                        {
                            for(int j = 0; j<c; j++)
                            {
                                num_grid[i][j].setPosition(j*tilesize, i*tilesize);
                                if(gameGrid[i][j]->value == 0)
                                {
                                    num_grid[i][j].setTexture(cell);
                                }
                                else if(gameGrid[i][j]->value == 1)
                                {
                                    num_grid[i][j].setTexture(num1);
                                }
                                else if(gameGrid[i][j]->value == 2)
                                {
                                    num_grid[i][j].setTexture(num2);

                                }
                                else if(gameGrid[i][j]->value == 3)
                                {
                                    num_grid[i][j].setTexture(num3);

                                }
                                else if(gameGrid[i][j]->value == 4)
                                {
                                    num_grid[i][j].setTexture(num4);
                                }
                                else if(gameGrid[i][j]->value == 5)
                                {
                                    num_grid[i][j].setTexture(num5);

                                }
                                else if(gameGrid[i][j]->value == 6)
                                {
                                    num_grid[i][j].setTexture(num6);
                                }
                                else if(gameGrid[i][j]->value == 7)
                                {
                                    num_grid[i][j].setTexture(num7);
                                }
                                else if(gameGrid[i][j]->value == 8)
                                {
                                    num_grid[i][j].setTexture(num8);
                                }
                                else
                                {
                                    num_grid[i][j].setTexture(bomb);
                                }
                            }
                        }
                        clock.restart();
                    }
                    continue;
                }

                //Debug button
                if(dbutton.getGlobalBounds().contains((sf::Vector2f)position))
                {
                    cout << "Debug button clicked" << endl;
                    if(bombhit==false && leaderboardhit == false)
                    {
                        debugpressed = !debugpressed;
                    }
                    continue;
                }

                //Pause/Play Button
                if(plbutton.getGlobalBounds().contains((sf::Vector2f)position))
                {
                    cout << "Pause/Play button clicked" << endl;
                    if(bombhit == false && win == false && leaderboardhit == false)
                    {
                        isplay = !isplay;
                        if(isplay == false)
                        {
                            timePlayed += clock.getElapsedTime().asSeconds();
                            clock.restart();
                        }
                        if(isplay == true)
                        {
                            clock.restart();
                        }
                        continue;
                    }
                }

                //Leaderboard button
                if(lbbutton.getGlobalBounds().contains((sf::Vector2f)position))
                {
                    cout << "Leader button clicked" << endl;
                    leaderboardhit = true;
                    continue;
                }
                    //clicking on game board
                    if(bombhit == false && win == false && leaderboardhit == false)
                    {
                        int xpos = (int)position.x/32;
                        cout << "xpos: " << xpos << endl;
                        int ypos = (int)position.y/32;
                        cout << "ypos: " << ypos << endl;
                        if(ypos > r-1 || xpos>c-1)
                        {
                            cout << "Nothing here" << endl;
                            continue;
                        }
                        if(gameGrid[ypos][xpos]->value==9 && gameGrid[ypos][xpos]->flag==false && isplay == true)
                        {
                            bombhit = true;
                            isplay = false;
                            clock.restart();
                        }
                        else
                        {
                            if(gameGrid[ypos][xpos]->visited == false && gameGrid[ypos][xpos]->flag ==false && isplay == true)
                            {
                                test.play(ypos, xpos);
                                if(test.checkwin()==true)
                                {
                                    win = true;
                                    isplay = false;
                                    updated = true;
                                }
                            }
                        }
                    }
            }

            //placing flag
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                int xpos = (int)position.x/32;
                int ypos = (int)position.y/32;
                if(gameGrid[ypos][xpos]->visited == false)
                {
                    gameGrid[ypos][xpos]->flag = !gameGrid[ypos][xpos]->flag;
                    test.changeCount(gameGrid[ypos][xpos]->flag);
                }
            }
        }
        window.clear(sf::Color::White);
        //Leaderboard button functionality
        if(leaderboardhit == true)
        {
            for(int i = 0; i<x; i++)
            {
                for(int j = 0; j<y; j++)
                {
                    window.draw(grid[i][j]);
                }
            }
            timePlayed += clock.getElapsedTime().asSeconds();
            clock.restart();
            Leaderboard(r, c, leaderboardhit);
            clock.restart();
        }
        //Game is on play
        if(isplay == true)
        {
            for(int i = 0; i<x; i++)
            {
                for(int j = 0; j<y; j++)
                {
                    window.draw(grid[i][j]);
                    window.draw(num_grid[i][j]);
                    if(gameGrid[i][j]->visited == false)
                    {
                        window.draw(c_grid[i][j]);
                    }
                    if(gameGrid[i][j]->flag == true)
                    {
                        window.draw(f[i][j]);
                    }
                }
            }

            //if debugged is pressed
            if(debugpressed==true)
            {
                for(int i = 0; i<x; i++)
                {
                    for(int j = 0; j<y; j++)
                    {
                        if(gameGrid[i][j]->value==9)
                        {
                            window.draw(num_grid[i][j]);
                        }
                    }
                }
            }
            window.draw(pabutton);
            window.draw(hfbutton);
        }

        //Game is on pause
        else
        {
            //lose condition
            if(bombhit == true)
            {
                cout << "Bomb hit" << endl;
                for(int i = 0; i<x; i++)
                {
                    for(int j = 0; j<y; j++)
                    {
                        window.draw(grid[i][j]);
                        window.draw(c_grid[i][j]);
                        if(gameGrid[i][j]->value==9)
                        {
                            window.draw(num_grid[i][j]);
                        }
                    }
                    window.draw(losebutton);
                    window.draw(pabutton);
                }
            }
            //display covered grid
            else
            {
                for(int i = 0; i<x; i++)
                {
                    for(int j = 0; j<y; j++)
                    {
                        window.draw(grid[i][j]);
                    }
                }
                window.draw(plbutton);
                timePlayed += clock.getElapsedTime().asSeconds();
                clock.restart();
                window.draw(hfbutton);
            }
            //Win condition
            if(win == true)
            {
                for(int i = 0; i<x; i++)
                {
                    for(int j = 0; j<y; j++)
                    {
                        window.draw(grid[i][j]);
                        window.draw(num_grid[i][j]);
                        if(gameGrid[i][j]->value==9)
                        {
                            window.draw(f[i][j]);
                        }
                    }
                }
                window.draw(winbutton);
                window.draw(pabutton);
                t = timePlayed;
                if(updated == true)
                {
                    UpdateLeaderBoard(t, name);
                    updated = false;
                }
            }

        }
        //drawing counter
        int num = test.getCount();
        int pos = 0;
        if(num < 0)
        {
            count.setTextureRect(sf::IntRect(210, 0, 21, 32));
            count.setPosition(12, 32 * (r + 0.5) + 16);
            pos++;
            window.draw(count);
        }
        string numstr = to_string(num);
        int x = 33;
        for(int i = pos; i<numstr.size(); i++)
        {
            int ch = numstr[i] - '0';
            count.setTextureRect(sf::IntRect(ch * 21, 0, 21, 32));
            count.setPosition(x, 32 * (r + 0.5) + 16);
            window.draw(count);
            x += 21;
        }

        //drawing buttons
        window.draw(dbutton);
        window.draw(lbbutton);
        window.draw(count);

        //setting and drawing in timer
        sf::Time elapsed = clock.getElapsedTime();
        int time;
        string timestr = "";
        if(bombhit == true)
        {
            time = 0;
            timestr += to_string(time) + to_string(time);
        }
        else
        {
            int t = elapsed.asSeconds();
            time = timePlayed + t;
            int min = time/60;
            int sec = time % 60;
            if(min < 10)
            {
                timestr += "0";
            }
            timestr += to_string(min);
            if(sec < 10)
            {
                timestr += "0";
            }
            timestr += to_string(sec);
        }
        int start = (c * 32) - 97;
        for(int i = 0; i<timestr.size(); i++)
        {
            int ch = timestr[i] - '0';
            cl.setTextureRect(sf::IntRect(ch * 21, 0, 21, 32));
            cl.setPosition(start, 32 * (r + 0.5) + 16);
            window.draw(cl);
            start +=21;
        }
        window.display();
    }
}

void UpdateLeaderBoard(int time, string &name)
{
    int minutes = time/60;
    int seconds = time % 60;
    string timestr;
    if(minutes < 10)
    {
        timestr += "0";
    }
    timestr += to_string(minutes);
    timestr += ":";
    if(seconds < 10)
    {
        timestr += "0";
    }
    timestr += to_string(seconds);
    name += "*";
    //reading in leaderboard file
    ifstream lb("files/leaderboard.txt");
    vector<string> names;
    vector<string> times;
    vector<string> ranks;
    string row;
    while(getline(lb, row))
    {
        istringstream iss(row);
        string ranking;
        getline(iss, ranking, ' ');
        string t;
        getline(iss, t,',');
        string n;
        getline(iss, n);
        ranks.push_back(ranking);
        times.push_back(t);
        names.push_back(n);
    }
    lb.close();
    int pos = 5;
    for(int i = 0; i<times.size(); i++)
    {
        int min, sec;
        auto colon = times[i].find(':');
        string m = times[i].substr(0, colon);
        min = stoi(m);
        string s = times[i].substr(colon + 1, 2);
        sec = stoi(s);
        if(minutes < min || (minutes == min && seconds <=sec))
        {
            pos = i;
            break;
        }
    }
    if(pos != 5)
    {
        times.insert(times.begin() + pos, timestr);
        names.insert(names.begin() + pos, name);
    }
    ofstream update("files/leaderboard.txt");
    for(int i = 0; i<5; i++)
    {
        //update leaderboard file
        update << ranks[i];
        update << ' ';
        update << times[i] << ',';
        update << names[i] << endl;
    }
    update.close();
}

void setLeaderBoardString(string & standings)
{
    ifstream lb("files/leaderboard.txt");
    vector<string> names;
    vector<string> times;
    vector<string> ranks;
    string row;
    while(getline(lb, row))
    {
        istringstream iss(row);
        string ranking;
        getline(iss, ranking, ' ');
        string t;
        getline(iss, t,',');
        string n;
        getline(iss, n);
        ranks.push_back(ranking);
        times.push_back(t);
        names.push_back(n);
    }
    lb.close();
    for(int i = 0; i<names.size(); i++)
    {
        standings += ranks[i] + "\t" + times[i] + "\t" + names[i];
        standings += "\n\n";
    }
}

void Leaderboard(int r, int c, bool &leaderboardhit)
{
    string st = "";
    setLeaderBoardString(st);
    int lheight = (r * 16) + 50;
    int lwidth = (c * 16);
    sf::RenderWindow window(sf::VideoMode(lwidth, lheight), "Minesweeper");
    sf::Font font;
    if(!font.loadFromFile("files/font.ttf"))
    {
        cout << "error" << endl;
    }
    sf::Text title, standings;
    title.setFont(font);
    standings.setFont(font);

    title.setString("LEADERBOARD");
    standings.setString(st);

    title.setCharacterSize(20);
    standings.setCharacterSize(18);

    title.setFillColor(sf::Color::White);
    standings.setFillColor(sf::Color::White);

    standings.setStyle(sf::Text::Bold);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);

    setText(standings, lwidth/2, (lheight/2) + 20);
    setText(title, lwidth/2, (lheight/2) - 120);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
                leaderboardhit = false;
            }
        }
        window.clear(sf::Color::Blue);
        window.draw(title);
        window.draw(standings);
        window.display();
    }
}

int main()
{
    //reading in config.fig
    ifstream file("files/config.cfg");
    if(!file.is_open())
    {
        cout << "File not opened" << endl;
    }
    int c, r, m;
    string line;
    getline(file, line);
    c = stoi(line);
    getline(file, line);
    r = stoi(line);
    getline(file, line);
    m = stoi(line);
    file.close();
    int height = (r * 32) + 100;
    int width = (c * 32);

    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper");
    //Loading game board
    Board test(r,c,m);
    test.setMines();
    test.setGrid();
    int time = 0;
    string name = "";
    welcomescreen(width, height, test, window, r, c, time, name);

    return 0;
}
