//max product of 4 adjacent elements in matrix
//{{6,2,3,4},{5,4,3,1},{7,4,5,6},{8,3,1,0}} 
//max=1680
public class maxproduct {
    public static void main(String[] args) {
        int[][] arr={{6,2,3,4},{5,4,3,1},{7,4,5,6},{8,3,1,0}} ;
        int row=arr.length;
        int col=arr[0].length;
        int max=0;
        int p=0;
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if((j-3)>=0){
                    p= arr[i][j]*arr[i][j-1]*arr[i][j-2]*arr[i][j-3];
                    max=Math.max(max,p);
                }
                if((i-3)>=0){
                    p=arr[i][j]*arr[i-1][j]*arr[i-2][j]*arr[i-3][j];
                    max=Math.max(p,max);
                }
                if((i-3)>=0 && (j-3)>=0){
                    p=arr[i][j]*arr[i-1][j-1]*arr[i-2][j-2]*arr[i-3][j-3];
                    max=Math.max(p,max);
                }
                if((i-3)>=0 && (j+3)<0){
                    p=arr[i][j]*arr[i-1][j+1]*arr[i-2][j+2]*arr[i-3][j+3];
                    max=Math.max(max,p);
                }
            }
        }
        System.out.println(max);
        

    }
}
