//find maximum sum such that no 2 elements are adjacent
public class maxsum2 {
    public static void main(String args[]){
        int[] arr={5,5,10,100,10,5};
        int n=arr.length;
        //output 110 -> 5,100,5
        int maxincl=arr[0];
        int maxexcl=0;
        int max=0;
        for(int i=1;i<n;i++){
            max=(maxexcl>maxincl)?maxexcl : maxincl;
            maxincl=maxexcl+arr[i];
            maxexcl=max;
        }
        int res=Math.max(maxexcl,maxincl);
        System.out.println(res);
    }
}
