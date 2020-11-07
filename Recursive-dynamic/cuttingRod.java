
public class cuttingRod {
    public static void main(String args[]){
        int[] cost={};
        System.out.println(cutrod(cost,cost.length));
    }
    static int cutrod(int[] c,int n){
        if(n<0){
            return 0;
        }
        int max=Integer.MIN_VALUE;
        for(int i=0;i<n;i++){
            max=Math.max(max,c[i]+cutrod(c, n-i-1));
        }
        return max;
    }
    static int cutrod2(int[] c,int n){
        int[] val=new int[n+1];
        val[0]=0;
        for(int i=1;i<n;i++){
            int max=Integer.MIN_VALUE;
            for(int j=0;j<i;j++){
                max=Math.max(max,val[i-j-1]);
            }
            val[i]=max;
        }
        return val[n];
    }
}