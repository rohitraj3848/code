import java.io.*;
import java.util.*;
public class containBalls{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		System.out.println("Input n");
		int n=scan.nextInt();
		int[][] cont=new int[n][n];
		System.out.println("imput matrix element:");
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
                cont[i][j]=scan.nextInt();
			}
		}
		String s=solution(cont);
		System.out.println(s);

	}
	public static String solution(int[][] cont){
		int n=cont[0].length;
         int[] sumcont=new int[n];
         int[] balltype=new int[n];
         int k=0;
         for(int i=0;i<n;i++){
         	for(int j=0;j<n;j++){
               sumcont[k]+=cont[i][j];
         	}
         	k++;
         }
         k=0;
         for(int i=0;i<n;i++){
         	for(int j=0;j<n;j++){
               balltype[k]+=cont[j][i];
         	}
         	k++;
         }
         Arrays.sort(sumcont);
         Arrays.sort(balltype);
         boolean c=Arrays.equals(sumcont,balltype);
         if(c)
         	return "possible";
         else
         	return "impossible";

	}
}