import java.io.*;
import java.util.*;

public class Roadandlibraries {

    // Complete the roadsAndLibraries function below.
    static long roadsAndLibraries(int n, int c_lib, int c_road, int[][] cities) {
        LinkedList<Integer> l=new LinkedList<>();
        int[][] graph=new int[n][n];
        for(int i=0;i<cities.length;i++){
            graph[cities[i][0]-1][cities[i][1]-1]=1;
            graph[cities[i][1]-1][cities[i][0]-1]=1;
        }
        boolean[] visited=new boolean[n];
        for(int i=0;i<n;i++){
            if(!visited[i]){
                int no_of_cities=visit(i,graph,visited);
                l.add(no_of_cities);
            }
        }
        long road_cost=0;
        for(int j=0;j<l.size();j++){
            road_cost+=c_road*(l.get(j)-1);
        }
        for(int i=0;i<l.size();i++){
            System.out.print(l.get(i)+" ");
        }
        System.out.println();
        long lib_cost=c_lib*l.size();
        if(n*c_lib< road_cost+lib_cost){
            return (long)n*c_lib;
        }
        return road_cost+lib_cost;
    }

    static int visit(int node,int[][] graph,boolean[] visited){
        int count=0;
        LinkedList<Integer> queue=new LinkedList<>();
        queue.add(node);
        visited[node]=true;
        while(queue.size()!=0){
            int nextnode=queue.poll();
            count++;
            for(int i=0;i<graph.length;i++){
                if(graph[nextnode][i]==1 && visited[i]==false){
                    visited[i]=true;
                    queue.add(i);
                }
            }
        }
        return count;
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(System.out));

        int q = scanner.nextInt();
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

        for (int qItr = 0; qItr < q; qItr++) {
            String[] nmC_libC_road = scanner.nextLine().split(" ");

            int n = Integer.parseInt(nmC_libC_road[0]);

            int m = Integer.parseInt(nmC_libC_road[1]);

            int c_lib = Integer.parseInt(nmC_libC_road[2]);

            int c_road = Integer.parseInt(nmC_libC_road[3]);

            int[][] cities = new int[m][2];

            for (int i = 0; i < m; i++) {
                String[] citiesRowItems = scanner.nextLine().split(" ");
                scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

                for (int j = 0; j < 2; j++) {
                    int citiesItem = Integer.parseInt(citiesRowItems[j]);
                    cities[i][j] = citiesItem;
                }
            }

            long result = roadsAndLibraries(n, c_lib, c_road, cities);

            bufferedWriter.write(String.valueOf(result));
            bufferedWriter.newLine();
        }

        bufferedWriter.close();

        scanner.close();
    }
}
