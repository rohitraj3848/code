import javax.swing.*;

public class SwingDemo{
	public SwingDemo(){
		JFrame jfrm=new JFrame("A simple swing application");
		jfrm.setSize(400,400);
		jfrm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		JLabel jlab=new JLabel("Swing means powrful GUIs");
		jfrm.add(jlab);
		jfrm.setVisible(true);
	}
	public static void main(String args[]){
		SwingUtilities.invokeLater(new Runnable(){
			public void run(){
				new SwingDemo();
			}
		});
	}
}