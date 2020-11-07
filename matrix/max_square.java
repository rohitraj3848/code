//find max square of 1s
public class max_square {
    public static void main(String[] args) {
        int mat[][] =
		{
			{ 0, 0, 1, 0, 1, 1 },
			{ 0, 1, 1, 1, 0, 0 },
			{ 0, 0, 1, 1, 1, 1 },
			{ 1, 1, 0, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 0, 1, 1, 1 },
			{ 1, 0, 1, 1, 1, 1 },
			{ 1, 1, 1, 0, 1, 1 }
        };
        System.out.println(maxsquare(mat));
        
    }
    static int maxsquare(int[][] mat){
        int m=mat.length;
        int n=mat[0].length;
        int max=0;
        int[][] T=new int[m][n];
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                T[i][j]=mat[i][j];
                if(i>0 && j>0 && mat[i][j]==1){
                    T[i][j]=Math.min(T[i-1][j-1],Math.min(T[i-1][j],T[i][j-1]))+1;
                }
                if(max < T[i][j]){
                    max=T[i][j];
                }
            }
        }
        return max;
    }


}
