import java.util.*;
public class NQueenProblem {
    public static void main(String[] args) {
        
    }
    public int totalNQueens(int n) {
        Integer[] columns=new Integer[n];
        ArrayList<Integer[]> results=new ArrayList<>();
        placeQueens(columns,0,results,n);
        return results.size();
    }
    static void placeQueens(Integer[] columns,int row,ArrayList<Integer[]> results,int n){
        if(row==n){
            results.add(columns.clone());
        }else{
            for(int col=0;col<n;col++){
                if(checkValid(columns,row,col)){
                    columns[row]=col;
                    placeQueens(columns,row+1,results,n);
                }
            }
        }
    }
    
    static boolean checkValid(Integer[] columns,int row1,int col1){
        for(int row2=0;row2<row1;row2++){
            int col2=columns[row2];
            if(col1==col2){
                return false;
            }
            int coldistance=Math.abs(col1-col2);
            int rowdistance=Math.abs(row1-row2);
            if(coldistance==rowdistance){
                return false;
            }
        }
        return  true;
    }
   
}
