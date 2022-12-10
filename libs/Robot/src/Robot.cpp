// Robot.cpp

#include "Robot.h"

// Robot's constructor
Robot::Robot(Position start_position, Position goal_position)
        :coordinates_{start_position}, goal_position_{goal_position}
{
        for(size_t i{0}; i < available_positions().size(); i++) {
                available_positions_.at(i).set_potential(0);
        }
        set_available_positions(start_position);

        previous_cell_ = start_position;
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

void Robot::find_min_potential()
{
        double minimum_potential{available_positions().at(0).potential()};
        int index_of_min_cell{0};
        for(size_t it{1}; it < available_positions().size(); it++) {
                if(available_positions().at(it).potential() < minimum_potential) {
                        if(!available_positions().at(it).is_obstacle()) {
                                minimum_potential = available_positions().at(it).potential();
                                index_of_min_cell = it;
                        }
                }
        }

        index_of_min_cell_ = index_of_min_cell;

        // std::cout << "Min potential: " << minimum_potential << " in cell: " << index_of_min_cell<< " (" << available_positions().at(index_of_min_cell).coordinates().x()
        //                 << "," << available_positions().at(index_of_min_cell).coordinates().y() << ")" << std::endl;
}

void Robot::move(vector<Position> obstacles_position, double max_influence_distance)
{
        bool arrived{false};
        while(!arrived) {
                // std::cout << "\nPrevious cell: (" << previous_cell().x() << "," << previous_cell().y() << ")" << std::endl;

                set_available_positions(Position(coordinates().x(),coordinates().y()));

                for(size_t i{0}; i < available_positions().size(); i++) {
                        available_positions_.at(i).potential_calculation(goal_position(),obstacles_position,max_influence_distance);
                        // std::cout << "Potential: " << available_positions().at(i).potential() << std::endl;
                }

                find_min_potential();
                if((previous_cell().x() == available_positions().at(index_of_min_cell_).coordinates().x()) && (previous_cell().y() == available_positions().at(index_of_min_cell_).coordinates().y())) {
                        std::cerr << "Error: local minimum found." << std::endl;
                        arrived = true;
                }
                else {
                        previous_cell_ = Position(coordinates().x(),coordinates().y());
                
                        coordinates_.set_x(available_positions().at(index_of_min_cell_).coordinates().x());
                        coordinates_.set_y(available_positions().at(index_of_min_cell_).coordinates().y());

                        // std::cout << "Previous cell: (" << previous_cell().x() << "," << previous_cell().y() << ")" << std::endl;
                        std::cout << "New cell: (" << coordinates().x() << "," << coordinates().y() << ")" << std::endl;
                        if((coordinates().x() == goal_position().x()) && (coordinates().y() == goal_position().y()))
                                arrived = true;
                }
        }
}