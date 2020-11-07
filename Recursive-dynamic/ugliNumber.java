
public class ugliNumber {
    public static void main(String args[]){
        int n=7;
        System.out.println(nthugly(n));
        System.out.println(uglydynamic(n));

    }
    //doing normally
    static int nthugly(int n){
        int i=1;
        int count=1;
        while(count<n){
            i++;
            if(isugly(i)==1){
                count++;
            }
        }
        return i;
    }
    static int isugly(int no){
        no=maxdivide(no, 2);
        no=maxdivide(no, 3);
        no=maxdivide(no, 5);
        return (no==1)?1:0;
    }
    //divide by the highest power of b
    static int maxdivide(int a,int b){
        while(a%b==0){
            a=a/b;
        }
        return a;
    }

    //using dynamic programming
    //convert in three sequence (1*2,2*2),(1*3,2*3),(1*5,2*5) fill the array 
    //according to the position
    static int uglydynamic(int n){
        int[] ugly=new int[n];
        int i2=0;
        int i3=0;
        int i5=0;
        ugly[0]=1;
        int ugly_num_2=ugly[i2]*2;
        int ugly_num_3=ugly[i3]*3;
        int ugly_num_5=ugly[i5]*5;
        int ugly_num_now=0;
        for(int i=1;i<n;i++){
            ugly_num_now=Math.min(ugly_num_3,Math.min(ugly_num_5,ugly_num_2));
            ugly[i]=ugly_num_now;
            if(ugly_num_now==ugly_num_2){
                i2+=1;
                ugly_num_2=ugly[i2]*2;
            }
            if(ugly_num_now==ugly_num_3){
                i3+=1;
                ugly_num_3=ugly[i3]*3;
            }
            if(ugly_num_now==ugly_num_5){
                i5+=1;
                ugly_num_5=ugly[i5]*5;
            }
        }
        return ugly_num_now;
    }
}