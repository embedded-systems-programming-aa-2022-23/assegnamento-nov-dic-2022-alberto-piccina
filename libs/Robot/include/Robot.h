// Robot.h

#ifndef Robot_h
#define Robot_h

#include "Map.h"

#include <array>

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

    // non-const member
    void set_available_positions(Position current_cell, double cell_size);
    void print_av_pos();
    void find_min_potential();
    void move(vector<Position> obstacles_position, double cell_size, double max_influence_distance);

private:
    Position coordinates_;
    Position goal_position_;
    std::array<Cell,8> available_positions_;
    Position previous_cell_;
    int index_of_min_cell_;
};

#endif 