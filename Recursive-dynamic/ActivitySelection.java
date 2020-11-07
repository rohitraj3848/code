import java.util.*;
public class ActivitySelection {
    public static void main(String[] args) {
        List<Pair> jobs = Arrays.asList(
				Pair.of(1, 4), Pair.of(3, 5), Pair.of(0, 6),
				Pair.of(5, 7), Pair.of(3, 8), Pair.of(5, 9),
				Pair.of(6, 10), Pair.of(8, 11), Pair.of(8, 12),
				Pair.of(2, 13), Pair.of(12, 14)
        );
        System.out.println(maxpairs(jobs));
    }
    static int maxpairs(List<Pair> jobs){
        int n=jobs.size();
        int dp[]=new int[n];

        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(jobs.get(j).finish<jobs.get(i).start && dp[i]<dp[j]){
                    dp[i]=dp[j];
                }
            }
            dp[i]++;
        }
        int max=0;
        for(int i=0;i<n;i++){
            if(dp[i]>max){
                max=dp[i];
            }
        }
        return max;


    }
}
class Pair
{
	public final int start;		// start field of a Pair
	public final int finish; 	// finish field of a Pair

	// Constructs a new Pair with specified values
	private Pair(int start, int finish)
	{
		this.start = start;
		this.finish = finish;
	}

	// Factory method for creating a Typed Pair immutable instance
	public static Pair of(int a, int b)
	{
		// calls private constructor
		return new Pair(a, b);
	}
}
