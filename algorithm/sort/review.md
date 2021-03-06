# 排序

## 各种排序算法
### 冒泡
要对一个数组多次重复遍历，比较相邻的两项，并且交换顺序排错的项，每堆数组进行一次遍历，就会有一个最大项排在了正确的位置，若数组有n项，则需要遍历n-1次

### 直接插入
总是保持一个位置靠前的已经排好的数组，然后每一个新的数据项被插入到前边保持好的子表中
### 选择排序
每一次遍历，只交换一次，即在遍历过程中记录最大项的索引，完成遍历后，再把它换到正确的位置，若数组有n项，则也需要遍历n-1次
### 快排
通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据都比另外一部分小，然后对两部分进行递归的快速排序。
### 归并
两两合并
### 堆排序
1. 将无需序列构建成一个堆，根据升序降序需求选择大顶堆或小顶堆;

2. 将堆顶元素与末尾元素交换，将最大元素"沉"到数组末端;

3. 重新调整结构，使其满足堆定义，然后继续交换堆顶元素与当前末尾元素，反复执行调整+交换步骤，直到整个序列有序。

## 各种内部排序方法性能比较
| 排序方法 | 最少比较 | 最多比较次数 |最少移动次数|最多移动次数|平均效率|辅助存储|稳定性|
| :-----:| :----: | :----: |:----: |:----: |:----: |:----: |:----: |
| 直接插入  | n-1  |(n+2)(n-1)/2 |0| (n+4)(n-1)/2 |O(n^2) |O(1) |稳定|
| 选择 | n(n-1)/2 | n(n-1)/2 |0 |3(n-1) | O(n^2)|O(1) |不稳定 |
| 冒泡 | n-1 | n(n-1)/2 |0|n(n-1)/2 |O(n^2) |O(1) |稳定 |
| 快排 | O(nlog2n) | n(n-1)/2 |O(nlog2n) |n(n-1)/2 |O(nlog2n) |log2n|不稳定 |
| 堆排序 |  O(nlog2n) |  O(nlog2n)| | | O(nlog2n) |O(1) |不稳定 |
| 归并排序 |  O(nlog2n) |  O(nlog2n) |/ |/| O(nlog2n) |O(n) |稳定 |
| 基数排序 | 单元格 | 单元格 |单元格 |单元格 |单元格 |单元格 |单元格 |
| 希尔排序 | 单元格 | 单元格 |单元格 |单元格 |单元格 |单元格 |单元格 |

## 分类
### 依据的原则来分
插入排序
交换排序
选择排序
归并排序
基数排序
### 时间复杂度来看
简单排序算法(直接插入，冒泡，选择)O（n^2)
先进的排序算法(堆排序，归并排序，快速排序)O(nlog2n)
基数排序O(d·n)
### 空间复杂度来看
归并 O(n)
快排（logn) 最坏情况为(n)
其他 O(1)
### 稳定性来看
稳定的：直接插入，冒泡，归并
不稳定的:选择排序，快排，堆排序

## 各种算法适应的场景
1. 直接插入适合原始数据基本有序或n较小的情况
2. 快排适合原始数据杂乱无章，n较大且堆稳定性没有要求
3. 堆排序适合n较大，原始数据可能出现正序或逆序且对稳定性没有要求
4. 归并排序适合n较大，空间允许且要求排序稳定的情况
5. 在最好的情况下，直接插入排序和冒泡排序最快，在平均情况下，快速排序最快，最坏的情况下，堆排序和归并排序最快
6. 以比较为基础的排序方法中，最少比较次数为n—l，最多比较次数为n(n-1)/2，最坏情况下能达到的最好的时间复杂度为O(n log2n)。
