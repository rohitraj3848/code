import java.util.Arrays;

public class RotateBy90 {
    public static void main(String[] args) {
        int[][] mat =
		{
			{ 1, 2, 3},
			{ 5, 6, 7 },
			{ 9, 10, 11 }
        };
        rotate(mat);
        for(var r : mat){
            System.out.println(Arrays.toString(r));
        }
    }
    static void rotate(int[][] mat){
        int N=mat.length;
        for(int i=0;i<N;i++){
            for(int j=0;j<i;j++){
                int temp=mat[i][j];
                mat[i][j]=mat[j][i];
                mat[j][i]=temp;
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N/2;j++){
                int temp=mat[i][j];
                mat[i][j]=mat[i][N-j-1];
                mat[i][N-j-1]=temp;
            }
        }
    }
}