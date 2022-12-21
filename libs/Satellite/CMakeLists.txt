cmake_minimum_required( VERSION 3.22.1 )

project( "Satellite's library "
	 VERSION 0.1
	 LANGUAGES CXX
	 DESCRIPTION ""
	 )
	 
add_library(Satellite
	STATIC 
	src/Satellite.cpp
	)

target_link_libraries( Satellite
	PUBLIC
	lib::Map
)

target_include_directories(Satellite PUBLIC include)

add_library(lib::Satellite ALIAS Satellite)
