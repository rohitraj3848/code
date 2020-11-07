import java.util.*;
public class ListOfDepths{
    public static void main(String args[]){
        treeNode root=new treeNode(1);
        treeNode h11=new treeNode(2);
        treeNode h12=new treeNode(3);
        treeNode h21=new treeNode(4);
        treeNode h22=new treeNode(5);
        treeNode h23=new treeNode(6);
        treeNode h24=new treeNode(7);
        root.right=h12;
        root.left=h11;
        h11.left=h21;
        h11.right=h22;
        h12.left=h23;
        h12.right=h24;

        ArrayList<LinkedList<treeNode>> r=listofdepths(root);
        for(List<treeNode> l:r){
            for(treeNode n : l){
                System.out.print(n.data+" ");
            }
            System.out.println();
        }
    }
    static ArrayList<LinkedList<treeNode>> listofdepths(treeNode root){
        ArrayList<LinkedList<treeNode>> lists=new ArrayList<>();
        listofdepths(root,lists,0);
        return lists;
    }
    static void listofdepths(treeNode root,ArrayList<LinkedList<treeNode>> lists,int level){
        if(root==null){
            return;
        }
        LinkedList<treeNode> list=null;
        if(lists.size()==level){
            list=new LinkedList<>();
        }else{
            list=lists.get(level);
        }
        list.add(root);
        listofdepths(root.left, lists, level+1);
        listofdepths(root.right, lists, level+1);
    }
    static ArrayList<ArrayList<treeNode>> listoflevels(treeNode root){
        ArrayList<ArrayList<treeNode>> lists=new ArrayList<>();
        if(root==null){
            return lists;
        }
        ArrayList<treeNode> current=new ArrayList<>();
        current.add(root);
        while(current.size()>0){
            lists.add(current);
            ArrayList<treeNode> parents=current;
            current=new ArrayList<>();
            for(treeNode parent : parents){
                if(parent.left!=null){
                    current.add(parent.left);
                }
                if(parent.right!=null){
                    current.add(parent.right);
                }
            }
        }
        return lists;
    }
}

 
class treeNode{
    int data;
    treeNode left;
    treeNode right;
    public treeNode(int data){
        this.data=data;
        this.left=null;
        this.right=null;
    }
}






