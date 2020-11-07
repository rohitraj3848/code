//max contigouos array product
public class maxproduct {
    public static void main(String args[]){
        int[] arr={4,1,-1,0,-3,4,5};
        System.out.println(maxProduct(arr));
    }
    public static int maxProduct(int[] nums) {
        if(nums.length==0){
            return -1;
        }
        int max=nums[0];
        int current_max=nums[0];
        int current_min=nums[0];
        for(int i=1;i<nums.length;i++){
            int temp=current_max;
            current_max=Math.max(Math.max(current_max*nums[i],current_min*nums[i]),nums[i]);
            current_min=Math.min(Math.min(temp*nums[i],current_min*nums[i]),nums[i]);
            if(max<current_max){
                max=current_max;
            }
        }
        return max;
    }    
    
}
