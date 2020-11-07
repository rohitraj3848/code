public class bitwiseAndOfRange {
    public static void main(String args[]){
        System.out.println(rangeBitwiseAnd(5,7));
    }
    public static int rangeBitwiseAnd(int m, int n) {
        int result=0;
        while(m>0 && n>0){
            int msb_m=find_msb(m);
            int msb_n=find_msb(n);
            System.out.println(msb_m+" "+msb_n);
            if(msb_m!=msb_n){
                break;
            }
            
            int val=(1<<msb_m);
            System.out.println("raised power = "+val);
            result+=val;
            System.out.println("result = "+result);
            m=m-val;
            n=n-val;
            System.out.println("value of m and n is "+m +" "+n);
            System.out.println();
        }
        return result;
        
    }
    
    static int find_msb(int a){
        if(a==0){
            return 0;
        }
        int msb=0;
        while(a!=0){
            a=a/2;
            msb++;
        }
        
        return msb-1;
    }

}
