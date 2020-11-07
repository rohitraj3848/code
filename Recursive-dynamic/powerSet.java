import java.util.*;
public class powerSet {
    public static void main(String args[]){
        int[] a={1,2,3,4,5};
        List<List<Integer>> sets=AllSubsets(a);
        System.out.println(sets);
        
    }
    public static List<List<Integer>> AllSubsets(int[] a){
        List<List<Integer>> subsets=new ArrayList<>();
        findSubset(0, a,new ArrayList<>(), subsets);
        return subsets;
    }
    public static void findSubset(int index,int[] a,List<Integer> current,List<List<Integer>> subsets){
        subsets.add(new ArrayList<>(current));
        for(int i=index;i<a.length;i++){
            current.add(a[i]);
            findSubset(i+1, a, current, subsets);
            current.remove(current.size()-1);
        }
    }
}