public class IsPalindrome {
    public static void main(String args[]){
        LinkedList l=new LinkedList();
        l.append(1);
        l.append(2);
        l.append(3);
        l.append(4);
        l.append(2);
        l.append(1);
        boolean b=checkpallindrome(l.head);
        System.out.println(b);
    }

    public static boolean checkpallindrome(ListNode head){
        ListNode reverse=reverseAndClone(head);
        return ispallindrome(head,reverse);
    }

    public static ListNode reverseAndClone(ListNode node){
        ListNode temp=null;
        while(node!=null){
            ListNode n=new ListNode(node.data);
            n.next=temp;
            temp=n;
            node=node.next; 
        }
        return temp;
    }

    public static boolean ispallindrome(ListNode a,ListNode b){
        while(a!=null && b!=null){
            if(a.data!=b.data){
                return false;
            }
            a=a.next;
            b=b.next;
        }
        return (a==null && b==null);
    }
}