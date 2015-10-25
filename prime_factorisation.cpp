/*
 *
 *    J1K7_7
 * 
 */
//Ad Infinitum 11 - Math Programming Contest
//https://www.hackerrank.com/contests/infinitum11/challenges/prime-factorization-2
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
int  pp[maxN+1];
ll cnt[maxN+1]; // cnt[r] - cnt[l-1]  number of primes in [l,r]
vector <int> prime,sp;

inline void pre_sieve()
{
    sp.resize(maxN);
    // there are 1007  primes < 8000 
    // there are 78499 primes < 1e6+7
    for(ll i = 2; i < maxN; i++ )
        if( pp[i] == 0 )
        {
            sp[i] = i;
            for(ll j = i*i; j < maxN; j += i)
                if ( pp[j] == 0 )
                {
                    sp[j] = i;
                    pp[j] = 1;
                }
        }
    // sp[i] = i  iff i is prime
    for(int i =2; i< maxN; i++)
        if(pp[i] == 0)
            prime.push_back(i);

    for(int i = 2; i < maxN; i++)
        cnt[i] = cnt[i-1] + !(pp[i]);
    //sp[i] : smallest prime dividing i

}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);

    pre_sieve();
    
    int t = nextint();
    ll ans = 0;
    while(t--)
    {
        int n  = nextint();
        ll fans = 0;
        while ( n > 1 )
        {
            fans += sp[n];
            n = n / sp[n];
        }
        ans += fans;
    }
    cout << ans << "\n";
    
    return 0;
}

