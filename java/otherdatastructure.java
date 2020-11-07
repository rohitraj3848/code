import java.util.PriorityQueue;

public class otherdatastructure {
    public static void main(String[] args) {
        PriorityQueue<Integer> pq=new PriorityQueue<>();
        int[] ar={1,2,9,6,5,3,4,2,7};
        for(int i=0;i<ar.length;i++){
            pq.add((-1*ar[i]));
        }
        while(!pq.isEmpty()){
            System.out.print(-1*pq.poll()+" ");
        }
        System.out.println();
    }
}
