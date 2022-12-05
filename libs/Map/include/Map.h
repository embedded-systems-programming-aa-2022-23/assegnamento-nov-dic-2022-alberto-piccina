// Map.h

#ifndef Map_h
#define Map_h

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class Position {
public:

    // constructor
    Position(int x, int y);
    Position();

    // const members
    int x() const {return x_; }
    int y() const {return y_; }

private:
    int x_;
    int y_;
};

struct obstacle {
    Position min_corner;
    Position max_corner;
};

class Cell {
public:
    
    // constructor
    Cell(Position cell_coordinates, float potential, bool not_obstacle);
    Cell();

    // const members
    Position coordinates() const {return coordinates_;}
    float potential() const {return potential_;}
    bool not_obstacle() const {return not_obstacle_;}
    void set_obstacles_to_cells();

    // non-const members
private:
    Position coordinates_;
    float potential_;
    bool not_obstacle_;
};

class Map {
public:

    // constructor
    Map(Position robot_start_position, Position goal_position, std::vector<obstacle> vector_obstacle);

    // const members
    std::vector<obstacle> obstacles() const {return obstacles_;}
    Position goal_position() const {return goal_position_;}
    Position start_position() const {return robot_start_position_;}

    // non-const member
    // Cell map_generator(Position map_origin, int number_of_horizontal_cells, int number_of_vertical_cells);
    // vector<vector<Cell>> map_generator(Position map_origin, int number_of_horizontal_cells, int number_of_vertical_cells);
    Position smallest_corner{};
    Position biggest_corner{};

private:
     Position robot_start_position_;
    Position goal_position_;
    vector<obstacle> obstacles_;
    bool start_goal_position_check(Position biggest_corner, Position smallest_corner);
};

bool operator<(const Position& p1, const Position& p2);


#endif
