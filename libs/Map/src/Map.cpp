// Map.cpp

#include "Map.h"

const int edges_surplus{10}; // in order to create a gap between obstacles and map's edges

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
Cell::Cell(Position coordinates, float potential, bool not_obstacle)
        :coordinates_{coordinates}, potential_{potential}, not_obstacle_{not_obstacle}
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

    std::cout << "Obstacles:\n\tsmallest corner: (" << smallest_corner.x() << ", " << smallest_corner.y() << ")"
                    <<"\n\tbigger corner: (" << biggest_corner.x() << ", " << biggest_corner.y() << ")" << std::endl;

    if(start_goal_position_check()) {
        int cell_size{1};
        int number_of_horizontal_cells{(biggest_corner.x() - smallest_corner.x() + edges_surplus) / cell_size};
        int number_of_vertical_cells{(biggest_corner.y() - smallest_corner.y() + edges_surplus) / cell_size};
        Position map_origin{smallest_corner.x() - (edges_surplus / 2), smallest_corner.y() - (edges_surplus / 2)};

        std::cout << "Map origin setted at: (" << map_origin.x() << ", " << map_origin.y() << ")" << std::endl;
        std::cout << "Number of horizontal cells: " << number_of_horizontal_cells << std::endl;
        std::cout << "Number of vertical cells: " << number_of_vertical_cells << std::endl;

        map_initialization(map_origin, number_of_horizontal_cells, number_of_vertical_cells);
        print_map();
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

    for(size_t i{0}; i < obstacles_.size(); i++) {
        Position smallest_corner_local_coordinates{(obstacles_[i].min_corner.x() - map_origin.x()), (obstacles_[i].min_corner.y() - map_origin.y())};
        Position bigger_corner_local_coordinates{(obstacles_[i].max_corner.x() - map_origin.x()), (obstacles_[i].max_corner.y() - map_origin.y())};

        std::cout << "small corner: " << smallest_corner_local_coordinates.x() << "," << smallest_corner_local_coordinates.y() << std::endl;
        std::cout << "big corner: " << bigger_corner_local_coordinates.x() << "," << bigger_corner_local_coordinates.y() << std::endl;
        
        for(int j{smallest_corner_local_coordinates.x()}; j <= bigger_corner_local_coordinates.x(); j++) {
            for(int k{smallest_corner_local_coordinates.y()}; k <= bigger_corner_local_coordinates.y(); k++) {
                map_[j][k].set_obstacles_to_cells();
            }
        }
    }
}

// function used to print the map
void Map::print_map() 
{
    for(size_t i{0}; i < map_.size(); i++) {
        for(size_t j{0}; j < map_[i].size(); j++) {
            std::cout <<  map_[i][j].not_obstacle() << " ";
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
    not_obstacle_= true;
}

// operator used to compare Position
bool operator<(const Position& p1, const Position& p2)
{
	return (p1.x() < p2.x() && p1.y() < p2.y());
}