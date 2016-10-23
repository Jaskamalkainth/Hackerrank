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
#define left(x)		   (x << 1)
#define right(x) 	   (x << 1) + 1
#define mid(l, r) 	   ((l + r) >> 1)
#define mp                 make_pair
#define pb                 push_back
#define all(a)             a.begin(),a.end()
#define debug(x)	   {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define debug3(x, y, z)    {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<"\n";}
#define debug4(x, y, z, w) {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<", "<<#w << " = " <<w <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		   memset(x,0,sizeof(x))

inline int nextint(){ int x; scanf("%d",&x);   return x; }
inline ll  nextll() { ll  x; scanf("%lld",&x); return x; }

#define gc getchar
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}
// variadics
template<typename T >T min_ ( T a , T b ) { return a > b ? b : a ; }
template < typename T ,  typename... Ts > T min_( T first , Ts... last ){ return  min_(first, min_(last...)); }

// lambda exp auto  square = [](int inp) { return inp * inp; } ;

template<class T, class S> std::ostream& operator<<(std::ostream &os, const std::pair<T, S> &t) {
	os<<"("<<t.first<<", "<<t.second<<")";
	return os;
}
template<typename T> ostream& operator<< (ostream& out, const vector<T>& v) {
    out << "["; size_t last = v.size() - 1; for(size_t i = 0; i < v.size(); ++i) {
    out << v[i]; if (i != last) out << ", "; } out << "]"; return out;
}

ll pwr(ll base, ll p, ll mod){
ll ans = 1; while(p) { if(p&1) ans=(ans*base)%mod; base=(base*base)%mod; p/=2; } return ans;
}
ll gcd(ll a, ll b) {  return b == 0 ? a : gcd(b,a%b); }
ll lcm(ll a, ll b) {  return a*(b/gcd(a,b)); }

const long double PI = (long double)(3.1415926535897932384626433832795);
const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();
const int mod = 1e9+7;
const int oo = 0x3f3f3f3f;
const ll  OO = 0x3f3f3f3f3f3f3f3fll;


const int maxn = 3e5+7;
ll color[maxn];
vi G[maxn];
vector<pii> edge;
int st[maxn],en[maxn],timer = 0;
int d[maxn];
ll flat[maxn];
int cnt_out[maxn],cnt_in[maxn];
ll d1 = 0 ,d2 = 0;



inline void dfs(int u , int p = -1)
{
	st[u] = ++timer;
	if(p+1)
		d[u] = d[p] + 1;
	else
		d[u] = 1;
	flat[timer] = color[u];
	for(auto &v: G[u])
		if(v != p)
			dfs(v,u);
	en[u] = timer;
}

int block = 350;
struct query
{
	int l,r,id;
	query(int _l = 0 , int _r = 0 , int _id = 0)
	{
		l = _l;
		r = _r;
		id = _id;
	}
	bool operator < (const query &b) const
	{
		if(l/block == b.l/block)
			return r < b.r;
		return l < b.l;
	}
}q[maxn];

inline void add(int id)
{
	int val = flat[id];
	cnt_in[val]++;
	if(cnt_in[val] == 1)
		d1++;
	cnt_out[val]--;
	if(cnt_out[val] == 0)
		d2--;
}
inline void remove(int id)
{
	int val = flat[id];
	cnt_in[val]--;
	if(cnt_in[val] == 0)
		d1--;
	cnt_out[val]++;
	if(cnt_out[val] == 1)
		d2++;
}
int curl = 1, curr = 0;
ll ans[maxn];
inline void solve(int n)
{
	for(int i = 1; i <= n-1; i++)
	{
//		debug(i);
		int req_l = q[i].l;
		int req_r = q[i].r;
	//	debug4(curl,curr,req_l,req_r);
//		debug(q[i].id);
		while(curl < req_l)
		{
			remove(curl++);  
		}
		while(curl > req_l)
		{
			add(--curl);  
		}
		while(curr < req_r)
		{
			add(++curr);  
		}
		while(curr > req_r)
		{
			remove(curr--);  
		}
		ans[q[i].id] = d1 * d2;
//		debug2(d1,d2);
	}
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);

	int n; cin >> n;

	ll b[maxn];
	ll mxx = -1;
	for(int i = 1; i <= n; i++)
	{
		cin >> color[i];
		b[i] = color[i];
		mxx = max((ll)color[i],mxx);
	}

	if(mxx >=  maxn)
	{
		sort(b + 1, b + n + 1);
		for (int i = 1; i <= n; ++i)
			color[i] = lower_bound(b + 1, b + n + 1,color[i]) - b; 
	}

	for(int i = 1; i <= n-1; i++)
	{
		int u , v; cin >> u >> v;
		G[u].pb(v); G[v].pb(u);
		edge.pb({u,v});
	}

	dfs(1);
//	for(int i = 1; i <= n; i++)
//		debug4(i,st[i],en[i],flat[i]);

	for(int i = 1; i <= n-1; i++)
	{
		int u , v;  
		u = edge[i-1].ff;
		v = edge[i-1].ss;
		if(d[u] > d[v])
			swap(u,v);
		q[i].l = st[v];
		q[i].r = en[v];
		q[i].id = i;
	}
	sort(q+1,q+n);
	for(int i = 1; i <= n; i++)
	{
		cnt_out[flat[i]]++;
		if(cnt_out[flat[i]] == 1)
			d2++;
	}
//	debug2(d1,d2);
	solve(n);
	ll fans = 0;
	for(int i = 1; i <= n-1; i++)
		fans += ans[i];
		//cout << ans[i] << " ";
	cout << fans << "\n";

    return 0;
}

