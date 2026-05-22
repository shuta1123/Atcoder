#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using VL  = vector<char>;
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

int check(ll h1,ll h2, ll w1,ll w2,VVL hu){

    repi(i,h1,h2+1){
        repi(j,w1,w2+1){
            if(hu.at(i).at(j)!=hu.at(h1+h2-i).at(w1+w2-j)){
                
                return 0;
            }
        }
    }
    // cout<<"h"<<h1<<','<<h2<<"w"<<w1<<","<<w2<<endl;
    return 1;
}

int main() {
    int h,w;
    ll a=0;
    cin>>h>>w;
    VVL hu(h,VL(w));
    rep(i,h){
        rep(j,w){
            char t;
            cin>>t;
            hu.at(i).at(j)=t;
        }
    }
    a=0;
    rep(h1,h){
        repi(h2,h1,h){
            rep(w1,w){
                repi(w2,w1,w){
                    
                    a+=check(h1,h2,w1,w2,hu);
                    
                }   
            }
        }
    }
    cout<<a<<endl;
}