// Robot.cpp

#include "Robot.h"

// Robot's constructor
Robot::Robot(Position start_position, Map map)
        :coordinates_{start_position}, map_{map}
{
        if(!check_with_cell_size()) {
                std::cout << "Robot(): invalid robot. Verify if start position and goal position are defined correctly." << std::endl;
                exit(EXIT_FAILURE);
        }

        for(size_t i{0}; i < available_positions().size(); i++) {

                available_positions_.at(i).set_potential(0);

        }

        set_available_positions(start_position);
}

// Robot's default constructor
Robot::Robot(Map map)
        :coordinates_{Position(0,0)}, map_{map}
{
}

// controlls if robot's position fits with the cell size
bool Robot::check_with_cell_size()
{
        double a{fmod(coordinates_.x(), map_.cell_size())};
        double b{fmod(coordinates_.y(), map_.cell_size())};
        double c{fmod(goal_position_.x(), map_.cell_size())};
        double d{fmod(goal_position_.y(), map_.cell_size())};

        if((a != 0) || (b != 0) || (c != 0) || (d != 0))
                return false;
        else
                return true;
}

// function to set the array of available positions where the robot can move
void Robot::set_available_positions(const Position& current_cell)
{
        Position new_cell{current_cell};

        // cell: Nord
        new_cell.set_y(current_cell.y() + map_.cell_size());
        available_positions_.at(0).set_coordinates(new_cell);
        if(available_positions_.at(0).is_obstacle())
                available_positions_.at(0).set_potential(std::numeric_limits<double>::max());

        // cell: NordEst
        new_cell.set_x(current_cell.x() + map_.cell_size());
        new_cell.set_y(current_cell.y() + map_.cell_size());
        available_positions_.at(1).set_coordinates(new_cell);
        if(available_positions_.at(1).is_obstacle())
                available_positions_.at(1).set_potential(std::numeric_limits<double>::max());

        // cell: Est
        new_cell.set_x(current_cell.x() + map_.cell_size());
        new_cell.set_y(current_cell.y());
        available_positions_.at(2).set_coordinates(new_cell);
        if(available_positions_.at(2).is_obstacle())
                available_positions_.at(2).set_potential(std::numeric_limits<double>::max());

        // cell: SudEst
        new_cell.set_x(current_cell.x() + map_.cell_size());
        new_cell.set_y(current_cell.y() - map_.cell_size());
        available_positions_.at(3).set_coordinates(new_cell);
        if(available_positions_.at(3).is_obstacle())
                available_positions_.at(3).set_potential(std::numeric_limits<double>::max());

        // cell: Sud
        new_cell.set_x(current_cell.x());
        new_cell.set_y(current_cell.y() - map_.cell_size());
        available_positions_.at(4).set_coordinates(new_cell);
        if(available_positions_.at(4).is_obstacle())
                available_positions_.at(4).set_potential(std::numeric_limits<double>::max());

        // cell: SudOvest
        new_cell.set_x(current_cell.x() - map_.cell_size());
        new_cell.set_y(current_cell.y() - map_.cell_size());
        available_positions_.at(5).set_coordinates(new_cell);
        if(available_positions_.at(5).is_obstacle())
                available_positions_.at(5).set_potential(std::numeric_limits<double>::max());

        // cell: Ovest
        new_cell.set_x(current_cell.x() - map_.cell_size());
        new_cell.set_y(current_cell.y());
        available_positions_.at(6).set_coordinates(new_cell);
        if(available_positions_.at(6).is_obstacle())
                available_positions_.at(6).set_potential(std::numeric_limits<double>::max());

        // cell: NordOvest
        new_cell.set_x(current_cell.x() - map_.cell_size());
        new_cell.set_y(current_cell.y() + map_.cell_size());
        available_positions_.at(7).set_coordinates(new_cell);
        if(available_positions_.at(7).is_obstacle())
                available_positions_.at(7).set_potential(std::numeric_limits<double>::max());
}

// function to set the coordinatesof the robot
Position Robot::set_coordinates_robot(const Position& new_position)
{
        coordinates_.set_x(new_position.x());
        coordinates_.set_y(new_position.y());

        return coordinates_;
}

// function to set the goal to reach
Position Robot::set_goal(const Position& goal_position)
{
        goal_position_.set_x(goal_position.x() - map_.origin().x());
        goal_position_.set_y(goal_position.y() - map_.origin().y());

        return goal_position_;
}

// to set robot's id (for concurrency)
int Robot::set_id(const int id_to_set)
{
        id_ = id_to_set;

        return id_;
}

// to clear old positions and set arrived_ to false
bool Robot::reset()
{
        position_record_.clear();
        return (arrived_ = false);
}

// print function: it prints the coordinates of all available positions
void Robot::print_av_pos()
{
        for(size_t i{0}; i < available_positions().size(); i++) {
                std::cout << "Cella " << i << "\t(" << available_positions().at(i).coordinates().x() << "," << available_positions().at(i).coordinates().y() << ")\n";
        }
}

// function to find the minimum potential in the available positions
void Robot::find_min_potential()
{
        double minimum_potential{available_positions_.at(0).potential()};
        int index{0};
        for(size_t it{0}; it < available_positions().size(); it++) {

                for(size_t j{0}; j < position_record_.size(); j++) {

                        if((available_positions_.at(it).coordinates().x() == position_record_.at(j).x()) && (available_positions_.at(it).coordinates().y() == position_record_.at(j).y())) {
                                available_positions_.at(it).set_potential(std::numeric_limits<double>::max());
                        }

                }

                if(available_positions_.at(it).is_obstacle()) {
                        available_positions_.at(it).set_potential(std::numeric_limits<double>::max());
                }
                else {
                        if(available_positions_.at(it).potential() < minimum_potential) {
                                minimum_potential = available_positions_.at(it).potential();
                                index = it;
                        }
                }

        }
        
        index_of_min_cell_ = index;
        
}

// function that allows robot to move of one cell
// void Robot::move(const vector<Position>& obstacles_position, const double max_influence_distance)
void Robot::step(const double max_influence_distance)
{
        position_record_.push_back(coordinates_);
        set_available_positions(Position(coordinates().x(),coordinates().y()));

        for(size_t i{0}; i < available_positions().size(); i++) {

                if((available_positions_.at(i).coordinates().x() == goal_position().x()) && (available_positions_.at(i).coordinates().y() == goal_position().y())) {
                        coordinates_.set_x(available_positions().at(i).coordinates().x());
                        coordinates_.set_y(available_positions().at(i).coordinates().y());
                        map_.change_robot_position(id_, coordinates_);
                        std::cout << "Robot " << id_ << " moved to " << map_.robot_start_position().at(id_).x() + map_.origin().x() << "," 
                                                << map_.robot_start_position().at(id_).y() + map_.origin().y() << std::endl;
                        arrived_ = true;
                        return ;
                }

                available_positions_.at(i).potential_calculation(goal_position(),map_.obstacle_positions(),max_influence_distance);
                
        }

        find_min_potential();

        bool check{true};
        for(auto& it : position_record_) {

                if((it.x() == available_positions_.at(index_of_min_cell_).coordinates().x()) && (it.y() == available_positions_.at(index_of_min_cell_).coordinates().y()))
                        check = false;
                        
        }
        if(!check) {
                std::cerr << "Error: local minimum found." << std::endl;
                arrived_ = true;
        }
        else {
                
                coordinates_.set_x(available_positions().at(index_of_min_cell_).coordinates().x());
                coordinates_.set_y(available_positions().at(index_of_min_cell_).coordinates().y());
                map_.change_robot_position(id_, coordinates_);
                std::cout << "Robot " << id_ << " moved to " << map_.robot_start_position().at(id_).x() + map_.origin().x() << "," 
                                        << map_.robot_start_position().at(id_).y() + map_.origin().y() << std::endl;

                if((coordinates().x() == goal_position().x()) && (coordinates().y() == goal_position().y())) {
                        arrived_ = true;
                }   
        }
}