import java.io.*;
import java.net.*;

//chat server  
public class ChatServer{
	//create a server for hosting the chat
	public ChatServer(int port) throws IOException{
		ServerSocket s=new ServerSocket(port);
		while(true)
			new ChatHandler(s.accept()).start();
	}

	public static void main(String args[])throws IOException{
		if(args.length!=1)
			throw new RuntimeException("Syntax: java chatServer <port>");
		new ChatServer(Integer.parseInt(args[0]));
	}
}