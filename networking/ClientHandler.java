import java.io.*;
import java.net.*;

public class ClientHandler extends Thread{
	protected Socket incoming;

	public ClientHandler(Socket incoming){
		this.incoming=incoming;
	}

	public void run(){
		try{
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
		}catch(Exception e){}
	}
}