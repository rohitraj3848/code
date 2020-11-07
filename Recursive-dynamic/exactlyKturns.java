public class exactlyKturns {
    //find no of ways taking exactly k turns to reach (M-1,N-1)
    private static int M=3;
    private static int N=3;
    public static void main(String[] args) {
        int k=2;
        System.out.println(countWays(0,0,k));
    }
    static int countWays(int i,int j,int k){
        return countWays(i+1, j, k,true)+countWays(i, j+1, k,false);
    }
    static int countWays(int i,int j,int k,boolean iscol){
        if(k==-1 || !isValid(i, j)){
            return 0;
        }
        if(i==M-1 && j==N-1 && k==0){
            return 1;
        }
        if(iscol){
            return countWays(i+1, j, k, iscol) + countWays(i, j+1, k-1, !iscol);
        }
        return countWays(i, j+1, k, iscol)+ countWays(i+1, j, k-1, !iscol);
    }
    static boolean isValid(int i,int j){
        if(i>=0 && i<M && j>=0 && j<N){
            return true;
        }
        return false;
    }
}
