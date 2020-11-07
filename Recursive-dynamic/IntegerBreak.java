public class IntegerBreak {
    public static void main(String[] args) {
        
    }
    public int integerBreak(int n) {
        //break the integer n such that the product is maximum.
        int[] dp=new int[n+1];
        for(int i=1;i<n;i++){
            for(int j=1;j<=i;j++){
                if(i+j<=n){
                   dp[i+j]=Math.max(Math.max(dp[i],i)*Math.max(dp[j],j),dp[i+j]);
                }
            }
        }
        return dp[n];
    }
}
