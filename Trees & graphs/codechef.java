/* package codechef; // don't place package name! */

import java.util.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
		// your code goes here
		Scanner scan=new Scanner(System.in);
		try{
		    int t=scan.nextInt();
		    for(int i=0;i<t;i++){
		        int n=scan.nextInt();
		        int[] a=new int[n];
		        for(int j=0;j<n;j++){
		            a[j]=scan.nextInt();
		        }
		        System.out.println(maxProfit(a,n));
		    }
		    
		}catch(NumberFormatException e){
		    System.out.println(e);
        }
        scan.close();
	}
	static int maxProfit(int[] a,int n){
        Arrays.sort(a);
        System.out.println(Arrays.toString(a));
        int profit=0;
        int index=0;
	    for(int i=n-1;i>=0;i--){
	        if((a[i]-index)<0){
	            profit+=0;
	        }else{
	            profit+=(a[i]-index);
            }
            index++;
	    }
	    return profit;
	}
}
