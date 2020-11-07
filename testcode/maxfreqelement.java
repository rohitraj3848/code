import java.util.*;
//find the sum of max frequent element in the matrix
public class maxfreqelement {
    public static void main(String[] args){
        int[][] arr={{1,1,1},{2,3,3},{4,5,3}};
        HashMap<Integer,Integer> map=new HashMap<>();
        for(int i=0;i<arr.length;i++){
            for(int j=0;j<arr[0].length;j++){
                map.put(arr[i][j],map.getOrDefault(arr[i][j],0)+1);
            }
        }
        int max=0;
        Set<Map.Entry<Integer,Integer>> set=map.entrySet();
        Iterator<Map.Entry<Integer,Integer>> itr=set.iterator();
        while(itr.hasNext()){
            int value=itr.next().getValue();
            if(value>max){
                max=value;
            }
        }
        itr=set.iterator();
        int sum=0;
        while(itr.hasNext()){
            int key=itr.next().getKey();
            int value=map.get(key);
            if(value==max){
                sum+=(key*value);
            }
        }
        System.out.println(sum);
    }

}

