//reach mat[m][n] consuming k cost
public class cost_path {
    
    public static void main(String[] args) {
        int[][] mat =
		{
			{ 4, 7, 1, 6 },
			{ 5, 7, 3, 9 },
			{ 3, 2, 1, 2 },
			{ 7, 1, 6, 3 }
        };
        int cost=25;
        System.out.println(checkpath(mat,mat.length-1,mat[0].length-1,cost));
    }
    static int checkpath(int mat[][],int m,int n,int cost){
        if(cost<0){
            return 0;
        }
        if(m==0 && n==0){
            return (cost-mat[m][n]==0)?1:0;
        }
        if(m==0){
            return checkpath(mat, 0, n-1, cost-mat[m][n]);
        }
        if(n==0){
            return checkpath(mat, m-1, 0, cost-mat[m][n]);
        }
        return checkpath(mat, m-1, n, cost-mat[m][n])+checkpath(mat, m, n-1, cost-mat[m][n]);
    }
}
