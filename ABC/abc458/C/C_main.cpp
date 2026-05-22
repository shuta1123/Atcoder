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

const string YN[2] = {"yes", "no"};

int main() {
    string s;
    cin>>s;
    VL n;
    ll a=0;

    rep(i,s.length()){
        if(s.at(i)=='C'){
            n.push_back(i);
        }
    }
    rep(i,size(n)){
        ll t=n.at(i)+1;
        if(n.at(i)>((s.length()-1)/2)){
            t=s.length()-n.at(i);
        }
        a+=t;
        // cout<<t<<endl;
    }
    cout<<a<<endl;
    
}