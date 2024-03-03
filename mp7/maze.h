#pragma once

#include "cs225/PNG.h"
#include "dsets.h"

#include <vector>

using namespace cs225;
using namespace std;

class SquareMaze {
public:
    //No-parameter constructor. Creates an empty maze.
    SquareMaze();

    //Destructor
    ~SquareMaze();

    //Makes a new SquareMaze of the given height and width.
    void makeMaze(int width, int height);

    //This uses your representation of the maze to determine whether it is possible to 
    //travel in the given direction from the square at coordinates (x,y).
    bool canTravel(int x, int y, int dir) const;

    //Sets whether or not the specified wall exists.
    void setWall(int x, int y, int dir, bool exists);

    //Solves this SquareMaze.
    vector<int> solveMaze();

    //Helper function for solveMaze
    vector<int> solveMaze(pair<int, int> start);

    //Draws the maze without the solution.
    PNG* drawMaze() const;

    //This function calls drawMaze, then solveMaze; 
    //it modifies the PNG from drawMaze to show the solution vector and the exit.
    PNG* drawMazeWithSolution();

    //draw pixel red
    void redden(HSLAPixel* pixel);

private:
    class Square {
    public:
        bool _right;
        bool _down;
    };

    DisjointSets* _disjointSets; 
    vector<Square> _maze; 
    int _width;
    int _height;

};