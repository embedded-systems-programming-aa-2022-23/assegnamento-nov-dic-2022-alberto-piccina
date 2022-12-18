#include "Robot.h"
#include <fstream>

void read_from_file(const std::string& filename, vector<Position>& vector_of_position) {

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

void read_from_file_obstacle(const std::string& filename, vector<obstacle>& vector_of_obstacles) {

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

    for(size_t it{0}; it < vector_of_start_position.size(); it++)
        std::cout << vector_of_start_position.at(it).x() << " " << vector_of_start_position.at(it).y() << std::endl;
    for(size_t it{0}; it < vector_of_goals.size(); it++)
        std::cout << vector_of_goals.at(it).x() << " " << vector_of_goals.at(it).y() << std::endl;
    // for(size_t it{0}; it < vector_of_obstacles.size(); it++)
    //     std::cout << vector_of_obstacles.at(it).x() << " " << vector_of_obstacles.at(it).y() << std::endl;

    double cell_size = 1;

    Map map{vector_of_start_position.at(0), vector_of_goals.at(0), vector_of_obstacles, cell_size};
    Robot r1(map.robot_start_position(), map.goal_position(), cell_size);

    // Map map{Position(0,4), Position(3,0), vector_of_obstacles, cell_size};
    // Robot r1(map.robot_start_position(), map.goal_position(), cell_size);

    // std::cout << std::endl;
    // for(size_t i{0}; i < map.obstacle_positions().size(); i++) {
    //     std::cout << "Obstacles position: (" << map.obstacle_positions()[i].x() << "," << map.obstacle_positions()[i].y() << ")" << std::endl;
    // }
    // std::cout << std::endl;


    // for(size_t it{0}; it < r1.available_positions().size(); it++) {
    //     r1.available_positions().at(it).potential_calculation(r1.goal_position(), map.obstacle_positions(), 5.0);
    //     std::cout << "Potential: " << r1.available_positions().at(it).potential() << std::endl;
    // }

    r1.move(map.obstacle_positions(), cell_size, 5.0);

    map.change_robot_position(r1.coordinates());
    
    map.print_map();

    // std::cout << std::endl;
    // for(size_t i{0}; i < r1.position_record().size(); i++) {
    //     std::cout << "record: (" << r1.position_record().at(i).x() << "," << r1.position_record().at(i).y() << ")" << std::endl;
    // }
    // std::cout << std::endl;

    return 0;
}