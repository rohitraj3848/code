import java.net.*;

public class Connect{
	public static void main(String args[])  throws Exception{
		String server_name="www.google.com";
		String ipno="172.217.160.228";
		System.out.println(server_name+"'s address is "+InetAddress.getByName(server_name).getHostAddress());
		System.out.println(ipno+"'s name is "+InetAddress.getByName(ipno).getHostName());
		try{
			Socket sock=new Socket(server_name,80);
			System.out.println("***connected to "+server_name+" *** ");
			sock.close();
		}
		catch(UnknownHostException e){
			System.err.println("error connecting to "+server_name+" *** ");
			return;
		}
		catch(java.io.IOException e){
			System.err.println("error connecting to "+server_name+" *** ");
			return;
		}
	}

}