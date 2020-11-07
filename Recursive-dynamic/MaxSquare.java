import java.util.*;
public class MaxSquare {
    public boolean makesquare(int[] nums) {
        if(nums.length==0 || nums==null){
            return false;
        }
        int sum=0;
        for(int i=0;i<nums.length;i++){
            sum+=nums[i];
        }
        if(sum%4!=0){
            return false;
        }
        Arrays.sort(nums);
        reverse(nums,0,nums.length-1);
        int side=sum/4;
        return dfs(nums,0,new int[4],side);
    }
    
    public boolean dfs(int[] nums,int index,int[] target,int perm){
        if(index==nums.length){
            for(int i : target){
                if(i!=perm) return false;
            }
            return true;
        }
        
        for(int i=0;i<4;i++){
            if(target[i]+nums[index]>perm)continue;
            target[i]+=nums[index];
            if(dfs(nums,index+1,target,perm))return true;
            target[i]-=nums[index];
        }
        return false;
    }
    
    
    
    public void reverse(int[] nums,int low,int high){
        while(low<high){
            int temp=nums[low];
            nums[low]=nums[high];
            nums[high]=temp;
            low++;
            high--;
        }
    }
}