cmake_minimum_required( VERSION 3.22.1 )

project( "Server's library "
	 VERSION 0.1
	 LANGUAGES CXX
	 DESCRIPTION ""
	 )
	 
add_library(Server
	STATIC 
	src/Server.cpp
	)

target_link_libraries( Server
	PUBLIC
	lib::Map
)

target_include_directories(Server PUBLIC include)

add_library(lib::Server ALIAS Server)
