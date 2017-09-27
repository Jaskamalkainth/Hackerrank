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
#define debug_hey(x)       {cerr << "hey " << #x << "\n";}
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

class suffixArray
{
public:
    string s;
    int len;
    vector<int> iSA,SA;
    vector<int> cnt,next_gen,lcp;
    vector<vector<int>> LCP;
    vector<bool> bh,b2h,m_arr;
    suffixArray(string sinp)
    {
        s = sinp;
        len = sinp.size();
        iSA.resize(len); SA.resize(len);
        cnt.resize(len); next_gen.resize(len); lcp.resize(len);
        LCP.resize(len);
        bh.resize(len); b2h.resize(len); m_arr.resize(len);
        for(int i = 0; i < len; i++)
            LCP[i].resize(22);
    }
    bool smaller_first_char(int a, int b){
        return s[a] < s[b];
    }
    void SuffixSort() {
        for (int i=0; i<len; ++i){
            SA[i] = i;
        }
        vector<pair<char,int> > arrr;
        for(int i = 0; i < len; i++)
            arrr.pb({s[SA[i]],SA[i]});
        sort(arrr.begin(),arrr.end());
        for(int i = 0; i < len; i++)
            SA[i] = arrr[i].ss;

        for (int i=0; i<len; ++i){
            bh[i] = i == 0 || s[SA[i]] != s[SA[i-1]];
            b2h[i] = false;
        }
        for (int h = 1; h < len; h <<= 1){
            int buckets = 0;
            for (int i=0, j; i < len; i = j){
                j = i + 1;
                while (j < len && !bh[j]) j++;
                next_gen[i] = j;
                buckets++;
            }
            if (buckets == len) break;
            for (int i = 0; i < len; i = next_gen[i]){
                cnt[i] = 0;
                for (int j = i; j < next_gen[i]; ++j){
                    iSA[SA[j]] = i;
                }
            }
            cnt[iSA[len - h]]++;
            b2h[iSA[len - h]] = true;
            for (int i = 0; i < len; i = next_gen[i]){
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
            for (int i=0; i<len; ++i){
                SA[iSA[i]] = i;
                bh[i] = bh[i] | b2h[i];
            }
        }
        for (int i=0; i<len; ++i){
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
        InitLCP(len);
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
    void PrintSA()
    {
        for(int i = 0; i < len; i++)
            debug4(i,SA[i],iSA[i],lcp[i]);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);

    int t; cin >> t;
    while(t--)
    {
      string s; cin >> s;
      suffixArray sa(s);
      sa.SuffixSort();
      sa.ConstructLCP();
      int origstrID = sa.iSA[0];
      ll ans = 0;
      for(int i = 0; i < s.size(); i++)
      {
          ans += sa.GetLCP(i,origstrID);
      }
      cout << ans << "\n";
    }
    return 0;
}

