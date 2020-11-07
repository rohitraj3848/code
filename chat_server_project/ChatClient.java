import java.io.*;
import java.net.*;

//this is the chat-client
public class ChatClient{
	//name
	String name;
	//socket for the client
	Socket socket;
	DataInputStream in;
	DataOutputStream out;
	ChatFrame gui;
   //constructor for the chat-client
	public ChatClient(String name,String server,int port){
		try{
			this.name=name;
			socket=new Socket(server,port);
			in=new DataInputStream(socket.getInputStream());
			out=new DataOutputStream(socket.getOutputStream());
			out.writeUTF(name);
			gui=new ChatFrame(this);
			while(true)
				gui.output.append(in.readUTF()+"\n");
		}catch(IOException e){

		}
	}

	//to send data 
	void sendTextToChat(String str){
		try{
			out.writeUTF(str);
		}catch(IOException e){
			e.printStackTrace();
		}
	}
    // to disconnect fromserver
	void disconnect(){
		try{
			in.close();
			out.close();
			socket.close();

		}catch(IOException e){
			e.printStackTrace();
		}
	}
	//main method 
	public static void main(String args[]){
		if(args.length!=3)
			throw new RuntimeException("Syntax :java ChatClient <name> <serverhost> <port>");
		new ChatClient(args[0],args[1],Integer.parseInt(args[2]));
	}
}