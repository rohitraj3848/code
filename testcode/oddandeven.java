import java.util.Arrays;

//sort the array so that a[i] is odd i is odd and a[i] is even ,i is even
//input {4,2,5,7} output {4,5,2,7};
public class oddandeven {
    public static void main(String args[]){
        int[] arr={4,2,5,7};
        int[] even=new int[arr.length/2];
        int[] odd=new int[arr.length/2];
        int evenindex=0;
        int oddindex=0;
        for(int i=0;i<arr.length;i++){
            if(arr[i]%2==0){
                even[evenindex]=arr[i];
                evenindex++;
            }else{
                odd[oddindex]=arr[i];
                oddindex++;
            }
        }
        evenindex=0;
        oddindex=0;
        for(int i=0;i<arr.length;i++){
            if(i%2==0){
                arr[i]=even[evenindex];
                evenindex++;
            }
            else{
                arr[i]=odd[oddindex];
                oddindex++;
            }
        }
        System.out.println(Arrays.toString(arr));
    }
}
