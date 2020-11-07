import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
/*
<applet code="MySwingApplet" width=220 height=90>
</applet>
*/
public class MySwingApplet extends JApplet{
	JButton jbtna;
	JButton jbtnb;
    JLabel jlab;
    public void init(){
    	try{
    		SwingUtilities.invokeAndWait(new Runnable(){
    			public void run(){
    				makeGUI();
    			}
    		});
    	}catch(Exception e){
    	System.out.println("can't create because of "+e);
    }
    }
    public void makeGUI(){
    	setLayout(new FlowLayout());
    	jbtna=new JButton("Alpha");
    	jbtnb=new JButton("Beta");
    	jbtna.addActionListener(new ActionListener(){
    		public void  actionPerformed(ActionEvent ae){
    			jlab.setText("alpha was pressed");
    		}
    	});
    	jbtnb.addActionListener(new ActionListener(){
    		public void actionPerformed(ActionEvent ae){
    			jlab.setText("beta was pressed");
    		}
    	});
    	add(jbtna);
    	add(jbtnb);
    	jlab=new JLabel("press a button");
    	add(jlab);

    }
}