public class LinkedList{
	
	ListNode head;

	public void append(int data){
    	if(isEmpty()){
    		head=new ListNode(data);
    	}
    	else{
        	ListNode curr= head;
        	while(curr.next!=null){
        		curr=curr.next;
        	}
        	curr.next=new ListNode(data);	
    	}
	}

	public void insertFirst(int data){
		if(isEmpty()){
			head=new ListNode(data);
		}else{
			ListNode li=new ListNode(data);
			li.next=head;
			head=li;
		}

	}

	public static void print(ListNode head){
		ListNode temp=head;
		while(temp!=null){
			System.out.print(temp.data+" ");
			temp=temp.next;
		}
		System.out.println();
	}


	public void remove(){
       if(isEmpty()){
       	return;
       }
       ListNode curr=head;
       ListNode previousToLast=null;
       while(curr.next!=null){
       	previousToLast=curr;
       	curr=curr.next;
       }
       previousToLast.next=null;
	}

	public void removeFirst(){
		if(isEmpty()){
			return;
		}
		ListNode l=head;
		head=head.next;
		l.next=null;

	}

	public boolean isEmpty(){
		return head==null;
	}

}