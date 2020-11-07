import java.net.*;
import java.io.*;

public class MultiEchoServer{
	public static void main(String args[]){
		try{
			ServerSocket s=new ServerSocket(8009);
			while(true){
				Socket incoming =s.accept();
				new ClientHandler(incoming).start();
			}
		}
		catch(Exception e){}
	}
}