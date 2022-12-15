cmake_minimum_required( VERSION 3.22.1 )

project( "Robots and Mars"
	 VERSION 0.1
	 LANGUAGES CXX
	 DESCRIPTION "PSE's assegnment nov-dic 2022"
	 )

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(TARGET_GROUP test CACHE STRING "Gruppo di sorgenti da compilare")

add_subdirectory(libs)

if(TARGET_GROUP STREQUAL stable)
	add_subdirectory(app)
elseif(TARGET_GROUP STREQUAL test)
	#include(CTest)
	set(dati "${CMAKE_CURRENT_SOURCE_DIR}/data")
	add_subdirectory(test)
	#add_subdirectory(external/Unity)
else()
	message(FATAL_ERROR " TARGET_GROUP sconosciuto")
endif() 
