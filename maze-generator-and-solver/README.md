A simple command-line based program made for 3rd Semi module 'CO2201 Data Structure and Algorithm' using c++.

Maze generated using **randomized DFS(Depth First Search)**, to make sure that there is only one path leads to destination. Maze will be generated and saved into 'SquaredMaze.txt' file. And Maze solved using **Backtracking** algorithm. Maze solver will take text file as input, solve the maze and outputs 'SquaredMazeSolved.txt' file. As there are n^2 cells, from each cell there are 3 unvisited neighbouring cells. So, the time complexity for solving maze using this algorithm is, **O(3^(n^2)). --Text files will be saved to 'maze' folder. 

*Starting point is denoted as 'A'
*Destination is denoted as 'B'
*Mazer border is marked as '1' and free space is marked as '0'
*Shortest valid path is shown by '#'  
