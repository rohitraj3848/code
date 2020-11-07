import java.util.*;
public class ContinuousSubArraySum {
    public static void main(String[] args) {
        
    }
    //given k find sum of subarray atleast 2 in length such that it divides k or multiple of k
    //solution is based on  if a%k=c and b%k=c then (a-b)%k=0 because a=m*k+c b=n*k+c (a-b)=(m-n)*k
    public boolean checkSubarraySum(int[] nums, int k) {
        if(nums==null || nums.length<=1){
            return false;
        }
        int n=nums.length;
        int[] presum=new int[n];
        presum[0]=nums[0];
        for(int i=1;i<n;i++){
            presum[i]=nums[i]+presum[i-1];
        }
        Map<Integer,Integer> map=new HashMap<>();
        map.put(0,-1);
        for(int i=0;i<n;i++){
            int res=presum[i];
            if(k!=0){
                res=res%k;
            }
            if(map.containsKey(res) && (i-map.get(res)>1)){
                return true;
            }
            if(!map.containsKey(res)){
                map.put(res,i);
            }
        }
        return false;
    }
}
