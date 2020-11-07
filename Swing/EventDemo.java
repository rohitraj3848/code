import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class EventDemo{
	JLabel jlab;
	public EventDemo(){
		JFrame jfrm=new JFrame("An Event Demo");
		jfrm.setLayout(new FlowLayout());
		jfrm.setSize(220,90);
		jfrm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		JButton jbtna=new JButton("Alpha");
		JButton jbtnb=new JButton("Beta");
		jbtna.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				jlab.setText("alpha was pressed");
			}
		});
		jbtnb.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				jlab.setText("beta was pressed");
			}
		});
		jfrm.add(jbtna);
		jfrm.add(jbtnb);
		jlab=new JLabel("Press a button");
		jfrm.add(jlab);
		jfrm.setVisible(true);
	}
	public static void main(String args[]){
		SwingUtilities.invokeLater(new Runnable(){
			public void run(){
				new EventDemo();
			}
		});
	}
}