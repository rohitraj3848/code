import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PallindromeSubstring {
    public static void main(String args[]) throws IOException{
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        String s=br.readLine();
        int start=0;
        int end=0;
        for(int i=0;i<s.length();i++){
            int len1=maxPallindrome(s, i, i);
            int len2=maxPallindrome(s, i, i+1);
            int len=Math.max(len1, len2);
            if(len > end-start){
                start=i-((len-1)/2);
                end=i+((len)/2);
            }
        }
        System.out.println(s.substring(start, end+1));
    }
    static int maxPallindrome(String s,int left,int right){
        if(s.length()==0 || left>right){
            return 0;
        }
        while(left>=0 && right<s.length() && s.charAt(left)==s.charAt(right)){
            left--;
            right++;
        }
        return right-left-1;
    }
}