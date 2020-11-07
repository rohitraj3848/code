import java.util.*;
public class learnlist {
    public static void main(String args[]){
        List<String> list=List.of("rohit","ankit","sunny");
        System.out.println(list.size());
        System.out.println(list.isEmpty());
        System.out.println(list.contains("sunny"));
        List<String> listvec=new Vector<String>(list);
        List<String> listarray=new ArrayList<String>(list);
        
        listvec.add("kajal");
        listarray.add("rakhi");
        listarray.add(2,"gungun");
        System.out.println(listvec);
        System.out.println(listarray);
        listarray.addAll(2,listvec);
        System.out.println(listarray);
        System.out.println(listarray.containsAll(listvec));
        List<String> s=listarray.subList(1,4);
        System.out.println(s);
        s.set(1,"hello");
        System.out.println(s);
        Iterator<String> itr=listarray.iterator();
        while(itr.hasNext()){
            System.out.print(itr.next()+" ");
        }
        System.out.println();
        ListIterator<String> litr=listarray.listIterator(2);
        while(litr.hasNext()){
            System.out.print(litr.next()+" ");
        }
        System.out.println();
        listarray.forEach(x -> System.out.print(x+" "));
        System.out.println();
        LinkedList<String> linked=new LinkedList<>(listarray);
        System.out.println(linked.peek());
        System.out.println(linked.poll());
        linked.addFirst("switi");
        linked.addLast("pinki");
        System.out.println(linked.getFirst()+" "+linked.getLast());
        System.out.println(linked.peekFirst()+" "+linked.peekLast());
        System.out.println(linked.pollFirst()+" "+linked.pollLast());
        System.out.println(linked.removeFirst()+" "+linked.removeLast());
        String[] str=new String[linked.size()];
        str=linked.toArray(str);
        System.out.println(Arrays.toString(str));
        
    }
}
