//given an array arrange it in such a way that it produces maximum number
//input {54,546,548,60}
//output {60,548,546,54}
import java.util.*;
public class maxArrange {
    public static void main(String args[]){
        String arr[]={"54","546","548","60"};
        List<String> l=Arrays.asList(arr);
        Collections.sort(l, new Comparator<String>(){
            public int compare(String x,String y){
                String xy=x+y;
                String yx=y+x;
                return xy.compareTo(yx)>0?-1:1;

            }
        });
        System.out.println(l);
    }
}
