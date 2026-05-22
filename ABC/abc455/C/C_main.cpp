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
    ll n,k;
    map<ll,ll> num;
    cin>>n>>k;
    rep(i,n){
        ll t;
        cin>>t;
        if(num.count(t)!=0){
            num[t]+=t;
        }else{
            num[t]=t;
        }
    }
    VL v(num.size());
    n=0;
    for(auto& p:num){
        v.at(n)=p.second;
        n++;
    }
    sort(v.begin(),v.end());
    ll a=0;
    rep(i,v.size()-k){
        a+=v.at(i);
    }
    cout<<a<<endl;
}