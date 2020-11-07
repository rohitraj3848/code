public class min_cost_path {
    public static void main(String[] args) {
        int[][] cost =
		{
			{ 4, 7, 8, 6, 4 },
			{ 6, 7, 3, 9, 2 },
			{ 3, 8, 1, 2, 4 },
			{ 7, 1, 7, 3, 7 },
			{ 2, 9, 8, 9, 3 }
        };
        System.out.println(findpath(cost,cost.length,cost[0].length));
        System.out.println(findMinCost(cost, cost.length, cost[0].length));
    }
    static int findpath(int[][] cost,int m,int n){
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(i==0 && j==0){
                    cost[i][j]=cost[i][j];
                }
                else if(i==0 && j!=0){
                    cost[i][j]=cost[i][j]+cost[i][j-1];
                }
                else if(i!=0 && j==0){
                    cost[i][j]=cost[i][j]+cost[i-1][j];
                }
                else{
                    cost[i][j]=Math.min(cost[i-1][j],cost[i][j-1])+cost[i][j];
                }
            }
        }
        return cost[m-1][n-1];
    }
    public static int findMinCost(int[][] cost, int m, int n)
	{
		// base case
		if (n == 0 || m == 0) {
			return Integer.MAX_VALUE;
		}

		// if we're at first cell (0, 0)
		if (m == 1 && n == 1) {
			return cost[0][0];
		}

		// include cost of the current cell in path and
		// recur to find minimum of the path from adjacent
		// left cell and adjacent top cell.
		return Integer.min(findMinCost(cost, m - 1, n),
						findMinCost(cost, m, n - 1))
				+ cost[m - 1][n - 1];
	}


}
