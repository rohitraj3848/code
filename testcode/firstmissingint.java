public class firstmissingint {
    public static void main(String[] args) {
        int arr[]={3,4,-1,1};
        System.out.println(find(arr));
    }
    static int find(int[] arr){
        if(arr==null || arr.length==0){
            return 1;
        }
        int n=arr.length;
        int countone=0;
        for(int i=0;i<n;i++){
            if(arr[i]==1){
                countone=1;
            }else if(arr[i]<=0 || arr[i]>n){
                arr[i]=1;
            }
        }
        if(countone==0){
            return 1;
        }
        for(int i=0;i<n;i++){
            int index=Math.abs(arr[i])-1;
            if(arr[index]>0){
                arr[index]=-1*arr[index];
            }
        }

        for(int i=0;i<n;i++){
            if(arr[i]>0){
                return i+1;
            }
        }
        return n+1;
    }
}
