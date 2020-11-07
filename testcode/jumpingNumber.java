import java.util.*;

public class jumpingNumber {
    public static void main(String args[]) {
        Scanner scan = new Scanner(System.in);
        System.out.println("input the number:");
        int i = scan.nextInt();
        solution(i);
        System.out.println("the number is " + i);
        scan.close();
    }

    public static void solution(int n) {
        for (int i = 0; i < n; i++) {
            boolean flag = false;
            String s = Integer.toString(i);
            char[] c = s.toCharArray();
            for (int j = 0; j < c.length - 1; j++) {
                int a = Integer.parseInt(String.valueOf(c[j]));
                int b = Integer.parseInt(String.valueOf(c[j + 1]));
                if (Math.abs(a - b) != 1) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                System.out.println(i);
            }
        }
    }
}