import java.util.*;
public class timeinwords{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		System.out.println("Input hour:");
		int h=scan.nextInt();
		System.out.println("Input minutes:");
		int m=scan.nextInt();
		System.out.println("time in words:");
		String result=timeInWords(h,m);
		System.out.println(result);

	}
	public static String timeInWords(int h, int m) {
		String res="";
		String[] s={"one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen","twenty"};
        if(m<=30){
        	if(m==15){
        		res+="quarter past " +s[h-1];
        	}
        	else if(m==30){
        		res+="half past "+s[h-1];

        	}
        	else if(m==0){
        		res+=s[h-1]+" o' clock";
        	}
        	else{
        		if(m==1){
                    res+=s[m-1]+" minute past "+s[h-1];
        		}
        		if(m>1 && m<=20){
        			res+=s[m-1] +" past " + s[h-1];
        		}
        		else{

        			res+=s[19] +" "+ s[m-20-1] +" minutes "+" past "+s[h-1];
        		}

        	}
        }
        if(m>30){
        	if(m==45){
        		res+="quarter to "+s[h];
        	}
        	else if(m>30 && m<40){
        		int l=60-m;
        		res+=s[19]+" " +s[l-20-1] +" minutes to " +s[h];
        	
        	}
        	else{
        		if(m==40){
                  res+=s[19]+" minutes to "+s[h];
        		}
        		else if(m==50){
                  res+=s[9]+" minutes to "+s[h];
        		}
        		else{
        			res+=s[60-m-1]+" minutes to "+s[h];
        		}
        	}

        		

        	}
        	return res;
        	}
        }
        
    
