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

const int maxn = 1e5+7;
vi G[maxn];
int parent[maxn];
int in[maxn],out[maxn],timer = 1;

struct node
{
	ll sum , sqsum;
	ll lazy;
	node()
	{
		sum = sqsum = 0;  
		lazy = 0;
	}
	void merge(node &l, node &r)
	{
		sum = l.sum + r.sum;
		sqsum = l.sqsum + r.sqsum;
	}
}tree[4*maxn];

inline void update(int id , int left ,int right , int lq ,int rq, int val)
{
	if(tree[id].lazy)
	{
		tree[id].sqsum += 2ll*tree[id].sum*tree[id].lazy+ 1ll*(right-left+1)*tree[id].lazy*tree[id].lazy;
		tree[id].sum += (right-left+1)*tree[id].lazy;
		if(left != right)
		{
			tree[2*id].lazy += tree[id].lazy;
			tree[2*id+1].lazy += tree[id].lazy;
		}
		tree[id].lazy = 0;
	}
	if(left > rq || right < lq)
		return ;
	if(left >= lq && right <= rq)
	{
		tree[id].sqsum += 2ll*tree[id].sum*val+ 1ll*(right-left+1)*val*val;
		tree[id].sum += (right-left+1)*val;
		if(left != right)
		{
			tree[2*id].lazy += val;
			tree[2*id+1].lazy += val;
		}
		return ;
	}
	int mid = mid(left,right);
	update(2*id,left,mid,lq,rq,val);
	update(2*id+1,mid+1,right,lq,rq,val);
	tree[id].merge(tree[2*id],tree[2*id+1]);
}

inline node query(int id, int left ,int right ,int lq ,int rq)
{
	if(tree[id].lazy)
	{
		tree[id].sqsum += 2ll*tree[id].sum*tree[id].lazy+ 1ll*(right-left+1)*tree[id].lazy*tree[id].lazy;
		tree[id].sum += (right-left+1)*tree[id].lazy;
		if(left != right)
		{
			tree[2*id].lazy += tree[id].lazy;
			tree[2*id+1].lazy += tree[id].lazy;
		}
		tree[id].lazy = 0;
	}
	
	if(left > rq || right < lq)
		return node();
	if(left >= lq && right <= rq)
	{
		return tree[id];
	}
	int mid = mid(left,right);
	node tl = query(2*id,left,mid,lq,rq);
	node tr = query(2*id+1,mid+1,right,lq,rq);
	node temp;
	temp.merge(tl,tr);
	return temp;
}

inline void dfs1(int u , int h , int p)
{
	in[u] = timer++;
	update(1,1,maxn,in[u],in[u],h);
	for(auto &v: G[u])
	{
		if(v != p)
		{
			dfs1(v,h+1,u);  
		}
	}
	out[u] = timer-1;
}
vi group[maxn];
int indexof[maxn];
ll ans[maxn];

int n;
inline void dfs2(int u, int p)
{
	for(int v : G[u])
	{
		update(1,1,maxn,in[v],out[v],-2);
		update(1,1,maxn,1,maxn,1);
		if(v!=p)
			dfs2(v,u);
		update(1,1,maxn,in[v],out[v],2);
		update(1,1,maxn,1,maxn,-1);
	}

	for(auto &i: group[u])
	{
		int v = indexof[i];
		ans[i] = query(1,1,maxn,in[v],out[v]).sqsum;
	}
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
	for(int i = 0; i < maxn; i++)
	{
		tree[i] = node();  
	}
	cin >> n;
	for(int i = 1; i <= n-1; i++)
	{
		int x; cin >> x;
		parent[i+1] = x;
		G[i+1].pb(x);
		G[x].pb(i+1);
	}
	dfs1(1,0,-1);

	int q; cin >> q;
	for(int i = 1; i <= q; i++)
	{
		int u, v; cin >> u >> v;
		indexof[i] = v;
		group[u].pb(i);
	}
	dfs2(1,-1);
	
	for(int i = 1; i <= q; i++)
		cout << ans[i] << "\n";

    return 0;
}

