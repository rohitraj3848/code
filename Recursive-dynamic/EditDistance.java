

//edit distance :-maxumum no of operations to convert string 1 to 2

public class EditDistance{
	public static void main(String args[]){
		String s="CART";
		String t="MARCH";
		int[][] r=solution(s,t);
		for(int i=0;i<s.length()+1;i++){
			for(int j=0;j<t.length()+1;j++){
				System.out.print(r[i][j]+" ");
			}
			System.out.print("\n");
	}
}

	public static int[][] solution(String s,String t){
		String s1="0"+s;
		String t1="0"+t;
		int[][] matrix=new int[s1.length()][t1.length()];

		for(int i=0;i<t1.length();i++){
			matrix[0][i]=i;
		}	
		for(int i=0;i<s1.length();i++){
			matrix[i][0]=i;
		}

		for(int i=1;i<s1.length();i++){
			for(int j=1;j<t1.length();j++){
				if(s1.charAt(i)==t1.charAt(j)){
					matrix[i][j]=matrix[i-1][j-1];
				}
				else{
					matrix[i][j]=1+ Math.min(matrix[i-1][j],Math.min(matrix[i][j-1],matrix[i-1][j-1]));
				}
			}
		}
		return matrix;	
	}
}