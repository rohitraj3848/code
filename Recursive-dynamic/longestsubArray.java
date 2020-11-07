import java.util.Arrays;

//maximum length alternating sign subarray 
public class longestsubArray {
    public static void main(String[] args) {
        int[] arr = { 1, -2, 6, 4, -3, 2, -4, -3 };
        find_subarray(arr);
    }
    static void find_subarray(int[] arr){
        int maxlen=0;
        int endindex=0;
        int currlen=1;
        for(int i=1;i<arr.length;i++){
            if(arr[i]*arr[i-1]<0){
                currlen++;
                if(currlen>maxlen){
                    maxlen=currlen;
                    endindex=i;
                }
            }else{
                currlen=1;
            }
        }
        int[] subArray=Arrays.copyOfRange(arr,endindex-maxlen+1,endindex+1);
        System.out.println(Arrays.toString(subArray));
    }
}
