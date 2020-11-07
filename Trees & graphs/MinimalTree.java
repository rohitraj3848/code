public class MinimalTree{
    public static void main(String args[]){
        int arr[]={1,2,3,4,5,6,7};
        TreeNode root=createMinimalBST(arr);
        System.out.println(root.data);
    }

    static TreeNode createMinimalBST(int[] arr){
        return createMinimalBST(arr,0,arr.length-1);
    }
    static TreeNode createMinimalBST(int[] arr,int start,int end){
        if(end<start){
            return null;
        }
        int mid=(start+end)/2;
        TreeNode n=new TreeNode(arr[mid]);
        n.left=createMinimalBST(arr, start,mid-1);
        n.right=createMinimalBST(arr,mid+1, end);
        return n;
    }

}

class TreeNode{
    int data;
    TreeNode left;
    TreeNode right;
    public TreeNode(int data){
        this.data=data;
        this.right=null;
        this.left=null;
    }
}