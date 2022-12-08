#include "Robot.h"

int main()
{
    Robot r1(Position(8,8), Position(14,15));

    std::cout << "Robot start position: (" << r1.coordinates().x() << "," << r1.coordinates().y() << ")" << std::endl;
    std::cout << "Robot goal position: (" << r1.goal_position().x() << "," << r1.goal_position().y() << ")" << std::endl;

    // std::cout << "Available cells: " << std::endl;
    // r1.print_av_pos();

    obstacle ob1{.min_corner{6,6}, .max_corner{7,7}};
    obstacle ob2{.min_corner{10,10}, .max_corner{12,12}};
    obstacle ob3{.min_corner{15,16}, .max_corner{16,17}};
    obstacle ob4{.min_corner{18,7}, .max_corner{19,8}};
    obstacle ob5{.min_corner{22,17}, .max_corner{23,19}};

    vector<obstacle> vector_of_obstacles;
    vector_of_obstacles.push_back(ob1);
    vector_of_obstacles.push_back(ob2);
    vector_of_obstacles.push_back(ob3);
    vector_of_obstacles.push_back(ob4);
    vector_of_obstacles.push_back(ob5);

    Map map{r1.coordinates(), r1.goal_position(), vector_of_obstacles};

    // for(size_t i{0}; i < map.obstacle_positions().size(); i++) {
    //     std::cout << "Obstacles position: (" << map.obstacle_positions()[i].x() << "," << map.obstacle_positions()[i].y() << ")" << std::endl;
    // }

    // for(size_t it{0}; it < r1.available_positions().size(); it++) {
    //     r1.available_positions().at(it).potential_calculation(r1.goal_position(), map.obstacle_positions(), 5.0);
    //     std::cout << "Potential: " << r1.available_positions().at(it).potential() << std::endl;
    // }

    r1.move(map.obstacle_positions(), 5.0);
}