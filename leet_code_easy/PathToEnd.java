class PathToEnd {
    public static void main(String args[]){
        int[][] grid={{2,4,3},{6,5,2}};
        System.out.println(hasValidPath(grid));
    }
    static boolean isValid(int x,int y,int[][] grid,int[][] visited){
        if(x<0 || y<0 || x>grid.length-1 || y>grid[0].length-1 || visited[x][y]==1){
            return false;
        }
        return true;
    }
    public static boolean hasValidPath(int[][] grid) {
        int lastrow=grid.length-1;
        int lastcol=grid[0].length-1;
        int x=0;
        int y=0;
        int[][] visited=new int[lastrow+1][lastcol+1];
        while(isValid(x,y,grid,visited)){
            if(grid[x][y]==1){
                if(isValid(x,y+1,grid,visited)&&(grid[x][y+1]==1 || grid[x][y+1]==3 || grid[x][y+1]==5)){
                        visited[x][y]=1;
                        y+=1;
                }
                else if(isValid(x,y-1,grid,visited)&&(grid[x][y-1]==1 || grid[x][y-1]==6 || grid[x][y-1]==4)){
                        visited[x][y]=1;
                        y-=1;
                }
                else{
                    break;
                }
            }
            else if(grid[x][y]==2){
                if(isValid(x-1,y,grid,visited)&&(grid[x-1][y]==3 || grid[x-1][y]==4|| grid[x-1][y]==2)){
                        visited[x][y]=1;
                        x-=1;
                }
                else if(isValid(x+1,y,grid,visited)&&(grid[x+1][y]==6 || grid[x+1][y]==5 || grid[x+1][y]==2)){
                        visited[x][y]=1;
                        x+=1;
                }
                else{
                    break;
                }
            }
            else if(grid[x][y]==3){
                if(isValid(x,y-1,grid,visited)&&(grid[x][y-1]==1 || grid[x][y-1]==4 || grid[x][y-1]==6)){
                        visited[x][y]=1;
                        y-=1;
                }
                else if(isValid(x+1,y,grid,visited)&&(grid[x+1][y]==2 || grid[x+1][y]==5 ||grid[x+1][y]==6)){
                        visited[x][y]=1;
                        x+=1;
                }
                else{
                    break;
                }
            }
            else if(grid[x][y]==4){
                if(isValid(x,y+1,grid,visited)&&(grid[x][y+1]==1 || grid[x][y+1]==3 || grid[x][y+1]==5)){
                        visited[x][y]=1;
                        y+=1;
                }
                else if(isValid(x+1,y,grid,visited)&&(grid[x+1][y]==2 || grid[x+1][y]==5 || grid[x+1][y]==6)){
                        visited[x][y]=1;
                        x+=1;
                }
                else{
                    break;
                }
            }
            else if(grid[x][y]==5){
                if(isValid(x-1,y,grid,visited)&&(grid[x-1][y]==2 || grid[x-1][y]==3 || grid[x-1][y]==4)){
                        visited[x][y]=1;
                        x-=1;
                }
                else if(isValid(x,y-1,grid,visited) && (grid[x][y-1]==1 || grid[x][y-1]==4 || grid[x][y-1]==6)){
                        visited[x][y]=1;
                        y-=1;
                }
                else{
                    break;
                }
            }
            else if(grid[x][y]==6){
                if(isValid(x-1,y,grid,visited) && (grid[x-1][y]==2 || grid[x-1][y]==3 || grid[x-1][y]==4)){
                        visited[x][y]=1;
                        x-=1;
                }
                else if(isValid(x,y+1,grid,visited) && (grid[x][y+1]==1 || grid[x][y+1]==3|| grid[x][y+1]==5)){
                        visited[x][y]=1;
                        y+=1;
                }
                else{
                    break;
                }
            }
            else{
                break;
            }

        }
        if(x==lastrow && y==lastcol){
            return true;
        }
        return  false;
        
    }
   
}