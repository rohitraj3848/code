
import java.util.*;
public class Urlify{
	public static void main(String args[]){
       Scanner scan=new Scanner(System.in);
       System.out.println("Input the string with needed space:");
       String str=scan.nextLine();
       System.out.println("Input the true length of string:");
       int truelength=scan.nextInt();
       String r=solution(str,truelength);
	   System.out.println(r);
	   scan.close();
	}
	public static String solution(String s,int truelength){
		char s1[]=new char[s.length()];
		char c[]=s.toCharArray();
		int k=s1.length-1;
		for(int i=truelength-1;i>=0 && k>=0;){
			if(c[i]!=' '){
				s1[k]=c[i];
				k--;
				i--;
			}
			else{
				i--;
				s1[k]='0';
				k--;
				s1[k]='2';
				k--;
				s1[k]='%';
				k--;
			}
		}
		String result=new String(s1);
		return result;
	}
}