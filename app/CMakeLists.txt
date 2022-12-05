cmake_minimum_required( VERSION 3.22.1 )

project( main
         VERSION 0.1
         LANGUAGES 
         DESCRIPTION "" )

add_executable(main src/main.cpp)

target_include_directories(main PRIVATE include) 

#target_link_libraries( potenze_tot
#	PRIVATE 
#	lib::csv
#	lib::gnuplot_i
#	lib::estrazione_csv
#	lib::formule
#	lib::parametri
#	lib::calcolo_output
#	lib::plot
#)

