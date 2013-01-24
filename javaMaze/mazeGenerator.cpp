#include <iostream>
#include <cstdlib>
#include <stack>
#include <ctime>
#include <fstream>

#define NORTH	0
#define SOUTH	1
#define EAST	2
#define WEST	3
#define SIZEX  10
#define SIZEY  10

using namespace std;

void printGrid(char grid[SIZEY][SIZEX]){
     ofstream foutput ("MAZE.txt");
	for (int i = 0; i < SIZEY; i++){
		for(int j = 0; j < SIZEX; j++){
			foutput << grid[i][j];
		}
		foutput << endl;
	}
}

int moveEW(int direction, int x){
        if (direction == EAST)
                return x + 1;
        else if (direction == WEST)
                return x - 1;
        else
                return x;
}

int moveNS(int direction, int y){
        if (direction == NORTH)
                return y - 1;
        else if (direction == SOUTH)
                return y + 1;
        else
                return y;
}

bool isGood(int x, int y, int direction, char grid[SIZEY][SIZEX]){
	x = moveEW(direction,x);
	y = moveNS(direction,y);

	if (grid[y][x] == '.' || x >= (SIZEX - 1) || x <= 0 || y <= 0 || y >= (SIZEY - 1)){
		return false;
	}

	// check cardinal directions
	if (direction == NORTH){
		if (grid[y][x-1] != '.' &&  grid[y-1][x] != '.' && grid[y][x+1] != '.' && grid[y-1][x-1] != '.' && grid[y-1][x+1] != '.'){
			return true;
		}
	}
	if (direction == SOUTH){
                if (grid[y][x-1] != '.' &&  grid[y+1][x] != '.' && grid[y][x+1] != '.' && grid[y+1][x-1] != '.' && grid[y+1][x+1] != '.'){
                        return true;
                }
        }
	if (direction == EAST){
                if (grid[y][x+1] != '.' &&  grid[y-1][x] != '.' && grid[y+1][x] != '.' && grid[y-1][x+1] != '.' && grid[y+1][x+1] != '.'){
                        return true;
                }
        }
	if (direction == WEST){
                if (grid[y][x-1] != '.' &&  grid[y-1][x] != '.' && grid[y+1][x] != '.' && grid[y-1][x-1] != '.' && grid[y+1][x-1] != '.'){
                        return true;
                }
        }
	return false;
}

main(){
	char grid[SIZEY][SIZEX];

	// init grid
	for (int i = 0; i < SIZEY; i++){
                for(int j = 0; j < SIZEX; j++){
                        grid[i][j] = '#';
                }
        }

	//init rand
	srand(time(0));

	//init stacks for xy coords
	stack<int> xValues;
	stack<int> yValues;

	int direction = 0, nGood = 0, locX = 1, locY = 1;

	do{
		//find n good moves
		for (int i = 0; i < 4; i++){
			if (isGood(locX,locY,i,grid))
				nGood++;
		}

		// if no good moves, move back in stack
		if (nGood == 0){
			locX = xValues.top();
			locY = yValues.top();
			xValues.pop();
			yValues.pop();
		}

		//if more than 0 good moves, push stack
		else{
			xValues.push(locX);
			yValues.push(locY);

			//direction to move randomly chosen
			do{
				direction = rand() % 4;
			}while (!isGood(locX,locY,direction,grid));

			locX = moveEW(direction,locX);
			locY = moveNS(direction,locY);
		}

		// set grid
		grid[locY][locX] = '.';
		//reset nGood value
                nGood = 0;
	}while(!xValues.empty());
     //Create Start and end
     grid[1][1] = 'S';
     grid[SIZEX-2][SIZEY-2] = 'G';
     
	//final maze output
	printGrid(grid);

     //system("pause");
	return 0;
}
