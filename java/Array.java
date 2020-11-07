import java.util.*;
public class Array {
    public static void main(String args[]){
        int upper=2;
        int lower=1;
        int[] colsum={1,1,1};
        List<List<Integer>> r=reconstructMatrix(upper, lower, colsum);
        System.out.println(r);
    }
    public static List<List<Integer>> reconstructMatrix(int upper, int lower, int[] colsum) {
        int n=colsum.length;
        List<List<Integer>> results=new ArrayList<>();
        boolean[] visited=new boolean[n];
        for(int i=0;i<2;i++){
            List<Integer> temp=new ArrayList<>();
            for(int j=0;j<n;j++){
                temp.add(0);
            }
            results.add(temp);
        }
        System.out.println(results);
        for(int i=0;i<n;i++){
            if(colsum[i]==2){
                visited[i]=true;
                results.get(0).set(i,1);
                results.get(1).set(i,1);
                upper--;
                lower--;
            }
            else if(colsum[i]==0){
                visited[i]=true;
                results.get(0).set(i,0);
                results.get(1).set(i,0);
            }
        }
        System.out.println(results);
        for(int i=0;i<n;i++){
            if(visited[i]==false && lower>0){
                visited[i]=true;
                results.get(1).set(i,1);
                lower--;
            }
        }
        System.out.println(results);
        for(int i=0;i<n;i++){
            if(visited[i]==false && upper>0){
                results.get(0).set(i,1);
                upper--;
            }
        }
        return results;
    }
}
