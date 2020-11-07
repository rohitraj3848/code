import java.util.*;
import java.io.*;
 
class iodemo
{
	public static void main(String args[]) throws IOException
	{
		Scanner scan=new Scanner(System.in);
		FileOutputStream fout=new FileOutputStream("file1.txt");

		System.out.println("content to write in file1:");
		String l="";
		String ls=System.getProperty("line.separator");
		while(!l.equals("end")){
			l=scan.nextLine();
			byte[] bit=l.getBytes();
			fout.write(bit);
			fout.write(ls.getBytes());
		    fout.flush();
	    }
	    fout.close();
	

		FileInputStream fin = new FileInputStream("file1.txt"); 
		BufferedInputStream bin = new BufferedInputStream(fin);

		 
		System.out.println("Number of remaining bytes:" + bin.available()); 

	 
		boolean b=bin.markSupported(); 
		if (b) 
			bin.mark(bin.available()); 

		
		System.out.println("FileContents :"); 

		
		int ch; 
		while ((ch=bin.read()) != -1) 
			System.out.print((char)ch); 

		
		bin.reset(); 
		while ((ch=bin.read()) != -1) 
			System.out.print((char)ch); 

		
		fin.close(); 
	} 
} 
