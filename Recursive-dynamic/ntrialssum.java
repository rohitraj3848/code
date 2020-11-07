//given a dice with k faces.we have n trial to make.find maximim possible ways to make get a sum.
public class ntrialssum {
    public static void main(String[] args) {
        System.out.println(getcount(2,6,10));
        int[][] dp=new int[3][11];
        int res=getcount1(2, 6, 10,dp);
        System.out.println(res);
        for(int i=0;i<dp.length;i++){
            for(int j=0;j<dp[0].length;j++){
                System.out.print(dp[i][j]+" ");
            }
            System.out.println();
        }
    }
    static int getcount(int n,int k,int sum){
        if(n==0){
            return (sum==0) ?1 :0;
        }
        if(n>sum || k*n <sum || sum <0){
            return 0;
        }
        int res=0;
        for(int i=0;i<=k;i++){
            res+=getcount(n-1, k, sum-i);
        }
        return res;
    }
    static int getcount1(int n,int k,int sum,int[][] dp){
        if(n==0){
            return (sum==0) ?1 :0;
        }
        if(sum<0 || k*n < sum || sum < n){
            return 0;
        }
        if(dp[n][sum]==0){
            for(int i=0;i<=k;i++){
                dp[n][sum]+=getcount1(n-1, k, sum-i,dp);
            }
        }
        return dp[n][sum];
    }

}
