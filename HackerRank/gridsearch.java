import java.io.*;
import java.util.*;
public class gridsearch{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		int n=scan.nextInt();
		int m=scan.nextInt();
		String[] G=new String[n];
		String[] P=new String[m];
		for(int i=0;i<n;i++){
			G[i]=scan.next();
		}
		for(int j=0;j<m;j++){
			P[j]=scan.next();
		}
		String r=search(G,P);
		System.out.println(r);
         
	}
	public static String search(String[] G,String[] P){
        int n=G.length;
        int m=P.length;
        int i=0;
        int j=0;
        boolean t=false;
        boolean z=false;
        while(i<m){
        	while(j<n){
        		if(G[j].contains(P[i])){
                   i++;
                   j++;
                   z=true;
                   if(i==m-1) {
                   	t=true;
                   	break;
                   }
                   if(!z){
                   	break;
                   }
        		}else{
        			j++;
        			z=false;

        		}
        	}
        	i++;
        }
        if(t){
        	return "YES";
        }
        else{
        	return "NO";
        }
	}
}