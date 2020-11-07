import java.util.*;


public class NextPermutation{
	public static void main(String args[]){
		String w="dkhc";
		String t=biggerIsGreater(w);
		System.out.println(t);		
	}
	 static String biggerIsGreater(String w) {
        int n=w.length();
        int[] c=new int[n];
        for(int i=0;i<n;i++){
            c[i]=(int)w.charAt(i);
        }
        System.out.println(Arrays.toString(c));
        int inv_point=n-2;
        while(inv_point>=0 && c[inv_point]>=c[inv_point+1]){
            inv_point--;  
        }
        for(int i=n-1;i>inv_point;i--){
            if(c[i]>c[inv_point]){
                int temp=c[i];
                c[i]=c[inv_point];
                c[inv_point]=temp;
                break;
            }
        }
        System.out.println(Arrays.toString(c));
        int low=inv_point+1;
        int high=n-1;
        while(low<high){
            int temp=c[low];
            c[low]=c[high];
            c[high]=temp;
            low++;
            high--;

        }
        System.out.println(Arrays.toString(c));
        char[] s=new char[n];
        for(int i=0;i<n;i++){
            s[i]=(char)c[i];
        }

        return new String(s);

     }
}