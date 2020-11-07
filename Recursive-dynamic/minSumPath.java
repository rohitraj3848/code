public class minSumPath {
    public static void main(String args[]){
        int dp[][]={{1,2,3},{6,5,4},{1,3,2}};
        int i=0;
        int j=0;
        for( i=0;i<dp.length;i++){
            for(j=0;j<dp[0].length;j++){
                if(i==0 && j!=0){
                    dp[i][j]=dp[i][j]+dp[i][j-1];
                }
                else if(j==0 && i!=0){
                    dp[i][j]=dp[i][j]+dp[i-1][j];
                }
                else if(i==0 && j==0){
                    dp[i][j]=dp[i][j];
                }
                else{
                    dp[i][j]=Math.min(dp[i-1][j]+dp[i][j],dp[i][j-1]+dp[i][j]);
                }
            }
        }
        System.out.println(dp[dp.length-1][dp[0].length-1]);
        for(i=0;i<dp.length;i++){
            for(j=0;j<dp.length;j++){
                System.out.print(dp[i][j]+" ");
            }
            System.out.println();
        }
    }
}