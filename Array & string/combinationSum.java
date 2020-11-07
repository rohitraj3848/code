import java.util.*;

public class combinationSum{
	public static void main(String args[]){
		int[] arr={7,6,2,3,5};
		List<List<Integer>> re=sum1(arr,7);
		System.out.println(re);
	}

	public static  List<List<Integer>> sum1(int[] arr,int target){
		List<List<Integer>> list=new ArrayList<>();
		Arrays.sort(arr);
		getCombination(list,new ArrayList<>(),arr,0,target);
		return list;

	}

	public static void getCombination(List<List<Integer>> list,List<Integer> templist,int[] nums,int start,int remain){
		if(remain<0){
			return;
		}
		if(remain==0){
			list.add(new ArrayList<>(templist));
		}
		else{
			for(int i=start;i<nums.length;i++){
				templist.add(nums[i]);
				getCombination(list,templist,nums,i,remain-nums[i]);
				templist.remove(templist.size()-1);
			}
		}
	}

}

