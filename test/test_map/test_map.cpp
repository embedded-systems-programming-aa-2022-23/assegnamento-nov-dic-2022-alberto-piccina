#include "Map.h"

int main()
{
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

    Position robot_start_pos{8,13};
    Position goal_pos{13, 15};

    std::cout << "Robot start pos: (" << robot_start_pos.x() << ", " << robot_start_pos.y() << ")" << std::endl;
    std::cout << "Goal pos: (" << goal_pos.x() << ", " << goal_pos.y() << ")" << std::endl;

    Map map{robot_start_pos, goal_pos, vector_of_obstacles};
}