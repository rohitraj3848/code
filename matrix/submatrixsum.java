
public class submatrixsum {
    public static void main(String[] args) {
        int[][] mat =
		{
			{ 0, 2, 5, 4, 1 },
			{ 4, 8, 2, 3, 7 },
			{ 6, 3, 4, 6, 2 },
			{ 7, 3, 1, 8, 3 },
			{ 1, 5, 7, 9, 4 }
        };
        int[][] matrix =
		{
			{ 3, -4, 6, -5, 1 },
			{ 1, -2, 8, -4, -2 },
			{ 3, -8, 9, 3, 1 },
			{ -7, 3, 4, 2, 7 },
			{ -3, 7, -5, 7, -6 }
		};

        int k=3;
        System.out.println(getsum(mat,1,1,3,3));
        point p=getsumK(matrix, k);
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                int r=i+p.x-k+1;
                int c=j+p.y-k+1;
                System.out.print(matrix[r][c]+" ");
            }
            System.out.println();
        }
        System.out.println(maxsum);
    }
    static int getsum(int[][] mat,int p,int q,int r,int s){
        int M=mat.length;
        int N=mat[0].length;
        int[][] sum=new int[M][N];
        sum[0][0]=mat[0][0];
        for(int i=1;i<M;i++){
            sum[i][0]=sum[i-1][0]+mat[i][0];
        }
        for(int i=1;i<N;i++){
            sum[0][i]=sum[0][i-1]+mat[0][i];
        }
        for(int i=1;i<M;i++){
            for(int j=1;j<N;j++){
                sum[i][j]=mat[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
            }
        }
        int total=sum[r][s];
        if(p-1>=0){
            total-=sum[p-1][s];
        }
        if(q-1>=0){
            total-=sum[r][q-1];
        }
        if(q-1>=0 && p-1>=0){
            total+=sum[p-1][q-1];
        }
        return total;
    }
    //get maxsum of K*k matrix 
    static int maxsum;
    static point getsumK(int[][] mat,int k){
        point p=null;
        int M=mat.length;
        int N=mat[0].length;
        int[][] sum=new int[M][N];
        sum[0][0]=mat[0][0];
        for(int i=1;i<M;i++){
            sum[i][0]=sum[i-1][0]+mat[i][0];
        }
        for(int i=1;i<N;i++){
            sum[0][i]=sum[0][i-1]+mat[0][i];
        }
        for(int i=1;i<M;i++){
            for(int j=1;j<N;j++){
                sum[i][j]=mat[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
            }
        }
        for(int i=k-1;i<M;i++){
            for(int j=k-1;j<N;j++){
                int total=sum[i][j];
                if(i-k>=0){
                    total-=sum[i-k][j];
                }
                if(j-k>=0){
                    total-=sum[i][j-k];
                }
                if(i-k>=0 && j-k>=0){
                    total+=sum[i-k][j-k];
                }
                if(total>maxsum){
                    maxsum=total;
                    p=new point(i,j);
                }

            }
        }

        return p;
    }
    //maximum sum submatrix
    static point p1=null;
    static point p2=null;
    static int getmaxSumsubmatrix(int[][] mat){
        int M=mat.length;
        int N=mat[0].length;
        int[][] sum=new int[M+1][N+1];
        for(int i=0;i<=M;i++){
            for(int j=0;j<=N;j++){
                if(i==0 || j==0){
                    sum[i][j]=0;
                }
                else{
                    sum[i][j]=mat[i-1][j-1]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
                }
            }
        }
        int max=Integer.MIN_VALUE;
        for(int i=0;i<M;i++){
            for(int k=i;k<M;k++){
                for(int j=0;j<N;j++){
                    for(int l=k;l<N;l++){
                        int submatrixsum=sum[k+1][l+1]-sum[k+1][j]-sum[i][l+1]+sum[i][j];
                        if(max<submatrixsum){
                            max=submatrixsum;
                            p1=new point(i,j);
                            p2=new point(k,l);
                        }
                    }
                }
            }
        }
        return max;
    }

    
}
class point{
    int x;
    int y;
    public point(int x,int y){
        this.x=x;
        this.y=y;
    }
}