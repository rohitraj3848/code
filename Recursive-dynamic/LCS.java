
//longest common subsequence
public class LCS{
	public static void main(String args[]){
		String s="APPEND";
		String t="EXPANDABLE";
		int[][] lcs=solution(s,t);

		for(int i=0;i<t.length()+1;i++){
			for(int j=0;j<s.length()+1;j++){
				System.out.print(lcs[i][j]+" ");
			}
			System.out.print("\n");
		}
	}


	public static int[][] solution(String s,String t){
		String s1="0"+s;
		String t1="0"+t;
		System.out.println(s1.length());
		System.out.println(t1.length());
		int[][] matrix=new int[t1.length()][s1.length()];
		for(int i=0;i<t1.length();i++){
			matrix[i][0]=0;
		}
		for(int i=0;i<s1.length();i++){
			matrix[0][i]=0;
		}

		for(int i=1;i<t1.length();i++){
			for(int j=1;j<s1.length();j++){
				if(s1.charAt(j)==t1.charAt(i)){
					matrix[i][j]=matrix[i-1][j-1]+1;
				}
				else{
					matrix[i][j]=Math.max(matrix[i-1][j],matrix[i][j-1]);
				}
			}
		}
		return matrix;
	}
}