import java.util.*;

public class jobSequencing {
    public static void main(String[] args) {
        List<Job> jobs = Arrays.asList(
				new Job( 0, 6, 60 ),
				new Job( 5, 9, 50 ),
				new Job( 1, 4, 30 ),
				new Job( 5, 7, 30 ),
				new Job( 3, 5, 10 ),
				new Job( 7, 8, 10 )
        );
        
        getmaxprofit(jobs, jobs.size());
        Collections.sort(jobs,Comparator.comparingInt(x->x.finish));
        System.out.println(maxProfit(jobs,jobs.size()-1));

    }  
    static void getmaxprofit(List<Job> jobs,int n){
        Collections.sort(jobs,Comparator.comparingInt(x->x.start));
        int maxprofit[]=new int[n];
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(jobs.get(j).finish<=jobs.get(i).start && maxprofit[i]<maxprofit[j]){
                    maxprofit[i]=maxprofit[j];
                }
            }
            maxprofit[i]+=jobs.get(i).profit;
        }
        int max=0;
        for(int i=0;i<maxprofit.length;i++){
            if(maxprofit[i]>max){
                max=maxprofit[i];
            }
        }
        System.out.println(Arrays.toString(maxprofit));
        System.out.println(max);
    }

    static int maxProfit(List<Job> jobs,int n){
        if(n<0){
            return 0;
        }
        if(n==0){
            return jobs.get(0).profit;
        }
        int index=getnonconflictingindex(jobs, n);
        int incl=jobs.get(n).profit+maxProfit(jobs,index);
        int excl=maxProfit(jobs,n-1);
        return Math.max(incl,excl);
    }
    static int getnonconflictingindex(List<Job> jobs,int n){
        for(int i=n-1;i>=0;i--){
            if(jobs.get(i).finish<jobs.get(n).start){
                return i;
            }
        }
        return -1;
    }   
    
}


class Job{
    int start;
    int finish;
    int profit;
    public Job(int s,int f,int p){
        this.start=s;
        this.finish=f;
        this.profit=p;
    }
}
