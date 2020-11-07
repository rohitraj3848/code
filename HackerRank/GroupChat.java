import java.net.*; 
import java.io.*; 
import java.util.*; 
public class GroupChat 
{ 
	private static final String TERMINATE = "Exit"; 
	static String name; 
	static volatile boolean finished = false; 
	public static void main(String[] args) 
	{ 
		if (args.length != 2) 
			System.out.println("Two arguments required: <multicast-host> <port-number>"); 
		else
		{ 
			try
			{ 
				InetAddress group = InetAddress.getByName(args[0]); 
				int port = Integer.parseInt(args[1]); 
				Scanner sc = new Scanner(System.in); 
				System.out.print("Enter your name: "); 
				name = sc.nextLine(); 
				MulticastSocket socket = new MulticastSocket(port); 
			
				// Since we are deploying 
				socket.setTimeToLive(0); 
				//this on localhost only (For a subnet set it as 1) 
				
				socket.joinGroup(group); 
				Thread t = new Thread(new
				ReadThread(socket,group,port)); 
			
				// Spawn a thread for reading messages 
				t.start(); 
				
				// sent to the current group 
				System.out.println("Start typing messages...\n"); 
				while(true) 
				{ 
					String message; 
					message = sc.nextLine(); 
					if(message.equalsIgnoreCase(GroupChat.TERMINATE)) 
					{ 
						finished = true; 
						socket.leaveGroup(group); 
						socket.close(); 
						break; 
					} 
					message = name + ": " + message; 
					byte[] buffer = message.getBytes(); 
					DatagramPacket datagram = new
					DatagramPacket(buffer,buffer.length,group,port); 
					socket.send(datagram); 
				} 
			} 
			catch(SocketException se) 
			{ 
				System.out.println("Error creating socket"); 
				se.printStackTrace(); 
			} 
			catch(IOException ie) 
			{ 
				System.out.println("Error reading/writing from/to socket"); 
				ie.printStackTrace(); 
			} 
		} 
	} 
} 
class ReadThread implements Runnable 
{ 
	private MulticastSocket socket; 
	private InetAddress group; 
	private int port; 
	private static final int MAX_LEN = 1000; 
	ReadThread(MulticastSocket socket,InetAddress group,int port) 
	{ 
		this.socket = socket; 
		this.group = group; 
		this.port = port; 
	} 
	
	@Override
	public void run() 
	{ 
		while(!GroupChat.finished) 
		{ 
				byte[] buffer = new byte[ReadThread.MAX_LEN]; 
				DatagramPacket datagram = new
				DatagramPacket(buffer,buffer.length,group,port); 
				String message; 
			try
			{ 
				socket.receive(datagram); 
				message = new
				String(buffer,0,datagram.getLength(),"UTF-8"); 
				if(!message.startsWith(GroupChat.name)) 
					System.out.println(message); 
			} 
			catch(IOException e) 
			{ 
				System.out.println("Socket closed!"); 
			} 
		} 
	} 
}
/* Save the file as GroupChat.java and compile it using javac and then run the program using two command line arguments as specified. A multicast host is specified by a class D IP address and by a standard UDP port number. Class D IP addresses are in the range 224.0.0.0 to 239.255.255.255, inclusive. The address 224.0.0.0 is reserved and should not be used.
Here is a sample output of the above program:
multicast socket api in java

multicast socket api in java1multicast socket api in java12
We have used the multicast host IP address as 239.0.0.0 and the port number as 1234 (since the port numbers 0 through 1023 are reserved). There are 3 members in the group: Ironman, CaptainAmerica, and Groot. Start all three terminals first before sending the message, otherwise messages which are sent before starting the terminal are lost (since there is no facility of buffer incorporated to store the messages.) We need two threads in this application. One for accepting the user input (using the java.util.Scanner class) and the other for reading the messages sent from other clients. Hence I have separated the thread which does the reading work into ReadThreadclass. For leaving the group, any of the user can type in Exit to terminate the session.

The above program is executed on a single machine. Socket programming is meant for distributed programming. The same piece of code snippet when present on different machines which have Java installed can satisfy that requirement. This is just the bare bones service logic. The project would be even more fascinating if the front-end is developed. You can use Java’s AWT (Abstract Window Toolkit) or its advanced counterpart, Java Swing to develop the front end. Since this wouldn’t be part of Socket programming I’m leaving it untouched without getting into the details.
Additional points:

You can incorporate network security feature by performing encryption before sending the message over the network.
Primitive techniques such as Caesar cipher or advanced methods such as RSA can be used to perform encryption-decryption. You can try using Java’s RMI (Remote Method Invocation) to perform the same task.
Here, you can leverage the abstraction offered by Java to maximum extent. However, if your primary objective is efficiency, then Socket programming is the best choice. Since it doesn’t require any run time support, it is a bit faster compared to RMI.
This article is contributed by Aditya ch. If you like GeeksforGeeks and would like to contribute, you can also write an article using contribute.geeksforgeeks.org or mail your article to contribute@geeksforgeeks.org. See your article appearing on the GeeksforGeeks main page and help other Geeks.   */