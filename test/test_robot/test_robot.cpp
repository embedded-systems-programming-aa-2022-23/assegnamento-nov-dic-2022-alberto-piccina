#include "Robot.h"

int main()
{
    Robot r1(Position(8,8), Position(15,12));

    std::cout << "Robot start position: (" << r1.coordinates().x() << "," << r1.coordinates().y() << ")" << std::endl;
    std::cout << "Robot goal position: (" << r1.goal_position().x() << "," << r1.goal_position().y() << ")" << std::endl;

    std::cout << "Available cells: " << std::endl;
    r1.print_av_pos();
}