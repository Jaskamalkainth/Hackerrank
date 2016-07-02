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
#define left(x) 		   (x << 1)
#define right(x) 		   (x << 1) + 1
#define mid(l, r) 	       ((l + r) >> 1)
#define mp                 make_pair
#define pb                 push_back
#define all(a)             a.begin(),a.end()
#define debug(x)	       {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define debug3(x, y, z)    {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<"\n";}
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

//the-string-monster-july-easy
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--)
	{
		int n; cin >> n;
		vector<string> inp;
		for(int i = 0; i < n; i++)
		{
			string str;		cin >> str;  
			inp.pb(str);
		}
		string desired_str; cin >> desired_str;
		vector<int> desired_cnt(27,0);
		for(auto &ch: desired_str)
			desired_cnt[ch-'a']++;
		//part1
		int sz1 = n/2;
		int sz2 = n-sz1;
		set<vector<int> > s1,s2;
		s1.clear();
		s2.clear();
		for(int i = 0; i < (1<<sz1); i++)
		{
			vector<int> mask_cnt(27,0);
			for(int j = 0; j < sz1; j++)
			{
				if(i&(1<<j))	
				{
					// j th string is included in the mask
					for(auto &ch: inp[j])
					{
						mask_cnt[ch-'a']++;  
					}
				}
			}
			s1.insert(mask_cnt);
		}
		
		for(int i = 0; i < (1<<sz2); i++)
		{
			vector<int> mask_cnt(27,0);
			for(int j = 0; j < sz2; j++)
			{
				if(i&(1<<j))	
				{
					// j th string is included in the mask
					for(auto &ch: inp[j+sz1])
					{
						mask_cnt[ch-'a']++;  
					}
				}
			}
			s2.insert(mask_cnt);
		}
		bool ok = false;
		for(auto &it: s2)
		{
			vector<int> wanted(27,0);
			for(int i = 0; i < 27; i++)
				wanted[i] = desired_cnt[i]-it[i];
			if(s1.find(wanted) != s1.end())
			{
				ok = true;
				break;
			}
		}
		if(ok)
		{
			cout << "YES\n";
		}
		else
		{
			cout << "NO\n";
		}
	}
    return 0;
}

