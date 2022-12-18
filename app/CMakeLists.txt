cmake_minimum_required( VERSION 3.22.1 )

project( main
         VERSION 0.1
         LANGUAGES 
         DESCRIPTION "" )

add_executable(main src/main.cpp)

add_custom_command(TARGET main POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
		"${dati}/start_robots_coordinates.txt"   # <--this is in-file
		"${dati}/goals_coordinates.txt"
		"${dati}/obstacles_coordinates.txt"
        $<TARGET_FILE_DIR:main>)                 # <--this is out-file path

target_link_libraries( main
	PRIVATE
	lib::Robot
    lib::Map
)

# target_include_directories(main PRIVATE include) 

