public class Partition {
    public static void main(String args[]){
        LinkedList l=new LinkedList();
        l.append(3);
        l.append(5);
        l.append(2);
        l.append(10);
        l.append(7);
        l.append(1);
        l.append(8);
        l.append(6);
        ListNode r=solution(l.head,5);
        LinkedList.print(r);
    }
    //all the nodes smaller than k lies before k and all greater than k after
    public static ListNode solution(ListNode node,int k){
        ListNode minhead=null;
        ListNode mintail=null;
        ListNode maxhead=null;
        ListNode maxtail=null;

        while(node!=null){
            if(node.data<k){
                if(minhead==null){
                    minhead=node;
                    mintail=minhead;
                }else{
                    mintail.next=node;
                    mintail=node;
                }
            }
            else{
                if(maxhead==null){
                    maxhead=node;
                    maxtail=maxhead;
                }
                else{
                    maxtail.next=node;
                    maxtail=node;
                }
            }
            node=node.next;
        }
        if(minhead==null){
            return maxhead;
        }
        mintail.next=maxhead;
        return minhead;
    }
}