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

const int maxN = 1e4+6;
vector<pii >G[maxN];
vector<pii> edge;
vector<int> par(maxN,-1);
vector<int> dist(maxN,1e7);
int  n  , m;

int ans = 0;
void prim( int source )
{
	set<pair<int,int> > s;
	for(int i = 1; i <= n; i++)
	{
		if(i == source)
			s.insert(pii(0,i));
		else
			s.insert(pii(dist[i],i));
	}
	dist[source] = 0;
	while(!s.empty())
	{
		pii top = *s.begin();
		s.erase(s.begin());
		int u = top.ss;
		int d = top.ff;
		ans += d;
		if( u != source)
			edge.pb(pii(par[u],u));
		for(auto &x: G[u])
		{
			int v = x.ff;
			int cost = x.ss;
			if(s.find(pii(dist[v],v)) != s.end())
			{
				if(dist[v] > cost)
				{
					s.erase(s.find(pii(dist[v],v)));
					dist[v] = cost;
					s.insert(pii(dist[v],v));
					par[v] = u;
				}
			}
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> m;
	while(m--)
	{
		int u , v ,wt; cin >> u >> v >> wt;
		int f = 0;
		for(auto &x: G[u])
			if(x.ff == v)
			{
				x.ss = min( x.ss , wt);
				f = 1;
			}
		for(auto &x: G[v])
			if(x.ff == u)
				x.ss = min( x.ss , wt);
		if(!f)
		{
			G[u].pb(pii(v,wt));
			G[v].pb(pii(u,wt));
		}
	}


		int s; cin >> s;
		prim(s);
		/*
		debug(edge.size());
		for(auto e: edge)
			printf("(%d -> %d ) ",e.ff,e.ss);
			*/

		cout << ans ;
    return 0;
}

