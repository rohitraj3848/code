//remove duplicates from a linked list
import java.util.*;
public class removeDups {
    public static void main(String args[]){
        LinkedList l=new LinkedList();
        l.append(1);
        l.append(1);
        l.append(2);
        l.append(3);
        l.append(4);
        l.append(4);
        l.append(4);
       // ListNode r=noDups(l.head);
       // LinkedList.print(r);
        //ListNode r1=noDupsII(l.head);
        //LinkedList.print(r1);
        ListNode r2=nodupsIII(l.head);
        LinkedList.print(r2);

    }
    // for unsorted list
    public static ListNode noDups(ListNode head){
        ListNode temp=head;
        Set<Integer> set=new HashSet<>();
        set.add(temp.data);
        while(temp.next!=null){
            if(set.contains(temp.next.data)){
                temp.next=temp.next.next;
            }
            else{
                set.add(temp.next.data);
                temp=temp.next;
            }
        }
        return head;
    }
    //for sorted list
    public static ListNode noDupsII(ListNode head){
        ListNode curr=head;
        while(curr.next!=null && curr!=null){
            if(curr.next.data==curr.data){
                curr.next=curr.next.next;
            }
            else{
                curr=curr.next;
            }
        }
        return head;
    }
    //remove all occurances of repeating integers
    public static ListNode nodupsIII(ListNode head){
        if(head==null || head.next==null){
            return head;
        }
        if(head.next.data!=head.data){
            head.next=nodupsIII(head.next);
            return head;
        }
        ListNode curr=head;
        while(curr.data==head.data && curr!=null){
            curr=curr.next;
        }
        return nodupsIII(curr);
    }
}