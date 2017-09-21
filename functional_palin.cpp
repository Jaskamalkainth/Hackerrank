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

const int mod=1e9+7;

template<class T> inline T gcd(T a,T b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
template<class T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}
template<typename T, typename S> T expo(T b, S e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}
template<typename T> T modinv(T a) { return expo(a, mod-2, mod); }

inline int nextint(){ int x; scanf("%d",&x); return x; }
inline ll nextll(){ ll x; scanf("%lld",&x); return x; }

const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();

const long double PI = (long double)(3.1415926535897932384626433832795);


const int MAXN = 1e5+6;

struct node {
    int next[26];
    int len;
    int sufflink;
    int num, l, r;
};

int len; // length of the string
char s[MAXN]; // orignal string
node tree[MAXN]; 
int num;            // node 1 - root with len -1, node 2 - root with len 0
int suff;           // max suffix palindrome
vector<int> adj[ MAXN ];
vector<pair<pair<int,int> , int > > A;
bool addLetter(int pos) {
    int cur = suff, curlen = 0;
    int let = s[pos] - 'a';

    while (true) {
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])     
            break;  
        cur = tree[cur].sufflink;
    }       
    if (tree[cur].next[let]) {  
        suff = tree[cur].next[let];
        tree[suff].num ++;
        return false;
    }

    num++;
    suff = num;
    tree[num].len = tree[cur].len + 2;
    tree[num].r = pos;
    tree[num].l = pos - tree[num].len + 1; 
    tree[cur].next[let] = num;
    if (tree[num].len == 1) {
        tree[num].sufflink = 2;
        tree[num].num = 1;
        return true;
    }

    tree[num].num ++;
    while (true) {
        cur = tree[cur].sufflink;
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
            tree[num].sufflink = tree[cur].next[let];
            break;
        }       
    }
    return true;
}

void initTree() {
    num = 2; suff = 2;
    tree[1].len = -1; tree[1].sufflink = 1;
    tree[2].len = 0; tree[2].sufflink = 1;
    tree[1].num = tree[2].num = 0; 
}

void dfs( int u ) {
    for( auto it: adj[u] ) {
        dfs(it);
        tree[u].num += tree[it].num;
     }
}
/*
 * Suffix Array
 */
int iSA[MAXN], SA[MAXN];
int cnt[MAXN], next_gen[MAXN], lcp[ MAXN ], LCP[MAXN][22]; //internal
bool bh[MAXN], b2h[MAXN],m_arr[MAXN];

bool smaller_first_char(int a, int b){
  return s[a] < s[b];
}
void SuffixSort(int n) {
    for (int i=0; i<n; ++i){
        SA[i] = i;
    }
  sort(SA, SA + n, smaller_first_char);
  for (int i=0; i<n; ++i){
    bh[i] = i == 0 || s[SA[i]] != s[SA[i-1]];
    b2h[i] = false;
  }
  for (int h = 1; h < n; h <<= 1){
    int buckets = 0;
    for (int i=0, j; i < n; i = j){
      j = i + 1;
      while (j < n && !bh[j]) j++;
      next_gen[i] = j;
      buckets++;
    }
    if (buckets == n) break;
    for (int i = 0; i < n; i = next_gen[i]){
      cnt[i] = 0;
      for (int j = i; j < next_gen[i]; ++j){
        iSA[SA[j]] = i;
      }
    }
    cnt[iSA[n - h]]++;
    b2h[iSA[n - h]] = true;
    for (int i = 0; i < n; i = next_gen[i]){
      for (int j = i; j < next_gen[i]; ++j){
        int s = SA[j] - h;
        if (s >= 0){
          int head = iSA[s];
          iSA[s] = head + cnt[head]++;
          b2h[iSA[s]] = true;
        }
      }
      for (int j = i; j < next_gen[i]; ++j){
        int s = SA[j] - h;
        if (s >= 0 && b2h[iSA[s]]){
          for (int k = iSA[s]+1; !bh[k] && b2h[k]; k++) b2h[k] = false;
        }
      }
    }
    for (int i=0; i<n; ++i){
      SA[iSA[i]] = i;
      bh[i] |= b2h[i];
    }
  }
  for (int i=0; i<n; ++i){
    iSA[SA[i]] = i;
  }
}

void InitLCP(int n) {
  for (int i=0; i<n; ++i) 
    iSA[SA[i]] = i;
  lcp[0] = 0;
  for (int i=0, h=0; i<n; ++i) {
    if (iSA[i] > 0) {
      int j = SA[iSA[i]-1];
      while (i + h < n && j + h < n && s[i+h] == s[j+h]) 
          h++;
      lcp[iSA[i]] = h;
      if (h > 0) 
        h--;
    }
  }
}

void ConstructLCP() {
    InitLCP( len );
    for(int i = 0;i<len;++i)
    LCP[i][0] = lcp[i];
    for(int j = 1;(1<<j)<=len;++j){
        for(int i = 0;i+(1<<j)-1<len;++i){
            if(LCP[i][j-1]<=LCP[i+ ( 1<<(j-1) )][j-1])
                LCP[i][j] = LCP[i][j-1];
            else
                LCP[i][j] = LCP[i+(1<<(j-1))][j-1];
        }
    }
}

int GetLCP(int x, int y) {
    if(x == y) return len-SA[x];
    if(x > y) swap(x,y);
    int log = 0;
    while((1<<log)<=(y-x)) ++log;
    --log;
    return min(LCP[x+1][log],LCP[y-(1<<log)+1][log]);
}
/*
 * SA END/
 *
 */
bool comp(const pair<pii,int> a, const pair<pii,int> b)
{
	int l1 = a.ff.ff;
	int r1 = a.ff.ss;

	int l2 = b.ff.ff;
	int r2 = b.ff.ss;

	int len1 = r1-l1+1;
	int len2 = r2-l2+1;

	if( GetLCP(iSA[l1],iSA[l2]) >=  min(len1,len2) )
	{
		return len1 < len2;  
	}
	else
	{
		return iSA[l1] < iSA[l2];  
	}
}

int P[MAXN], HashF[MAXN], HashR[MAXN];
class RollingHash {
    public:
        RollingHash() {
            prime = 100001;
            mod1 = 1000000007;
            mod2 = 1897266401;
            P[0] = 1;
            for(int i=1; i<MAXN; i++) {
                P[i] = 1LL * P[i-1] * prime % mod1;
            }
        }

        void Construct() {
            HashF[0] = HashR[ len+1 ] = 0;
            for(int i=1; i<=len; i++) {
                HashF[i] = ( 1LL * HashF[i-1] * prime + s[i-1] ) % mod1;
                HashR[len-i+1] = ( 1LL * HashR[len-i+2] * prime + s[ len - i ] ) % mod1; 
            }
        }

        int GetForwardHash( int l, int r ) {
            if( l == 1 ) return HashF[r];
            int hash = HashF[r] - 1LL * HashF[l-1] * P[ r - l + 1 ] % mod1;
            if( hash < 0 ) hash += mod1;
            return hash;
        }
        int GetBackwardHash( int l, int r ) {
            if( r == len ) return HashR[l];
            int hash = HashR[l] - 1LL * HashR[r+1] * P[ r - l + 1 ] % mod1;
            if( hash < 0 ) hash += mod1;
            return hash;
        }
        bool IsPalin( int l, int r ) {
            if( r < l ) return true;
            return (GetForwardHash(l, r) == GetBackwardHash(l, r));
        }

    private:
        int prime, mod1, mod2;
};
//	RollingHash obj;
//	obj.Construct();


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
	int n ,q; cin >> n >> q;
	cin >> s;
	len = strlen(s);
	

	SuffixSort(len);
	ConstructLCP();
	initTree();
    for (int i = 0; i < len; i++) 
        addLetter(i);
    for(int i=2; i<=num; i++) 
        adj[tree[i].sufflink].push_back(i);
    dfs(1);
	for(int i = 3; i <= num ; i++)
	{
		A.pb(mp(mp(tree[i].l,tree[i].r),tree[i].num));  
	}
	sort(all(A),comp);

	RollingHash obj;
	obj.Construct();

	vll prefixcnt;
	vll myhash;
	ll val = 0;
	for(int i = 0; i < A.size(); i++)
	{
		val += A[i].ss;
		prefixcnt.pb(val);
		myhash.pb(obj.GetForwardHash(A[i].ff.ff+1,A[i].ff.ss+1));
	}

	while(q--)
	{
		ll k; cin >> k;  
		if(k > val )
		{
			cout << "-1\n";  
			continue;
		}
		auto it = lower_bound(all(prefixcnt),k);
		cout << myhash[it-prefixcnt.begin()] << "\n";
	}
    return 0;
}

