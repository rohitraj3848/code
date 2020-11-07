public class hasCycle{
    public static void main(String args[]){
        ListNode head=new ListNode(3);
        ListNode a=new ListNode(1);
        ListNode b=new ListNode(5);
        ListNode c=new ListNode(4);
        head.next=a;
        a.next=b;
        b.next=c;
        System.out.println(detectCycle(head));
        ListNode r=detectCycle2(head);
        System.out.println(r.data);
    }
    //to return whether there is or not cycle
    static  boolean detectCycle(ListNode head){
        if(head==null){
            return false;
        }
        ListNode slow=head;
        ListNode fast=head.next;
        while(slow!=fast){
            if(fast==null || fast.next==null){
                return false;
            }
            slow=slow.next;
            fast=fast.next.next;

        }
        return true;
    }

    // to return the node where cycle is present
    static ListNode detectCycle2(ListNode head){
        if(head==null){
            return null;
        }
        ListNode slow=head;
        ListNode fast=head;
        while(fast !=null && fast.next!=null){
            slow=slow.next;
            fast=fast.next.next;
            if(slow==fast){
                break;
            }
        }
        if(fast==null || fast.next==null) return null;
        fast=head;
        while(slow!=fast){
            slow=slow.next;
            fast=fast.next;
        }
        return slow;
    } 
}