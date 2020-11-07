public class sumList {
    public static void main(String args[]){
        LinkedList l=new LinkedList();
        l.append(2);
        l.append(3);
        l.append(5);
        LinkedList r=new LinkedList();
        r.append(8);
        r.append(3);
        r.append(8);
        LinkedList sumlist=sum(l.head, r.head);
        LinkedList.print(sumlist.head);
    }

    public static LinkedList sum(ListNode a,ListNode b){
        LinkedList result=new LinkedList();
        int s=0;
        int carry=0;
        int data=0;
        while(a!=null || b!=null){
             s=a.data+b.data+carry;
             carry=s/10;
             data=s%10;
             result.append(data);
             a=a.next;
             b=b.next;
        }
        while(a!=null){
            s=carry+a.data;
            carry=s/10;
            data=s%10;
            result.append(data);
            a=a.next;
        }
        while(b!=null){
            s=carry+b.data;
            carry=s/10;
            data=s%10;
            result.append(data);
            b=b.next;
        }
        if(carry==1){
            result.append(carry);
        }
        return result;
    }
}