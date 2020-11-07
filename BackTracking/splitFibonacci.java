import java.util.*;

public class splitFibonacci {
    public static void main(String args[]){

    }
    public List<Integer> splitIntoFibonacci(String S) {
        List<Integer> res=new ArrayList<>();
        util(res,S,0);
        return res;
    }
    
    private boolean  util(List<Integer> res,String s,int pos){
        if(pos==s.length()){
            return res.size()>2 ? true : false;
        }
        int num=0;
        int n=s.length();
        for(int i=pos;i<n;i++){
            num=num*10+(s.charAt(i)-'0');
            if(num<0)return false;
            if(res.size()<2 || res.get(res.size()-1)+res.get(res.size()-2)==num){
                res.add(num);
                if(util(res,s,i+1)) return true;
                res.remove(res.size()-1);
            }
            if(pos==i && s.charAt(i)=='0')return false;
        }
        return false;
    }

}