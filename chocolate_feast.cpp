#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        int c;
        int m;
        cin >> n >> c >> m;

		int chock = n/c;
		int ans = n/c;
		int wrapper = n/c;
		while(wrapper >= m )
		{
			chock = wrapper / m;
			ans += chock;
			int rem = wrapper%m;
			wrapper = chock+rem;
		}
		cout << ans << "\n";
    }
    return 0;
}

