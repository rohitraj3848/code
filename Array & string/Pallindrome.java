import java.io.*;
import java.util.*;
public class Pallindrome{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		System.out.println("Input the String:");
		String str=scan.nextLine();
		boolean b=solution(str);
		System.out.println(b);
	}
	public static boolean solution(String s){
		char[] c=s.toCharArray();
		HashMap<Character,Integer> h=new HashMap<>();
		for(int i=0;i<c.length;i++){
			h.put(c[i],0);
		}
        for(int i=0;i<c.length;i++){
        	int t=h.get(c[i]);
        	t++;
        	h.put(c[i],t);
        }
        int k=0;
        for(int i=0;i<c.length;i++){
        	int r=h.get(c[i]);
        	if(r%2==1){
        		k++;
        	}
        }
        if(k>1){
        	return false;
        }
        else{
        	return true;
        }


	}
}