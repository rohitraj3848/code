import java.util.*;
public class isUnique{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		System.out.println("Input the string:");
		String s=scan.nextLine();
		boolean t=Solution(s);
		System.out.println(t);
		scan.close();
	}
	public static boolean Solution(String s){
		if(s.length()>26){
			return false;
		}
		boolean b[]=new boolean[26];
		for(int i=0;i<s.length();i++){
            int val=s.charAt(i);
            if(val>=65 && val<=90){
            	if(b[(val+32)%97]){
            		return false;
            	}
            }
            else{
            	if(b[val%97]){
            		return false;
            	}
            }
            if(val>=65 && val<=90){
            	b[(val+32)%97]=true;
            }else{
            b[val%97]=true;
        }
		}
		return true;
	}
}