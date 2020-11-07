import java.io.*;
import java.util.*;
public class patternMatching{
	static  int d=256;
	public static void main(String args[]){
		String pat="geek";
		String text="geeksforgeeks";
		solution(pat,text,11);

	}

	public static void solution(String pat,String text,int q){
		int m=pat.length();
		int n=text.length();

		int i,j;
		int p=0;
		int t=0;
		int h=1;

		for(i=0;i<m-1;i++){
			h=(h*d)%q;
		}

		for(i=0;i<m;i++){
			p=(d*p+(int)pat.charAt(i))%q;
			t=(d*t+(int)text.charAt(i))%q;
		}

		for(i=0;i<=n-m;i++){
			if(p==t){
				for(j=0;j<m;j++){
					if(text.charAt(i+j)!=pat.charAt(j)){
						break;
					}
					
				}
				if(j==m){
					System.out.println("pattern found at "+i);
				}
			}
		}
		if(i<n-m){
			t=(d*(t-(int)text.charAt(i)*h)+(int)text.charAt(i+m))%q;
			if(t<0){
				t=t+q;
			}
		}
	}
}