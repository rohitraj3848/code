import java.util.*;
import java.io.*;
public class Solution {
    static BufferedWriter bw;
    public static void solve(int books,int libs,int days,int[] scores,List<List<Integer>> libdata,List<List<Integer>> libbooks){
        HashMap<Integer,Integer> map=new HashMap<>();
        for(int i=0;i<scores.length;i++){
            map.put(i,scores[i]);
        }
        List<Integer> signupdays=new ArrayList<>();
        for(int i=0;i<libs;i++){
            signupdays.add(libdata.get(i).get(1));
        }
        List<Integer> noofbooks=new ArrayList<>();
        for(int i=0;i<libs;i++){
            noofbooks.add(libdata.get(i).get(0));
        }
        List<Integer> maxsentbooks=new ArrayList<>();
        for(int i=0;i<libs;i++){
            maxsentbooks.add(libdata.get(i).get(2));
        }
        int signup=0;
        for(int i=0;i<days;i++){
            signup=Collections.min(signupdays);
        }
    }
}