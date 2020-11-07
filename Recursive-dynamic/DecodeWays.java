public class DecodeWays {
    public static void main(String args[]){
        String s="312";
        System.out.println(decode(s));
    }
    //A-1,B-2 ...Z-26 
    //given an integer find the number of ways it can be decoded
    //like 12 can be decoded in 2 ways AB 
    public static int decode(String s){
        int n=s.length();
        if(n==0)
            return 0;
        
        int[] dp=new int[n+1];
        dp[n]=1;
        dp[n-1]=s.charAt(n-1)!='O'? 1 :0;
        for(int i=n-2;i>=0;i--){
            if(s.charAt(i)=='O')
                continue;
            else
                dp[i]=(Integer.parseInt(s.substring(i,i+2))<=26) ? dp[i+1]+dp[i+2]:dp[i+1];
        }
        return dp[0];
    }
}