import java.util.*;
public class Top_sort {
    public static void topological_sort(LinkedList<Integer> graph[],int n) {
    	Stack<Integer> stack=new Stack<>();
    	boolean[] visited=new boolean[n];
    	for(int i=0;i<n;i++) {
    		if(visited[i]==false) {
    			top_sort(graph,i,visited,stack);
    		}
    	}
    	while(stack.empty()==false) {
    		System.out.print(stack.pop()+" ");
    	}
    	
    }
    
    public static void top_sort(LinkedList<Integer> graph[],int v,boolean[] visited,Stack<Integer> stack) {
    	visited[v]=true;
    	Integer i;
    	Iterator<Integer> it=graph[v].iterator();
    	while(it.hasNext()) {
    		i=it.next();
    		if(!visited[i]) {
    			top_sort(graph,i,visited,stack);
    		}
    	}
    	stack.push(v);
    }
}
