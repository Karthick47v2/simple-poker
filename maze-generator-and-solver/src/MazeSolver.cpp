#include <iostream>						////Console in out
#include <vector>
#include <fstream>						//file in out
#include <chrono>                       //to measure code execution time

bool pathFound = false;										//To terminate when path was found

/*Using a struct to mark and store starting 
 cell coordinate easily */
struct Cell{
    int x;
    int y;
};
Cell start;
 
/* Checks whether move is valid
   or not.... As borders  and walls 
   are 1s we dont need to care about
   distinguish them ..Thats why row and 
   col borders are taken as boundary*/
bool isValidMove(int row, int col, char **maze, bool **visited, int n){
    if (row == -1 || col == -1 || row == n || col == n || visited[row][col] || maze[row][col] == '1'){
    	return false;
	}
    return true;
}
 
void findPath(auto mazeSolveStart, int row, int col, char **maze, bool **visited, std::string& path, std::vector<std::string>& botPath, int n){
    if(pathFound){									
    	return;																								//terminate if path found
	}
    if (row == -1 || col == -1 ||row == n ||  col == n || visited[row][col] || maze[row][col] == '1'){
        return;																								//return if current pos not valid pos
	}
 
	//check until path found
    if (maze[row][col] == 'B') {
    	/*As finding path finished here and printing on console
    	  takes much time we are stopping time here*/
    	auto mazeSolveStop = std::chrono::high_resolution_clock::now();		//Maze solve end 
        botPath.push_back(path);
        pathFound = true;
        
        std::ofstream file;
		file.open("../maze/SquaredMazeSolved.txt");
        
        //Print & save path
        for(int i = 0; i < n; i++){
        	for(int j = 0; j < n; j++){
        		if(i == start.x && j == start.y){
        			file << "A ";
        			std::cout << "A ";
        			continue;
				}
        		if(i == row && j == col){
        			file << "B ";
        			std::cout << "B ";
        			continue;
				}
				if(visited[i][j] == true){
					file << "# ";
					std::cout << "# ";
					continue;
				}
				file << maze[i][j]  <<" ";
        		std::cout << maze[i][j] << " " ; 
			}
			file << "\n";
			std::cout << "\n";
		}  
		std::cout << "Time Taken to solve maze : " << std::chrono::duration_cast<std::chrono::microseconds>(mazeSolveStop - mazeSolveStart).count() << "microseconds\n";      
        return;
    }
 
    // Mark cell as visited
    visited[row][col] = true;
 
    /* Check directions (in down, left,
       right, up order
	   
	   D - down
	   L - left
	   R - right
	   U - up	 
	   
	   and if valid, push it to vector &
	   recursively find path, if not valid
	   at certain point pop it and do backtracking  
	   */
 
    // Check down move valid or not
    if (isValidMove(row + 1, col, maze, visited, n)){
        path.push_back('D');
        findPath(mazeSolveStart, row + 1, col, maze, visited, path, botPath, n);
        path.pop_back();
    }
 
    // Check left move valid or not
    if (isValidMove(row, col - 1, maze, visited, n)){
        path.push_back('L');
        findPath(mazeSolveStart, row, col - 1, maze, visited, path, botPath, n);
        path.pop_back();
    }
 
    // Check right move valid or not
    if (isValidMove(row, col + 1, maze, visited, n)){
        path.push_back('R');
        findPath(mazeSolveStart, row, col + 1, maze, visited, path, botPath, n);
        path.pop_back();
    }
 
    // Check up move valid or not
    if (isValidMove(row - 1, col, maze, visited, n)){
        path.push_back('U');
        findPath(mazeSolveStart, row - 1, col, maze, visited, path, botPath, n);
        path.pop_back();
    }
 
    /* Mark cell as not visited for
     other possible paths */
    visited[row][col] = false;
}

/*As system don't know the starting
  point, first we find starting point
  using iteration and send it to maze
  solving function (findPath())*/
void findRoot(char **m, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(m[i][j] == 'A'){
				start.x = i;
				start.y = j;
				return;
			}
		}
	}
}
 
void printPath(char **maze, int n, bool **visited){
    std::vector<std::string> botPath;											// vector to store path of bot
    std::string path;
    
    findRoot(maze, n);												//find starting point
    
    auto mazeSolveStart = std::chrono::high_resolution_clock::now();		//Maze solver start
    
    findPath(mazeSolveStart, start.x, start.y, maze, visited, path, botPath, n);	//find path
}
 
int main(){
	int n = 0;
	char **maze;													//dynamically allocate
	bool **visited;															//memories for arrays
	
	/*get maze from txt file and assign it
	  to maze array and at the same time 
	  initialize visited boolean array to
	  false	*/
	std::ifstream file("../maze/SquaredMaze.txt");
    if(file.is_open()){
    	file >> n;
    	maze = new char*[n];
    	visited = new bool*[n];
    	
        for(int i = 0; i < n; i++){
        	maze[i] = new char[n];
        	visited[i] = new bool[n];
        	for(int j = 0; j < n; j++){
        		file >> maze[i][j];
        		visited[i][j] = false;
			}
        }
    }

    printPath(maze, n, visited);
    
    for(int i = 0; i < n; ++i) {									//free the
        delete[] maze[i];   					
        delete[] visited[i];												//allocated
    }
    delete[] maze;																	//dynamic 
    delete[] visited;																			//memories
 
    return 0;
}
 
