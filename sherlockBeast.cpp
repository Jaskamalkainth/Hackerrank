#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
	// c3 + c5 = n
	// c3%5 + c5%5 = n%5
	// c3%3 + c5%3 = n%3
	int t; cin >> t;
	while(t--)
	{
		int n; cin >> n;
		if( n <= 2) 
		{
			cout <<"-1"<<"\n";
			continue;
		}
		int cnt = -1;
		for(int i = n; i>=0; i--)
		{
			if((i%3 == 0) && ( (n-i)%5==0))
			{
				cnt = i;
				break;
			}
		}
		if(cnt==-1)
		{
			cout <<"-1\n";
			continue;
		}
		for(int i = 0; i < cnt; i++)
			cout <<5;
		int x = n-cnt;
		while(x--)
			cout <<3;
		cout << "\n";
		continue;
	}
	return 0;
}

