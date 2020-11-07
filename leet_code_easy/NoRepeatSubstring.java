import java.io.*;
import java.util.*;

public class NoRepeatSubstring {
    public static void main(String args[])throws IOException{
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        String s=br.readLine();
        System.out.println(s);
        int i=0;
        int j=0;
        Set<Character> set=new HashSet<>();
        int max=0;
        int n=s.length();
        while(j<n){
            if(!set.contains(s.charAt(j))){
                set.add(s.charAt(j));
                j++;
                max=Math.max(set.size(),max);
            }
            else{
                set.remove(s.charAt(i));
                i++;
            }
        }
        System.out.println(max);
    }
}