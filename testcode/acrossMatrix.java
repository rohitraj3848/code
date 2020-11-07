//given a matrix whose elements represent coins
//give different paths to go across the matrix from (0,0) to (n-1,n-1) 
//using exactly given coins  you can travel right or down
public class acrossMatrix {
    public static void main(String args[]){
        int[][] matrix={{1,2,3},
                        {4,6,5},
                        {3,2,1}};
        //given coins
        int k=12;
        int result=pathcount(matrix, k, matrix.length, matrix[0].length);
        System.out.println(result);
    }
    
    static int findPath(int[][] matrix,int m,int n,int k){
        if(m<0 || n<0){
            return 0;
        }
        if(m==0 && n==0 && (k==matrix[m][n])){
            return 1;
        }
        return findPath(matrix,m-1, n, k-matrix[m][n]) + findPath(matrix, m, n-1, k-matrix[m][n]);
    }
    static int pathcount(int[][] matrix,int k,int r,int c){
        return findPath(matrix,r-1,c-1,k);
    }
}