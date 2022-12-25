// main.cpp

#include "Robot.h"
#include "Server.h"
#include <fstream>
#include <thread>

const int number_of_robots{2};
const double cell_size = 1;
const int k_parameter = 3;

Server monitor;
std::mutex robot_mutex;
std::mutex cout_mutex;

void consumer(const int id, Robot robot)
{
    robot.set_id(id);
    // bool loop{true};

    // while(loop) {
    robot.set_goal(monitor.position_take());
    cout_mutex.lock();
    std::cout << "Robot " << id << " fetched (" << robot.goal_position().x() << "," << robot.goal_position().y() << ")" << std::endl;
    cout_mutex.unlock();

        // to manage the non-simultaneously robot's movement
        while(!robot.arrived()) {
            robot_mutex.lock();
            robot.step(5.0);
            robot_mutex.unlock();
        }
        cout_mutex.lock();
        std::cout << "Robot " << robot.id() << " reached (" << robot.coordinates().x() << " " 
                                                << robot.coordinates().y() << ")" << std::endl;
        cout_mutex.unlock();
    // }

    // to verify
    std::cout << robot.id() << ": new start (" << robot.coordinates().x() << "," << robot.coordinates().y() << ")" << std::endl;
    // std::cout << robot.map().robot_start_position().at(robot.id()).x() << " " << robot.map().robot_start_position().at(robot.id()).y() << std::endl;
    // robot.map().print_map();
}

void producer(const int id, const vector<Position>& goals){
    for(auto& new_pos : goals) {
        monitor.position_append(new_pos);
        cout_mutex.lock();
        std::cout << "Satellite " << id << " produced (" << new_pos.x() << "," << new_pos.y() << ")" << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        cout_mutex.unlock();
    }
}

int main()
{
    monitor.update_queue(number_of_robots, k_parameter);

    std::string filename_start_position{"start_robots_coordinates.txt"};
    std::string filename_goal_position_1{"goals_coordinates_satellite_1.txt"};
    std::string filename_goal_position_2{"goals_coordinates_satellite_2.txt"};
    std::string filename_obstacles{"obstacles_coordinates.txt"};

    vector<Position> vector_of_start_position;
    vector<obstacle> vector_of_obstacles;
    vector<Position> satellite_1;
    vector<Position> satellite_2;

    read_from_file(filename_start_position, vector_of_start_position);
    read_from_file(filename_goal_position_1, satellite_1);
    read_from_file(filename_goal_position_2, satellite_2);
    read_from_file_obstacle(filename_obstacles, vector_of_obstacles);

    vector<Position> vector_of_goals;
    for(auto& it : satellite_1) {
        vector_of_goals.push_back(it);
    }
    for(auto& it : satellite_2) {
        vector_of_goals.push_back(it);
    }

    // to stamp what I save from file.txt
    // for(size_t it{0}; it < vector_of_start_position.size(); it++)
    //     std::cout << vector_of_start_position.at(it).x() << " " << vector_of_start_position.at(it).y() << std::endl;
    // for(size_t it{0}; it < vector_of_goals.size(); it++)
    //     std::cout << vector_of_goals.at(it).x() << " " << vector_of_goals.at(it).y() << std::endl;
    // for(size_t it{0}; it < vector_of_obstacles.size(); it++)
    //     std::cout << vector_of_obstacles.at(it).x() << " " << vector_of_obstacles.at(it).y() << std::endl;

    Map map{vector_of_start_position, vector_of_goals, vector_of_obstacles, cell_size};

    vector<Robot> list_of_robots;
    for(size_t i{0}; i < vector_of_start_position.size(); i++) {
        list_of_robots.push_back(Robot(map.robot_start_position().at(i), map));
    }

    // to stamp initial position of each robot
    // for(auto& it : list_of_robots) {
    //     std::cout << it.coordinates().x() << "," << it.coordinates().y() << std::endl;
    // }

    std::thread satellite1(producer, 0, satellite_1);
    std::thread satellite2(producer, 1, satellite_2);

    vector<std::thread> robots_thread;
    for(size_t i{0}; i < vector_of_start_position.size(); i++) {
        robots_thread.push_back(std::thread(consumer, i, list_of_robots.at(i)));
    }

    satellite1.join();
    satellite2.join();
    for(auto& it : robots_thread) {
        it.join();
    }

    return 0;
}