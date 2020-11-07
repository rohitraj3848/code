import java.util.*;
public class learnMap{
    public static void main(String args[]){
        int[] arr={2,1,4,5,2,3};
        Map<Integer,Integer> map=new HashMap<>();
        Map<Integer,Integer> sortedmap=new TreeMap<>();
        Map<Integer,Integer> samemap=new LinkedHashMap<>();
        for(int i=0;i<arr.length;i++){
            map.put(arr[i],0);
            sortedmap.put(arr[i],0);
            samemap.put(arr[i],0);
        }
        System.out.println(map.containsKey(1));
        System.out.println(map.containsValue(1));
        Set<Map.Entry<Integer,Integer>> set=map.entrySet();
        Iterator<Map.Entry<Integer,Integer>> it=set.iterator();
        while(it.hasNext()){
            int key=it.next().getKey();
            System.out.println(key+" --> "+map.get(key));
        }
        Set<Integer> set2=map.keySet();
        System.out.println(set2);
        map.remove(4);
        map.remove(2,0);
        System.out.println(map);
    }
}