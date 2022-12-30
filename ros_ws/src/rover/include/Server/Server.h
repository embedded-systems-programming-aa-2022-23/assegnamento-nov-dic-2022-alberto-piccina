// Server.h

#ifndef Server_h
#define Server_h

#include "Robot/Robot.h"

#include <deque>
using std::deque;

#include <istream>
#include <fstream>
#include <list>
#include <string>
#include <mutex>
#include <condition_variable>

class Server {
public:

    // constructor
    Server(int number_of_robots, int arbitrary_parameter);

    // default constructor
    Server();

    // const members
    deque<Position> goal_queue() const {return goal_queue_;}
    int parameter() const {return parameter_;}

    // producer-consumer functions
    void position_append(Position new_pos);
    Position position_take(Position robot_coordinates);

    void update_queue(const int number_of_robots, const int arbitrary_parameter);
    Position find_minimum_position(Position robot_coordinates);

private:
    deque<Position> goal_queue_;
    int number_of_robots_;
    int parameter_;
    int capacity_;
    int count_;
    int min_index_;

    std::mutex mutex_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
};

void read_from_file(const std::string& filename, vector<Position>& vector_of_position);
void read_from_file_obstacle(const std::string& filename, vector<obstacle>& vector_of_obstacles);

#endif