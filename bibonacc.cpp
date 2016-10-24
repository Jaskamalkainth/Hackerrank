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
#include <cstring>
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
#define eb 				   emplace_back
#define all(a)             a.begin(),a.end()
#define debug(x)	   {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define debug3(x, y, z)    {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<"\n";}
#define debug4(x, y, z, w) {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<", "<<#w << " = " <<w <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		   memset(x,0,sizeof(x))
#define builtinpopcount    __builtin_popcount(x)

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
const int oo = 0x3f3f3f3f;
const ll  OO = 0x3f3f3f3f3f3f3f3fll;

const ld TIME_LIMIT = 5.000001;
inline int break_TIME_LIMIT() { if(( 1.0 * clock() / CLOCKS_PER_SEC ) > TIME_LIMIT) return 1; else return 0; }
/* if(break_TIME_LIMIT())
			break;
*/

const int maxn = 3e5+7;

/*
 * matrix lib
 */
int mod;
inline int add(int a , int b){
	int res = a + b;
	if(res >= mod)
		return res - mod;
	else
		return res;
}
inline int mult(int a , int b)
{
	long long res = a;
	res *= b;
	if(res >= mod)
		return res % mod;
	else
		return res;
}
const int SZ = 3;
struct matrix{
	int arr[SZ][SZ];
	inline void reset()
	{
		memset(arr , 0 , sizeof(arr));
	}
	inline void make_iden()
	{
		reset();
		for(int i = 0 ; i < SZ ; ++i)
			arr[i][i] = 1;
	}
	matrix operator + (const matrix &o) const 
	{
		matrix res;
		for(int i = 0 ; i < SZ ; ++i)
			for(int j = 0 ; j < SZ ; ++j)
				res.arr[i][j] = add(arr[i][j],o.arr[i][j]);
		return res;
	}
	matrix operator * (const matrix &o) const 
	{
		matrix res;
		for(int i = 0 ; i < SZ ; ++i)
			for(int j = 0 ; j < SZ ; ++j)
			{
				res.arr[i][j] = 0;
				for(int k = 0 ; k < SZ ; ++k)
					res.arr[i][j] = add(res.arr[i][j] , mult(arr[i][k] , o.arr[k][j]));
			}
		return res;
	}
	void print()
	{
		for(int i = 0 ; i < SZ ; ++i)
		{
			for(int j = 0 ; j < SZ ; ++j)
				cout << arr[i][j] << " ";
			cout << "\n";
		}
	}
};
matrix power(matrix a , int b)
{
	matrix res;
	res.make_iden();
	while(b)
	{
		if(b & 1)
			res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}
ll a[maxn];
matrix m;

inline matrix T(int id)
{
	return power(m,id);  
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);


	int n; cin >> n >> mod;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	m.arr[0][0] = 1;
	m.arr[0][1] = 1;
	m.arr[0][2] = 1;

	m.arr[1][0] = 1;
	m.arr[1][1] = 0;
	m.arr[1][2] = 0;

	m.arr[2][0] = 0;
	m.arr[2][1] = 0;
	m.arr[2][2] = 1;

	
	matrix pans = T(a[1]-1);
	matrix ans = pans;
	matrix tans;
	matrix iden; 
	iden.make_iden();
	for(int i = 2; i <= n; i++)
	{
		tans = (pans * T(1) + iden) * T(a[i]-1);
		pans = tans;
		ans = ans + tans;
	}
	cout << (ans.arr[0][0] + ans.arr[0][1] + ans.arr[0][2]) % mod << "\n";

    return 0;
}

