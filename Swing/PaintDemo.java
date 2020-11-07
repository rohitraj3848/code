import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
class  PaintPanel extends JPanel{
	Insets ins;
	Random rand;
	PaintPanel(){
		setBorder(BorderFactory.createLineBorder(Color.RED,5));
		rand=new Random();
	}
	protected void paintComponent(Graphics g){
		super.paintComponent(g);
		int x,y,x2,y2;
		int heigth=getHeight();
		int width=getWidth();
		ins=getInsets();
		for(int i=0;i<10;i++){
			x=rand.nextInt(width-ins.left);
			y=rand.nextInt(heigth-ins.bottom);
			x2=rand.nextInt(width-ins.left);
			y2=rand.nextInt(heigth-ins.bottom);
			g.drawLine(x,y,x2,y2);
		}
	}
}
public class PaintDemo{
	JLabel jlab;
	PaintPanel pp;
	PaintDemo(){
		JFrame jfrm=new JFrame("paint Demo");
		jfrm.setSize(400,600);
		jfrm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		pp=new PaintPanel();
		jfrm.add(pp);
		jfrm.setVisible(true);
	}
	public static void main(String args[]){
		SwingUtilities.invokeLater(new Runnable(){
			public void run(){
				new PaintDemo();
			}
		});
	}
}