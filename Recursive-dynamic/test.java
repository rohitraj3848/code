
import java.util.*;
public class test{
    public static void main(String args[]){
        //Scanner scan=new Scanner(System.in);
       String text="abcabcabc";
       System.out.println(distinctEchoSubstrings(text));

    }
    public static int distinctEchoSubstrings(String text) {
        int n=text.length();
        if(text.length()==0){
            return 0;
        }
        Set<String> set=new HashSet<>();
        int num=0;
        for (int i = 0; i < n; i++){
            for (int j = i+1; j <= n; j++){
                String str=text.substring(i,j);
                if(str.length()%2==0 && !set.contains(str)){
                    set.add(str);
                    int mid=str.length()/2;
                    String left=str.substring(0,mid);
                    String right=str.substring(mid,str.length());
                    if(left.hashCode() == right.hashCode()){
                        num++;
                        System.out.println(str);
                    }
                }
            }

        }
        return num;
    }
    

}