import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

//sing based user interface
public class ChatFrame extends JFrame{
	//text area to display all chat
	JTextArea output=new JTextArea();
	//text field to input the chat of client
	JTextField input=new JTextField();
    
    //constructor for the  chat-frame
	public ChatFrame(final ChatClient client){
		super(client.name);
		Container pane=getContentPane();
		pane.setLayout(new BorderLayout());
		pane.add(new JScrollPane(output),BorderLayout.CENTER);
		output.setEditable(false);
		pane.add(input,BorderLayout.SOUTH); 
		input.addKeyListener(new KeyAdapter(){
			public void keyPressed(KeyEvent e){
				if(e.getKeyCode()==KeyEvent.VK_ENTER){
					client.sendTextToChat(input.getText());
					input.setText("");
				}
			}
		});
		addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e){
				client.disconnect();
				System.exit(0);
			}
		});
		setSize(400,200);
		setVisible(true);
		input.requestFocus();
	}
}