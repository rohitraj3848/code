import java.util.*;
public class MinArrows{
    public static void main(String args[]){
        int[][] points={{10,16}, {2,8}, {1,6},{7,12}};
        System.out.println(findMinArrowShots(points));

    }
    static int findMinArrowShots(int[][] points) {
        if(points.length==0){
            return 0;
        }
        Arrays.sort(points,new Comparator<int[]>() {
            public int compare(int[] entry1, int[] entry2) { 
            if (entry1[1] > entry2[1]) 
                return 1; 
            else
                return -1; 
          } 

        });
        int arrowpos=points[0][1];
        int arrow=1;
        for(int i=0;i<points.length;i++){
            if(points[i][0]<=arrowpos){
                continue;
            }
            arrow++;
            arrowpos=points[i][1];
        }
        return arrow;
    }
}