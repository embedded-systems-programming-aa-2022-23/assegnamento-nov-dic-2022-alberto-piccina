cmake_minimum_required( VERSION 3.22.1 )

project( "Map's library "
	 VERSION 0.1
	 LANGUAGES 
	 DESCRIPTION ""
	 )
	 
add_library(Map
	STATIC 
	src/Map.cpp
	)

#target_link_libraries( estrazione_csv
	#PUBLIC
	#lib::csv
#)

target_include_directories(Map PUBLIC include)

add_library(lib::Map ALIAS Map)
