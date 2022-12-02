// Robot.cpp

#include <iostream>
using std::endl;

#include "Position.h"

Position::Position(int x, int y)
        :x_{x}, y_{y}
{
    if(x_< 0 || y_< 0) {
        std::cerr << "Position(): invalid position.\n" << "Position can't be < 0." << endl;
    }
}

const Position& default_position()
{
    static Position p{0, 0};    // default position at (x, y) = (0, 0)
    return p;
}

Position::Position()
        :x_{default_position().x()},
        y_{default_position().y()}
{
}