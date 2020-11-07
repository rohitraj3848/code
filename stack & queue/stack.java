import java.util.*;
public class stack{
	static class stackNode{
	public int data;
	public stackNode next;

	public stackNode(int data){
		this.data=data;
	}
}
    public static  stackNode top;

	public int pop(){
		if(top==null)throw new EmptyStackException();
          int item=top.data;
          top=top.next;
          return item;

	}

	public void push(int data){
		stackNode s=new stackNode(data);
		s.next=top;
		top=s;

	}

	public int peek(){
        if(top==null)throw new EmptyStackException();
        return top.data;
	}

	
}