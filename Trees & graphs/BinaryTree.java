import java.util.*;
public class BinaryTree {
    public static Node createNode(int k){
        Node a=new Node();
        a.data=k;
        a.left=null;
        a.right=null;
        return a;
    }
    static void inorder(Node node){
        if(node==null){
            return;
        }
        inorder(node.left);
        System.out.print(node.data+" ");
        inorder(node.right);
    }
    static void inorderNoRec(Node node){
        if(node==null){
            return;
        }
        Stack<Node> s=new Stack<>();
        while(node!=null){
            s.push(node);
            node=node.left;
        }
        while(s.size()>0){
            Node t=s.pop();
            System.out.print(t.data+" ");
            if(t.right!=null){
                Node tmp=t.right;
                while(tmp!=null){
                    s.push(tmp);
                    tmp=tmp.left;
                }
            }
        }
    }
    static void preorder(Node node){
        if(node==null){
            return;
        }
        System.out.print(node.data+" ");
        preorder(node.left);
        preorder(node.right);
    }
    public void preorderWithoutRecursion(Node node) {
        if(node == null) {
          return;
        }
        
        Stack<Node> s = new Stack<Node>();
        
        s.push(node);
        
        while(s.size() > 0) {
          Node t = s.pop();
          System.out.print(t.data + " ");
          
          if(t.right != null) {
            s.push(t.right);
          }
          
          if(t.left != null) {
            s.push(t.left);
          }
        }
      }
    static void postorder(Node node){
        if(node==null){
            return;
        }
        postorder(node.left);
        postorder(node.right);
        System.out.print(node.data+" ");
    }
    public void postorderUsingTwoStack(Node node) {
        if(node == null) {
          return;
        }
        
        Stack<Node> s1 = new Stack<Node>();
        Stack<Node> s2 = new Stack<Node>();
        
        s1.push(node);
        
        while(s1.size() > 0) {
          Node t = s1.pop();
          
          if(t.left != null) {
            s1.push(t.left);
          }
          
          if(t.right != null) {
            s1.push(t.right);
          }
          
          s2.push(t);
        }
        
        while(s2.size() > 0) {
          System.out.print(s2.pop().data + " ");
        }
      }
    public static void main(String args[]){
        BinaryTree b=new BinaryTree();
        Node root=b.createNode(2);
        root.left=b.createNode(7);
        root.right=b.createNode(5);
        root.left.left=b.createNode(2);
        root.left.right=b.createNode(6);
        root.left.right.left=b.createNode(5);
        root.left.right.right=b.createNode(11);
        root.right.right=b.createNode(9);
        root.right.right.left=b.createNode(4);
        System.out.print("In order:");
        inorder(root);
        System.out.println();
        System.out.print("pre order:");
        preorder(root);
        System.out.println();
        System.out.print("post order:");
        postorder(root);
        System.out.println();
    }
    static int getSumOfdata(Node node){
        if(node==null){
            return 0;
        }
        return node.data+getSumOfdata(node.left)+getSumOfdata(node.right);
    }
    static int getNoOfNodes(Node node){
        if(node==null){
            return 0;

        }
        return 1+getNoOfNodes(node.left)+getNoOfNodes(node.right);
    }
    static int getNoOfleaves(Node node){
        if(node==null){
            return 0;
        }
        if(node.left==null && node.right==null){
            return 1;
        }
        return getNoOfleaves(node.left)+getNoOfNodes(node.right);
    }
    
    static int max(int a,int b){
        return a>b?a:b;
    }
 
    static void printAtlevel(Node node,int level){
        if(node==null){
            return;
        }
        if(level==1){
            System.out.print(node.data+" ");
            return;
        }
        printAtlevel(node.left, level-1);
        printAtlevel(node.right, level-1);
    }
    public void LevelOrderTransversal(Node node){
        if(node==null){
            return;
        }
        Queue<Node> q=new  LinkedList<>();
        q.add(node);
        while(q.size()>0){
            Node top=q.remove();
            System.out.print(top.data+" ");
            if(top.left!=null){
                q.add(top.left);
            }
            if(top.right!=null){
                q.add(top.right);
            }
        }
    }

    public void reverseLevelOrderTransversal(Node node){
        if(node==null){
            return;
        }
        int height=getHeightOfTree(node);
        for(int i=height;i>=0;i--){
            printAtlevel(node,i+1);
            System.out.println();  
        }
    }
    public void levelOrderTraversalUsingRecursion(Node node) {
        if (node == null) {
          return;
        }
        
        int height = getHeightOfTree(node);
        
        for(int i = 0; i <= height; i++) {
          printAtlevel(node, i + 1);
          System.out.println();
        }
      }
      
      public int getHeightOfTree(Node node) {
        if(node == null){
          return -1;
        }
        
        return Math.max(getHeightOfTree(node.left), getHeightOfTree(node.right)) + 1;
      }
      int maxLevel;
      public void leftViewOfTree(Node node, int level) {
        if(node == null) {
          return;
        }
        
        if(level >= maxLevel) {
          System.out.print(node.data + " ");
          maxLevel++;
        }
        
        leftViewOfTree(node.left, level + 1);
        leftViewOfTree(node.right, level + 1);
      }
  
    
  
      public void rightViewOfTree(Node node, int level) {
        if(node == null) {
          return;
        }
        
        if(level >= maxLevel) {
          System.out.print(node.data + " ");
          maxLevel++;
        }
        
        rightViewOfTree(node.right, level + 1);
        rightViewOfTree(node.left, level + 1);
      }

      public void topView(Node node) {
        if (node == null) {
          return;
        }
    
        TreeMap<Integer, Integer> m = new TreeMap<Integer, Integer>();
    
        Queue<Node> q = new LinkedList<Node>();
        q.add(node);
    
        while (!q.isEmpty()) {
          Node temp = q.remove();
        
          Stack<Node> s = new Stack<Node>();
          int hd = temp.height;
          
          if (m.get(hd) == null) {
            m.put(hd, temp.data);
          }
    
          if (temp.left != null) {
            temp.left.height = hd - 1;
            q.add(temp.left);
          }
    
          if (temp.right != null) {
            temp.right.height = hd + 1;
            q.add(temp.right);
          }
        }
        System.out.println(m.values());
      }
      public void bottomView(Node node) {
        if (node == null) {
          return;
        }
    
        TreeMap<Integer, Integer> m = new TreeMap<Integer, Integer>();
    
        Queue<Node> q = new LinkedList<Node>();
        q.add(node);
    
        while (!q.isEmpty()) {
          Node temp = q.remove();
          int hd = temp.height;
          
          m.put(hd, temp.data);
      
          if (temp.left != null) {
            temp.left.height = hd - 1;
            q.add(temp.left);
          }
    
          if (temp.right != null) {
            temp.right.height = hd + 1;
            q.add(temp.right);
          }
        }
        System.out.println(m.values());
      }
      static Node mirrorTree(Node node){
        if(node==null){
          return null;
        }
        Node t=node.left;
        node.left=node.right;
        node.right=t;
        mirrorTree(node.left);
        mirrorTree(node.right);
        return node;

      }
      static boolean checkIdentical(Node node1,Node node2){
        if(node1==null && node2==null){
          return true;
        }
        if(node1==null || node2==null){
          return false;
        }
        return node1.data==node2.data && checkIdentical(node1.left, node2.left) && checkIdentical(node1.right, node2.right);
      }

      static void printBoundryNode(Node node){
        if(node==null){
          System.out.println(node.data+" ");
        }
        printBoundryleft(node.left);
        printleaves(node.left);
        printleaves(node.right);
        printBoundryright(node.right);
      }
      static void printBoundryleft(Node node){
        if(node==null){
          return;
        }
        if(node.left!=null){
          System.out.println(node.data+" ");
          printBoundryleft(node.left);
        }
        else if(node.right!=null){
          System.out.print(node.data+" ");
          printBoundryleft(node.right);
        }
      }
      static void printBoundryright(Node node){
        if(node==null){
          return;
        }
        if(node.right!=null){
          System.out.println(node.data+" ");
          printBoundryright(node.right);
        }
        else if(node.left!=null){
          System.out.print(node.data+" ");
          printBoundryleft(node.left);
        }
      }
      static void printleaves(Node node){
        if(node==null){
          return;
        }
        printleaves(node.left);
        if(node.left==null && node.right==null){
          System.out.print(node.data+" ");
        }
        printleaves(node.right);
      }
      static int preindex=0;
      static Node createtreeInorderpreorder(int[] inor,int[] pre,int start,int end){
        if(start<end){
          return null;
        }
        Node node=createNode(pre[preindex++]);;
        if(start==end){
          return node;
        }
        int inorderindex=getinorderIndex(inor,node.data);
        node.left=createtreeInorderpreorder(inor, pre, start, inorderindex-1);
        node.right=createtreeInorderpreorder(inor, pre, inorderindex+1,end);
        return node;

      }
      static int getinorderIndex(int[] inor,int value){
        for(int i=0;i<inor.length;i++){
          if(inor[i]==value){
            return i;
          }
        }
        return -1;
      }
      static int diameter;
      static int getDiameter(Node node){
        if(node==null){
          return 0;
        }
        if(node.left==null && node.right==null){
          return 1;
        }
        int lh=getDiameter(node.left);
        int rh=getDiameter(node.right);
        diameter=Math.max(lh+rh+1,diameter);
        return Math.max(lh,rh)+1;

      }
      static int max_sum;
      public void rootToleave_maxsum(Node node,int sum){
        if(node==null){
          return;
        }
        if(node.left==null && node.right==null && sum+node.data>max_sum ){
          max_sum=sum+node.data;
        }
        rootToleave_maxsum(node.left, node.data+sum);
        rootToleave_maxsum(node.right,node.data+sum);
      }

    

}

class Node{
    int data;
    Node left;
    Node right;
    int height;
}