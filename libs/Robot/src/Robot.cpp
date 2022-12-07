// Robot.cpp

#include "Robot.h"

// Robot's constructor
Robot::Robot(Position start_position, Position goal_position)
        :coordinates_{start_position}, goal_position_{goal_position}
{
        set_available_positions(start_position);
}

// Robot's default constructor
Robot::Robot()
        :coordinates_{Position(0,0)}
{
}

void Robot::set_available_positions(Position current_cell)
{
        Position new_cell{current_cell};
        // std::cout << "Current cell: (" << current_cell.x() << "," << current_cell.y() << ")" << std::endl;

        // cell: Nord
        new_cell.set_y(current_cell.y()+1);
        available_positions_.at(0).set_coordinates(new_cell);

        // cell: NordEst
        new_cell.set_x(current_cell.x()+1);
        new_cell.set_y(current_cell.y()+1);
        available_positions_.at(1).set_coordinates(new_cell);

        // cell: Est
        new_cell.set_x(current_cell.x()+1);
        new_cell.set_y(current_cell.y());
        available_positions_.at(2).set_coordinates(new_cell);

        // cell: SudEst
        new_cell.set_x(current_cell.x()+1);
        new_cell.set_y(current_cell.y()-1);
        available_positions_.at(3).set_coordinates(new_cell);

        // cell: Sud
        new_cell.set_x(current_cell.x());
        new_cell.set_y(current_cell.y()-1);
        available_positions_.at(4).set_coordinates(new_cell);

        // cell: SudOvest
        new_cell.set_x(current_cell.x()-1);
        new_cell.set_y(current_cell.y()-1);
        available_positions_.at(5).set_coordinates(new_cell);

        // cell: Ovest
        new_cell.set_x(current_cell.x()-1);
        new_cell.set_y(current_cell.y());
        available_positions_.at(6).set_coordinates(new_cell);

        // cell: NordOvest
        new_cell.set_x(current_cell.x()-1);
        new_cell.set_y(current_cell.y()+1);
        available_positions_.at(7).set_coordinates(new_cell);
}

void Robot::print_av_pos()
{
        for(size_t i{0}; i < available_positions().size(); i++) {
                std::cout << "Cella " << i << "\t(" << available_positions().at(i).coordinates().x() << "," << available_positions().at(i).coordinates().y() << ")\n";
        }
}