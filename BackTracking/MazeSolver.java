public class MazeSolver{
	public static void main(String args[]){

	}

	public static booelan isSafe(int[][] maze,int row,int col){
		if(row>maze.length || row<0 || col <0 || col >maze[0].length || maze[row][col]==0){
			return false;
		}
		return true;
	}

	public static boolean solveMaze(int[][] maze,int row,int col,int[][] sol){
		if(row==maze.length-1 && col==maze[0].length-1){
			sol[row][col]=1;
			return true;
		}
		if(isSafe(maze,row,col)){
			sol[row][col]=1;

			if(solveMaze(maze,row+1,col,sol))
				return true;
			
			if(solveMaze(maze,row,col+1,sol))
				return true;

			sol[row][col]=0;
			return false;
			
		}
		return false;
	}
}