import java.util.*;
public class uniqueTree {
    public static void main(String args[]){

    }
    public List<treenode> generateTrees(int n) {
        if(n<1){
            return new ArrayList<>();
        }
        return uniqueBST(1,n);
    }
    public static List<treenode> uniqueBST(int low,int high){
        List<treenode> ans=new ArrayList<>();
        if(low>high){
            ans.add(null);
            return ans;
        }
        for(int i=low;i<=high;i++){
            List<treenode> lefttree=uniqueBST(low,i-1);
            List<treenode> righttree=uniqueBST(i+1,high);
            for(treenode l:lefttree){
                for(treenode r:righttree){
                    treenode root=new treenode(i);
                    root.left=l;
                    root.right=r;
                    ans.add(root);
                }
            }
        }
        return ans;
    }
}
class treenode {
    int val;
    treenode left;
    treenode right;
    treenode() {}
    treenode(int val) { this.val = val; }
    treenode(int val, treenode left, treenode right) {
        this.val = val;
        this.left = left;
        this.right = right;
   }
}

