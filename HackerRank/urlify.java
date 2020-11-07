import java.io.*;
import java.util.*;
public class urlify{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		System.out.println("Input the string:");
		String s=scan.nextLine();
		char[] c=s.toCharArray();
		System.out.println("Input the truelength:");
		int n=scan.nextInt();
		String r=solution(c,n);
		System.out.println(r);

	}
	public static String solution(char[] c,int truelength){
       int spacecount=0;
       for(int i=0;i<truelength;i++){
       	if(c[i]==' '){
       		spacecount++;
       	}
       }
       int index=truelength+spacecount*2;
       if(truelength<c.length){
       	c[truelength]='\0';
       }
       for(int i=truelength-1;i>=0;i--){
       	if(c[i]==' '){
       		c[index-1]='0';
       		c[index-2]='2';
       		c[index-3]='%';
       		index=index-3;
       	}
       	else{
       		c[index-1]=c[i];
       		index--;
       	}
       }  
     String s1=new String(c);
     return s1;
	}
}