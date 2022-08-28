using namespace std;
#include<iostream>

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
//二分查找法的变种：upper_ceil
//==target，返回target最大索引；无target，返回>target的最小值的索引
template<typename T>
int upper_ceil(T data[], int length, T target) {
	int u = upper(data, length, target);
	if (u - 1 >= 0 && data[u - 1] == target)
		return u - 1;
	return u;
}
//lower_ceil:返回>=target的最小索引
template<typename T>
int lower_ceil(T data[], int length, T target) {
	int l = 0, r = length;
	while (l < r) {
		int mid = l + (r - l) / 2;
		if (data[mid] >= target)
			r = mid;
		else
			l = mid + 1;
	}
	return l;
}
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
//lower_floor:若存在target返回其最小索引；不存在返回小于target的最大索引(lower)
template<typename T>
int lower_floor(T data[], int length, T target) {
	int u = lower(data, length, target);
	if (u + 1 <= length && data[u + 1] == target)
		return u + 1;
	return u;
}
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
//用找>=target的最小值(lower_ceil)的思路实现查找
template <typename T>
int Search(T data[], int length, T target) {
	int u = lower_ceil(data, length, target);
	if (data[u] == target)
		return u;
	return -1;
}
int main() {
	const int n = 100;
	int data[n];
	for (int i = 0; i < n; i++) {
		data[i] = i;
	}
	cout<<BinarySearch(data, n, 66)<<endl;
	cout<<BinarySearch2(data, n, 56)<<endl;
	int data1[] = { 1,1,3,3,5,5,7,7 };
	for (int i = 0; i < 8; i++) {
		cout << data1[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 8; i++) {
		cout << upper(data1, 8, i) << " ";
	}
	cout << endl;
	for (int i = 0; i < 8; i++) {
		cout << upper_ceil(data1, 8, i) << " ";
	}
	cout << endl;
	for (int i = 0; i < 8; i++) {
		cout << lower_ceil(data1, 8, i) << " ";
	}
	cout << endl;
	for (int i = 0; i < 8; i++) {
		cout << lower(data1, 8, i) << " ";
	}
	cout << endl;
	for (int i = 0; i < 8; i++) {
		cout << lower_floor(data1, 8, i) << " ";
	}
	cout << endl;
	for (int i = 0; i < 8; i++) {
		cout << upper_floor(data1, 8, i) << " ";
	}
	cout << endl;
	for (int i = 0; i < 8; i++) {
		cout << Search(data1, 8, i) << " ";
	}
	cout << endl;
	return 0;
}