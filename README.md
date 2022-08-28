# BinarySearch
# 二分查找法及相关应用
## 二分查找法
又称折半查找。对于有序数列才能使用，数组必须是有序的才能实现查找。在一组有序数列中取中间值mid与目标值比较，根据结果再决定是到中间值左边还是右边查找，然后取左边或右边序列的中间值比较，直到mid等于目标值。
由此可知二分查找的时间复杂度为O($logn$)，算上排序时间的话则为O($nlogn$)。将“有序”作为运行二分查找的前置条件，应用于多次查找，能更有效地发挥二分查找的优势。
这里取序列的中间元素角标mid时（l为最左边元素角标，r为最右边）应为mid=l+(r-l)/2。若是mid=(l+r)/2，可能会发生整型溢出，该问题在数据规模很大时触发（应该是亿级及以上时）。
### 二分查找法的递归写法
与Select K相似，对于递增有序数组data[length]，初始条件为l=0,r=length-1，取中间元素mid，若data[mid]>目标值target，则递归查找左边此时r=mid-1；若data[mid]=target，则说明找到目标值，返回mid；若data[mid]<target，则递归查找右边此时l=mid+1。
```c++
//递归实现二分查找
template <typename T>
int SearchR(T data[], int l, int r, T target) {
	if (l > r) return -1;
	int mid = l + (r - l) / 2;
	if (data[mid] == target)
		return mid;
	else if (data[mid] > target)
		return SearchR(data, l, mid - 1, target);
	else
		return SearchR(data, mid + 1, r, target);
}
template <typename T>
int BinarySearchR(T data[], int length, T target) {
	return SearchR(data, 0, length - 1, target);
}
```
### 非递归实现二分查找法
需要一个while循环，循环不变量为：在data[l,r]中找target，逻辑与递归实现相同，当l=r时循环结束。
```c++
//非递归实现二分查找
template <typename T>
int BinarySearch(T data[], int length, T target) {
	//在data[l,r]的范围内查找target
	int l = 0, r = length - 1;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (data[mid] == target)
			return mid;
		else if (data[mid] > target)
			r = mid - 1;
		else
			l = mid + 1;
	}
	return -1;
}
```
用这个方法可以非递归实现Select K，对于leetcode 215题可以用非递归解。
将递归的find函数改为
```c++
//非递归实现
int  find(vector<int>&  nums,int  k){
int l=0,r=nums.size()-1;
while(l<=r){
	int p=partition(nums,l,r,k);
	if(k==p) return p;
	else  if(k<p)
		r=p-1;
	else
		l=p+1;
	}
return -1;
}
```
### 换定义实现
将循环不变量改为：在data[l,r)的范围内查找target，这样其实条件、循环条件、循环内部逻辑都相应发生变化。
```c++
//换定义非递归实现二分查找
template <typename T>
int BinarySearch2(T data[], int length, T target) {
	//在data[l,r)的范围内查找target
	int l = 0, r = length ;
	while (l < r) {
		int mid = l + (r - l) / 2;
		if (data[mid] == target)
			return mid;
		else if (data[mid] > target)
			r = mid ;
		else
			l = mid + 1;
	}
	return -1;
}
```
## 二分查找的变种
### upper
查找大于target的最小值，搜索范围data[l,r]，r=length(target可能比数组中所有值都大，所以搜索范围向右扩大一个)。

 - data[mid]>target，mid及左侧范围内有解，不能将mid排除，此时令r=mid；
 - data[mid]<=target，mid右侧范围内有解，mid一定不是解，此时令l=mid+1；

```c++
//二分查找法的变种：upper
//查找>target的最小值的索引
template <typename T>
int upper(T data[], int length, T target) {
	//搜索范围为arr[l,r]r=length
	int l = 0, r = length;
	while (l < r) {
		int mid = l + (r - l) / 2;
		if (data[mid] > target)
			r = mid;
		else
			l = mid + 1;
	}
		return l;
}
```
### upper_ceil
查找target，若存在则返回等于该元素的最大索引；不存在返回大于其的最小值的索引(upper)。
利用upper()方法先求出大于target的最小索引u，判断data[u]是否等于target，相等则存在target，返回u-1;不等则不存在，返回u。
```c++
//二分查找法的变种：upper_ceil
//==target，返回target最大索引；无target，返回>target的最小值的索引
template<typename T>
int upper_ceil(T data[], int length, T target) {
	int u = upper(data, length, target);
	if (u - 1 >= 0 && data[u - 1] == target)
		return u - 1;
	return u;
}
```
### lower_ceil
查找target，若存在则返回等于该元素的最小索引；不存在返回大于其的最小值的索引(upper)。相当于查找>=target的最小值。这样只需改一下upper的if条件。
```c++
//lower_ceil:返回>=target的最小索引
template<typename T>
int lower_ceil(T data[], int length, T target) {
	int l = 0, r = length;
	while (l < r) {
		int mid = l + (r - l) / 2;
		if (data[mid] >= target)//更改的地方
			r = mid;
		else
			l = mid + 1;
	}
	return l;
}
```
### lower
查找小于target的最大值，初始条件l=-1(原因与upper相同)。
这个里面存在一个二分查找的坑，起初令mid=l+(r-l)/2，程序陷入死循环，当l与r相邻时搜索空间不变，无法到达l=r就会一直循环。因为当l与r相邻时由于人(r-l)/2下取整为0，则mid=l;此时若data[mid]<target，又会导致l=mid，如此循环不止。对此就需要对mid进行上取整，令mid = l + (r - l + 1) / 2。
```c++
//lower:返回小于target的最大索引
template<typename T>
int lower(T data[], int length, T target) {
	int l = -1, r = length-1;
	while (l < r) {
		int mid = l + (r - l + 1) / 2;//防止l与r相邻时进入死循环，mid值进行上取整
		if (data[mid] < target)
			l = mid;
		else
			r = mid - 1;
	}
	return l;
}
```
### lower_floor
查找target，若存在则返回等于该元素的最小索引；不存在返回小于其的最大值的索引(lower)。（与upper_ceil方法类似）。
```c++
//lower_floor:若存在target返回其最小索引；不存在返回小于target的最大索引(lower)
template<typename T>
int lower_floor(T data[], int length, T target) {
	int u = lower(data, length, target);
	if (u + 1 <= length && data[u + 1] == target)
		return u + 1;
	return u;
}
```
### upper_floor
查找target，若存在则返回等于该元素的最大索引；不存在返回小于其的最大值的索引(lower)。相当于查找<=target的最小值。(与lower_ceil方法类似）
```c++
//upper_floor:返回<=target的最大索引
template<typename T>
int upper_floor(T data[], int length, T target) {
	int l = -1, r = length - 1;
	while (l < r) {
		int mid = l + (r - l + 1) / 2;//防止l与r相邻时进入死循环，mid值进行上取整
		if (data[mid] <= target)
			l = mid;
		else
			r = mid - 1;
	}
	return l;
}
```
### 二分查找变种总结
|  |upper|upper_ceil|lower_ceil|lower|lower_floor|upper_floor
|--|--|--|--|--|--|--|
| 存在target |>target的最小值|=target的最大索引|>=target的最小值|<target的最大值|=target的最小索引|<=target的最大值
|不存在target|>target的最小值|返回upper|>=target的最小值|<target的最大值|返回lower|<=target的最大值

## 用>=target的最小值思路实现二分查找
利用lower_ceil()方法求出>=target的最小值的索引u，若data[u]=target则数组中存在target，返回索引u;若不等则不存在，返回-1。
```c++
//用找>=target的最小值(lower_ceil)的思路实现查找
template <typename T>
int Search(T data[], int length, T target) {
	int u = lower_ceil(data, length, target);
	if (data[u] == target)
		return u;
	return -1;
}
```
## 使用二分查找法搜索问题的解
### leetcode 875 爱吃香蕉的珂珂
H为规定时间，eatingTime为珂珂吃香蕉所用时间，k为珂珂1小时吃香蕉的量，使珂珂在规定时间内吃完香蕉。可知k->eatingTime单调递减，求出对应k时的eatingTime，利用二分搜索求eatingTime(k)<=H的最大eatingTime对应的k。
```c++
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int l=1,r=*max_element(piles.begin(),piles.end());
        while(l<r){
            int mid=l+(r-l)/2;
            if(eatingTime(piles,mid)<=h)
            r=mid;
            else
            l=mid+1;
        }
        return l;
    }
    //速度为k时吃香蕉所用时间
    int eatingTime(vector<int>&piles,int k){
        int eT=0;
        for(int pile:piles){
            eT+=pile/k + (pile%k>0 ? 1:0);
        }
        return eT;
    }
};
```
### leetcode 1011 在D天内送达包裹的能力
在给定的days天内完成weights[]数组的货物运输，每天最低载重为k。
首先求出载重为k时的运输天数Days,Days(k)单调递减。利用二分搜索的思路，求Days<=days时最大的Days对应的最小的k。
在求k对应的运输天数时，可以设一个while循环w作索引，d保存天数起始为1，weight保存当前船上货物总重量。
每次循环船上货物重量weight加上当前索引所在的对应包裹的重量，然后判断是否超重。若weight<=k，未超重，索引w++，继续往船上加下一个包裹(即进入下一轮循环)；若weight>k，超重，则此包裹不能放入船而是作为下一天的第一个包裹，w不向后移，天数加1 d++，开始下一天船上重量暂时清零weight=0。当w=weights.size()-1时循环停止。
然后二分搜索找最小的k时，初始条件k的最小取值应为weights数组中最大的值，否则将有包裹永远无法被运走；最大取值为数组的和，此时只需运输一天。
```c++
class  Solution {
public:
	int  shipWithinDays(vector<int>&  weights, 	int  days) {
	int l=*max_element(weights.begin(),weights.end());
	int r=accumulate(weights.begin(),weights.end(),0);
	while(l<r){
		int mid=l+(r-l)/2;
		if(Days(weights,mid)<=days)
			r=mid;
		else
			l=mid+1;
		}
return l;
	}
//运载能力为k时的运载天数d
	int  Days(vector<int>&weights,int  k){
	int d=1;
	int weight=0;//保存当时船上的重量
	int w=0;//第w个包裹
	while(w<weights.size()){
		weight+=weights[w];
		if(weight<=k){
			w++;
			}
		else{
			d++;
			weight=0;
			}
		}
	return d;
	}
};
```
## 小结
本周学习了二分查找法及其变种和相关的一些应用，同时复习了上周的Select K。通过对二分查找法的学习锻炼了逻辑思维，学会利用二分搜索的思路来解决问题，受益匪浅。
