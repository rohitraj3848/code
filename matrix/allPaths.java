import java.util.*;
//find all path from first element to last
public class allPaths {
    public static void main(String args[]){
        int[][] mat =
		{
			{ 1, 2, 3 ,11 },
			{ 4, 5, 6 ,34},
			{ 7, 8, 9 ,77}
        };
        Stack<Integer> path=new Stack<Integer>();
        
        find(mat, path, 0, 0,mat.length,mat[0].length);
    }
        

    static void find(int[][] mat,Stack<Integer> path,int i,int j,int M,int N){
        if(i==M-1 && j==N-1){
            path.push(mat[i][j]);
            System.out.println(path);
            path.pop();
            return;
        }
        path.push(mat[i][j]);
        if(j+1<N){
            find(mat, path, i, j+1,M,N);
        }
        if(i+1<M){
            find(mat, path, i+1, j,M,N);
        }
        path.pop();

    }


}
