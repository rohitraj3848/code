import java.util.*;
public class leaderboard{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		System.out.println("Input the no of players:");
		int n=scan.nextInt();
		int[] a=new int[n];
		System.out.println("Input their scores:");
		for(int i=0;i<n;i++){
			a[i]=scan.nextInt();
		}
		System.out.println("Input the no of match of alice:");
		int m=scan.nextInt();
		int[] b=new int[m];
		System.out.println("Input the score of alice:");
		for(int j=0;j<m;j++){
			b[j]=scan.nextInt();
		}
		int res[]=climbingLeaderboard(a,b);
		for(int j=0;j<m;j++){
			System.out.println(res[j]);
		}


	} 
	static int[] climbingLeaderboard(int[] scores, int[] alice) {
         List<Integer> l=new ArrayList<>();
         int n=scores.length;
         int m=alice.length;
         l.add(scores[0]);
         for(int i=1;i<n;i++){
            if(scores[i]!=scores[i-1]){
            	l.add(scores[i]);
            }
         }
         System.out.println(l);
         int[] result=new int[m];
         for(int i=0;i<m;i++){
         	int x=alice[i];
         	for(int j=0;j<l.size();j++){
         		if(x>=l.get(j)){
         			result[i]=j+1;
         			break;
         		}
         		
         		if(x<l.get(l.size()-1)){
         			result[i]=l.size()+1;
         			break;
         		}
         		
         		if(x==l.get(l.size()-1)){
         			result[i]=l.size();
         		}
         		
         	}
         }
         return result;

    }
}