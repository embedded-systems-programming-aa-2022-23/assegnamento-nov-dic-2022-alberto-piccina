// Map.cpp

#include "Map.h"

const double edges_surplus{6}; // in order to create a gap between obstacles and map's edges
const double zeta{5}; // attractive field's scale factor
const double eta{20}; // repulsive field's scale factor

// *************************************************************
// ***************************  MAP  ***************************
// *************************************************************

// Position's constructor
Position::Position(const double x, const double y)
        :x_{x}, y_{y}
{
    // if you want to use only positive coordinates
    // if(x_< 0 || y_< 0) {
    //     std::cerr << "Position(): invalid position.\n" << "Position can't be < 0." << std::endl;
    //     exit(EXIT_FAILURE);
    // }
}

const Position& default_position()
{
    static Position p{0, 0};    // default position at (x, y) = (0, 0)
    return p;
}

// Position's default constructor
Position::Position()
        :x_{default_position().x()},
        y_{default_position().y()}
{
}

// function that set x_ value
double Position::set_x(const double x)
{
    x_ = x;
    return x_;
}

// function that set y_ value
double Position::set_y(const double y)
{
    y_ = y;
    return y;
}


// function that set Cell's coordinates_ 
Position Cell::set_coordinates(const Position& point)
{
    coordinates_.set_x(point.x());
    coordinates_.set_y(point.y());

    return coordinates_;
}

//  Cell's constructor
Cell::Cell(Position coordinates, double potential, bool is_obstacle)
        :coordinates_{coordinates}, potential_{potential}, is_obstacle_{is_obstacle}
{
}

// Cell's default constructor
Cell::Cell()
{
}

// to find the minimum position in the vector of robots' start position
void Map::find_min_start_position()
{
    for(auto &it : robot_start_positions_) {

        if(it.x() < smallest_corner.x()) 
            smallest_corner.set_x(it.x());
        if(it.y() < smallest_corner.y())
            smallest_corner.set_y(it.y());

    }
}

// to fin the maximum position in the vector of goals' position
void Map::find_max_goal_position()
{
    for(auto &it : goal_positions_) {

        if(biggest_corner.x() < it.x())
            biggest_corner.set_x(it.x());
        if(biggest_corner.y() < it.y())
            biggest_corner.set_y(it.y());

    }
}

// to verify if robot and goal position don't go outside the map
void Map::check_map_limits()
{
    for(auto &i : goal_positions_) {

        if(i.x() < smallest_corner.x())
            smallest_corner.set_x(i.x());
        if(i.y() < smallest_corner.y())
            smallest_corner.set_y(i.y());

    }

    for(auto &j : robot_start_positions_) {

        if(j.x() > biggest_corner.x())
            biggest_corner.set_x(j.x());
        if(j.y() > biggest_corner.y())
            biggest_corner.set_y(j.y());

    }
}

// Map's constructor
Map::Map(vector<Position> vec_of_start_position, vector<Position> vec_of_goals, vector<obstacle> vector_obstacle, double cell_size)
        :robot_start_positions_{vec_of_start_position}, goal_positions_{vec_of_goals}, obstacles_{vector_obstacle}, cell_size_{cell_size}
{
    if(cell_size_ == 0) {
        std::cout << "Map(): invalid map. " << "Cell size can't be set at 0, please change the value imposted by argument." << std::endl;
        exit(EXIT_FAILURE);
    }

    for(auto& it : robot_start_positions_) {
        
        if((fmod(it.x(),cell_size_) != 0) || (fmod(it.y(),cell_size_) != 0)) {
            std::cout << "Map(): invalid map." << "\n" << "Verify if start positions are concordant to the cell size imposted." << std::endl;
            exit(EXIT_FAILURE);
        }

    }

    for(auto& it : goal_positions_) {
        
        if((fmod(it.x(),cell_size_) != 0) || (fmod(it.y(),cell_size_) != 0)) {
            std::cout << "Map(): invalid map." << "\n" << "Verify if goal positions are concordant to the cell size imposted." << std::endl;
            exit(EXIT_FAILURE);
        }
            
    }

    for(auto& it : obstacles_) {
        
        if((fmod(it.min_corner.x(),cell_size_) != 0) || (fmod(it.min_corner.y(),cell_size_) != 0) || (fmod(it.max_corner.x(),cell_size_) != 0) || (fmod(it.max_corner.y(),cell_size_) != 0)) {
            std::cout << "Map(): invalid map." << "\n" << "Verify if obstacles positions are concordant to the cell size imposted." << std::endl;
            exit(EXIT_FAILURE);
        }
            
    }

    smallest_corner = robot_start_positions_.at(0);
    biggest_corner = goal_positions_.at(0);

    find_min_start_position();
    find_max_goal_position();

    for(size_t i{0}; i < obstacles_.size(); i++) {

        if(obstacles_[i].min_corner.x() < smallest_corner.x())
            smallest_corner.set_x(obstacles_[i].min_corner.x());

        if(obstacles_[i].min_corner.y() < smallest_corner.y())
            smallest_corner.set_y(obstacles_[i].min_corner.y());

        if(obstacles_[i].max_corner.x() < smallest_corner.x())
            smallest_corner.set_x(obstacles_[i].max_corner.x());

        if(obstacles_[i].max_corner.y() < smallest_corner.y())
            smallest_corner.set_y(obstacles_[i].max_corner.y());


        if(biggest_corner.x() < obstacles_[i].max_corner.x())
            biggest_corner.set_x(obstacles_[i].max_corner.x());

        if(biggest_corner.y() < obstacles_[i].max_corner.y())
            biggest_corner.set_y(obstacles_[i].max_corner.y());

        if(biggest_corner.x() < obstacles_[i].min_corner.x())
            biggest_corner.set_x(obstacles_[i].min_corner.x());

        if(biggest_corner.y() < obstacles_[i].min_corner.y())
            biggest_corner.set_y(obstacles_[i].min_corner.y());
    }

    check_map_limits();

    double number_of_horizontal_cells{(biggest_corner.x() - smallest_corner.x() + edges_surplus)};        
    double number_of_vertical_cells{(biggest_corner.y() - smallest_corner.y() + edges_surplus)};

    map_origin_ = Position(smallest_corner.x() - (edges_surplus / 2), smallest_corner.y() - (edges_surplus / 2));

    std::cout << "Map origin setted at: (" << map_origin_.x() << ", " << map_origin_.y() << ")" << std::endl;

    map_initialization(number_of_horizontal_cells, number_of_vertical_cells);
    // print_map();
}

// function that initialize the map with free cells and obstacles
void Map::map_initialization(const int number_of_horizontal_cells, const int number_of_vertical_cells)
{
    for(double i{0}; i < number_of_horizontal_cells; i += cell_size_) {
        vector<Cell> v;
        for(double j{0}; j < number_of_vertical_cells; j += cell_size_) {
            
            v.push_back(Cell(Position(i,j), 0.0, false));
        }
        map_.push_back(v);
    }

    int it{0};
    for(size_t i{0}; i < obstacles_.size(); i++) {

        Position smallest_corner_local_coordinates{((obstacles_[i].min_corner.x() - map_origin_.x()) / cell_size_), ((obstacles_[i].min_corner.y() - map_origin_.y()) / cell_size_)};
        Position bigger_corner_local_coordinates{((obstacles_[i].max_corner.x() - map_origin_.x()) / cell_size_), ((obstacles_[i].max_corner.y() - map_origin_.y()) / cell_size_)};
        
        for(double j{smallest_corner_local_coordinates.x()}; j <= bigger_corner_local_coordinates.x(); j += cell_size_) {

            for(double k{smallest_corner_local_coordinates.y()}; k <= bigger_corner_local_coordinates.y(); k += cell_size_) {

                map_[j][k].set_obstacles_to_cells();
                obstacle_positions_.push_back(Position(map_[j][k].coordinates().x(),map_[j][k].coordinates().y()));
                it++;

                }

        }

    }

    check_start_and_goal_position();

    // to see the new coordinates after the translation
    for(auto& it : robot_start_positions_) {

        it.set_x(it.x() - map_origin_.x());
        it.set_y(it.y() - map_origin_.y());
        map_[it.x()][it.y()].set_obstacles_to_cells();
        obstacle_positions_.push_back(it);

    }

    for( auto& it : goal_positions_) {

        it.set_x(it.x() - map_origin_.x());
        it.set_y(it.y() - map_origin_.y());

    }
}

// to verify if a start position or a goal position is inside an obstacle
void Map::check_start_and_goal_position()
{
    // because robots can't spawn inside an obstacle
    for(auto &it : robot_start_positions_) {

        if(!map_[(it.x() - map_origin_.x()) / cell_size_][(it.y() - map_origin_.y()) / cell_size_].is_obstacle()) {
        }
        else {
            std::cerr << "Map(): invalid map. \n" << "Robot start position is inside an obstacle." << std::endl;
            exit(EXIT_FAILURE);
        }

    }
    
    // because a goals can't be inside an obstacle
    for(auto &it : goal_positions_) {

        if(!map_[(it.x() - map_origin_.x()) / cell_size_][(it.y() - map_origin_.y()) / cell_size_].is_obstacle()) {
        }
        else {
            std::cerr << "Map(): invalid map. \n" << "Goal position is inside an obstacle." << std::endl;
            exit(EXIT_FAILURE);
        }

    }

}

// function used to print the map
void Map::print_map() 
{
    // for(size_t i{0}; i < map_.size(); i++) {
    //     for(size_t j{0}; j < map_[i].size(); j++) {
    //         std::cout <<  map_[i][j].is_obstacle() << " ";
    //     }
    //     std::cout << std::endl;
    // }

    for(auto& rows : map_) {
        for(auto& cols : rows) {
            if(cols.is_obstacle())
                std::cout << "X";

    //         // it's temporary
            else if((cols.coordinates().x() == robot_start_positions_.at(0).x()) && (cols.coordinates().y() == robot_start_positions_.at(0).y()))
                std::cout << "R";
            else if((cols.coordinates().x() == goal_positions_.at(0).x()) && (cols.coordinates().y() == goal_positions_.at(0).y()))
                std::cout << "G";
            else if((cols.coordinates().x() == robot_start_positions_.at(1).x()) && (cols.coordinates().y() == robot_start_positions_.at(1).y()))
                std::cout << "R";
            else if((cols.coordinates().x() == goal_positions_.at(1).x()) && (cols.coordinates().y() == goal_positions_.at(1).y()))
                std::cout << "G";
            // else if((cols.coordinates().x() == robot_start_positions_.at(2).x()) && (cols.coordinates().y() == robot_start_positions_.at(2).y()))
            //     std::cout << "R";
            else if((cols.coordinates().x() == goal_positions_.at(2).x()) && (cols.coordinates().y() == goal_positions_.at(2).y()))
                std::cout << "G";
            // else if((cols.coordinates().x() == robot_start_positions_.at(3).x()) && (cols.coordinates().y() == robot_start_positions_.at(3).y()))
            //     std::cout << "R";
            else if((cols.coordinates().x() == goal_positions_.at(3).x()) && (cols.coordinates().y() == goal_positions_.at(3).y()))
                std::cout << "G";
            else    
                std::cout << "-";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

// function that set is_obstacles_ to true
void Cell::set_obstacles_to_cells()
{
    is_obstacle_= true;
}

// function that set is_obstacle_ to false
void Cell::set_cells_free()
{
    is_obstacle_ = false;
}

// function that update the new robot position after its movement
Position Map::change_robot_position(const int robot_id, const Position& new_position)
{
    for(size_t i{0}; i < robot_start_positions_.size(); i++) {

        if(static_cast<int>(i) == robot_id) {
            map_[robot_start_positions_.at(i).x()][robot_start_positions_.at(i).y()].set_cells_free();
            for(size_t it{0}; it < obstacle_positions_.size(); it++) {

                if( (obstacle_positions_.at(it).x() == robot_start_positions_.at(i).x()) && (obstacle_positions_.at(it).y() == robot_start_positions_.at(i).y()) )
                    obstacle_positions_.erase(obstacle_positions_.begin() + (it - 1));

            }
        
            robot_start_positions_.at(i).set_x(new_position.x());
            robot_start_positions_.at(i).set_y(new_position.y());
            map_[robot_start_positions_.at(i).x()][robot_start_positions_.at(i).y()].set_obstacles_to_cells();
            obstacle_positions_.push_back(robot_start_positions_.at(i));
        }

    }

    return new_position;
}

// operator used to compare Position
bool operator<(const Position& p1, const Position& p2)
{
	return (p1.x() < p2.x() && p1.y() < p2.y());
}


// *******************************************************************
// ***************************  POTENTIAL  ***************************
// *******************************************************************

// function to set the potential of a cell
double Cell::set_potential(const double potential)
{
    potential_ = potential;

    return potential_;
}

// function to calculate the potential of a cell and set it
double Cell::potential_calculation(const Position& goal_position, const vector<Position>& obstacles_position, const double max_influence_distance)
{
    double distance{distance_calculation(coordinates(), goal_position)};

    // attractive field
    double attractive_field{0.5 * zeta * pow(distance,2)};

    // repulsive field
    distance = distance_calculation(coordinates(),obstacles_position.at(0));
    
    for(size_t i{0}; i < obstacles_position.size(); i++) {

        double provv_distance = distance_calculation(coordinates(),obstacles_position.at(i));
        if(provv_distance < distance) {
            distance = provv_distance;
        }

    }
        
    double repulsive_field{0.0};
    if(distance > max_influence_distance) {
        repulsive_field = 0.0;
    } else {
        repulsive_field = (0.5 * eta * pow(((1 / distance) - (1 / max_influence_distance)),2));
    }

    double total_field = attractive_field + repulsive_field;

    set_potential(attractive_field + repulsive_field);

    return total_field;
}

double Cell::distance_calculation(const Position& p1, const Position& p2)
{
    double var1{p2.x() - p1.x()};
    double var2{p2.y() - p1.y()};
    double dist{sqrt((var1 * var1) + (var2 * var2))};

    return dist;
}