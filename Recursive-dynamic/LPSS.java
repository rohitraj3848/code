public class LPSS {
    public static void main(String args[]){
        String s="BABCBAB";
        System.out.println(solution(s));
    }
    public static int solution(String s){
        int n=s.length();
        int[][] dp=new int[n][n];
        for(int i=0;i<n;i++){
            dp[i][i]=1;
        }
        for(int j=1;j<n;j++){
            int temp=j;
            int k=0;
            while(temp<n){
                if(s.charAt(k)==s.charAt(temp)){
                    dp[k][temp]=dp[k+1][temp-1]+2;
                }
                else{
                    dp[k][temp]=Math.max(dp[k][temp-1],dp[k+1][temp]);
                }
                k++;
                temp++;
            }
        }
        return dp[0][n-1];
    }
    public static String longestPalindrome(String s) {
        if(s==null || s.length()==0){
            return "";
        }
        int start=0;
        int end=0;
        for(int i=0;i<s.length();i++){
            int len1=expand(s,i,i);
            int len2=expand(s,i,i+1);
            int len=Math.max(len1,len2);
            if(len>end-start){
                start=i-((len-1)/2);
                end=i+(len/2);
            }
        }
        return s.substring(start,end+1);
    }
    static int expand(String s,int l,int h){
        if(s==null){
            return -1;
        }
        while(l>=0 && h<s.length() && s.charAt(l)==s.charAt(h)){
            l--;
            h++;
        }
        
        return h-l-1;
    }
}