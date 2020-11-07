import java.util.*;

public class RouteBwnNodes {
    public static void main(String[] args) {
        
    }
    static boolean findRoute(int[][] graph,int i,int j){
        if(i==j){
            return true;
        }
        boolean[] visited =new boolean[graph.length];
        LinkedList<Integer> queue=new LinkedList<>();
        queue.add(i);
        visited[i]=true;
        while(queue.size()>0){
            int u=queue.poll();
            for(int v=0;v<graph.length;v++){
                if(graph[u][v]==1 && visited[v]==false){
                    if(v==j){
                        return true;
                    }else{
                        visited[v]=true;
                        queue.add(v);
                    }
                }
            }
        }

        return false;
    }
}
