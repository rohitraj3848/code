public class CountDist {
    public static void main(String args[]){
        int[] nums = {1,0,0,0,1,0,0,1};
        int k=2;
        System.out.println(kLengthApart(nums,k));
    }
    public static boolean kLengthApart(int[] nums, int k) {
        int n=nums.length;
        int count=0;
        int index=0;
        if(nums[0]==1){
            count=0;
            index=1;
        }
        else{
            count=1;
            index=0;
        }
        int i=0;
        for(i=index;i<n;i++){
            if(nums[i]==1){
                if(count<k){
                    break;
                }else{
                    count=0;
                }
            }
            else{
                count++;
            }
        }
        System.out.println(i);
        System.out.println(n-1);
        if(i!=n){
            return false;
        }
        return true;
    }

}