import java.io.*;
import java.util.*;
import java.util.stream.*;
public class library{
    static  BufferedReader br;
    public static void main(String args[])throws IOException{
        File file=new File("input.txt");
        br=new BufferedReader(new FileReader(file));
        BufferedWriter bw = new BufferedWriter(new FileWriter("ommitedInput.txt"));
        String inputFileLine="";
        while((inputFileLine = br.readLine()) != null) {
            if(inputFileLine.length() == 0)
                continue;
            bw.write(inputFileLine);
            bw.newLine();
        }
        bw.close();
        br=new BufferedReader(new FileReader("ommitedInput.txt"));
        String[] s=br.readLine().split(" ");
        int books=Integer.parseInt(s[0]);
        int libraries=Integer.parseInt(s[1]);
        int days=Integer.parseInt(s[2]);
        String[] s1=br.readLine().split(" ");
        int[] bookScores=new int[books];
        for (int i = 0; i < books; i++) {
            int BItem = Integer.parseInt(s1[i]);
            bookScores[i] = BItem;
        }
        List<List<Integer>> LibData =new ArrayList<>();
        List<List<Integer>> LibBooks=new ArrayList<>();
        IntStream.range(0, libraries).forEach(tItr ->{
            try{
                String[] t1=br.readLine().split(" ");
                String[] t2=br.readLine().split(" ");
                List<Integer> temp1=new ArrayList<>();
                for(int i=0;i<t1.length;i++){
                    temp1.add(Integer.parseInt(t1[i]));
                }
                LibData.add(temp1);
                List<Integer> temp2=new ArrayList<>();
                for(int i=0;i<t2.length;i++){
                    temp2.add(Integer.parseInt(t2[i]));
                }
                LibBooks.add(temp2);
                
            }
            catch(IOException e){
                throw new RuntimeException(e);
            }
        });
        Solution.solve(books,libraries, days,bookScores, LibData, LibBooks);
        br.close();
    }
    
}