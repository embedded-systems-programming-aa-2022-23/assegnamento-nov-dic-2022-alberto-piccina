// Robot.cpp

#include "Robot.h"

// Robot's constructor
Robot::Robot(Position start_position, Position goal_position, double cell_size)
        :coordinates_{start_position}, goal_position_{goal_position}
{
        if(!check_with_cell_size(cell_size)) {
                std::cout << "Robot(): invalid robot. Verify if start position and goal position are defined correctly." << std::endl;
                exit(EXIT_FAILURE);
        }
        for(size_t i{0}; i < available_positions().size(); i++) {
                available_positions_.at(i).set_potential(0);
        }
        set_available_positions(start_position, cell_size);

        previous_cell_ = start_position;
}

// Robot's default constructor
Robot::Robot()
        :coordinates_{Position(0,0)}
{
}

bool Robot::check_with_cell_size(double cell_size)
{
        double a{fmod(coordinates_.x(),cell_size)};
        double b{fmod(coordinates_.y(),cell_size)};
        double c{fmod(goal_position_.x(),cell_size)};
        double d{fmod(goal_position_.y(),cell_size)};

        if((a != 0) || (b != 0) || (c != 0) || (d != 0))
                return false;
        else
                return true;
}

void Robot::set_available_positions(Position current_cell, double cell_size)
{
        Position new_cell{current_cell};
        // std::cout << "Current cell: (" << current_cell.x() << "," << current_cell.y() << ")" << std::endl;

        // cell: Nord
        new_cell.set_y(current_cell.y() + cell_size);
        available_positions_.at(0).set_coordinates(new_cell);
        if(available_positions_.at(0).is_obstacle())
                available_positions_.at(0).set_potential(10000);

        // cell: NordEst
        new_cell.set_x(current_cell.x() + cell_size);
        new_cell.set_y(current_cell.y() + cell_size);
        available_positions_.at(1).set_coordinates(new_cell);
        if(available_positions_.at(1).is_obstacle())
                available_positions_.at(1).set_potential(10000);

        // cell: Est
        new_cell.set_x(current_cell.x() + cell_size);
        new_cell.set_y(current_cell.y());
        available_positions_.at(2).set_coordinates(new_cell);
        if(available_positions_.at(2).is_obstacle())
                available_positions_.at(2).set_potential(10000);

        // cell: SudEst
        new_cell.set_x(current_cell.x() + cell_size);
        new_cell.set_y(current_cell.y() - cell_size);
        available_positions_.at(3).set_coordinates(new_cell);
        if(available_positions_.at(3).is_obstacle())
                available_positions_.at(3).set_potential(10000);

        // cell: Sud
        new_cell.set_x(current_cell.x());
        new_cell.set_y(current_cell.y() - cell_size);
        available_positions_.at(4).set_coordinates(new_cell);
        if(available_positions_.at(4).is_obstacle())
                available_positions_.at(4).set_potential(10000);

        // cell: SudOvest
        new_cell.set_x(current_cell.x() - cell_size);
        new_cell.set_y(current_cell.y() - cell_size);
        available_positions_.at(5).set_coordinates(new_cell);
        if(available_positions_.at(5).is_obstacle())
                available_positions_.at(5).set_potential(10000);

        // cell: Ovest
        new_cell.set_x(current_cell.x() - cell_size);
        new_cell.set_y(current_cell.y());
        available_positions_.at(6).set_coordinates(new_cell);
        if(available_positions_.at(6).is_obstacle())
                available_positions_.at(6).set_potential(10000);

        // cell: NordOvest
        new_cell.set_x(current_cell.x() - cell_size);
        new_cell.set_y(current_cell.y() + cell_size);
        available_positions_.at(7).set_coordinates(new_cell);
        if(available_positions_.at(7).is_obstacle())
                available_positions_.at(7).set_potential(10000);
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
                if(!available_positions().at(it).is_obstacle()) {
                        if(available_positions().at(it).potential() < minimum_potential) {
                                minimum_potential = available_positions().at(it).potential();
                                index_of_min_cell = it;
                        }
                }
                else {
                        available_positions_.at(it).set_potential(10000);
                        std::cout << "OSTACOLOOO" << std::endl;
                }

                // if(available_positions().at(it).potential() < minimum_potential) {
                        // std::cout << "ostacolo: " << available_positions().at(it).is_obstacle() << std::endl;
                        // if(!available_positions().at(it).is_obstacle()) {
                                // minimum_potential = available_positions().at(it).potential();
                                // index_of_min_cell = it;
                        // }
                // }
        }

        index_of_min_cell_ = index_of_min_cell;

        // std::cout << "Min potential: " << minimum_potential << " in cell: " << index_of_min_cell<< " (" << available_positions().at(index_of_min_cell).coordinates().x()
        //                 << "," << available_positions().at(index_of_min_cell).coordinates().y() << ")" << std::endl;
}

void Robot::move(vector<Position> obstacles_position, double cell_size, double max_influence_distance)
{
        bool arrived{false};
        while(!arrived) {
                // std::cout << "\nPrevious cell: (" << previous_cell().x() << "," << previous_cell().y() << ")" << std::endl;
                position_record_.push_back(coordinates_);
                set_available_positions(Position(coordinates().x(),coordinates().y()), cell_size);

                for(size_t i{0}; i < available_positions().size(); i++) {
                        if((available_positions_.at(i).coordinates().x() == goal_position().x()) && (available_positions_.at(i).coordinates().y() == goal_position().y())) {
                                coordinates_.set_x(available_positions().at(i).coordinates().x());
                                coordinates_.set_y(available_positions().at(i).coordinates().y());
                                std::cout << "New cell: (" << coordinates().x() << "," << coordinates().y() << ")" << std::endl;
                                std::cout << "Done." << std::endl;
                                arrived = true;
                                exit(EXIT_SUCCESS);  // TEMPORANEO
                        }
                        available_positions_.at(i).potential_calculation(goal_position(),obstacles_position,max_influence_distance);
                        // std::cout << "Potential: " << available_positions().at(i).potential() << std::endl;
                }

                find_min_potential();
                // if((available_positions().at(index_of_min_cell_).coordinates().x() == ))

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