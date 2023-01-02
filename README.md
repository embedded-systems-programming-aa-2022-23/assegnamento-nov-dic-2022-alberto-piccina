# assegnamento-nov-dic-2022-alberto-piccina
assegnamento-nov-dic-2022-alberto-piccina created by GitHub Classroom

# Introduction
With this code it's possible to simulate a robot's fleet that find and reach a bunch of goals.
For more information, read the PDF file of the assignment.

  [2022_Inverno_v3.pdf](https://github.com/embedded-systems-programming-aa-2022-23/assegnamento-nov-dic-2022-alberto-piccina/files/10333724/2022_Inverno_v3.pdf)

To test the final code, you must move to the secondary branch named "Ros2-implementation". Here the list of commands to use:

    git clone https://github.com/embedded-systems-programming-aa-2022-23/assegnamento-nov-dic-2022-alberto-piccina.git
    
    cd assegnamento-nov-dic-2022-alberto-piccina
    
    git checkout ros2-implementation
    
From now you can choose to test the mere code or to test the ros's code.

N.B. : all data about start positions, goal positions and obstacles positions can be changed modifing the file.txt inside the directory data. The coordinates must be inserted following the current format: (x,y), instead for obstacles following this format: (x_min, y_min, x_max, y_max).

# Code
    mkdir build && cd build
    
    cmake ..
    
    make
    
    cd app/
    
    ./main 1 10
    
 The last command is just an example where the first argument is the cell size and the second argument is the arbitrary parameter used to calculate the capacity of the buffer.
 
 # Ros
 After sourcing your Ros environment and building the packages, these are the command to use:
 
    cd data/
    
    ros2 launch rover_visualizer rover_launch.py
