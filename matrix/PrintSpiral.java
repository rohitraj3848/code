class PrintSpiral {
    public static void main(String[] args) {
        int[][] mat =
		{
			{ 1,  2,  3,  4, 5},
			{16, 17, 18, 19, 6},
			{15, 24, 25, 20, 7},
			{14, 23, 22, 21, 8},
			{13, 12, 11, 10, 9}
        };
        int top=0,left=0;
        int right=mat[0].length-1,bottom=mat.length-1;
        while(true){
            if(left>right){
                break;
            }
            for(int i=left;i<=right;i++){
                System.out.print(mat[left][i]+" ");
            }
            top++;
            if(top>bottom){
                break;
            }
            for(int i=top;i<=bottom;i++){
                System.out.print(mat[i][right]+" ");
            }
            right--;
            if(left>right){
                break;
            }
            for(int i=right;i>=left;i--){
                System.out.print(mat[bottom][i]+" ");
            }
            bottom--;
            if(top>bottom){
                break;
            }
            for(int i=bottom;i>=top;i--){
                System.out.print(mat[i][left]+" ");
            }
            left++;
        }
        System.out.println();
    }
}