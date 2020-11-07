import java.util.*;

public class matrixRank {
    public static void main(String args[]) {
        Scanner scan = new Scanner(System.in);
        System.out.println("input the row of matrix:");
        int r = scan.nextInt();
        System.out.println("input the column of matrix:");
        int c = scan.nextInt();
        int[][] matrix = new int[r][c];
        for (int i = 0; i < r; i++) {
            System.out.println("Input " + i + 1 + " row");
            for (int j = 0; j < c; j++) {
                matrix[i][j] = scan.nextInt();
            }
        }
        int result=solution(matrix, r, c);
        System.out.println("rank of matrix is "+result);

        scan.close();

    }
    static void swap(int mat[][],  
          int row1, int row2, int col) 
    { 
        for (int i = 0; i < col; i++) 
        { 
            int temp = mat[row1][i]; 
            mat[row1][i] = mat[row2][i]; 
            mat[row2][i] = temp; 
        } 
    } 

    static int solution(int[][] matrix,int r,int c) {
        int rank=c;
        for(int row=0;row<rank;row++){
            if(matrix[row][row]!=0){
                for(int col=0;col<r;col++){
                    if(col!=row){
                        double mult=(double)matrix[col][row]/matrix[row][row];
                        for(int i=0;i<rank;i++){
                            matrix[col][i]-=mult*matrix[row][i];
                        }
                    }
                }
            }
            else{
                boolean reduce=true;
                for(int i=row+1;i<r;i++){
                    if(matrix[i][row]!=0){
                        swap(matrix, row, i,rank);
                        reduce=false;
                        break;
                    }
                }
                if(reduce){
                    rank--;
                    for(int i=0;i<r;i++){
                        matrix[i][row]=matrix[i][rank];
                    }
                    row--;
                }
            }
        }
        return rank;

    }
}