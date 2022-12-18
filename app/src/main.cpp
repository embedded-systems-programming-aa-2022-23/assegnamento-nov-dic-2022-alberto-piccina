// main.cpp

#include "Robot.h"
#include "Server.h"
#include <fstream>

int main()
{
    std::string filename_start_position{"start_robots_coordinates.txt"};
    std::string filename_goal_position{"goals_coordinates.txt"};
    std::string filename_obstacles{"obstacles_coordinates.txt"};

    vector<Position> vector_of_start_position;
    vector<Position> vector_of_goals;
    vector<obstacle> vector_of_obstacles;

    read_from_file(filename_start_position, vector_of_start_position);
    read_from_file(filename_goal_position, vector_of_goals);
    read_from_file_obstacle(filename_obstacles, vector_of_obstacles);

    // for(size_t it{0}; it < vector_of_start_position.size(); it++)
    //     std::cout << vector_of_start_position.at(it).x() << " " << vector_of_start_position.at(it).y() << std::endl;
    // for(size_t it{0}; it < vector_of_goals.size(); it++)
    //     std::cout << vector_of_goals.at(it).x() << " " << vector_of_goals.at(it).y() << std::endl;
    // for(size_t it{0}; it < vector_of_obstacles.size(); it++)
    //     std::cout << vector_of_obstacles.at(it).x() << " " << vector_of_obstacles.at(it).y() << std::endl;

    double cell_size = 1;

    Map map{vector_of_start_position.at(0), vector_of_goals.at(0), vector_of_obstacles, cell_size};
    Robot r1(map.robot_start_position(), map.goal_position(), cell_size);

    r1.move(map.obstacle_positions(), cell_size, 5.0);

    map.change_robot_position(r1.coordinates());
    
    map.print_map();

    return 0;
}