cmake_minimum_required( VERSION 3.22.1 )

project( test_map
	VERSION 0.1
	LANGUAGES CXX
	DESCRIPTION "Testing Map class"
	)

add_executable( test_map test_map.cpp )

target_link_libraries( test_map
	PRIVATE
	lib::Map
)