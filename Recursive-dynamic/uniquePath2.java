public class uniquePath2{
    public static void main(String args[]){
        int[][] matrix={{0,0,0},{0,1,0},{0,0,0}};
        for(int i=0;i<matrix.length;i++){
            if(matrix[i][0]==1){
                break;
            }
            matrix[i][0]=1;
        }
        for(int i=0;i<matrix[0].length;i++){
            if(matrix[0][i]==1){
                break;
            }
            matrix[0][i]=1;
        }
        for(int i=1;i<matrix.length;i++){
            for(int j=1;j<matrix[0].length;j++){
                if(matrix[i][j]==1){
                    matrix[i][j]=0;
                }
                else{
                    matrix[i][j]=matrix[i-1][j]+matrix[i][j-1];
                }
            }
        }
        for(int i=0;i<matrix.length;i++){
            for(int j=0;j<matrix[0].length;j++){
                System.out.print(matrix[i][j]+" ");
            }
            System.out.println();
        }
        System.out.println(matrix[matrix.length-1][matrix[0].length-1]);
    }
}