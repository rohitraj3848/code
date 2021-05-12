import java.util.*;

public class AllSubSetOfSizeK {
	static int min=Integer.MAX_VALUE;
	public void subset(int[] A, int k, int start, int currLen, boolean[] used,List<List<Integer>> subsets) {
        List<Integer> curr=new LinkedList<Integer>();
		if (currLen == k) {
			for (int i = 0; i < A.length; i++) {
				if (used[i] == true) {
					curr.add(A[i]);
				}
			}
			subsets.add(curr);
			return;
		}
		if (start == A.length) {
			return ;
		}
		// For every index we have two options,
		// 1.. Either we select it, means put true in used[] and make currLen+1
		used[start] = true;
		subset(A, k, start + 1, currLen + 1, used,subsets);
		// 2.. OR we dont select it, means put false in used[] and dont increase
		// currLen
		used[start] = false;
		subset(A, k, start + 1, currLen, used,subsets);
	}
	
	// For every ind

	public static void main(String[] args) {
		int A[] = { 1, 2, 3, 4, 5 };
		List<List<Integer>> subsets=new LinkedList<>();
		boolean[] B = new boolean[A.length];
		AllSubSetOfSizeK i = new AllSubSetOfSizeK();
		i.subset(A, 3, 0, 0, B,subsets);
		System.out.println(subsets);

	}

}