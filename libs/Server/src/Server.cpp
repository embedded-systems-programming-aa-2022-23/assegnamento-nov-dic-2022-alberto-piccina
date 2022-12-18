// Server.cpp

#include "Server.h"

void read_from_file(const std::string& filename, vector<Position>& vector_of_position)
{

    // std::ifstream encapsulates the functionality of an 
    // input file stream as a class, is created by
    // providing a filename as its constructor argument
    std::ifstream infile{filename,std::iostream::in};

    while (!infile.eof()) {
        double x, y;
        infile >> x >> y;
        if (infile.fail() || infile.bad()) {
            std::cerr << "Error in input or eof  \n";
            break;
        }
        vector_of_position.push_back(Position(x,y));
        
        // std::cout << x << " " << y << "\n";
    }

}

void read_from_file_obstacle(const std::string& filename, vector<obstacle>& vector_of_obstacles)
{

    // std::ifstream encapsulates the functionality of an 
    // input file stream as a class, is created by
    // providing a filename as its constructor argument
    std::ifstream infile{filename,std::iostream::in};
    bool flag{true};
    obstacle temp;

    while (!infile.eof()) {
        double x1, y1, x2, y2;
        if(flag) {
            infile >> x1 >> y1;
            if (infile.fail() || infile.bad()) {
                std::cerr << "Error in input or eof  \n";
                break;
            }
            flag = !flag;
        }
        else {
            infile >> x2 >> y2;
            if (infile.fail() || infile.bad()) {
                std::cerr << "Error in input or eof  \n";
                break;
            }
            obstacle temp{.min_corner{x1, y1}, .max_corner{x2, y2}};
            vector_of_obstacles.push_back(temp);
            flag = !flag;
        }        
    }
}