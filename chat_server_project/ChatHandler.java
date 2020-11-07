import java.io.*;
import java.net.*;
import java.util.*;

//class to handle chat an interaction between server and the client
public class ChatHandler extends Thread{
	//socket for each client 
	Socket socket;
	DataInputStream in;
	DataOutputStream out;

	//set of all the client to the chat server
	static Set<ChatHandler> handlers=new HashSet<ChatHandler>();

    //constructor
	public ChatHandler(Socket socket)throws IOException{
		this.socket=socket;
		in=new DataInputStream(socket.getInputStream());
		out=new DataOutputStream(socket.getOutputStream());
		handlers.add(this);
	}


    //creating different thread for each client 
	public void run(){
		String name="";
		try{
			name=in.readUTF();
			System.out.println("new client "+name+"from "+socket.getInetAddress());
			broadcast(name+" entered");
			while(true){
				broadcast(name+" :"+in.readUTF());
			}
		}catch(IOException e){
			System.out.println("--connection to user lost.");
		}
		finally{
			handlers.remove(this);
			try{
			broadcast(name+" left");
			in.close();
			out.close();
			socket.close();
		}
		catch(IOException e){}
		}

	}
	//synchronizing the  messages sent by each client and also barodcasting to others 
	static synchronized void broadcast(String message)throws IOException{
		for(ChatHandler handler :handlers){
			handler.out.writeUTF(message);
			handler.out.flush();
		}
	}
}