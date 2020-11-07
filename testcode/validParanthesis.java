import java.util.*;
public class validParanthesis {
    public static void main(String[] args) {
        String s="((){})";
        System.out.println(isValid(s));
    }
    static boolean isValid(String s){
        Stack<Character> stack=new Stack<>();
        HashMap<Character,Character> mapping=new HashMap<>();
        mapping.put(')','(');
        mapping.put('}','{');
        mapping.put(']','[');
        for(int i=0;i<s.length();i++){
            char c=s.charAt(i);
            if(mapping.containsKey(c)){
                char top=stack.empty() ? 'o' : stack.pop();
                if(top!=mapping.get(c)){
                    return false;
                }
            }
            else{
                stack.push(c);
            }
        }
        return stack.isEmpty();
    }
}
