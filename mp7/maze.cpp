#include "maze.h"
#include <stdlib.h>
#include <stack>

//No-parameter constructor. Creates an empty maze.
SquareMaze::SquareMaze() {
    _maze = vector<Square>();
    _disjointSets = new DisjointSets();
}

//Destructor
SquareMaze::~SquareMaze() {
    _maze.clear();
    delete _disjointSets;
    _width = 0;
    _height = 0;
}

//Makes a new SquareMaze of the given height and width.
void SquareMaze::makeMaze(int width, int height) {
    if (_maze.size() != 0) {
        _maze.clear();
        delete _disjointSets;
    } //If this object already represents a maze it will clear all the existing data before doing so
    _maze = vector<Square>(width * height);
    _width = width;
    _height = height;
    _disjointSets->addelements(width * height); // initialize _maze
    for (int i = 0; i < width * height; i++) {
        _maze[i]._down = true;
        _maze[i]._right = true;
        vector<int> dirs;
        if ((i + 1) % width != 0 && 
        (_disjointSets->find(i) != _disjointSets->find(i + 1) || _disjointSets->find(i) == -1))
            dirs.push_back(0);
        if (i < width * (height - 1) && 
        (_disjointSets->find(i) != _disjointSets->find(i + width) || _disjointSets->find(i) == -1)) 
            dirs.push_back(1);
        if (i % width != 0 && 
        (_disjointSets->find(i) != _disjointSets->find(i - 1) || _disjointSets->find(i) == -1))
            dirs.push_back(2);
        if (i >= width && 
        (_disjointSets->find(i) != _disjointSets->find(i - width) || _disjointSets->find(i) == -1))
            dirs.push_back(3);    
        /*dir = 0 represents a rightward step (+1 to the x coordinate)
        dir = 1 represents a downward step (+1 to the y coordinate)
        dir = 2 represents a leftward step (-1 to the x coordinate)
        dir = 3 represents an upward step (-1 to the y coordinate)*/
        if (dirs.size() != 0) {
            int dir = dirs[rand() % dirs.size()];
            switch(dir) {
                case 0: _maze[i]._right = false;
                        _disjointSets->setunion(i, i + 1);
                        break;
                case 1: _maze[i]._down = false;
                        _disjointSets->setunion(i, i + width);
                        break;
                case 2: _maze[i - 1]._right = false;
                        _disjointSets->setunion(i, i - 1);
                        break;
                case 3: _maze[i - width]._down = false;
                        _disjointSets->setunion(i, i - width);
                        break;                         
            }
        }
    }
}

//This uses your representation of the maze to determine whether it is possible to 
//travel in the given direction from the square at coordinates (x,y).
bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (x < 0 || y < 0 || x >= _width || y >= _height) return false; // if square is out of range
    else if (dir == 0 && x + 1 < _width) return !_maze[x + y * _width]._right;
    else if (dir == 1 && y + 1 < _height) return !_maze[x + y * _width]._down;
    else if (dir == 2 && x > 0) return !_maze[x - 1 + y * _width]._right;
    else if (dir == 3 && y > 0) return !_maze[x + (y - 1) * _width]._down;
    else return false;
}

//Either 0 (right) or 1 (down),
//Sets whether or not the specified wall exists.
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (dir == 0) _maze[x + y * _width]._right = exists;
    else _maze[x + y * _width]._down = exists;
}

//Solves this SquareMaze.
/*For each square on the bottom row (maximum y coordinate), there is a distance from the origin (i.e. the top-left cell), 
which is defined as the length (measured as a number of steps) of the only path through the maze from the origin to that square.
Select the square in the bottom row with the largest distance from the origin as the destination of the maze. 
solveMaze() returns the winning path from the origin to the destination as a vector of integers, 
where each integer represents the direction of a step, using the same encoding as in canTravel().
If multiple paths of maximum length exist, use the one with the destination cell that has the smallest x value.*/
vector<int> SquareMaze::solveMaze() {
    return solveMaze(pair<int, int>(0, 0));
}

//Helper function for solveMaze
vector<int> SquareMaze::solveMaze(pair<int, int> start) {
    vector<int> parent;
    parent.assign(_width * _height, -1); // store parent for every square
    vector<int> path;
    path.assign(_width * _height, -1); // store path for every square
    stack<int> DFS; // Depth first
    DFS.push(start.first  + _width * start.second);
    while (DFS.size() != 0) {
        int i = DFS.top();
        //dir = 0 represents a rightward step (+1 to the x coordinate)
        if ((i + 1) % _width != 0 && !_maze[i]._right && parent[i + 1] < 0) {
            DFS.push(i + 1);
            parent[i + 1] = i;
            path[i + 1] = 0;
        }
        //dir = 1 represents a downward step (+1 to the y coordinate)
        else if (i < _width * (_height - 1) && !_maze[i]._down && parent[i + _width] < 0) {
            DFS.push(i + _width);
            parent[i + _width] = i;
            path[i + _width] = 1;
        }
        //dir = 2 represents a leftward step (-1 to the x coordinate)
        else if (i % _width != 0 && !_maze[i - 1]._right && parent[i - 1] < 0) {
            DFS.push(i - 1);
            parent[i - 1] = i;
            path[i - 1] = 2;
        }
        //dir = 3 represents an upward step (-1 to the y coordinate)
        else if (i >= _width && !_maze[i - _width]._down && parent[i - _width] < 0) {
            DFS.push(i - _width);
            parent[i - _width] = i;
            path[i - _width] = 3;
        }
        else {
            DFS.pop();
        }
    }
    int maxd = 0;
    int solidx = _width * (_height - 1);
    for (int i = 0; i < _width; i++) {
        int d = 0;
        int j = i + _width * (_height - 1);
        while (j > 0) {
            j = parent[j];
            d++;
        }
        if (d > maxd) {//If multiple paths of maximum length exist, 
        //use the one with the destination cell that has the smallest x value
            maxd = d;
            solidx = i + _width * (_height - 1);
        }   
    }
    vector<int> solution;
    while (solidx > 0) {
        solution.push_back(path[solidx]);
        solidx = parent[solidx];
    }
    vector<int> reverse;
    for (int i = solution.size() - 1; i >= 0; i--) {
        reverse.push_back(solution[i]);
    }
    return reverse;
}

//Draws the maze without the solution.
PNG* SquareMaze::drawMaze() const {
    //First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1).
    PNG* out = new PNG(_width * 10 + 1, _height * 10 + 1);
    //Blacken the entire topmost row and leftmost column of pixels, 
    //except the entrance (1,0) through (9,0). 
    for (int i = 10; i < _width * 10 + 1; i++) out->getPixel(i, 0)->l = 0;
    for (int j = 0; j < _height * 10 + 1; j++) out->getPixel(0, j)->l = 0;
    for (int x = 0; x < _width; x++) { 
        for (int y = 0; y < _height; y++) {
        //For each square in the maze, call its maze coordinates (x,y).
            if (_maze[x + y * _width]._right) {
                for (int k = 0; k < 11; k++) out->getPixel((x + 1) * 10, y * 10 + k)->l = 0;
            }//If the right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10. 
            if (_maze[x + y * _width]._down) {
                for (int k = 0; k < 11; k++) out->getPixel(x * 10 + k, (y + 1) * 10)->l = 0;
            }//If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
        }
    }
    return out;
}

//This function calls drawMaze, then solveMaze{} 
//it modifies the PNG from drawMaze to show the solution vector and the exit.
PNG* SquareMaze::drawMazeWithSolution() {
    PNG* out = drawMaze();
    vector<int> solution = solveMaze();
    pair<int, int> curr(5, 5); //Start at pixel (5,5). 
    for (int dir : solution) {
        if (dir == 0) {//dir = 0 represents a rightward step (+1 to the x coordinate)
            for (int i = 0; i < 10; i++) {
                redden(out->getPixel(curr.first, curr.second));
                curr.first++;
            }
        }
        else if (dir == 1) {//dir = 1 represents a downward step (+1 to the y coordinate)
            for (int i = 0; i < 10; i++) {
                redden(out->getPixel(curr.first, curr.second));
                curr.second++;
            }
        }
        else if (dir == 2) {//dir = 2 represents a leftward step (-1 to the x coordinate)
            for (int i = 0; i < 10; i++) {
                redden(out->getPixel(curr.first, curr.second));
                curr.first--;
            }
        }
        else if (dir == 3) {//dir = 3 represents an upward step (-1 to the y coordinate)
            for (int i = 0; i < 10; i++) {
                redden(out->getPixel(curr.first, curr.second));
                curr.second--;
            }            
        }
    }
    redden(out->getPixel(curr.first, curr.second));
    //Make the exit by undoing the bottom wall of the destination square: 
    //call the destination maze coordinates (x,y), 
    //and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
    for (int k = 1; k < 10; k++) out->getPixel(curr.first - 5 + k, _height * 10)->l = 1;
    return out;
}

// draw pixel red
void SquareMaze::redden(HSLAPixel* pixel) {
    pixel->h = 0;
    pixel->s = 1;
    pixel->l = 0.5;
    pixel->a = 1;
}//(Red is 0,1,0.5,1 in HSLA). 