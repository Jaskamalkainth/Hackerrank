/*
 *    J1K7_7
 *
 *    You can use my contents on a Creative Commons - Attribution 4.0 International - CC BY 4.0 License.  XD 
 *    - JASKAMAL KAINTH
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
#include <cassert>
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
#define debug4(x, y, z, w) {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<", "<<#w << " = " <<w <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		       memset(x,0,sizeof(x))

const int maxn = 1e5+7;
int node[maxn];
map<int,int> compress;
int rev_map[maxn];
vector<pair<int,pii> > edge_list , query_list;
vector<pii> edges[maxn];
int ans[maxn],lo[maxn],hi[maxn];
int rankN[maxn];
int parentN[maxn];

set<int> cities[maxn];
inline void make_set(int n)
{
	for(int i = 1; i <= n; i++)
		parentN[i] = rankN[i] = i;  
}
inline int find_set(int u)
{
	if(parentN[u] != u )
		parentN[u] = find_set(parentN[u]);
	return parentN[u];
}
inline void union_set(int u,int v)
{
	int pu = find_set(u);
	int pv = find_set(v);
	if(pu == pv)
		return ;
	if(rankN[pu] > rankN[pv])
	{
		parentN[pv] = pu;  
		for(auto &c: cities[pv])
			cities[pu].insert(c);
		cities[pv].clear();
	}
	else
	{
		parentN[pu] = pv;
		for(auto &c: cities[pu])
			cities[pv].insert(c);
		cities[pu].clear();
		if(rankN[pu] == rankN[pv])
			rankN[pv]++;
	}
}

vector<int> tocheck[maxn];
int n , m , q , cc;

inline void parallel_binary_search()
{
	for(int i = 1; i <= q; i++)
	{
		lo[i] = 1;
		hi[i] = cc;
		ans[i] = cc+1;
		tocheck[mid(lo[i],hi[i])].pb(i);  
	}


	bool ok = true;
	while(ok)
	{
		ok = false;
		// clear
		make_set(n);
		for(int i = 1; i <= n; i++)
		{
			cities[i].clear();
			cities[i].insert(node[i]);
		}

		// loop from 1->maxbinsearch value
		for(int i = 1; i <= cc; i++)
		{
			// update 
			for(auto &e: edges[i])
			{
				union_set(e.ff,e.ss);
			}
			while(!tocheck[i].empty())
			{
				int idx = tocheck[i].back();
				tocheck[i].pop_back();
				int u = query_list[idx].ss.ff;
				int v = query_list[idx].ss.ss;
				int k = query_list[idx].ff;

				int pu = find_set(u);
				int pv = find_set(v);
				if(pu == pv && cities[pu].size() >= k)
				{
					hi[idx] = i-1;  
					ans[idx] = min(ans[idx], i);
				}
				else
				{
					lo[idx] = i+1;  
				}
				if(lo[idx] <= hi[idx])
				{
					tocheck[mid(lo[idx],hi[idx])].pb(idx);
					ok = true;
				}
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin  >> n >> m >> q;
	for(int i = 1; i <= n; i++)
	{
		cin >> node[i];
	}
	for(int i = 1; i <= m; i++)
	{
		int u , v , c; cin >> u >> v >> c;
		edge_list.pb({c,{u,v}});
		compress[c] =  1;
	}
	cc = 0;
	for(auto &i: compress)
	{
		i.ss = ++cc;  
		rev_map[cc] = i.ff;
	}
	for(auto &e: edge_list)
	{
		edges[compress[e.ff]].pb({e.ss.ff,e.ss.ss}); 
	}
	query_list.pb({0,{0,0}});
	for(int i = 1; i <= q; i++)
	{
		int u , v , k; cin >> u >> v >> k;  
		query_list.pb({k,{u,v}});
	}
	parallel_binary_search();
	rev_map[cc+1] = -1;
	for(int i = 1; i <= q; i++)
	{
		cout << rev_map[ans[i]] << "\n";  
	}
    return 0;
}

