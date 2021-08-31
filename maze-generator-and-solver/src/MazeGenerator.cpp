#include <iostream>						//Console in out
#include <vector>						
#include <cstdlib>						//Random no gen
#include <ctime>						//Seed time to random no gen to get completely random no
#include <fstream>						//file in out
#include <chrono>                       //to measure code execution time

#define DOWN 2
#define RIGHT 4
#define LEFT 6
#define UP 8

/*As we are dealing with dynamic maze generation 
  for ease of work we use vector */
std::vector<int> rows;
std::vector<int> cols;
std::vector<int> dirs;

/* Assumption was taken as, 1 as Wall 
   and 0 as Freespace */

/*Using a struct to mark and store starting 
 and ending cells coordinate easily */
struct Cell{
    int x;
    int y;
};

/*Generate maze with all 1s as
  printing takes more time
  than assiging value firstly we
  assign value to cells and lastly
  we print them */
void genrateMaze(char **maze, int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            maze[i][j] = '1';
        }
    }
}

void push(int x, int y, int direct){
    rows.push_back(x);
    cols.push_back(y);
    dirs.push_back(direct);
}

int countNoOfWall(int x, int y, int sizeW){//Calculate the number of walls around the current position
    int wallCount = 0;
    if(x + 1 <= sizeW){							//chk down
        push(x + 1, y, DOWN);
        wallCount++;
    } 
    if(y + 1 <= sizeW){							//chk right
        push(x, y + 1, RIGHT);
        wallCount++;
    } 
    if(x - 1 >= 1){								//chk up
        push(x - 1, y, UP);
        wallCount++;
    } 
    if(y - 1 >= 1){								//chk left
        push(x, y - 1, LEFT);
        wallCount++;
    } 
    return wallCount;
}

void saveMaze(char **maze, int size){
	std::ofstream file;
	file.open("../maze/SquaredMaze.txt");
	
	file << size << "\n";
	
	for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
        	if(i == 0 || i == size - 1){
        		file << 1 << " ";
        		std::cout << 1 << " ";
        		continue;
			}
			if(j == 0 || j == size - 1){
				file << 1 << " ";
				std::cout << 1 << " ";
				continue;
			}
			file << maze[i][j] << " ";
			std::cout << maze[i][j] << " ";
        }
        file << "\n";
        std::cout << "\n";
    }
}

int main(){
	srand((unsigned)time(0));
	Cell start, current ,end;
    
    //SAY BORDER WILL BE PLACED
    
    int size;
    std::cout << "Example : Size : 2 \n 1 1 1 1\n 1 A 0 1\n 1 0 B 1\n 1 1 1 1\n";
    std::cout << "\n..Border Will be automatically added.. Type parameter SIZE as given above ..\n";
    
    do{
    	std::cout << " Enter Size of maze (> 1): ";
    	std::cin >> size;
	}while(size < 2);
    
    
    /* Always starting point will be on first row
       and ending point will be on last row (for making
	   compilciated)*/
    
    start.x = 1;													//Starting
    start.y = rand() % size + 1;									//			Cell
    
    current.x = start.x;
    current.y = start.y;
    
    end.x = size;												//Ending 
    end.y = rand() % size + 1;										//			Cell
    
    char **maze = new char*[size + 2];
    for(int i = 0; i < size + 2; ++i) {
        maze[i] = new char[size + 2];
    }
    
    genrateMaze(maze, size + 2);
    
    countNoOfWall(current.x, current.y, size);
    
    //time taken
    maze[start.x][start.y] = 0;
    auto gridGenStart = std::chrono::high_resolution_clock::now();		//Maze gen start
	        
    while(rows.size()){
        int num = rows.size();
        int randNo = rand() % num;							//Gen random no b/w 0 - num

        switch(dirs[randNo]){
            case DOWN :
                current.x = rows[randNo] + 1;
                current.y = cols[randNo];
                break;
            case RIGHT:
                current.x = rows[randNo];
                current.y = cols[randNo] + 1;
                break;  
            case LEFT:
                current.x = rows[randNo];
                current.y = cols[randNo] - 1;
                break;
            case UP:
                current.x = rows[randNo] - 1;
                current.y = cols[randNo];
                break;
        }
        
        if(maze[current.x][current.y] == '1'){				//chk wall
            maze[rows[randNo]][cols[randNo]] = '0';			//go 
            maze[current.x][current.y] = '0';					//		through
            countNoOfWall(current.x, current.y, size);		//push no of walls around now to vect
        }         
        
		//dlt data for alreayd generated path
        rows.erase(rows.begin() + randNo);
		cols.erase(cols.begin() + randNo);
        dirs.erase(dirs.begin() + randNo);
    }
    auto gridGenStop = std::chrono::high_resolution_clock::now();		//Maze gen end
    
    maze[start.x][start.y] = 'A';
	maze[end.x][end.y] = 'B';
    
    saveMaze(maze, size + 2);								//save to file
    std::cout << "\nMaze Generated and saved to \"SquaredMaze.txt\" file\n";
    std::cout << "Time Taken " << std::chrono::duration_cast<std::chrono::microseconds>(gridGenStop - gridGenStart).count() << " microseconds\n";
    return 0;
}
