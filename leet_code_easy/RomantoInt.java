import java.io.*;
/*I=1
  V=5
  X=10
  L=50
  C=100
  D=500
  M=1000
*/
public class RomantoInt {
    public static void main(String args[]) throws IOException{
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        String s=br.readLine();
        System.out.println(solution(s));

    }
    static int solution(String s){
        int value=0;
        for(int i=s.length()-1;i>=0;i--){
            switch(s.charAt(i)){
                case 'M':
                value+=1000;
                break;

                case 'D':
                value+=500;
                break;

                case 'C':
                value+=100*(value>=500 ? -1 : 1);
                break;

                case 'L':
                value+=50;
                break;

                case 'X':
                value+=10*(value>=50?-1:1);
                break;

                case 'V':
                value+=5;
                break;

                case 'I':
                value+=(value>=5?-1:1);
                break;

                default:
                break;

            }
        }
        return value;
    }

}