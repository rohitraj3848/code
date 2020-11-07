import java.util.*;
public class problem1{
    public static void main(String[] args) {
        Scanner scan=new Scanner(System.in);
        int cases=scan.nextInt();
        for(int i=0;i<cases;i++){
            int a=scan.nextInt();
            int b=scan.nextInt();
            System.out.println(getMin(a,b));
        }
        scan.close();
    }
    //output the min value of (a^x)+(b^x)
    static int getMin(int a,int b){
        int max=Math.max(a,b);
        int min=Math.min(a,b);
        int result=Integer.MAX_VALUE;
        for(int i=0;i<=min;i++){
            int temp=(max^i)+(min^i);
            if(result>temp){
                result=temp;
            }
        }
        return result;
    }
}