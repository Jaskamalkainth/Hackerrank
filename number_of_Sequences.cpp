#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<algorithm>
using namespace std;


#define ll long long

const int maxn = 1e5+7;
int prime[maxn] , single_prime_factor[maxn];
int arr[maxn];
const int mod = 1e9+7;

int main()
{
	prime[1] = 1;
	for(int i = 2; i < maxn; i++)
	{
		if(prime[i]) continue;
		for(int j = 2*i; j < maxn; j += i)
		{
			prime[j] = 1;
		}
		for(long long j = 1ll*i*i; j < maxn; j *= i)
		{
			single_prime_factor[j] = i;  
		}
	}


	int n; cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> arr[i];


	for(int i = 2; i <= n; i++)
	{
		for(int j = 2*i; j <= n; j += i)
		{
			if(arr[j] == -1) continue;
			int temp_arr = arr[j]%i;
			//fix i
			if(arr[i] == -1)
				arr[i] = temp_arr;
			else if(arr[i] != temp_arr)
			{
				cout << "0\n";
				return 0;
			}
		}
	}


	long long ans = 1ll;
	for(int i = 2;i <= n ; i++)
	{
		if(arr[i] != -1) continue;
		if(prime[i] == 0)
			ans = (ans*1ll*i) % mod;
		else if(single_prime_factor[i] != 0)
		{
			ans = (ans * single_prime_factor[i]) %mod;  
		}
	}
	cout << ans;
	return 0;
}
