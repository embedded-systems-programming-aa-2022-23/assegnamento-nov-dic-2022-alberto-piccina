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

Position::Position()
        :x_{default_position().x()},
        y_{default_position().y()}
{
}

//  Cell's constructor
Cell::Cell(Position cell_coordinates, float potential, bool not_obstacle)
        :coordinates_{cell_coordinates}, potential_{potential}, not_obstacle_{not_obstacle}
{
}

// Map's constructor
Map::Map(Position robot_start_position, Position goal_position, vector<obstacle> vector_obstacle)
        :robot_start_position_{robot_start_position}, goal_position_{goal_position}, obstacles_{vector_obstacle}
{
    smallest_corner=obstacles_[0].min_corner;
    biggest_corner=obstacles_[0].max_corner;
    //smallest_corner{obstacles_[0].min_corner};
    //Position biggest_corner{obstacles_[0].max_corner};

    for(size_t i{0}; i < obstacles_.size(); i++) {
        if(obstacles_[i].min_corner < smallest_corner)
            smallest_corner = obstacles_[i].min_corner;
        if(biggest_corner < obstacles_[i].max_corner)
            biggest_corner = obstacles_[i].max_corner;
    }

    std::cout << "Obstacles:\n\tsmallest corner: (" << smallest_corner.x() << ", " << smallest_corner.y() << ")"
                    <<"\n\tbigger corner: (" << biggest_corner.x() << ", " << biggest_corner.y() << ")" << std::endl;

    if(start_goal_position_check(biggest_corner, smallest_corner)) {
        int cell_size{1};
        int number_of_horizontal_cells{(biggest_corner.x() - smallest_corner.x() + edges_surplus) / cell_size};
        int number_of_vertical_cells{(biggest_corner.y() - smallest_corner.y() + edges_surplus) / cell_size};
        Position map_origin{smallest_corner.x() - (edges_surplus / 2), smallest_corner.x() - (edges_surplus / 2)};
        //Cell map{map_generator(map_origin, number_of_horizontal_cells, number_of_vertical_cells)};

        std::cout << "Map origin setted at: (" << map_origin.x() << ", " << map_origin.y() << ")" << std::endl;
        std::cout << "Number of horizontal cells: " << number_of_horizontal_cells << std::endl;
        std::cout << "Number of vertical cells: " << number_of_vertical_cells << std::endl;
    }
    else {
        std::cerr << "Map(): invalid map. \n" << "Robot start position or goal position are outside the edges." << std::endl;
        exit(EXIT_FAILURE);
    }
}

// function to check if robot_start_position_ and goal_position_ are inside the map's edges
bool Map::start_goal_position_check(Position biggest_corner, Position smallest_corner)
{
    if((robot_start_position_ < biggest_corner) && (smallest_corner < robot_start_position_) && (goal_position_ < biggest_corner) && (smallest_corner < goal_position_)) {
        return true;
    }
    else {
        std::cerr << "Map(): invalid map.\n" << "Robot start position or goal position are outside the edges." << std::endl;
        exit(EXIT_FAILURE);
    }
}

// function to generate the map
// vector<vector<Cell>> Map::map_generator(Position map_origin, int number_of_horizontal_cells, int number_of_vertical_cells)
// {
//     vector<Cell> vect_lenght(number_of_horizontal_cells);
//     vector<vector<Cell>> matrix(number_of_vertical_cells, vect_lenght);

//     for(auto &it : obstacles_)
// }



// Cell Map::map_generator(Position map_origin, int number_of_horizontal_cells, int number_of_vertical_cells)
// {
//     Cell matrix[number_of_vertical_cells][number_of_horizontal_cells];
//     for(size_t i{0}; i < obstacles_.size(); i++) {
//         Position smallest_corner_local_coordinates{(obstacles_[i].min_corner.x() - map_origin.x()), (obstacles_[i].min_corner.y() - map_origin.y())};
//         Position bigger_corner_local_coordinates{(obstacles_[i].max_corner.x() - map_origin.x()), (obstacles_[i].max_corner.y() - map_origin.y())};
        
//         for(int j{smallest_corner_local_coordinates.y()}; j < bigger_corner_local_coordinates.y(); j++) {
//             for(int k{smallest_corner_local_coordinates.x()}; k < bigger_corner_local_coordinates.x(); k++) {
//                 matrix[j][k].set_obstacles_to_cells();
//             }
//         }
//     }

//     matrix[robot_start_position_.y()][robot_start_position_.x()].set_obstacles_to_cells();
//     matrix[goal_position_.y()][goal_position_.x()].set_obstacles_to_cells();

//     return matrix[number_of_vertical_cells][number_of_horizontal_cells];
// }

void Cell::set_obstacles_to_cells()
{
    not_obstacle_=false;
}

bool operator<(const Position& p1, const Position& p2)
{
	return (p1.x() < p2.x() && p1.y() < p2.y());
}