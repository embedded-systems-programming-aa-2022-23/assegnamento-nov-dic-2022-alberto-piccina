cmake_minimum_required( VERSION 3.22.1 )

project( test_robot_and_map
	VERSION 0.1
	LANGUAGES CXX
	DESCRIPTION "Testing Robot and Map implementation"
	)

add_executable( test_robot_and_map test_robot_and_map.cpp )

target_link_libraries( test_robot_and_map
	PRIVATE
	lib::Robot
    lib::Map
)