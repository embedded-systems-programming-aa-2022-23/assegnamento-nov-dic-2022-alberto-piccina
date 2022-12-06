cmake_minimum_required( VERSION 3.22.1 )

project( "Robot's library "
	 VERSION 0.1
	 LANGUAGES CXX
	 DESCRIPTION ""
	 )
	 
add_library(Robot
	STATIC 
	src/Robot.cpp
	)

target_link_libraries( Robot
	PUBLIC
	lib::Map
)

target_include_directories(Robot PUBLIC include)

add_library(lib::Robot ALIAS Robot)
