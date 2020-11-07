import java.util.*;


public class n_2_sorting{
	public static void main(String args[]){
		int[] arr={3,4,1,6,7,4,2,9};
		int[] result=n_2_sorting.selectionSort(arr);
		int[] re=n_2_sorting.bubbleSort(arr);
		System.out.println(Arrays.toString(result));
		System.out.println(Arrays.toString(re));
	}

	public static int[] selectionSort(int[] a){
		int n=a.length;
		for(int i=0;i<n-1;i++){
			int imin=0;
			int min=Integer.MAX_VALUE;
			for(int j=i+1;j<n;j++){
				if(a[j]<min){
					min=a[j];
					imin=j;
				}
			}
			int temp=a[i];
			a[i]=a[imin];
			a[imin]=temp;
		}
		return a;
	}

	public static int[] bubbleSort(int[] a){
		int n=a.length;
		for(int j=0;j<n;j++){
			for(int i=0;i<n-1;i++){
				if(a[i]>a[i+1]){
				int temp=a[i];
				a[i]=a[i+1];
				a[i+1]=temp;
			    }
			
			}
		}

		return a;

	}
}