import java.util.*;
public class TwoSum {
    public static void main(String args[]){
        int[] arr={2,7,11,15};
        int target=9;
        System.out.println(Arrays.toString(solution(arr,target)));

    }
    static int[] solution(int[] a,int target){
        Map<Integer,Integer> m=new HashMap<>();
        for(int i=0;i<a.length;i++){
            int re=target-a[i];
            if(m.containsKey(re)){
                return new int[]{i,m.get(re)};
            }
            m.put(a[i],i);
        }
        throw new IllegalArgumentException("sum not found");
    }
}