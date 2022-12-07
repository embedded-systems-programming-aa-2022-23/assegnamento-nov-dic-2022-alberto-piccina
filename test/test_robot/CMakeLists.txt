cmake_minimum_required( VERSION 3.22.1 )

project( test_robot
	VERSION 0.1
	LANGUAGES CXX
	DESCRIPTION "Testing Robot class"
	)

add_executable( test_robot test_robot.cpp )

# target_link_libraries( test_map
# 	PRIVATE
# 	lib::Map
# )
target_link_libraries( test_robot
	PRIVATE
	lib::Robot
    lib::Map
)