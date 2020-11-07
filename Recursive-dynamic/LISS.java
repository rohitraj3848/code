import java.util.*;
//longest increasing sub-sequence
public class LISS{
	public static void main(String args[]){
		int[] a={10,22,9,3,21,50,41};
		int r=solution(a);
		System.out.println(r);
		System.out.println(LDSS(a));
		System.out.println(MISS(a,a.length));

	}

	public static int solution(int[] a){
		int n=a.length;
		int[] l=new int[n];
		Arrays.fill(l,1);

		for(int i=1;i<n;i++){
			for(int j=0;j<i;j++){
				if(a[i]>a[j] && l[i]<l[j]+1){
					l[i]=l[j]+1;
				}
			}
		}
		int max=0;
		for(int i=0;i<n;i++){
			if(l[i]>max){
				max=l[i];
			}
		}
		return max;
	}

	static int  LDSS(int[] a){
		int n=a.length;
		int[] l=new int[n];
		Arrays.fill(l,1);
		for(int i=1;i<n;i++){
			for(int j=0;j<i;j++){
				if(a[i]<a[j] && l[i]<l[j]+1){
					l[i]=l[j]+1;
				}
			}
		}
		int max=0;
		for(int i=0;i<n;i++){
			if(l[i]>max){
				max=l[i];
			}
		}
		return max;
	}
	//maximum increasing subsequence sum 
	static int MISS(int[] a,int n){
		int[] d=new int[n];
		for(int i=0;i<n;i++){
			d[i]=a[i];
		}
		for(int i=1;i<n;i++){
			for(int j=0;j<i;j++){
				if(a[i]>a[j] && d[i]<d[j]+a[i]){
					d[i]=d[j]+a[i];
				}
			}
		}
		int max=0;
		for(int i=0;i<n;i++){
			if(d[i]>max){
				max=d[i];
			}
		}
		return max;
	}
}