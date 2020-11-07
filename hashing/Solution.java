import java.util.*;
public class Solution{
    public static void main(String args[]){
        List<Long> arr=new ArrayList<>();
        for(int i=0;i<100;i++){
            arr.add(1L);
        }
        long r=1;
        System.out.println(countTriplets(arr, r));
    }
    private static long countTriplets(List<Long> arr, long r) {
        Map<Long, Long> potential = new HashMap<>();
        Map<Long, Long> counter = new HashMap<>();
        long count = 0;
        for (int i = 0; i < arr.size(); i++) {
            long a = arr.get(i);
            long key = a / r;
            
            if (counter.containsKey(key) && a % r == 0) {
                count += counter.get(key);
            }
            
            if (potential.containsKey(key) && a % r == 0) {
                long c = potential.get(key);
                counter.put(a, counter.getOrDefault(a, 0L) + c);
            }
            
            potential.put(a, potential.getOrDefault(a, 0L) + 1); 
        }
        return count;
    }
    /*static long countTriplets(List<Long> arr, long r) {
        Map<Long,Long> mapright=new HashMap<>();
        Map<Long,Long> mapleft=new HashMap<>();
        for(long a :arr){
            mapright.put(a,mapright.getOrDefault(a,0L)+1);
        }

        long count=0L;
        for(int i=0;i<arr.size();i++){
            long c1=0L;
            long c2=0L;
            long ar=arr.get(i);
            mapleft.put(ar,mapleft.getOrDefault(ar,0L)+1);
            mapright.put(ar,mapright.getOrDefault(ar,0L)-1);
            long key1=ar/r;
            long key2=ar*r;
            if(mapleft.containsKey(key1) && (ar % r)==0){
                c1=mapleft.get(key1);
            }
            if(mapright.containsKey(key2) && (ar % r)==0){
                c2=mapright.get(key2);
            }
            if(c1 !=0L && c2 != 0L){
                count+=(c1*c2);
            }
        }
        return count;

    }*/
}