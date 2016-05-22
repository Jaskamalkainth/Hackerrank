/*
 *    J1K7_7
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <list>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <limits>
using namespace std;
typedef long long          ll;
typedef unsigned long long ull;
typedef long double        ld;
typedef pair<int,int>      pii;
typedef pair<ll,ll>        pll;
typedef vector<int>        vi;
typedef vector<long long>  vll;
#define l(x) 		       (x << 1) + 1
#define r(x) 		       (x << 1) + 2
#define mid(l, r) 	       ((l + r) >> 1)
#define mp                 make_pair
#define pb                 push_back
#define all(a)             a.begin(),a.end()
#define debug(x)	       {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		       memset(x,0,sizeof(x))
#define snuke(c,itr)       for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

template<class T>
inline bool ispow2(T x){return (x!=0 && (x&(x-1))==0);} //0 or 1

template<class T> inline T powmod(T a,T b,T mod) {ll res = 1; while(b){if(b&1) res = (res*a)%mod;a = (a*a)%mod;b >>= 1;}return res;}
template<class T> inline T gcd(T a,T b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
template<class T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}

inline int nextint(){ int x; scanf("%d",&x); return x; }
inline ll nextll(){ ll x; scanf("%lld",&x); return x; }

const int mod=1e9+7;

const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();

const long double PI = (long double)(3.1415926535897932384626433832795);
int main() {
	int len , k; cin >> len >> k;
	string num; cin >> num;
	int cnt = 0;
	for(int i = 0 ; i < len/2; i++)
	{
		if(num[i] != num[len-i-1])
			cnt++;
	}
	if( cnt > k )
	{
		cout << -1 ;
		return 0;
	}
	string ans = num;
	int extra = k - cnt;	

	for(int i = 0; i < len/2; i++)
	{
		if(num[i] != num[len-i-1])
		{
			if(extra >= 1)
			{
				if(num[i]  != '9' && num[len-i-1] != '9')
				{
					ans[i] = '9';
					ans[len-i-1] = '9';
					extra--;
					k--;
				}
				else
				{	
					if( num[i] < num[len-i-1])
					{
						ans[len-i-1] = num[len-i-1];
						ans[i] = num[len-i-1];
					}
					else if( num[i] > num[len-i-1])
					{
						ans[i] = num[i];
						ans[len-i-1] = num[i];
					}
				}
			}
			else
			{
				if( num[i] < num[len-i-1])
				{
					ans[len-i-1] = num[len-i-1];
					ans[i] = num[len-i-1];
				}
				else if( num[i] > num[len-i-1])
				{
					ans[i] = num[i];
					ans[len-i-1] = num[i];
				}
			}
			k--;
		}
		else
		{
				if(extra >= 2)
				{
					if(num[i]  != '9' && num[len-i-1] != '9')
					{
						ans[i] = '9';
						ans[len-i-1] = '9';
						extra -= 2;
						k-=2;
					}
				}
		}
	}
	if( k >= 1 && len&1)
	{
		ans[len/2] = '9';
	}

	cout << ans;

	return 0;
}

