import java.io.*;
import java.util.*;
public class ladybug{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		System.out.println("input n:");
		int n=scan.nextInt();
		System.out.println("Input the string:");
		String b=scan.next();
		String r=happy(b);
		System.out.println(r);

	}
	public static String happy(String b){
		  boolean t=true;
          Map<Character,Integer> m=new HashMap<>();
          char[] c=b.toCharArray();
          m.put('_',0);
          String alpha="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
          char[]  d=alpha.toCharArray();
          for(int i=0;i<d.length;i++){
          	m.put(d[i],0);
          }
          for(int j=0;j<c.length;j++){
          	int val=m.get(c[j]);
          	val++;
          	m.put(c[j],val);
          }
          if(m.get('_')==0){
          	int count=0;
              	for(int i=1;i<c.length;i++){
              		if(c[i]==c[i-1]){
              			count++;
              		}
              		else{
              			if(count>=1 && i!=(c.length-1)){
              				count=0;
              			}
              			else{
              				t=false;
              				break;
              			}
              		}
              	}

          }else{
          for(int k=0;k<c.length;k++){
              int value=m.get(c[k]);
              if(value==1){
              	if(c[k]=='_'){
              		t=true;
              	}
              	else{
              		t=false;
              		break;
              	}
              }
          }
        }
          if(t){
          	return "YES";
          }
          else{
          	return "NO";
         }

	}
}