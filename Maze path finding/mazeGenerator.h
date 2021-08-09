#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>
#include <stdlib.h>

using namespace std;

const int maze_width = 1200, maze_height = 600, unit_length = 20, gap_length = 5;

enum dir { top = 0b1, right = 0b10, down = 0b100, left = 0b1000, visited = 0b10000 };//using binary to indicated which pos is avaliable

class mazeGenerator
{
private:

	int gapVer_size;
	int gapHor_size;
	int* avaDir;//
	sf::RectangleShape* rect;
	sf::RectangleShape* gapVer;
	sf::RectangleShape* gapHor;

	void setMaze(sf::RectangleShape*);

public:

	mazeGenerator();
	void creatMaze(sf::RenderWindow&);
	void cleanVisitedHis();
	int& getAvaDir(const int&);
	sf::RectangleShape& getRect(const int&);
};

#endif