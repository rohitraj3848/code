//find the maximum absolute difference of |A[i]-A[j]|+|i-j| in O(n) time
public class maxabsdiff {
    public static void main(String args[]){
        int[] arr={1,3,-1};
        int max1=Integer.MIN_VALUE;
        int min1=Integer.MAX_VALUE;
        int max2=Integer.MIN_VALUE;
        int min2=Integer.MAX_VALUE;

        for(int i=0;i<arr.length;i++){
            max1=Math.max(max1,arr[i]+i);
            min1=Math.min(min1,arr[i]+i);
            max2=Math.max(max2,arr[i]-i);
            min2=Math.min(min2,arr[i]-i);
        }
        
        System.out.println(Math.max(max1-min1,max2-min2));

    }
}