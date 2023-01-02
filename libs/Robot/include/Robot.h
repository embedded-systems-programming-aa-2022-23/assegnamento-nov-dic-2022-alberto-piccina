// Robot.h

#ifndef Robot_h
#define Robot_h

#include "Map.h"

#include <array>
#include <algorithm>
#include <limits>
#include <mutex>
#include <condition_variable>

class Robot {
public:

    // constructor
    Robot(Position start_position, Map map);
    Robot(Map map);

    // const members
    Position coordinates() const {return coordinates_;}
    Position goal_position() const {return goal_position_;}
    std::array<Cell,8> available_positions() const {return available_positions_;}
    std::vector<Position> position_record() const {return position_record_;}
    Map map() const {return map_;}
    int id() const {return id_;}
    bool arrived() const {return arrived_;}

    Position set_coordinates_robot(const Position& new_position);
    Position set_goal(const Position& goal_position);
    int set_id(const int id_to_set);
    bool reset();
    void step();

private:
    Position coordinates_;
    Position goal_position_;
    std::array<Cell,8> available_positions_;
    Position previous_cell_;
    int index_of_min_cell_;
    int id_;
    std::vector<Position> position_record_;
    Map map_;
    bool arrived_;

    bool check_with_cell_size();
    void set_available_positions(const Position& current_cell);
    void print_av_pos();
    void find_min_potential();

    // std::mutex mutex_;
    // std::condition_variable not_in_movement;
};

#endif 