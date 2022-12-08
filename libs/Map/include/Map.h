// Map.h

#ifndef Map_h
#define Map_h

#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>

// #include "Robot.h"

using std::vector;

class Position {
public:

    // constructor
    Position(int x, int y);
    Position();

    // const members
    int x() const {return x_; }
    int y() const {return y_; }

    // non-const members
    int set_x(int x);
    int set_y(int y);

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
    Cell(Position coordinates, double potential, bool is_obstacle);
    Cell();

    // const members
    Position coordinates() const {return coordinates_;}
    double potential() const {return potential_;}
    bool is_obstacle() const {return is_obstacle_;}

    // non-const members
    Position set_coordinates(Position point);
    void set_obstacles_to_cells();
    double set_potential(double potential);
    double potential_calculation(Position goal_position, vector<Position> obstacles_position, double max_influence_distance);
    double distance_calculation(Position p1, Position p2);

private:
    Position coordinates_;
    double potential_;
    bool is_obstacle_;
};

class Map {
public:

    // constructor
    Map(Position robot_start_position, Position goal_position, std::vector<obstacle> vector_obstacle);

    // const members
    std::vector<obstacle> obstacles() const {return obstacles_;}
    Position goal_position() const {return goal_position_;}
    Position start_position() const {return robot_start_position_;}
    vector<Position> obstacle_positions() const {return obstacle_positions_;}

    // non-const member
    Position smallest_corner{};
    Position biggest_corner{};

private:
    Position robot_start_position_;
    Position goal_position_;
    vector<obstacle> obstacles_;
    vector<vector<Cell>> map_;
    vector<Position> obstacle_positions_;
    bool start_goal_position_check();
    void map_initialization(Position map_origin, int number_of_horizontal_cells, int number_of_vertical_cells);
    void print_map();
};

bool operator<(const Position& p1, const Position& p2);

#endif
