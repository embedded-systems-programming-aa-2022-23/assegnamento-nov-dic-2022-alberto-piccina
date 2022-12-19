// Server.h

#ifndef Server_h
#define Server_h

#include "Robot.h"

#include <queue>
using std::queue;

#include <fstream>
#include <mutex>
#include <condition_variable>

class Server {
public:

    // constructor
    Server(int number_of_robots, int capacity);

    // const members
    queue<Position> goal_queue() const {return goal_queue_;}
    int parameter() const {return parameter_;}

    // producer-consumer functions
    void position_append(Position new_pos);
    Position position_take();

private:
    queue<Position> goal_queue_;
    int number_of_robots_;
    int parameter_;
    int capacity_;
    int count_;

    std::mutex mutex_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
};

void read_from_file(const std::string& filename, vector<Position>& vector_of_position);
void read_from_file_obstacle(const std::string& filename, vector<obstacle>& vector_of_obstacles);

#endif