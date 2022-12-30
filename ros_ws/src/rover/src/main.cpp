#include "rclcpp/rclcpp.hpp"
#include "rover/publisher.h"
#include "rover_visualizer/msg/rover_position.hpp"

rclcpp::Node::SharedPtr g_node;
rclcpp::Publisher<rover_visualizer::msg::RoverPosition>::SharedPtr g_publisher;

Server monitor;
std::mutex cout_mutex;

void producer(const int id, const vector<Position>& goals){
    for(auto& new_pos : goals) {
        monitor.position_append(new_pos);
        cout_mutex.lock();
        std::cout << "Satellite " << id << " produced (" << new_pos.x() << "," << new_pos.y() << ")" << std::endl;
        cout_mutex.unlock();
    }
}

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);

  g_node = rclcpp::Node::make_shared("rover_publisher");
  g_publisher = g_node->create_publisher<rover_visualizer::msg::RoverPosition>(
      "rover", 10);

  std::string filename_start_position{"start_robots_coordinates.txt"};
  std::string filename_goal_position_1{"goals_coordinates_satellite_1.txt"};
  std::string filename_goal_position_2{"goals_coordinates_satellite_2.txt"};
  std::string filename_obstacles{"obstacle_positions.txt"};

  vector<Position> vector_of_start_position;
  vector<obstacle> vector_of_obstacles;
  vector<Position> satellite_1;
  vector<Position> satellite_2;

  read_from_file(filename_start_position, vector_of_start_position);
  read_from_file(filename_goal_position_1, satellite_1);
  read_from_file(filename_goal_position_2, satellite_2);
  read_from_file_obstacle(filename_obstacles, vector_of_obstacles);

  int k_parameter{3};
  monitor.update_queue(vector_of_start_position.size(), k_parameter);

  vector<Position> vector_of_goals;
  for(auto& it : satellite_1) {
      vector_of_goals.push_back(it);
  }
  for(auto& it : satellite_2) {
      vector_of_goals.push_back(it);
  }

  double cell_size{1};
  Map map{vector_of_start_position, vector_of_goals, vector_of_obstacles, cell_size, 5, 20};

  vector<Robot> list_of_robots;
    for(size_t i{0}; i < vector_of_start_position.size(); i++) {
        list_of_robots.push_back(Robot(map.robot_start_position().at(i), map));
    }

  std::thread satellite1(producer, 0, std::ref(satellite_1));
  std::thread satellite2(producer, 1, std::ref(satellite_2));

  vector<std::thread> rovers_threads;
  for(size_t i{0}; i < list_of_robots.size(); i++) {
        rovers_threads.push_back(std::thread(Rover(list_of_robots.at(i), monitor, i, 0.2)));
  }

  rclcpp::spin(g_node);

  satellite1.join();
  satellite2.join();
  for(auto& it : rovers_threads) {
    it.join();
  }

  // example code that spawns 2 rovers
  // auto rover0 = Rover(0, 0.2);  // Spawn a rover with id 0 and "speed" 0.4m/s
  //                               // for each axis (0.2m every 500ms)
  // auto rover1 = Rover(1, -0.2);  // Spawn a rover with id 1 and "speed" -0.4m/s
  //                                // for each axis (0.2m every 500ms)
  // rover1.setX_pos(10);  // Set rover1 x_pos to 10
  // rover1.setY_pos(8);   // Set rover1 y_pos to 8

  rclcpp::shutdown();

  exit(EXIT_SUCCESS);
}
