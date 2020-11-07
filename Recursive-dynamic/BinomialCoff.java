

public class BinomialCoff{
	public static void main(String  args[]){
       System.out.println(solution1(4,2));
       System.out.println(solution2(4,2));
       System.out.println(solution3(4,2));
	}

	public static int solution1(int n,int r){
		if(r==0 || r==n)
			return 1;
		else
			return solution1(n-1,r)+solution1(n-1,r-1);
	}

	public static int solution2(int n,int r){
		int[][] m =new int[n+1][r+1];

		for(int i=0;i<=n;i++){
			for(int j=0;j<=Math.min(i,r);j++){
				if(j==0 || j==i)
					m[i][j]=1;
				else
					m[i][j]=m[i-1][j]+m[i-1][j-1];
			}
		}
		for(int i=0;i<=n;i++){
			for(int j=0;j<=r;j++){
				System.out.print(m[i][j]+" ");
			}
			System.out.println();
		}
		return m[n][r];
	}

	public static int solution3(int n,int r){
		int[] c=new int[r+1];
		c[0]=1;

		for(int i=0;i<=n;i++){
			//compute next row of pascal triangle using the previous row
			for(int j=Math.min(i,r);j>0;j--){
				c[j]=c[j]+c[j-1];
			}
		}
		return c[r];
	}
}