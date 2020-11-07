class Grandparent{
	public void show(){
		System.out.println("Grandparent called");
	}
}
class Parent extends Grandparent{
	public void show(){
		super.show();
		System.out.println("parent called");
	}
}
class Child extends Parent{
	public void show(){
		super.show();
		System.out.println("child called");
	}
}
public class Inheritancedemo{
	public static void main(String args[]){
		Child c=new Child();
		c.show();
	}
	
}