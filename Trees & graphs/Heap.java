import java.util.*;
//minHeap implementation
public class Heap {
    private int capacity=10;
    private int[] heap=new int[capacity];
    private int heapSize=0;

    

    public boolean isEmpty(){
        return heapSize==0;
    }

    public boolean isFull(){
        return heapSize==heap.length;
    }

    private int getParent(int index){
        return (index-1)/2;
    }

    private int getLeftChild(int index){
        return 2*index+1;
    }
    private  int getRightChild(int index){
        return 2*index+1;
    }
    private boolean hasLeftChild(int index){
        return getLeftChild(index) < heapSize;
    }

    private boolean hasRightChild(int index){
        return getRightChild(index) < heapSize;
    }

    private boolean hasParent(int index){
        return getParent(index) < heapSize;
    }

    private int leftChild(int index){
        return heap[getLeftChild(index)];
    }

    private int rightChild(int index){
        return heap[getRightChild(index)];
    }

    private int parent(int index){
        return heap[getParent(index)];
    }

    private void swap(int i,int j){
        int temp=heap[i];
        heap[i]=heap[j];
        heap[j]=temp;
    }

    private void incrementCapacity(){
        if(isFull()){
            heap=Arrays.copyOf(heap,heapSize*2);
            capacity*=2;
        }
    }

    public int peek(){
        if(heapSize==0){
            throw new IllegalStateException();
        }
        return heap[0];
    }

    public int poll(){
        if(heapSize==0){
            throw new IllegalStateException();
        }
        int item=heap[0];
        heap[0]=heap[heapSize-1];
        heapSize--;
        heapifyDown();
        return item;
    }

    public void add(int item){
        incrementCapacity();
        heap[heapSize]=item;
        heapSize++;
        heapifyUp();
    }

    private void heapifyUp(){
        int index=heapSize-1;
        while(hasParent(index) && parent(index) > heap[index]){
            swap(getParent(index),index);
            index=getParent(index);
        }
    }

    private void heapifyDown(){
        int index=0;
        while(hasLeftChild(index)){
            int smallerChild=getLeftChild(index);
            if(hasRightChild(index) && rightChild(index)<leftChild(index)){
                smallerChild=getRightChild(index);
            }
            if(heap[index]<heap[smallerChild]){
                break;
            }else{
                swap(index,smallerChild);
                index=smallerChild;
            }
        }
    }



    public static void main(String args[]){
        Heap h=new Heap();
        h.add(10);
        h.add(30);
        h.add(3);
        h.add(1);
        h.add(12);
    }
}