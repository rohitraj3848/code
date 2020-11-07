import java.util.*;

public class mergeSorted{
	public static void main(String args[]){
		int[] a={1,3,5,7,9};
		int[] b={2,4,6,8};
		int[] result=sorted(a,b);
		System.out.println(Arrays.toString(result));
	}

	public static int[] sorted(int a[],int b[]){
		int i=0;
		int j=0;
		int n=a.length+b.length;
		int[] arr=new int[n];
		int k=0;
		while(i<a.length && j<b.length){
			if(a[i]<=b[j]){
				arr[k]=a[i];
				i++;
			}else{
				arr[k]=b[j];
				j++;
			}
			k++;
		}
		while(i<a.length){
					arr[k]=a[i];
					k++;
					i++;
		}
		while(j<b.length){
					arr[k]=b[j];
					k++;
					j++;
		}
		return arr;
	}
}