/*
 *
 *    J1K7_7
 * 
 */
// Euler Totient Function , Triangular numbers , sieve , prefix sums for O(1) query
//Ad Infinitum 10 - Math Programming Contest
//https://www.hackerrank.com/contests/infinitum10/challenges/a-weird-function
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
#include <iomanip>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
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
#define pr(n)              printf("%d",n)
#define s(n)               scanf("%d",&n)
#define debug(x)	       {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		       memset(x,0,sizeof(x))
#define snuke(c,itr)       for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
const int mod=1e9+7;

const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();

const long double PI = (long double)(3.1415926535897932384626433832795);

inline bool ispow2(int x){return (x!=0 && (x&(x-1))==0);} //0 or 1

int msb(unsigned x){ union { double a; int b[2]; }; a = x; return (b[1] >> 20) - 1023; }

template<class T>
inline void cinarr(T a, int n){ for (int i=0;i<n;++i) cin >> a[i];}

inline ll powmod(ll a,ll b) {ll res = 1; while(b){if(b&1) res = (res*a)%mod;a = (a*a)%mod;b >>= 1;}return res;}

inline ll gcd(ll a,ll b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
inline ll lcm(ll a,ll b){return a/gcd(a,b)*b;}

inline int nextint(){ int x; scanf("%d",&x); return x; }
inline ll nextll(){ ll x; scanf("%lld",&x); return x; }

const int maxN = 2e6+7;

vll etf , P;
inline void ETF()
{
    etf.resize(maxN+1);
    P.resize(maxN+1,0);
    for(int i = 1;i <= maxN;i++)
        etf[i] = i;
    for(int i = 2;i <= maxN;i++)
    {
        if(!P[i])
        {
            etf[i]-=(etf[i]/i);
            int j = 2 * i;
            while( j <= maxN)
            {
                etf[j] -= (etf[j]/i);
                P[j] = 1;
                j += i;
            }
        }
    }
}


// other array which stores the number of numbers relative prime to the ith triangular number
// calculated using the etf array
// etf( m * n ) = etf(m) * etf(n) where (m,n) = 1 
// triangular number is of the form i * (i+1) / 2


vll wf(maxN+1);
inline void weird_function()
{
    for(int i = 1; i < maxN; i++)
    {
        if ( i & 1)
        {
            wf[i] = etf[i] * 1ll * etf[(i+1)/2];
        }
        else
        {
            wf[i] = etf[i/2] * 1ll * etf[i+1];
        }
    }
    // prefix sum to query in constant time coz O(1) is _/\_  ;) :D  
    for(int i = 1; i < maxN; i++)
    {
        wf[i] = wf[i-1] + wf[i];
    }
}


inline ll query(ll L , ll R)
{
    // find the l such that L >= (l * (l+1) / 2)
    // find the r such that R <= (l * (l+1) / 2)

    // l^2 + l <= 2*L
    // l^2 + l - 2*L <= 0 
    // l = ( -1 + sqrt(1 + 8*L) ) / 2
    // similarly
    // r = ( -1 + sqrt(1 + 8*R) ) / 2

    ll l = ( -1ll + sqrt(1 + 8*1ll*L) ) / 2;
    ll r = ( -1ll + sqrt(1 + 8*1ll*R) ) / 2;

    if( l* 1ll * (l+1) == 2 * L * 1ll )
        return wf[r] - wf[l-1];
    else
        return wf[r] - wf[l];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);

    ETF();
    weird_function();   
   
    int t = nextint();
    while ( t--)
    {
        ll l = nextll();
        ll r = nextll();
        cout << query ( l , r ) << "\n";
        
    }
    return 0;
}

