public class isRotation {
    public static void main(String[] args) {
        System.out.println(isrotated("waterbottle","erbottlewat"));
    }
    public static boolean isrotated(String s,String r){
        int len=s.length();
        if(len==r.length() && len >0){
            String t=s+s;
            return t.contains(r);
        }
        return false;
    }
}
