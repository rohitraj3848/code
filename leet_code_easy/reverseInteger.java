public class reverseInteger{
    public static void main(String args[]){
        int num=123;
        int num1=-124;
        System.out.println(solution(num));
        System.out.println(solution(num1));
    }
    static int solution(int n){
        long r=0;
        boolean negative=false;
        if(n<0){
            negative=true;
            n=-n;
        }
        while(n>0){
            int digit=n%10;
            r=r*10+digit;
            n=n/10;
        }
        if(negative){
            r=-r;
        }
        if(r>Integer.MAX_VALUE || r<Integer.MIN_VALUE){
            return 0;
        }
        return (int)r;
    }
}