#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
#define ll long long


const int maxN = 1e6+7;
ll cnt_prime_powers[maxN];
inline void pre()
{
	for(int i = 2; i < maxN; i++)
	{
		if(cnt_prime_powers[i]) continue;
		for(int j = i; j < maxN; j += i)
		{
			int num = j;
			while( num%i == 0) {
				cnt_prime_powers[j]++; 
				num /= i;
			}
		}
	}
}
// cnt_prime_powers[i] : sum of prime powers in the factorisation of i

int a[17];

int main()
{
	pre();
	for(int i = 2;i < maxN;i++)
		cnt_prime_powers[i] += cnt_prime_powers[i-1];
	int n; cin >> n;
	for(int i = 0; i < n; i++)
		cin >> a[i];
	ll ans = 0;
	for(int mask = 1; mask < (1<<n); mask++)
	{
		vector<ll> sub;
		for(int i = 0; i < n; i++)
			if(mask & (1<<i))
				sub.push_back(cnt_prime_powers[a[i]]);
		ll sum = 0;
		for(auto &x: sub)
			sum += x;
		if(!(sum&1))
			ans += sum;
	}
	cout << ans << "\n";
	return 0;
}
