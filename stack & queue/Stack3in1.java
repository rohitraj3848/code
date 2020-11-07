import java.util.EmptyStackException;

public class Stack3in1{
	int[] arr;
	int[] sizes;
	int stacks=3;
	int stackcapacity;

	public Stack3in1(int stackSize){
		stackcapacity=stackSize;
		arr=new int[stacks*stackcapacity];
		sizes=new int[stacks];
	}

	public void push(int stackNum,int data){
        if(isFull(stackNum)){
        	System.out.println("stack full");
        }else{
        	sizes[stackNum]++;
        	arr[topOfStack(stackNum)]=data;	
        }

	}

	public int pop(int stackNum){
		if(isEmpty(stackNum)){
			throw new EmptyStackException();
		}
		int value=arr[topOfStack(stackNum)];
		arr[topOfStack(stackNum)]=0;
		sizes[stackNum]--;
        return value;
	}

	public int peek(int stackNum){
		if(isEmpty(stackNum)){
			throw new EmptyStackException();
		}
		int value=arr[topOfStack(stackNum)];
        return value;
	}

	public boolean isFull(int stackNum){
       return sizes[stackNum]==stackcapacity;
	}

	public  boolean isEmpty(int stackNum){
       return sizes[stackNum]==0;
	}

	public int topOfStack(int stackNum){
		int offset=stackNum*stackcapacity;
		int size=sizes[stackNum];
		return size+offset-1;
	}

}