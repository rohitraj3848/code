/**/ 

import java.util.*;
public class Larry_Array {
    static String larrysArray(int[] A) {
        Map<Integer,Integer> map=new HashMap<>();
        for(int i=0;i<A.length;i++){
            map.put(A[i],i);
        }
        int index=0;
        while(index<A.length){
            if(A[index]==index+1){
                index++;
                continue;
            }
            int nextmin=map.get(index+1);
            if(nextmin-index>=2){
                int temp=A[nextmin-2];
                A[nextmin-2]=A[nextmin-1];
                A[nextmin-1]=A[nextmin];
                A[nextmin]=temp;

                map.put(A[nextmin],nextmin);
                map.put(A[nextmin-1],nextmin);
                map.put(A[nextmin-2],nextmin-2);
            }
            else if(nextmin-index==1){
                if(nextmin==A.length-1)return "NO";

                int temp=A[nextmin-1];
                A[nextmin-1]=A[nextmin];
                A[nextmin]=A[nextmin+1];
                A[nextmin+1]=temp;

                map.put(A[nextmin],nextmin);
                map.put(A[nextmin-1],nextmin);
                map.put(A[nextmin+1],nextmin+1);
            }
        }
        return index==A.length ? "YES" : "NO";
    }
}