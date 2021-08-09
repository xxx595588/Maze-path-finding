#include <SFML/Graphics.hpp>
#include "mazeGenerator.h"

using namespace std;

void DFS(sf::RenderWindow& window, mazeGenerator& maze) {

    int x = rand() % (maze_width / unit_length);
    int y = rand() % (maze_height / unit_length);

    stack<pair<int, int>> path, bestPath;
    pair<int, int> cur = make_pair(0, 0), target = make_pair(x, y);

    path.push(cur);

    int visit = 1, step = INT_MAX, curStep = 1;


    maze.getRect(target.first + (target.second * (maze_width / unit_length))).setFillColor(sf::Color::Blue);
    window.draw(maze.getRect(target.first + (target.second * (maze_width / unit_length))));
    window.display();


    while (visit < (maze_width / unit_length) * ((maze_height / unit_length))) {

        cur = path.top();

        window.setFramerateLimit(20);

        maze.getAvaDir(cur.first + (cur.second * (maze_width / unit_length))) |= dir::visited;


        if (cur.first == target.first && cur.second == target.second) {
            if (curStep < step) {
                step = curStep;
                bestPath = path;
            }
        }


        if (maze.getAvaDir(cur.first + (cur.second * (maze_width / unit_length))) & dir::top && !(maze.getAvaDir(cur.first + ((cur.second - 1) * (maze_width / unit_length))) & dir::visited)) {//if top is available
            path.push(make_pair(cur.first, cur.second - 1));
            curStep++;
            visit++;
        }
        else if (maze.getAvaDir(cur.first + (cur.second * (maze_width / unit_length))) & dir::right && !(maze.getAvaDir((cur.first + 1) + (cur.second * (maze_width / unit_length))) & dir::visited)) {//if right is available
            path.push(make_pair(cur.first + 1, cur.second));
            curStep++;
            visit++;
        }
        else if (maze.getAvaDir(cur.first + (cur.second * (maze_width / unit_length))) & dir::down && !(maze.getAvaDir(cur.first + ((cur.second + 1) * (maze_width / unit_length))) & dir::visited)) {//if down is available
            path.push(make_pair(cur.first, cur.second + 1));
            curStep++;
            visit++;
        }
        else if (maze.getAvaDir(cur.first + (cur.second * (maze_width / unit_length))) & dir::left && !(maze.getAvaDir((cur.first - 1) + (cur.second * (maze_width / unit_length))) & dir::visited)) {//if left is available
            path.push(make_pair(cur.first - 1, cur.second));
            curStep++;
            visit++;
        }
        else {
            curStep--;
            path.pop();
        }
    }

    vector<pair<int, int>>sol;
    int s = bestPath.size();

    sf::CircleShape* dot = new sf::CircleShape[s];

    for (; bestPath.size() > 0;) {
        sol.push_back(bestPath.top());
        bestPath.pop();
    }

    window.setFramerateLimit(10);

    for (int i = sol.size() - 1, k = 0; i >= 0; i--, k++) {

        dot[k].setPosition(maze.getRect(sol[i].first + (sol[i].second * (maze_width / unit_length))).getPosition());
        dot[k].setRadius(5);
        dot[k].setOrigin(-(unit_length / 5), -(unit_length / 5));
        dot[k].setFillColor(sf::Color::Red);
        dot[k].setOutlineColor(sf::Color::Blue);


        for (int k = 0; k < s; k++)
            window.draw(dot[k]);


        window.draw(maze.getRect(target.first + (target.second * (maze_width / unit_length))));
        window.display();
    }


}

int main()
{
    sf::RenderWindow window(sf::VideoMode(maze_width, maze_height), "maze");
    //window.setFramerateLimit(50);

    mazeGenerator maze = mazeGenerator();

    maze.creatMaze(window);

    DFS(window, maze);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

    }

    return 0;
}