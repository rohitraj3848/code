import java.util.*;
public class AllPermutation {
   public static void main(String[] args) {
       String s="abcd";
       ArrayList<String> res=getperm(s);
       System.out.println(res);
       permute(s, 0, s.length()-1);
       System.out.println(set);

   } 

   static ArrayList<String> getperm(String s){
       if(s==null){
           return null;
       }
       ArrayList<String> permutations=new ArrayList<>();
       if(s.length()==0){
            permutations.add("");
            return permutations;
       }
       char first=s.charAt(0);
       String remainder=s.substring(1);
       ArrayList<String> words=getperm(remainder);
       for(String word : words){
            for(int i=0;i<word.length();i++){
                String perm=insertCharAt(word,first,i);
                permutations.add(perm);
                System.out.println(permutations);
            }
       }
       return permutations;
   }
   static String insertCharAt(String word,char c,int i){
       String start=word.substring(0, i);
       String end=word.substring(i);
       return start+c+end;
   }
   static String swap(String a,int i,int j){
        char[] c=a.toCharArray();
        char temp=c[i];
        c[i]=c[j];
        c[j]=temp;
        return String.valueOf(c);
   }
   static TreeSet<String> set=new TreeSet<>();
   static void permute(String s,int l,int r){
       if(l==r){
           set.add(s);
           return;
       }
       else{
           for(int i=l;i<=r;i++){
               s=swap(s,l,i);
               permute(s, l+1, r);
               s=swap(s, l, i);
           }
       }
   }
}
/*public static String subsequences(String word) {
    2     if (word.isEmpty()) {
    3         return ""; // base case
    4     } else {
    5         char firstLetter = word.charAt(0);
    6         String restOfWord = word.substring(1);
    7         
    8         String subsequencesOfRest = subsequences(restOfWord);
    9         
   10         String result = "";
   11         for (String subsequence : subsequencesOfRest.split(",", -1)) {
   12             result += "," + subsequence;
   13             result += "," + firstLetter + subsequence;
   14         }
   15         result = result.substring(1); // remove extra leading comma
   16         return result;
   17     }
   18 }
*/