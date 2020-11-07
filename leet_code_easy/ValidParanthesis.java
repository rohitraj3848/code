import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;

public class ValidParanthesis {
    public static void main(String args[]) throws IOException{
        BufferedReader br =new BufferedReader(new InputStreamReader(System.in));
        String s=br.readLine();
        System.out.println(solution(s));   
     }

     static boolean solution(String s){
         Stack<Character> st=new Stack<>();
         for(int i=0;i<s.length();i++){
             if(s.charAt(i)=='(' || s.charAt(i)=='{' || s.charAt(i)=='['){
                 st.push(s.charAt(i));
             }
             else{
                 char c=st.peek();
                 if(c=='{'){
                     if(s.charAt(i)=='}'){
                         st.pop();
                     }
                 }
                 else if(c=='['){
                    if(s.charAt(i)==']'){
                        st.pop();
                    }
                }
                else if(c=='('){
                    if(s.charAt(i)==')'){
                        st.pop();
                    }
                }
             }
         }
         if(st.empty()){
             return true;
         }
         return false;
     }
}