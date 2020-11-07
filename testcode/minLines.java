import java.util.*;
public class minLines {
    public static void main(String[] args) {
        int points[][] = 
        { 
            {-1, 3}, 
            {4, 3}, 
            {2, 1}, 
            {-1, -2}, 
            {3, -3} 
        }; 
        List<List<point>> res=findnooflines(points);
        for(int i=0;i<res.size();i++){
            List<point> l=res.get(i);
            for(int j=0;j<l.size();j++){
                System.out.println("[ "+l.get(j).x+" , "+l.get(j).y+" ] ");
            }
            System.out.println();
        }
        
    }
    static List<List<point>> findnooflines(int[][] points){
        List<List<point>> lines=new ArrayList<>();
        Set<Integer> slopes=new HashSet<>();
        for(int i=0;i<points.length;i++){
            for(int j=0;j<points.length;j++){
                List<point> current=new ArrayList<>();
                if(i!=j){
                    if(points[i][0]==points[j][0]){
                        continue;
                    }
                    else{
                        int slope=(points[i][1]-points[j][1])/(points[i][0]-points[j][0]);
                        if(slopes.contains(slope)){
                            continue;
                        }else{
                            slopes.add(slope);
                            current.add(new point(points[i][0],points[i][1]));
                            current.add(new point(points[j][0],points[j][1]));
                            for(int k=0;k<points.length;k++){
                                if(k!=i && k!=j){
                                    if(points[k][1]-points[i][1]==(slope*(points[k][0]-points[i][0]))){
                                        current.add(new point(points[k][0],points[k][1]));
                                    }
                                }
                            }
                        }
                    }
                    
                }
                lines.add(current);
                
            }
        }
        return lines;
    }
}
class point{
    int x;
    int y;
    public point(int x,int y){
        this.x=x;
        this.y=y;
    }
}