// Server.h

#ifndef Server_h
#define Server_h

#include "Robot.h"

#include <queue>
using std::queue;

#include <fstream>

void read_from_file(const std::string& filename, vector<Position>& vector_of_position);
void read_from_file_obstacle(const std::string& filename, vector<obstacle>& vector_of_obstacles);

#endif