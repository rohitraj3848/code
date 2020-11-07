class test{
    static int a;
    static{
        a=4;
        System.out.println("inside static block");
        
        System.out.println("a = "+a);
    }
    test(){
        System.out.println("inside constructor");
        a=10;
    }
    {
        System.out.println("Empty block 1 called");
    }
    {
        System.out.println("Empty block 2 called");
    }
    public static void func(){
        a=a+1;
        System.out.println("a = "+a);
    }
}
public class constructers {

    public static void main(String args[]){
        test t=new test();
        t.func();  
    }
}
