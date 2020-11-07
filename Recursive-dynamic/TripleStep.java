
public class TripleStep{
	public static void main(String args[]){
		int r=solution(9);
		System.out.println(r);

	}

	public static int solution(int n){
		if(n<0){
			return 0;
		}
		if(n==0){
			return 1;
		}else{
			return solution(n-1) + solution(n-2) + solution(n-3);
		}
	 }
}