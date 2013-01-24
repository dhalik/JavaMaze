import java.util.Stack;
import java.util.Random;

public class Maze{
	private int[][] grid;
	private int sizex;
	private int sizey;
	
	final int NORTH = 0;
	final int SOUTH = 1;
	final int EAST = 2;
	final int WEST = 3;
	
	private Stack xValues = new Stack();
	private Stack yValues = new Stack();
	
	public void init(){
		for (int i = 0; i < sizex; i++){
			for (int j = 0; j < sizey; j++){
				grid[i][j] = 1;
			}
		}
	}
	
	public void printGrid(){
		for (int i = 0; i < sizex; i++){
			for (int j = 0; j < sizey; j++){
                                System.out.print(grid[i][j]);
                        }
			System.out.print("\n");
                }
	}
	
	public boolean isGood(int x, int y, int direction){
		
		if (grid[y][x] == 1 || x >= (sizex - 1) || x <= 0 || y <= 0 || y >= (sizey - 1)){
			return false;
		}
		
		// check cardinal directions
		if (direction == NORTH){
			if (grid[y][x-1] != 1 &&  grid[y-1][x] != 1 && grid[y][x+1] != 1 && grid[y-1][x-1] != 1 && grid[y-1][x+1] != 1){
				return true;
			}
		}
		if (direction == SOUTH){
			if (grid[y][x-1] != 1 &&  grid[y+1][x] != 1 && grid[y][x+1] != 1 && grid[y+1][x-1] != 1 && grid[y+1][x+1] != 1){
				return true;
			}
		}
		if (direction == EAST){
			if (grid[y][x+1] != 1 &&  grid[y-1][x] != 1 && grid[y+1][x] != 1 && grid[y-1][x+1] != 1 && grid[y+1][x+1] != 1){
				return true;
			}
		}
		if (direction == WEST){
			if (grid[y][x-1] != 1 &&  grid[y-1][x] != 1 && grid[y+1][x] != 1 && grid[y-1][x-1] != 1 && grid[y+1][x-1] != 1){
				return true;
			}
		}
		return false;
	}
	
	public void createMaze(){
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

	}
	
	public Maze(int x, int y){
		grid = new int[x][y];
		sizex = x;
		sizey = y;
		init();
	}
}