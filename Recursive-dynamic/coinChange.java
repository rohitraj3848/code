
import java.util.*;
public class coinChange {
    public static void main(String args[]){
        int[] s={1,2,3};
        int n=10;
        System.out.println(noofways(s,s.length,n));
        System.out.println(countways(s, s.length, n));
    }
    static int noofways(int[] s,int m,int n){
        if(n==0){
            return 1;
        }
        if(n<0){
            return 0;
        }
        
        if(m<=0 && n>=1){
            return 0;
        }
        return noofways(s, m-1, n) + noofways(s, m, n-s[m-1]); 
    }
    static int countways(int[] s,int m,int n){
        int[] d=new int[n+1];
        d[0]=1;
        for(int i=0;i<m;i++){
            for(int j=s[i];j<=n;j++){
                d[j]+=d[j-s[i]];
            }
        }
        return d[n];
    }
    static int mincoinChange(int[] coins, int amount) {
        if(amount==0){
            return 0;
        }
        int[] dp=new int[amount+1];
        Arrays.fill(dp,Integer.MAX_VALUE);
        dp[0]=0;
        for(int i=1;i<=amount;i++){
            for(int coin :coins){
                if(i==coin){
                    dp[i]=1;
                }
                else if(i>coin){
                    if(dp[i-coin]==Integer.MAX_VALUE){
                        continue;
                    }
                    dp[i]=Math.min(dp[i-coin]+1,dp[i]);
                }
            }
        }
        if(dp[amount]==Integer.MAX_VALUE){
            return -1;
        }
        return dp[amount];
    }
}