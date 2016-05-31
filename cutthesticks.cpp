#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int n;
	cin >> n;
	vector<int> arr(n);
	for(int arr_i = 0;arr_i < n;arr_i++){
		cin >> arr[arr_i];
	}
	sort(arr.begin(),arr.end());
	int left = n;
	cout << left << "\n";
	int i = 0;
	for(; i <= n-2;)
	{
		int cnt = 1;
		int ele = arr[i];
		while(ele == arr[i+1])
		{
			cnt++; 
			i++;
		}
		if(left-cnt == 0 )
			break;
		cout <<left-cnt << "\n";
		left = left-cnt;
		i++;

	}
	return 0;
}

