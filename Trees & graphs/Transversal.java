import java.util.*;

public class Transversal {
	static LinkedList<Integer> adj_list[];
	static int n=0;
	public static void main(String[] args) {
		Scanner scan=new Scanner(System.in);
		System.out.println("enter the no of nodes");
	    n=scan.nextInt();
		adj_list =new LinkedList[n];
		for (int i=0; i<n; i++) {
            adj_list[i] = new LinkedList<Integer>();
    	}
		addEdge(0, 1); 
        addEdge(0, 2); 
        addEdge(1, 2); 
        addEdge(2, 0); 
        addEdge(2, 3); 
        addEdge(3, 3); 
		boolean[] visited=new boolean[n];
		int[][] graph_adj_matrix= {{0,1,1,0},{1,0,1,0},{1,1,0,1},{0,0,1,0}};
		DFS_adj_matrix(graph_adj_matrix, 1, visited);
		scan.close();
		
	}
	
	public static void addEdge(int v,int w) {
		adj_list[v].add(w);
		adj_list[w].add(v);
	}

	public static void DFS_adj_matrix(int[][] graph,int v,boolean[] visited) {
		int n=graph.length;
		if(!visited[v]){
			visited[v]=true;
			System.out.println(v+" ");
			for(int i=0;i<n;i++){
				if(graph[v][i]==1 && visited[i]==false){
					DFS_adj_matrix(graph, i, visited);
				}
			}
		}
	}
	
	public static void DFS_adj_List(int v,LinkedList<Integer> graph[],boolean[] visited) {
		if(!visited[v]){
			visited[v]=true;
			System.out.print(v+" ");
			for(int i=0;i<graph[v].size();i++){
				if(visited[graph[v].get(i)]==false){
					int u=graph[v].get(i);
					DFS_adj_List(u, graph, visited);
				}
			}
		}
	}
	
	public static void BFS_adj_matrix(int[][] graph,int n,int v) {
		boolean[] visited=new boolean[n];
		LinkedList<Integer> queue=new LinkedList<>();
		visited[v]=true;
		queue.add(v);
		while(queue.size()!=0){
			int i=queue.poll();
			System.out.print(i+" ");
			for(int j=0;j<n;j++){
				if(graph[i][j]==1 && visited[j]==false){
					visited[j]=true;
					queue.add(j);
				}
			}
		}
	}
	
	public static void BFS_adj_List(LinkedList<Integer> graph[],int n,int v) {
		boolean[] visited=new boolean[n];
		LinkedList<Integer> queue=new LinkedList<>();
		visited[v]=true;
		queue.add(v);
		while(queue.size()!=0){
			int i=queue.poll();
			System.out.print(i+" ");
			for(int j=0;j<graph[i].size();j++){
				if(visited[graph[i].get(j)]==false){
					int u=graph[i].get(j);
					visited[u]=true;
					queue.add(u);

				}
			}
		}
		
	}

}
