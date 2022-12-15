#include "Robot.h"
#include <fstream>

void read_from_file(const std::string& filename) {

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
        std::cout << x << " " << y << "\n";
    }

}

int main()
{
    std::string filename_start_position{"start_robots_coordinates.txt"};
    std::string filename_goal_position{"goals_coordinates.txt"};
    std::string filename_obstacles{"obstacles_coordinates.txt"};

    read_from_file(filename_start_position);
    read_from_file(filename_goal_position);
    read_from_file(filename_obstacles);

    double cell_size = 1;

    // std::cout << "Robot start position: (" << r1.coordinates().x() << "," << r1.coordinates().y() << ")" << std::endl;
    // std::cout << "Robot goal position: (" << r1.goal_position().x() << "," << r1.goal_position().y() << ")" << std::endl;

    // std::cout << "Available cells: " << std::endl;
    // r1.print_av_pos();

    obstacle ob1{.min_corner{1,1}, .max_corner{2,2}};
    obstacle ob2{.min_corner{8,10}, .max_corner{12,12}};
    obstacle ob3{.min_corner{-5,-7}, .max_corner{-1,-1}};
    obstacle ob4{.min_corner{-9,-5}, .max_corner{-3,-3}};

    // obstacle ob1{.min_corner{6,6}, .max_corner{7,7}};
    // obstacle ob2{.min_corner{-6,-5}, .max_corner{-2,-2}};
    // obstacle ob3{.min_corner{15,16}, .max_corner{16,17}};
    // obstacle ob4{.min_corner{18,7}, .max_corner{19,8}};
    obstacle ob5{.min_corner{22,17}, .max_corner{23,19}};

    vector<obstacle> vector_of_obstacles;
    vector_of_obstacles.push_back(ob1);
    vector_of_obstacles.push_back(ob2);
    vector_of_obstacles.push_back(ob3);
    vector_of_obstacles.push_back(ob4);
    vector_of_obstacles.push_back(ob5);

    // Map map{r1.coordinates(), r1.goal_position(), vector_of_obstacles, cell_size};
    // Robot r1(Position(4,7), Position(20,20), cell_size);

    Map map{Position(0,0), Position(20,20), vector_of_obstacles, cell_size};
    Robot r1(map.robot_start_position(), map.goal_position(), cell_size);

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

    // std::cout << std::endl;
    // for(size_t i{0}; i < r1.position_record().size(); i++) {
    //     std::cout << "record: (" << r1.position_record().at(i).x() << "," << r1.position_record().at(i).y() << ")" << std::endl;
    // }
    // std::cout << std::endl;

    return 0;
}