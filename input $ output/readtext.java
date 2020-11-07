import java.io.*;
import java.util.*;
public class readtext{
	public static void main(String args[]) throws IOException{
		//bufferedReader and FileReader
		File file=new File("file1.txt");
		BufferedReader br=new BufferedReader(new FileReader(file));
		String st;
		while((st=br.readLine())!=null){
			System.out.println(st);
		}
		//FileReader
		FileReader fr =new FileReader("file1.txt");
		int i;
		while((i=fr.read())!=-1){
			System.out.println((char)i);
		}
		//scanner
		File file1 = new File("file1.txt"); 
        Scanner sc = new Scanner(file1); 
  
        while (sc.hasNextLine()) 
        System.out.println(sc.nextLine());

        //without using loop
		File file2 = new File("file1.txt");
        Scanner sc1 = new Scanner(file2); 
        sc1.useDelimiter("\\Z"); 
        System.out.println(sc1.next()); 
 


	}

}