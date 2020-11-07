import java.util.*;
public class RemoveDups {
    public static void main(String args[]){
        int[] r={0,0,1,1,1,2,2,2,3,3,3,3,4};
        System.out.println(Arrays.toString(r));
        List<Integer> l=new ArrayList<>();
        l.add(r[0]);
        for(int i=1;i<r.length;i++){
            if(r[i]==r[i-1]){
                continue;
            }else{
                l.add(r[i]);
            }
        }
        for(Integer i : l){
            System.out.print(i+" ");
        }
        System.out.println();
    }
}