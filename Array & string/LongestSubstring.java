import java.util.*;
public class LongestSubstring{
    //length of max substring with no repeating character
    public static void main(String args[]){
        String s="abcabcbb";
        String s1="bbbbb";
        String s2="pwwkew";
        System.out.println(solution(s));
        System.out.println(solution(s1));
        System.out.println(solution(s2));
        System.out.println(maxNonrepeatingstring(s));
        System.out.println(maxNonrepeatingstring(s1));
        System.out.println(maxNonrepeatingstring(s2));
    }


    static int solution(String s){
        if(s.length()==0){
            return 0;
        }
        int max=0;
        Map<Character,Integer> map=new HashMap<>();
        for(int i=0,j=0;i<s.length();++i){
            if(map.containsKey(s.charAt(i))){
                j=Math.max(j,map.get(s.charAt(i))+1);
            }
            map.put(s.charAt(i),i);
            max=Math.max(max,i-j+1);
        }
        return max;
    }
    public static int maxNonrepeatingstring(String s){
        int max=0;
        int start_index=0;
        int end_index=0;
        Set<Character> set=new HashSet<>();
        while(end_index<s.length()){
            if(!set.contains(s.charAt(end_index))){
                set.add(s.charAt(end_index));
                end_index++;
                max=Math.max(max, set.size());
            }
            else{
                set.remove(s.charAt(start_index));
                start_index++;
            }
        }
        return max;
    }

}