import java.util.*;
public class knightDialer
{   
  /*  int mod=(int)1e9+7;
    public int KnightDialer(int N) {
    Dictionary map = new Dictionary();

    map.Add(0, new int[] { 4, 6, });
    map.Add(1, new int[] { 6, 8 });
    map.Add(2, new int[] { 7, 9 });
    map.Add(3, new int[] { 4, 8 });
    map.Add(4, new int[] { 0, 3, 9 });
    map.Add(5, new int[] { });
    map.Add(6, new int[] { 0, 1, 7 });
    map.Add(7, new int[] { 2, 6 });
    map.Add(8, new int[] { 1, 3 });
    map.Add(9, new int[] { 2, 4 });

    //DP
    int[] previous = new int[10];
    int[] current = new int[10];

    //N=1
    for (int i = 0; i < 10; i++)
    {
    previous[i] = 1;
    }
    current = (int[])previous.Clone();

    //N>1
    for (int i = 1; i < N; i++)
    {
    current = new int[10];
    for (int j = 0; j < 10; j++)
    {
    current[j]= 0;
    int[] mapArray = map[j];
    for (int z = 0; z < mapArray.Length; z++)
    {
    current[j] = (current[j] + previous[mapArray[z]]) % mod;
    }
    }

    previous = (int[])current.Clone();
    }

    int sum = 0;
    for (int i = 0; i < 10; i++)
    {
    sum = (sum + current[i]) % mod;
    }

    return sum;
}


        public static void main(String[] args) {
        int N=3;
        System.out.println(KnightDialer(N));
    }
    */
}


