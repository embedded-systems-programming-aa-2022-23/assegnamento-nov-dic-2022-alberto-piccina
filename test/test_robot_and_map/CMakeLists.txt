cmake_minimum_required( VERSION 3.22.1 )

project( test_robot_and_map
	VERSION 0.1
	LANGUAGES CXX
	DESCRIPTION "Testing Robot and Map implementation"
	)

add_executable( test_robot_and_map test_robot_and_map.cpp )

add_custom_command(TARGET test_robot_and_map POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
		"${dati}/start_robots_coordinates.txt"   # <--this is in-file
		"${dati}/goals_coordinates.txt"
		"${dati}/obstacles_coordinates.txt"
        $<TARGET_FILE_DIR:test_robot_and_map>)                 # <--this is out-file path

target_link_libraries( test_robot_and_map
	PRIVATE
	lib::Robot
    lib::Map
)