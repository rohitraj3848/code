
import java.io.*;
import java.net.*;
public class EchoServer {
	public static void main(String args[]) {
		try {
			ServerSocket s=new ServerSocket(8008);
			while(true) {
				Socket incoming=s.accept();
				BufferedReader in=new BufferedReader(new InputStreamReader(incoming.getInputStream()));
				PrintWriter out=new PrintWriter(new OutputStreamWriter(incoming.getOutputStream()));
				out.println("helllo! this is java EchoServer.");
				out.println("Enter BYE to exit.");
				out.flush();
				while(true) {
					String str=in.readLine();
					if(str==null)
						break;
					out.println("Echo: "+str);
					out.flush();
					if(str.trim().equals("BYE"))
						break;
				}
				in.close();
				out.close();
				incoming.close();
				s.close();
				
			}
		}catch(Exception e) {
			
		}
	}
}
