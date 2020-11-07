//minimum deletion required to make pallindrome
public class makePallindrome {
    public static void main(String[] args) {
        String s = "ACBCDBAA";
        int r=mindeletion(s,0,s.length()-1);
        System.out.println(r);
    }
    static int mindeletion(String s,int l,int r){
        if(l>=r){
            return 0;
        }
        if(s.charAt(l)==s.charAt(r)){
            return mindeletion(s, l+1, r-1);
        }
        return 1 + Math.min(mindeletion(s, l+1, r),mindeletion(s, l, r-1));
    }
}