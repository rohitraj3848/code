import java.io.*;
import java.util.*;

public class StringCompression{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		System.out.println("Input the string to be compressed:");
		String str=scan.nextLine();
		String r=Solution(str);
		System.out.println(r);
	}
	public static String Solution(String s){
       String copy=s;
       String r="";
       r+=copy.charAt(0);
       char temp=copy.charAt(0);
       int index=0;
       int count=1;
       for(int i=1;i<copy.length();i++){
       	if(copy.charAt(i)==temp){
       		count++;
       		if(i==copy.length()-1){
       			r+=count;
       		}
       		if(i==copy.length()-2 && s.charAt(i+1)!=temp){
       			r+=count;
       		}
       	}
       	else if(copy.charAt(i)!=temp && i==copy.length()-1){
       		r+=copy.charAt(i);
       		r+=1;
       	}
       	else{
       		r+=count;
       		r+=copy.charAt(i);
       		temp=copy.charAt(i);
       		count=1;
       	}
       }
       if(r.length()<copy.length()){
       	return r;
       }
       else{
       	return s;
       }
	}
}