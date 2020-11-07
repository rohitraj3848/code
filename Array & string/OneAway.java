import java.util.*;

public class OneAway{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		System.out.println("Input the strings:");
		String str=scan.nextLine();
		String str2=scan.nextLine();
		boolean b=solution(str,str2);
		System.out.println(b);
		scan.close();
	}
	public static boolean solution(String s1,String s2){
		if(s1.length()==s2.length()){
			return oneEditReplace(s1,s2);
		}
		else if(s1.length()+1==s2.length()){
			return oneEditInsert(s1,s2);
		}
		else if(s1.length()+1==s2.length()){
			return oneEditInsert(s1,s2);
		}


		return false;
		
	}

	public static boolean oneEditReplace(String s1,String s2){
		boolean t=false;
		for(int i=0;i<s1.length();i++){
			if(s1.charAt(i)!=s2.charAt(i)){
				if(t){
					return false;
				}
				t=true;
			}
		}
		return true;
	}

	public static boolean oneEditInsert(String s1,String s2){
		int index1=0;
		int index2=0;
		while(index1<s1.length() && index2<s2.length()){
			if(s1.charAt(index1)!=s2.charAt(index2)){
				if(index1!=index2){
					return false;
				}
				index2++;
			}
			else{
				index1++;
				index2++;
			}
		}
		return true;
	}
}