#include "mazeGenerator.h"

mazeGenerator::mazeGenerator() {//constructor

    avaDir = new int[(maze_width / unit_length) * (maze_height / unit_length)]{};//create one corresponding element for each grid by using binary num to indicate avaliable direction

    rect = new  sf::RectangleShape[(maze_width / unit_length) * (maze_height / unit_length)];//create all grids for the maze
    setMaze(&rect[0]);//initialize the maze

    gapVer_size = 0;
    gapHor_size = 0;

    //create hor & ver gap object
    gapVer = new  sf::RectangleShape[(maze_width / unit_length) * ((maze_height / unit_length) - 1)];
    gapHor = new  sf::RectangleShape[(maze_width / unit_length) * ((maze_height / unit_length) - 1)];

    for (int i = 0; i < (maze_width / unit_length) * ((maze_height / unit_length) - 1); i++) {//set size for all gap objects
        gapVer[i].setSize(sf::Vector2f(gap_length, unit_length - gap_length));
        gapHor[i].setSize(sf::Vector2f(unit_length - gap_length, gap_length));
    }
}

void mazeGenerator::setMaze(sf::RectangleShape* rectPtr) {//generate the empty maze
    for (int i = 0; i < maze_height / unit_length; i++)//drawing....
        for (int k = 0; k < maze_width / unit_length; k++) {
            rectPtr[k + (i * (maze_width / unit_length))].setSize(sf::Vector2f(unit_length - gap_length, unit_length - gap_length));
            rectPtr[k + (i * (maze_width / unit_length))].setPosition(sf::Vector2f(unit_length * k, unit_length * i));
            rectPtr[k + (i * (maze_width / unit_length))].setFillColor(sf::Color::Blue);
        }
}

int& mazeGenerator::getAvaDir(const int& pos) {//get the avaliable direction for calling grid
    return this->avaDir[pos];
}

sf::RectangleShape& mazeGenerator::getRect(const int& pos) {//get the grid
    return this->rect[pos];
}

void mazeGenerator::cleanVisitedHis() {//reset the visited dir for each grid
    for (int i = 0; i < (maze_width / unit_length) * (maze_height / unit_length); i++)
        avaDir[i] ^= dir::visited;
}

void mazeGenerator::creatMaze(sf::RenderWindow& window) {

    srand(time(nullptr));
    pair<int, int> cur;//current pos
    stack<pair<int, int>> path;//contain the path by using stack

    path.push(std::make_pair(0, 0));//start from (0,0)
    int visit = 0;//num of visited grid

    while (visit < (maze_width / unit_length) * (maze_height / unit_length)) {//need to visited all grid
        if (path.empty())//if path is empty
            break;

        cur = path.top();//get the cur pos
        vector<int> avail_path;//store the avaliable direction

        if (cur.second > 0 && !(avaDir[cur.first + ((cur.second - 1) * (maze_width / unit_length))] & dir::visited))//top path is available
            avail_path.push_back(0);
        if (cur.first < (maze_width / unit_length) - 1 && !(avaDir[(cur.first + 1) + (cur.second * (maze_width / unit_length))] & dir::visited))//right path is available
            avail_path.push_back(1);
        if (cur.second < (maze_height / unit_length) - 1 && !(avaDir[cur.first + ((cur.second + 1) * (maze_width / unit_length))] & dir::visited))//down path is available
            avail_path.push_back(2);
        if (cur.first > 0 && !(avaDir[(cur.first - 1) + (cur.second * (maze_width / unit_length))] & dir::visited))//left path is available
            avail_path.push_back(3);

        if (avail_path.empty()) {//if current pos has no avaliable direction to visited
            avaDir[cur.first + (cur.second * (maze_width / unit_length))] |= dir::visited;//set current pos as visited 
            path.pop();//set the latest visited pos as cur
        }
        else {
            int randDir = avail_path[rand() % avail_path.size()];//get the random direction


            if (randDir == 0) {//going up
                gapHor[gapHor_size].setPosition(sf::Vector2f(cur.first * unit_length, (cur.second * unit_length) - gap_length));
                gapHor_size++;//increase num of horizontal gap
                avaDir[cur.first + (cur.second * (maze_width / unit_length))] |= dir::visited;//set current pos as visited 

                avaDir[cur.first + (cur.second * (maze_width / unit_length))] |= dir::top;//set top direction as visited for cur pos
                avaDir[cur.first + ((cur.second - 1) * (maze_width / unit_length))] |= dir::down;//set down direction as visited for next pos

                path.push(make_pair(cur.first, cur.second - 1));//push next to path
                visit++;
            }
            if (randDir == 1) {//going right
                gapVer[gapVer_size].setPosition(sf::Vector2f((cur.first * unit_length) + (unit_length - gap_length), cur.second * unit_length));
                gapVer_size++;//increase num of vertical gap
                avaDir[cur.first + (cur.second * (maze_width / unit_length))] |= dir::visited;//set current pos as visited 

                avaDir[cur.first + (cur.second * (maze_width / unit_length))] |= dir::right;//set right direction as visited for cur pos
                avaDir[(cur.first + 1) + (cur.second * (maze_width / unit_length))] |= dir::left;//set left direction as visited for next pos

                path.push(make_pair(cur.first + 1, cur.second));//push next to path
                visit++;
            }
            if (randDir == 2) {//going down
                gapHor[gapHor_size].setPosition(sf::Vector2f(cur.first * unit_length, (cur.second * unit_length) + (unit_length - gap_length)));
                gapHor_size++;//increase num of horizontal gap
                avaDir[cur.first + (cur.second * (maze_width / unit_length))] |= dir::visited;//set current pos as visited 

                avaDir[cur.first + (cur.second * (maze_width / unit_length))] |= dir::down;//set down direction as visited for cur pos
                avaDir[cur.first + ((cur.second + 1) * (maze_width / unit_length))] |= dir::top;//set top direction as visited for next pos

                path.push(make_pair(cur.first, cur.second + 1));//push next to path
                visit++;
            }
            if (randDir == 3) {//going left
                gapVer[gapVer_size].setPosition(sf::Vector2f((cur.first * unit_length) - gap_length, cur.second * unit_length));
                gapVer_size++;//increase num of vertical gap
                avaDir[cur.first + (cur.second * (maze_width / unit_length))] |= dir::visited;//set current pos as visited 

                avaDir[cur.first + (cur.second * (maze_width / unit_length))] |= dir::left;//set left direction as visited for cur pos
                avaDir[(cur.first - 1) + (cur.second * (maze_width / unit_length))] |= dir::right;//set right direction as visited for next pos

                path.push(make_pair(cur.first - 1, cur.second));//push next to path
                visit++;
            }
        }

        window.clear();


        for (int i = 0; i < maze_height / unit_length; i++)
            for (int k = 0; k < maze_width / unit_length; k++)
                window.draw(rect[k + (i * (maze_width / unit_length))]);//update grids

        for (int i = 0; i < gapVer_size; i++)
            window.draw(gapVer[i]);//update ver gap

        for (int i = 0; i < gapHor_size; i++)
            window.draw(gapHor[i]);//update hor gap

        window.display();

        rect[cur.first + (cur.second * (maze_width / unit_length))].setFillColor(sf::Color::White);//change the visited pos to white color
    }

    cleanVisitedHis();//reset the visited history
}