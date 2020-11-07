public class QueueArray{
	private int[] data;
	private int f=0;
	private int size=0;

	public QueueArray(int capacity){
		data=new int[capacity];
	}

	public int size(){
		return size;
	}

	public boolean isEmpty(){
		return size==0;
	}



	public void enqueue(int item) throws IllegalStateException{
		if(size==data.length)throw new IllegalStateException("Queue is full!");
		int avail=(f+size)%data.length;
		data[avail]=item;
		size++;
	}

	public int dequeue(){
		if(isEmpty())
			return 0;
		int r=data[f];
		data[f]=0;
		f=(f+1)%data.length;
		size--;
		return r;
	}

}