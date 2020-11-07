import java.io.*;
import java.util.*;


public class Solution {

    // Complete the flatlandSpaceStations function below.
    static int flatlandSpaceStations(int n, int[] c) {
        Set<Integer> set=new HashSet<>();
        for(int i : c){
            set.add(i);
        }
        int max=0;
        for(int i=0;i<n;i++){
            int min=0;
            if(set.contains(i)){
                min=0;
            }
            else{
                int min1=0;
                int min2=0;
                for(int j=i;j<n;j++){
                    if(set.contains(j)){
                        min1=(j-i);
                        break;
                    }
                }
                for(int j=i;j>=0;j--){
                    if(set.contains(j)){
                        min2=(i-j);
                        break;
                    }
                }
                if(min1==0){
                    min=min2;
                }
                if(min2==0){
                    min=min1;
                }
                if(min1<min2 && min1!=0 && min2!=0){
                    min=min1;
                }
                if(min1>min2 && min1!=0 && min2!=0){
                    min=min2;
                }
                if(min1==min2){
                    min=min1;
                }
            }
            if(min>max){
                max=min;
            }
        }
        return max;
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(System.out));

        String[] nm = scanner.nextLine().split(" ");

        int n = Integer.parseInt(nm[0]);

        int m = Integer.parseInt(nm[1]);

        int[] c = new int[m];

        String[] cItems = scanner.nextLine().split(" ");
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

        for (int i = 0; i < m; i++) {
            int cItem = Integer.parseInt(cItems[i]);
            c[i] = cItem;
            
        }

        int result = flatlandSpaceStations(n, c);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedWriter.close();

        scanner.close();
    }
}
