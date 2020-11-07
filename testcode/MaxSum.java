//find the maximum sum contiguous Array
public class MaxSum {
    public static void main(String args[]){
        int arr[]={1,2,3,4,-10};
        int result=Solution(arr);
        System.out.println(result);
    }

    static int Solution(int[] arr){
        int max_so_far=0;
        int max_ending_here=0;
        for(int i=0;i<arr.length;i++){
            max_ending_here=max_ending_here+arr[i];
            if(max_ending_here<0){
                max_ending_here=0;
            }
            if(max_so_far<max_ending_here){
                max_so_far=max_ending_here;
            }
        }
        return max_so_far;
    }
}