import java.util.*;
public class nextpermutation {
    public static void main(String[] args) {
        //find the next permutation of the array in lexographical order
        int arr[]={4,5,6,3,2,1};
        nextPer(arr);
        System.out.println(Arrays.toString(arr));

    }
    static void nextPer(int[] arr){
        int n=arr.length;
        int index=0;
        for(int i=n-1;i>0;i--){
            if(arr[i]>arr[i-1]){
                index=i-1;
                break;
            }
        }
        if(index==0){
            reverse(arr, 0, n-1);
            return;
        }
        int index1=0;
        for(int i=n-1;i>0;i--){
            if(arr[index]<arr[i]){
                index1=i;
                break;
            }
        }
        swap(arr,index,index1);
        reverse(arr,index+1,n-1);
    }
    static void swap(int[] arr,int i,int j){
        int temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
    static void reverse(int[] arr,int i,int j){
        while(i<j){
            swap(arr,i,j);
            i++;
            j--;
        }
    }
}
