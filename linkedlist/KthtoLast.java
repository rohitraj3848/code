public class KthtoLast {
    public static void main(String args[]){
        LinkedList l=new LinkedList();
        
        l.append(1);
        l.append(2);
        l.append(3);
        l.append(4);
        l.append(5);
        l.append(6);
        l.append(7);
        ListNode r=solution(l.head,4);
        LinkedList.print(r);
    }

    public static ListNode solution(ListNode head,int k){
        ListNode p1=head;
        ListNode p2=head;
        for(int i=0;i<k;i++){
            if(p1==null){
                return null;
            }
            p1=p1.next;
        }
        while(p1!=null){
            p1=p1.next;
            p2=p2.next;
        }

        return p2;
    }
}