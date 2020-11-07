import java.util.*;
public class robotInGrid {
    public static void main(String[] args) {
        int[][] matrix={
            {0,1,1,0},
            {0,0,1,1},
            {1,0,1,0},
            {1,0,0,0}

        };
        List<point> points=findPath(matrix);
        for(int i=0;i<points.size();i++){
            System.out.println("[ "+points.get(i).x+" , "+points.get(i).y+" ] ");
        }
        System.out.println();
    }
    static List<point> findPath(int[][] matrix){
        List<point> path=new ArrayList<>();
        Set<point> failedpoints=new HashSet<>();
        if(hasPath(matrix,matrix.length-1,matrix[0].length-1,path,failedpoints)){
            return path;
        }
        return null;
    }
    static boolean hasPath(int[][] matrix,int r,int c,List<point> path,Set<point> failPoints){
        if(r<0 || c <0 || matrix[r][c]==1){
            return false;
        }
        point p=new point(r,c);
        if(failPoints.contains(p)){
            return false;
        }
        boolean isatorigin= (r==0 && c==0);
        if(isatorigin || hasPath(matrix, r-1, c, path, failPoints) || hasPath(matrix, r, c-1, path, failPoints)){
            path.add(p);
            return true;
        }
        failPoints.add(p);
        return false;
    }
}
class point{
    int x;
    int y;
    point(int x,int y){
        this.x=x;
        this.y=y; 
   }
}
