import java.util.*;
public class WordBreak {
    public static void main(String args[]){
        
    }
    public static boolean wordbreak(String s,int index,Set<String> set){
        if(s.length()==0){
            return true;
        }
        for(int i=index;i<=s.length();i++){
            if(set.contains(s.substring(0,i)) && wordbreak(s,i, set)){
                return true;
            }
        }
        return false;
    }
    //given a non-empty string and a non-empty set of strings
    //return whether the string can be formed by using string of set
    public static boolean solution(String s,Set<String> set){
        int n=s.length();
        boolean[] dp=new boolean[n+1];
        dp[0]=true;
        for(int i=1;i<=n;i++){
            for(int j=0;j<i;j++){
                if(dp[j] && set.contains(s.substring(j,i))){
                    dp[i]=true;
                    break;
                }
            }
        }
        return dp[n];
    }
    public boolean wordBreak(String s, List<String> wordDict) {
        Node t = new Node();
		for (String word: wordDict) {
			insertTrie(t, word);
		}
        if(wordBreak(t,s)){
            return true;
        }
        return false;
    }
    public static void insertTrie(Node head, String str)
	{
		Node node = head;
		for (char c: str.toCharArray())
		{
			if (node.next[c - 'a'] == null) {
				node.next[c - 'a'] = new Node();
			}
			node = node.next[c - 'a'];
		}
		node.exist = true;
	}
    public static boolean wordBreak(Node head, String str)
	{
		boolean[] good = new boolean[str.length() + 1];
		good[0] = true;

		for (int i = 0; i < str.length(); i++)
		{
			if (good[i])
			{
				Node node = head;
				for (int j = i; j < str.length(); j++)
				{
					if (node == null) {
						break;
					}

					node = node.next[str.charAt(j) - 'a'];
					if (node != null && node.exist) {
						good[j + 1] = true;
					}
				}
			}
		}
        return good[str.length()];
    }

}
class Node{
	int CHAR_SIZE = 26;
	boolean exist;
	Node[] next;
	Node() {
		next = new Node[CHAR_SIZE];
		exist = false;
	}
}