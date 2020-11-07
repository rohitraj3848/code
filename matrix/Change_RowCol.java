//change all elements of row r and col c if it contains if mat[r][c] contains 0
public class Change_RowCol {
    public static void main(String[] args) {
        int[][] mat =
		{
			{ 1, 1, 0, 1, 1 },
			{ 1, 1, 1, 1, 1 },
			{ 1, 1, 0, 1, 1 },
			{ 1, 1, 1, 1, 1 },
			{ 0, 1, 1, 1, 1 }
        };
        int M=mat.length;
        int N=mat[0].length;
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                if(mat[i][j]==0){
                    change(mat, M, N, i, j);
                }
            }
        }
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                if(mat[i][j]==-1){
                    mat[i][j]=0;
                }
            }
        }
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                System.out.print(mat[i][j]+" ");
            }
            System.out.println();
        }
        

    }
    static  void change(int[][] mat,int M,int N,int x,int y){
        for(int i=0;i<N;i++){
            if(mat[x][i]!=0){
                mat[x][i]=-1;
            }
        }
        for(int i=0;i<M;i++){
            if(mat[i][y]!=0){
                mat[i][y]=-1;
            }
        }
    }
}
