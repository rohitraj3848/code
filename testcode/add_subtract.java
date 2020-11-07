import java.util.*;
public class add_subtract {
    public static void main(String args[]){
        int n=5;
        int k=3;
        int[] arr={9,7,4,4,9};
        System.out.println(cost(arr,n,k));

    }
    static int cost(int[] arr,int n,int k){
        Arrays.sort(arr);
        int mincost=Integer.MAX_VALUE;
        for(int i=0;i<=n-k;i++){
            int min=Integer.MAX_VALUE;
            int max=Integer.MIN_VALUE;
            for(int j=i;j<i+k;j++){
                if(arr[j]<min){
                    min=arr[j];
                }
                if(arr[j]>max){
                    max=arr[j];
                }
            }
            int count1=0;
            int count2=0;
            for(int j=i;j<i+k;j++){
                count1+=(max-arr[j]);
                count2+=(arr[j]-min);
            }
            if(mincost>Math.min(3*count1,5*count2)){
                mincost=Math.min(3*count1,5*count2);
            }
            System.out.println(max+" "+min+" "+count1+" "+count2+" "+mincost);
            
        }
        return mincost;
    }
}