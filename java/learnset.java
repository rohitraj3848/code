import java.util.*;
public class learnset {
    public static void main(String args[]){
        List<Integer> l=List.of(5,3,1,2,2,7,6,3,5,1,1,3,2,1);
        Set<Integer> set=new HashSet<>();
        Set<Integer> sortedset=new TreeSet<>();
        Set<Integer> set1=new LinkedHashSet<>();
        set.addAll(l);
        sortedset.addAll(l);
        set1.addAll(l);
        //System.out.println(set);
        //System.out.println(sortedset);
        //System.out.println(set1);
        System.out.println(set.contains(10));
        set.remove(1);
        System.out.println(set);
        Integer[] arr=new Integer[set.size()];
        arr=set.toArray(arr);
        System.out.println(set.isEmpty());
        Iterator<Integer> it= set.iterator();
        while(it.hasNext()){
            System.out.print(it.next()+" ");
        }
        System.out.println();
    }
}
