// Map.h

#ifndef Map_h
#define Map_h

#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <map>
#include <algorithm>

// #include "Robot.h"

using std::vector;

class Position {
public:

    // constructor
    Position(double x, double y);
    Position();

    // const members
    double x() const {return x_; }
    double y() const {return y_; }

    // non-const members
    double set_x(const double x);
    double set_y(const double y);
    double distance(Position p1, Position p2);

private:
    double x_;
    double y_;
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
    Position set_coordinates(const Position& point);
    void set_obstacles_to_cells();
    void set_cells_free();
    double set_potential(const double potential);
    double potential_calculation(const Position& goal_position, const vector<Position>& obstacles_position, const double max_influence_distance);
    double distance_calculation(const Position& p1, const Position& p2);

private:
    Position coordinates_;
    double potential_;
    bool is_obstacle_;
};

class Map {
public:

    // constructor
    // Map(Position robot_start_position, Position goal_position, std::vector<obstacle> vector_obstacle, double cell_size);
    Map(vector<Position> vec_of_start_position, vector<Position> vec_of_goals, vector<obstacle> vector_obstacle, double cell_size);

    // const members
    std::vector<obstacle> obstacles() const {return obstacles_;}
    vector<Position> goal_position() const {return goal_positions_;}
    vector<Position> robot_start_position() const {return robot_start_positions_;}
    vector<Position> obstacle_positions() const {return obstacle_positions_;}
    double cell_size() const {return cell_size_;}
    Position origin() const {return map_origin_;}

    // non-const member
    Position smallest_corner;
    Position biggest_corner;
    void print_map();
    Position change_robot_position(const int robot_id, const Position& new_position);
    void find_min_start_position();
    void find_max_goal_position();
    void check_map_limits();
    void check_start_and_goal_position();


private:
    vector<Position> robot_start_positions_;
    vector<Position> goal_positions_;
    vector<obstacle> obstacles_;
    vector<vector<Cell>> map_;
    vector<Position> obstacle_positions_;
    double cell_size_;
    Position map_origin_;
    void map_initialization(const int number_of_horizontal_cells, const int number_of_vertical_cells);
    // void print_map();
};

bool operator<(const Position& p1, const Position& p2);

#endif
