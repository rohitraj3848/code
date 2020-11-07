import java.util.Scanner;

//minimum no of flips to convert the binary string to monotonically increasing 00110 - 00111 no of flips =1
public class fliptoMon {
    public static void main(String args[]){
        Scanner scan=new Scanner(System.in);
        String s=scan.nextLine();

        if(s==null || s.length()==0){
            System.out.println("0");
        }
        int ones=0;
        int flip=0;

        for(char c : s.toCharArray()){
            if(c=='0'){
                if(ones!=0){
                    flip++;
                }else{
                    continue;
                }
            }
            else{
                ones++;
            }
            if(flip>ones){
                flip=ones;
            }
        }
        System.out.println(flip);
        scan.close();
    }
}