#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using VL  = vector<ll>;
using VVL = vector<VL>;

#define rep(i, n)      for (ll i = 0; i < (ll)(n); i++)
#define rep1(i, n)     for (ll i = 1; i <= (ll)(n); i++)
#define repi(i, a, b)  for (ll i = (ll)(a); i < (ll)(b); i++)
#define repr(i, n)     for (ll i = (ll)(n) - 1; i >= 0; i--)
#define all(x)         (x).begin(), (x).end()
#define rall(x)        (x).rbegin(), (x).rend()
#define sz(x)          ((ll)(x).size())

#ifdef LOCAL
#define dbg(x)   cerr << #x << " = " << (x) << "\n"
#define dbgv(v)  { cerr << #v << " = ["; for (auto& _x : (v)) cerr << _x << ", "; cerr << "]\n"; }
#define dbgvv(v) { cerr << #v << ":\n"; for (auto& _row : (v)) { for (auto& _x : _row) cerr << _x << " "; cerr << "\n"; } }
#else
#define dbg(x)
#define dbgv(v)
#define dbgvv(v)
#endif

const string YN[2] = {"Yes", "No"};

int main() {
    ll n,q;
    map<ll,list<ll>> m;
    cin>>n>>q;
    VL v(n);
    rep(i,n){
        m[0].push_back(i);
    }
    ll t1,t2;
    rep(i,q){
        cin>>t1>>t2;
        if(t1==1){
            erase(m[v.at(t2-1)],t2-1);
            m[v.at(t2-1)+1].push_back(t2-1);
            v.at(t2-1)++;
            if(m[0].size()==0){
                for( auto [key,value] :m){
                    m[key-1]=value;
                    m.erase(key);
                }
            }
        }else{
            ll co=0;
            for( auto [key,value] :m){
                if(t2<=key){
                    co+=value.size();
                }
            }
            cout<<co<<endl;
        }
        // cout<<'i'<<i<<endl;
    }
}