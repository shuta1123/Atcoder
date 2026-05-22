#line 1 "B_main.cpp"
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
    int h,w;
    cin>>h>>w;
    rep(i,h){
        rep(j,w){
            int t=4;
            if(h==1){
                t--;
            }
            if(w==1){
                t--;
            }else if(j==0){
                t--;
            }
            if(i==0||i==h-1){
                t--;
            }
            
            if(j==w-1){
                t--;
                cout<<t<<endl;
                continue;
            }
            cout<<t<<' ';
        }
    }
}
