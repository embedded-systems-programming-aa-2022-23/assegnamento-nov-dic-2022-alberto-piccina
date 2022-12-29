// Server.cpp

#include "Server.h"

using std::mutex;
using std::unique_lock;

// Server's constructor
Server::Server(int number_of_robots, int arbitrary_parameter)
        :number_of_robots_{number_of_robots}, parameter_{arbitrary_parameter}
{
    capacity_ = number_of_robots_ * parameter_;
}

// default constructor
Server::Server()
        :capacity_{10}
{
}

void Server::update_queue(const int number_of_robots, const int arbitrary_parameter)
{
    number_of_robots_ = number_of_robots;
    parameter_ = arbitrary_parameter;

    capacity_ = number_of_robots_ * parameter_;
}

void Server::position_append(Position new_pos)
{
    unique_lock<std::mutex> mlock(mutex_);
    while(count_ == capacity_)
        not_full_.wait(mlock);
    goal_queue_.push_back(new_pos);
    ++count_;
    mlock.unlock();
    not_empty_.notify_one();
}

Position Server::position_take(Position robot_coordinates)
// Position Server::position_take()
{
    std::unique_lock<std::mutex> mlock(mutex_);
    while(count_ == 0)
        not_empty_.wait(mlock);
    // Position pos{goal_queue_.front()};
    Position pos{find_minimum_position(robot_coordinates)};
    // goal_queue_.pop_front();
    goal_queue_.erase(goal_queue_.begin() + min_index_);
    --count_;
    mlock.unlock();
    not_full_.notify_one();

    return pos;
}

Position Server::find_minimum_position(Position robot_coordinates)
{
    int min_index{0};
    // double minimum{std::numeric_limits<double>::infinity()};
    double distance{sqrt(pow(goal_queue_.at(0).x() - robot_coordinates.x(), 2) + pow(goal_queue_.at(0).y() - robot_coordinates.y(), 2))};
    for(size_t i{0}; i < goal_queue_.size(); i++) {
        double provv_distance = sqrt(pow(goal_queue_.at(i).x() - robot_coordinates.x(), 2) + pow(goal_queue_.at(i).y() - robot_coordinates.y(), 2));
        if(provv_distance < distance) {
            // minimum = distance;
            distance = provv_distance;
            min_index = i;
        }
    }

    min_index_ = min_index;

    return goal_queue_.at(min_index);
}



void read_from_file(const std::string& filename, vector<Position>& vector_of_position)
{

    // std::ifstream encapsulates the functionality of an 
    // input file stream as a class, is created by
    // providing a filename as its constructor argument
    std::ifstream infile{filename,std::iostream::in};

    while (!infile.eof()) {
        double x, y;
        infile >> x >> y;
        if (infile.fail() || infile.bad()) {
            std::cerr << "Error in input or eof  \n";
            break;
        }
        vector_of_position.push_back(Position(x,y));
    }

}

void read_from_file_obstacle(const std::string& filename, vector<obstacle>& vector_of_obstacles)
{

    // std::ifstream encapsulates the functionality of an 
    // input file stream as a class, is created by
    // providing a filename as its constructor argument
    std::ifstream infile{filename,std::iostream::in};

    while(!infile.eof()) {
        double x_min, y_min, x_max, y_max;
        infile >> x_min >> y_min >> x_max >> y_max;
        if (infile.fail() || infile.bad()) {
            std::cerr << "Error in input or eof  \n";
            break;
        }
        obstacle temp{.min_corner{x_min, y_min}, .max_corner{x_max, y_max}};
        vector_of_obstacles.push_back(temp);
    }

    // while (!infile.eof()) {
    //     double x1, y1, x2, y2;
    //     if(flag) {
    //         infile >> x1 >> y1;
    //         if (infile.fail() || infile.bad()) {
    //             std::cerr << "Error in input or eof  \n";
    //             break;
    //         }
    //         flag = !flag;
    //     }
    //     else {
    //         infile >> x2 >> y2;
    //         if (infile.fail() || infile.bad()) {
    //             std::cerr << "Error in input or eof  \n";
    //             break;
    //         }
    //         obstacle temp{.min_corner{x1, y1}, .max_corner{x2, y2}};
    //         vector_of_obstacles.push_back(temp);
    //         flag = !flag;
    //     }        
    // }
}