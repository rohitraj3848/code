//find prime factors of number in most optimized way
//54 - 2,3,3,3
//120 - 2,2,2,3,5
import java.util.*;
public class primeFactors {
    public static void main(String args[]){
        int n=12;
        List<Integer> l=new ArrayList<>();
        while(n%2==0){
            n=n/2;
            l.add(2);
        }
        for(int i=3;i<=Math.sqrt(n);i++){
            if(n%i==0){
                while(n%i==0){
                    n=n/i;
                    l.add(i);
                }
            }
        }
        if(n>2){
            l.add(n);
        }
        System.out.println(l);
    }
}
