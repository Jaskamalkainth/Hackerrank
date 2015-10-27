/*
 *
 *    J1K7_7
 * 
 */
//Ad Infinitum 13 - Math Programming Contest
//https://www.hackerrank.com/contests/infinitum13/challenges/pairwise-gcd
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

const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();

const int mod=1234567891;


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


const int maxN = 1e5+7;
int n , m;
ll a[maxN];
ll b[maxN];


// Polynomial evaluation


ll poly_eval ( int deg , ll x )
{
    ll ans = 0ll;
    for(int i = deg ; i >= 0; i--)
    {
        ans = (x *ans + b[i] + mod ) % mod;
    }
    return ans;
}

ll p[maxN];



ll fdiv[maxN];
vector<ll> getDivisors(ll n)
{
    set<ll> fcd;
    for(ll i = 1; i * i <= n ; i++)
    {
        if ( n % i == 0 )
        {
            fcd.insert(i);
            fcd.insert(n/i);
        }
    }
    vector<ll> cd;
    for(auto x: fcd)
        cd.push_back(x);

    return cd;
}


ll  mobius[maxN];

void mob()
{
    mobius[1] = 1;
    for (int i = 2; i < maxN; i++)
    {
        for (int j = 1; j * j <= i; ++j)
        {
            if (i % j != 0)
                continue;
            mobius[i] -= mobius[j];
            if (i != j * j && j != 1)
                mobius[i] -= mobius[i / j];
        }
    }
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);

    n = nextint();
    m = nextint();

    for(int i = 0; i < n ; i++)
    {
        a[i] = nextll();
    }
    for(int i = 0; i <= m ; i++)
    {
        b[i] = nextll();
    }

    // O(m*maxN)
    // pre-calculating the values of polynomial from 0 to maxN.
    for (int i = 0 ; i < maxN; i++)
    {
        p[i] = poly_eval(m,i);
    }

    // D(x): number of pairs such that x is Common Divisor
    // G(x): number of pairs such that x is GCD 


    vll t_div;

    // O(n * sqrt(n))
    for( int i = 0; i < n; i++)
    {
        t_div.clear();
        t_div = getDivisors(a[i]);

        for ( auto x : t_div )
        {
            fdiv[x]++;
        }
    }
     


    mob();


    ll ans = 0ll;
    //
    // O(maxN*sqrt(maxN))
    for(ll i = 0; i < maxN; i++)
    {
        if ( fdiv[i] < 2 )  continue;

        ll pairs = ( fdiv[i] * 1ll * ( fdiv[i] - 1) / 2 ) % mod ;
        
        ll prod = 0ll;
        for ( ll j = 1; j * j <= i; j++ )
        {
            if ( i % j == 0 )
            {
                prod =( prod + mod +  ( p[j] * mobius[i/j] )  ) % mod;

                if ( j * j != i )
                {
                    prod =( prod + mod +  ( p[i/j] * mobius[j] )  ) % mod;
                }
            }
        }

        ans = (ans + mod + prod * pairs ) % mod;
    }

    cout << ans << "\n";

    return 0;
}

