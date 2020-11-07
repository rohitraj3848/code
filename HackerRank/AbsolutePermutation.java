public class AbsolutePermutation {
    static int[] absolutePermutation(int n, int k) {
        int[] ar={-1};
        int arr[]=new int[n];
        if(k==0){
            for(int i=0;i<n;i++){
                arr[i]=i+1;
            }
            return arr;
        }
        else if(n%(2*k)!=0){
            return ar;
        }
        else{
            for(int i=0;i<n;++i){
                if((i/k)%2==0){
                    arr[i]=i+k+1;
                }
                else{
                    arr[i]=i-k+1;
                }
            }
        }
        return arr;

    } 
}