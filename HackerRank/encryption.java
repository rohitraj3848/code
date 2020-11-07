import java.io.*;
import java.util.*;
public class encryption{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
        System.out.println("input the string to be encrypted:");
        String s=scan.nextLine();
        String r=encrypt(s);
        System.out.println(r);

	}
	public static String encrypt(String s){
		String t=s.replaceAll("\\s+","");
		int l=t.length();
		int a=(int)Math.floor(Math.sqrt(l));
		int b=(int)Math.ceil(Math.sqrt(l));
		if((a*b)<l){
			b++;
		}
		char[] c=t.toCharArray();
		char[][] d=new char[a][b];
		int i,j=0;
		for(i=0;i<a;i++){
			for(j=0;j<b;j++){
				if(((i*b)+j)==c.length){
					break;
				}
				d[i][j]=c[(i*b)+j];
			}
			if(((i*b)+j)==c.length){
				break;
				
			}
			}
		String z="";
		for(i=0;i<b;i++){
			for(j=0;j<a;j++){
				if(d[j][i]==' '){
					break;
				}else{z+=d[j][i];}

				
			}
			z+=" ";
		}

     return z;
	}
}