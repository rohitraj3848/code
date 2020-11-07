public class minjumpstoend {
    public static void main(String[] args) {
        int[] arr = { 1, 3, 6, 1, 0, 9 };
        int jumps=find_min_jump(arr,0,arr.length-1);
        System.out.println(jumps);
    }
    static int find_min_jump(int[] arr,int index,int end){
        if(arr[index]==0){
            return Integer.MAX_VALUE;
        }
        if(index==end){
            return 0;
        }
        int minjumps=Integer.MAX_VALUE;
        for(int i=index+1;i<=index+arr[index] && i<=end;i++){
            int cost=find_min_jump(arr,i, end);
            if(cost!=Integer.MAX_VALUE){
                minjumps=Math.min(minjumps,cost+1);
            }
        }

        return minjumps;
    }
}
