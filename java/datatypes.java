public class datatypes {
    public static void main(String args[]){
        for(int i=0;true;i++){
            System.out.println("hello");
            break;
        }
        Double object=new Double("2.4");
        int a=object.intValue();
        byte b=object.byteValue();
        float d=object.floatValue();
        double c=object.doubleValue();
        System.out.println(a+b+c+d);

    }
}
