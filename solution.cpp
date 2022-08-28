#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>//�����ֵ����ͷ�ļ�
#include<numeric>//�������ͷ�ļ�

//��������Ϊkʱ����������d
int Days(vector<int>& weights, int k) {
    int d = 1;
    int weight = 0;//���浱ʱ���ϵ�����
    int w = 0;//��w������
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