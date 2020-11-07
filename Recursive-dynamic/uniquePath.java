public class uniquePath{
    public static void main(String args[]){
        int m=3;
        int n=7;

        int N=m+n-2;
        int k=n-1;
        int res=1;
        for(int i=1;i<=k;i++){
            res=res*(N-k+i)/i;
        }

        int[][] matrix=new int[m][n];
        int result=solution(matrix);
        System.out.println(result);
        System.out.println(res);
    }

    static int solution(int[][] matrix){
        for(int i=0;i<matrix.length;i++){
            matrix[i][0]=1;
        }
        for(int i=0;i<matrix[0].length;i++){
            matrix[0][i]=1;
        }
        for(int i=1;i<matrix.length;i++){
            for(int j=1;j<matrix[0].length;j++){
                matrix[i][j]=matrix[i-1][j]+matrix[i][j-1];
            }
        }
        return matrix[matrix.length-1][matrix[0].length-1];
    }
}