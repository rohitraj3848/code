

public class WordSearch{
	public static void main(String args[]){

	}


	public static boolean Search(char[][] grid,String s){
		for(int i=0;i<grid.length;i++){
             for(int j=0;j<grid[0].length;j++){
             	if(grid[i][j]==s.charAt(0) && recSearch(grid,i,j,0,s))
             		return true;
             }
		}
		return false;
	}


	public static boolean recSearch(char[][] grid,int i,int j,int pos,String s){
		if(pos==s.length()){
			return true;
		}
		if(i<0 || i>=grid.length || j<0 || j>=grid[0].length || grid[i][j]!=s.charAt(pos)){
			return false;
		}
		char temp=grid[i][j];
		grid[i][j]=' ';
		boolean found=recSearch(grid,i+1,j,pos+1,s) || recSearch(grid,i-1,j,pos+1,s) || recSearch(grid,i,j+1,pos+1,s) || recSearch(grid,i,j-1,pos+1,s);
		grid[i][j]=temp;
		return found;
	}
}