//no of ways to place 4*1 tiles in 5*4 rooms  or   n*4
public class filltiles {
    public static void main(String[] args) {
        int n=6;
        System.out.println(fill(n));
    }
    static int fill(int n){
        if(n<0){
            return 0;
        }
        if(n<4){
            return 1;
        }
        if(n==4){
            return 2;
        }
        return fill(n-1)+fill(n-4);
    }

}
