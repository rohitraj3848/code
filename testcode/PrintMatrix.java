//generate two functions time complexity O(n)
//to print matrix in z form 
//to print square of both diagonal
public class PrintMatrix {
    public static void main(String args[]){
        int[][] matrix={
            {1,2,3},
            {4,5,6},
            {7,8,9}
        };
        printZ(matrix);
        printSquare(matrix);
    }

    static void printZ(int[][] matrix){
        for(int i=0;i<matrix.length-1;i++){
            System.out.print(matrix[0][i]+" ");
        }
        for(int i=0;i<matrix.length;i++){
            System.out.print(matrix[i][matrix.length-(i+1)]+" ");
        }
        for(int i=1;i<matrix.length;i++){
            System.out.print(matrix[matrix.length-1][i]+" ");
        }
        System.out.println();
    }

    static void printSquare(int[][] matrix){
        for(int i=0;i<matrix.length;i++){
            System.out.print((matrix[i][i]*matrix[i][i])+" ");
        }
        System.out.println();
        for(int i=0;i<matrix.length;i++){
            System.out.print(matrix[i][matrix.length-(i+1)]*matrix[i][matrix.length-(i+1)]+" ");
        }
        System.out.println();
    }
}
