// Map.cpp

#include "Map.h"

const int edges_surplus{10}; // in order to create a gap between obstacles and map's edges

// *************************************************************
// ***************************  MAP  ***************************
// *************************************************************

// Position's constructor
Position::Position(int x, int y)
        :x_{x}, y_{y}
{
    if(x_< 0 || y_< 0) {
        std::cerr << "Position(): invalid position.\n" << "Position can't be < 0." << std::endl;
        exit(EXIT_FAILURE);
    }
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
int Position::set_x(int x)
{
    x_ = x;
    return x_;
}

// function that set y_ value
int Position::set_y(int y)
{
    y_ = y;
    return y;
}

Position Cell::set_coordinates(Position point)
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

// Map's constructor
Map::Map(Position robot_start_position, Position goal_position, vector<obstacle> vector_obstacle)
        :robot_start_position_{robot_start_position}, goal_position_{goal_position}, obstacles_{vector_obstacle}
{
    smallest_corner=obstacles_[0].min_corner;
    biggest_corner=obstacles_[0].max_corner;

    for(size_t i{0}; i < obstacles_.size(); i++) {
        if(obstacles_[i].min_corner < smallest_corner)
            smallest_corner = obstacles_[i].min_corner;
        if(biggest_corner < obstacles_[i].max_corner)
            biggest_corner = obstacles_[i].max_corner;
    }

    // std::cout << "Obstacles:\n\tsmallest corner: (" << smallest_corner.x() << ", " << smallest_corner.y() << ")"
    //                 <<"\n\tbigger corner: (" << biggest_corner.x() << ", " << biggest_corner.y() << ")" << std::endl;

    if(start_goal_position_check()) {
        int cell_size{1};
        int number_of_horizontal_cells{(biggest_corner.x() - smallest_corner.x() + edges_surplus) / cell_size};
        int number_of_vertical_cells{(biggest_corner.y() - smallest_corner.y() + edges_surplus) / cell_size};
        Position map_origin{smallest_corner.x() - (edges_surplus / 2), smallest_corner.y() - (edges_surplus / 2)};

        std::cout << "Map origin setted at: (" << map_origin.x() << ", " << map_origin.y() << ")" << std::endl;
        std::cout << "Number of horizontal cells: " << number_of_horizontal_cells << std::endl;
        std::cout << "Number of vertical cells: " << number_of_vertical_cells << std::endl;

        map_initialization(map_origin, number_of_horizontal_cells, number_of_vertical_cells);
        // print_map();
    }
    else {
        std::cerr << "Map(): invalid map. \n" << "Robot start position or goal position are outside the edges." << std::endl;
        exit(EXIT_FAILURE);
    }
}

// function that initialize the map with free cells and obstacles
void Map::map_initialization(Position map_origin, int number_of_horizontal_cells, int number_of_vertical_cells)
{
    for(int i{0}; i < number_of_horizontal_cells; i++) {
        vector<Cell> v;
        for(int j{0}; j < number_of_vertical_cells; j++) {
            
            v.push_back(Cell(Position(i,j), 0.0, false));
        }
        map_.push_back(v);
    }

    int it{0};
    for(size_t i{0}; i < obstacles_.size(); i++) {
        Position smallest_corner_local_coordinates{(obstacles_[i].min_corner.x() - map_origin.x()), (obstacles_[i].min_corner.y() - map_origin.y())};
        Position bigger_corner_local_coordinates{(obstacles_[i].max_corner.x() - map_origin.x()), (obstacles_[i].max_corner.y() - map_origin.y())};

        // std::cout << "small corner: " << smallest_corner_local_coordinates.x() << "," << smallest_corner_local_coordinates.y() << std::endl;
        // std::cout << "big corner: " << bigger_corner_local_coordinates.x() << "," << bigger_corner_local_coordinates.y() << std::endl;
        
        for(int j{smallest_corner_local_coordinates.x()}; j <= bigger_corner_local_coordinates.x(); j++) {
            for(int k{smallest_corner_local_coordinates.y()}; k <= bigger_corner_local_coordinates.y(); k++) {
                map_[j][k].set_obstacles_to_cells();
                obstacle_positions_.push_back(Position(map_[j][k].coordinates().x(),map_[j][k].coordinates().y()));
                it++;
                // std::cout << "it = " << it << std::endl;            
                }
        }

        map_[robot_start_position_.x() - map_origin.x()][robot_start_position_.y() - map_origin.y()].set_obstacles_to_cells();
        map_[goal_position().x() - map_origin.x()][goal_position().y() - map_origin.y()].set_obstacles_to_cells();
    }
}

// function used to print the map
void Map::print_map() 
{
    for(size_t i{0}; i < map_.size(); i++) {
        for(size_t j{0}; j < map_[i].size(); j++) {
            std::cout <<  map_[i][j].is_obstacle() << " ";
        }
        std::cout << std::endl;
    }

    for(size_t i{0}; i < map_.size(); i++) {
        for(size_t j{0}; j < map_[i].size(); j++) {
            std::cout << "(" <<  map_[i][j].coordinates().x() << "," << map_[i][j].coordinates().y() << ")";
        }
        std::cout << std::endl;
    }
}

// function to check if robot_start_position_ and goal_position_ are inside the map's edges
bool Map::start_goal_position_check()
{
    if((robot_start_position_ < biggest_corner) && (smallest_corner < robot_start_position_) && (goal_position_ < biggest_corner) && (smallest_corner < goal_position_)) {
        return true;
    }
    else if((robot_start_position_ < smallest_corner) || (biggest_corner < goal_position_)) {
        if(robot_start_position_ < smallest_corner) {
            smallest_corner.set_x(robot_start_position_.x());
            smallest_corner.set_y(robot_start_position_.y());
        }
        if(biggest_corner < goal_position_) {
            biggest_corner.set_x(goal_position_.x());
            biggest_corner.set_y(goal_position_.y());
        }
        return true;
    }
    else {
        std::cerr << "Map(): invalid map.\n" << "Robot start position or goal position are outside the edges." << std::endl;
        exit(EXIT_FAILURE);
    }
}

// function that set not_obstacles_ to true
void Cell::set_obstacles_to_cells()
{
    is_obstacle_= true;
}

// operator used to compare Position
bool operator<(const Position& p1, const Position& p2)
{
	return (p1.x() < p2.x() && p1.y() < p2.y());
}


// *******************************************************************
// ***************************  POTENTIAL  ***************************
// *******************************************************************

const float zeta{2.0};
const float eta{2.0};

double Cell::set_potential(double potential)
{
    potential_ = potential;

    return potential_;
}

double Cell::potential_calculation(Position goal_position, vector<Position> obstacles_position, double max_influence_distance)

{
    // distance calculation
    // std::cout << "\nCurrent pos: (" << coordinates().x() << "," << coordinates().y() << ")" << std::endl;
    // std::cout << "Current potential: " << potential() << std::endl;
    // std::cout << "goal: (" << goal_position.x() << "," << goal_position.y() << ")" << std::endl;

    double distance{distance_calculation(coordinates(), goal_position)};
    // std::cout << "Distance between this cell and goal position: " << distance << std::endl;

    // attractive field
    double attractive_field{0.5 * zeta * pow(distance,2)};
    // std::cout << "The attractive field in this cell is about " << attractive_field << std::endl;

    // repulsive field
    distance = distance_calculation(coordinates(),obstacles_position.at(0));
    
    for(size_t i{1}; i < obstacles_position.size(); i++) {
        double provv_distance = distance_calculation(coordinates(),obstacles_position.at(i));
        // std::cout << "provv_dist: " << provv_distance << " obstacle: (" << obstacles_position.at(i).x() << "," << obstacles_position.at(i).y() << ")" << std::endl;
        if(provv_distance < distance)
            distance = provv_distance;
    }
    
    // std::cout << "min_dist: " << distance << std::endl;
    
    double repulsive_field{0.0};
    if(distance > max_influence_distance) {
        repulsive_field = 0.0;
    } else {
        repulsive_field = (0.5 * eta * pow(((1 / distance) - (1 / max_influence_distance)),2));
    }

    // std::cout << "The repulsive field of this cell is about " << repulsive_field << std::endl;

    double total_field = attractive_field + repulsive_field;
    // std::cout << "The total field of this cell is about " << total_field << std::endl;

    set_potential(attractive_field + repulsive_field);
    // potential_ = total_field;
    // std::cout << "Current potential: " << potential() << std::endl;

    return total_field;
}

double Cell::distance_calculation(Position p1, Position p2)
{
    double var1{static_cast<double>(p2.x() - p1.x())};
    double var2{static_cast<double>(p2.y() - p1.y())};
    double dist{sqrt((var1 * var1) + (var2 * var2))};

    // for output verifies
    // std::cout << "p1: (" << p1.x() << "," << p1.y() << ")" << std::endl;
    // std::cout << "p2: (" << p2.x() << "," << p2.y() << ")" << std::endl;
    // std::cout << "x-x = " << (p2.x() - p1.x()) << std::endl;
    // std::cout << "y-y = " << (p2.y() - p1.y()) << std::endl;
    // std::cout << "Dist: " << dist << std::endl;
    return dist;
}