import java.io.*;
public class console{
	public static void main(String args[]){
		String str;
		Console con;

		con=System.console();
		if(con==null)
			return;
		str=con.readLine("Enter a String:");
		con.printf("here is the String:%s\n",str);
	}
}