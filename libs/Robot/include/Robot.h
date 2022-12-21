// Robot.h

#ifndef Robot_h
#define Robot_h

#include "Map.h"

#include <array>
#include <limits>

class Robot {
public:
    // enum class Direction {
    //     Nord = 0, NordEst, Est, SudEst, Sud, SudOvest, Ovest, NordOvest
    // };

    // constructor
    Robot(Position start_position, Position goal_position, double cell_size);
    Robot();

    // const members
    Position coordinates() const {return coordinates_;}
    Position goal_position() const {return goal_position_;}
    std::array<Cell,8> available_positions() const {return available_positions_;}
    Position previous_cell() const {return previous_cell_;}
    std::vector<Position> position_record() const {return position_record_;}

    // non-const member
    bool check_with_cell_size(const double cell_size);
    void set_available_positions(const Position& current_cell, const double cell_size);
    Position set_coordinates_robot(const Position& new_position);
    void print_av_pos();
    void find_min_potential();
    void move(const vector<Position>& obstacles_position, const double cell_size, const double max_influence_distance);

private:
    Position coordinates_;
    Position goal_position_;
    std::array<Cell,8> available_positions_;
    Position previous_cell_;
    int index_of_min_cell_;
    std::vector<Position> position_record_;
};

#endif 