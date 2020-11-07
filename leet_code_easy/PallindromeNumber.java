public class PallindromeNumber {
    public static void main(String args[]){
        int num=121;
        int num1=-121;
        int num2=10;
        System.out.println(solution(num));
        System.out.println(solution(num1));
        System.out.println(solution(num2));
    }
    static boolean solution(int n){
        if(n<0 || (n%10)==0){
            return false;
        }
        String s=Integer.toString(n);
        int length=s.length();
        boolean r=true;
        for(int i=0;i<length/2;i++){
            if(s.charAt(i)==s.charAt(length-i-1)){
                continue;
            }else{
                r=false;
                break;
            }
        }
        if(r){
            return true;
        }
        return false;
    }
}