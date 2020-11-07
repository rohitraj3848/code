import java.util.*;
public class LargestRec{
    public static void main(String argsp[]) {
        int[] h={1,2,3,4,5};
        System.out.println(largestRectangle(h));
    }
    static long largestRectangle(int[] h) {
        Stack<int[]> s = new Stack<>(); // Create stack of span = [i, j]
        int n = h.length;
        h = Arrays.copyOf(h, n+1); // Append a sentinel to array h
        int j;
        int maximum = 0;
        for(int i = 0; i <= n; i++){
            for(j=i; !s.isEmpty() && h[s.peek()[0]] >= h[i];) {
                int[] x = s.pop();
                j = x[1];
                maximum = Math.max(maximum, h[x[0]] * (i - j));
            }
            s.push(new int[]{i, j});
        }
        return maximum;
    }
}