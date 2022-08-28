#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>//求最大值所需头文件
#include<numeric>//求和所需头文件

//运载能力为k时的运载天数d
int Days(vector<int>& weights, int k) {
    int d = 1;
    int weight = 0;//保存当时船上的重量
    int w = 0;//第w个包裹
    while (w < weights.size()) {
        weight += weights[w];
        if (weight <= k) {
            w++;
        }
        else {
            d++;
            weight = 0;
        }
    }
    return d;
}
int shipWithinDays(vector<int>& weights, int days) {
    int l = *max_element(weights.begin(), weights.end());
    int r = accumulate(weights.begin(), weights.end(), 0);
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (Days(weights, mid) <= days)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
int main() {
    vector<int> weights = { 3,3,3,3,3,3 };
    int days = 2;
    cout << shipWithinDays(weights, days) << endl;
}