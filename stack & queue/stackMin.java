import java.io.*;
import java.util.*;

public class stackMin{
	public static void main(String args[]){
		Stack3in1 s=new Stack3in1(5);
		s.push(1,2);
		s.push(1,4);
		s.push(3,5);
		s.push(2,6);
		int a=s.pop(2);
		int b=s.peek(1);
		System.out.println(a+" "+b);
	}
}