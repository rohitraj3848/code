import java.util.*;

public class GroupAnagrams{
	public static void main(String args[]){
		String[] a={"rohit","abhinav","ratan","rajat","ithor","taran","jarat"};
		Arrays.sort(a,new AnagramComparator());
		System.out.println(Arrays.toString(a));
	}
}

class AnagramComparator implements Comparator<String>{
	 public String sortChars(String s){
	 	char[] content=s.toCharArray();
	 	Arrays.sort(content);
	 	return new String(content);
	 }

	 public int compare(String s1,String s2){
	 	return sortChars(s1).compareTo(sortChars(s2));
	 }
}