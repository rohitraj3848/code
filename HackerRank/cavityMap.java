import java.io.*;
import java.util.*;
public class cavityMap{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		System.out.println("input no of strings and their size:");
		int n=scan.nextInt();
		String[] s=new String[n];
		System.out.println("input strings:");
		for(int i=0;i<n;i++){
            s[i]=scan.next();
		}
		solution(s);
		System.out.println("after replacement:");
		for(int i=0;i<n;i++){
			System.out.println(s[i]);
		}

	}
	public static String[] solution(String[] s){
		int m=s.length;
         for(int i=1;i<m-1;i++){
         	for(int j=1;j<m-1;j++){
         		     char x1=s[i].charAt(j);
                     int x=Character.getNumericValue(x1);
                     char a1=s[i].charAt(j-1);
                     int a=Character.getNumericValue(a1);
                     char b1=s[i].charAt(j+1);
                     int b=Character.getNumericValue(b1);
                     char c1=s[i-1].charAt(j);
                     int c=Character.getNumericValue(c1);
                     char d1=s[i+1].charAt(j);
                     int d=Character.getNumericValue(d1);
                     if(x>a && x>b && x>c && x>d){
                     	 StringBuilder sb = new StringBuilder(s[i]);
                        sb.setCharAt(j, 'X');
                        s[i] = sb.toString();
                     }

         		}
         	}
         	return s;
         }
	}


