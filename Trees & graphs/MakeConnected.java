import java.util.*;
public class MakeConnected {
    public static void main(String[] args) {
        
    }
    public static int makeConnected(int n, int[][] connections) {
        DSU du = new DSU(n);
        int extraConnection = 0;
        for(int[] con : connections) {
            if(!du.merge(con[0], con[1])) {
                extraConnection++;
            }
        }
        Set<Integer> group = new HashSet<>();
        for(int i = 0; i < n; i++) {
            group.add(du.findParent(i));
        }
        return (group.size() - 1 > extraConnection) ? -1 : group.size() - 1;
    }

}
class DSU {
        
        int[] group;
        
        DSU(int n) {
            group = new int[n];
            for(int i = 0; i < n; i++) {
                group[i] = i;
            }
        }
        
        boolean merge(int a, int b) {
            if(findParent(a) == findParent(b)) return false;
            group[findParent(a)] = group[findParent(b)];
            return true;
        }
        
        int findParent(int a) {
            if(group[a] != a) {
                group[a] = findParent(group[a]);
            }
            return group[a];
        }
        
        
    }