// Server.cpp

#include "Satellite.h"

using std::mutex;
using std::unique_lock;

Satellite::Satellite(vector<Position> vector_of_goals)
        :goals_{vector_of_goals}
{

}

// // Server's constructor
// Server::Server(int number_of_robots, int arbitrary_parameter)
//         :number_of_robots_{number_of_robots}, parameter_{arbitrary_parameter}
// {
//     capacity_ = number_of_robots_ * parameter_;
// }

// // void Server::position_append(Position new_pos)
// // {
// //     unique_lock<std::mutex> mlock(mutex_);
// //     while(count_ == capacity_)
// //         not_full_.wait(mlock);
// //     goal_queue_.push(new_pos);
// //     ++count_;
// //     mlock.unlock();
// //     not_empty_.notify_one();
// // }

// Position Server::position_take()
// {
//     std::unique_lock<std::mutex> mlock(mutex_);
//     while(count_ == 0)
//         not_empty_.wait(mlock);
//     Position pos{goal_queue_.front()};
//     goal_queue_.pop();
//     --count_;
//     mlock.unlock();
//     not_full_.notify_one();

//     return pos;
// }

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
        
        // std::cout << x << " " << y << "\n";
    }

}

void read_from_file_obstacle(const std::string& filename, vector<obstacle>& vector_of_obstacles)
{

    // std::ifstream encapsulates the functionality of an 
    // input file stream as a class, is created by
    // providing a filename as its constructor argument
    std::ifstream infile{filename,std::iostream::in};
    bool flag{true};
    obstacle temp;

    while (!infile.eof()) {
        double x1, y1, x2, y2;
        if(flag) {
            infile >> x1 >> y1;
            if (infile.fail() || infile.bad()) {
                std::cerr << "Error in input or eof  \n";
                break;
            }
            flag = !flag;
        }
        else {
            infile >> x2 >> y2;
            if (infile.fail() || infile.bad()) {
                std::cerr << "Error in input or eof  \n";
                break;
            }
            obstacle temp{.min_corner{x1, y1}, .max_corner{x2, y2}};
            vector_of_obstacles.push_back(temp);
            flag = !flag;
        }        
    }
}