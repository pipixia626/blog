/*时间复杂度nlogn
  空间复杂度
*/
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 将给定数组排序
     * @param arr int整型vector 待排序的数组
     * @return int整型vector
     */
    vector<int> MySort(vector<int>& arr) {
       quickSort(arr,0,arr.size()-1);
           return arr;
        }
    void quickSort(vector<int>& arr,int left,int right )
    {
        if(left<right){
            int point=partition(arr,left, right);
            quickSort(arr, left,  point-1);
            quickSort(arr, point+1, right);
        }
    }
    int partition(vector<int>& arr,int left,int right){
       int first=arr[left];
           while(left<right){
               while(left<right&&arr[right]>=first){
                   right--;
               }
               swap(arr,left,right);
          
               while(left<right&&arr[left]<=first){
                   left++;
               }
               swap(arr,left,right);
           }
           return left;
       }
     
     void swap(vector<int>& arr,int i,int j){
        int temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
        // write code here
 
};
